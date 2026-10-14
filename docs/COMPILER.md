# Compiler and build profile

## Summary

| Item | Value | Status |
|---|---|---|
| Compiler, allocator | gcc 2.5.7 (decompals/old-gcc `gcc-2.5.7-psx`) | `LIBC_Calloc` distinguishes it from 2.6.x–2.8.1 |
| Compiler, current engine/SDK units | gcc 2.6.3 (`GCC_VERSION` per file) | Per-unit profiles; full EXE SHA-1 verified |
| Optimisation | `-O2` | Matches |
| Small data | `-G8`, gp = `0x800563FC` (start of `.sdata`) | 638 gp-relative accesses in retail |
| Assembler | maspsx `--aspsx-version=2.34 --expand-div` | Reproduces the `mflo` / `nop` hazard padding |
| PsyQ libraries | libgpu `sys.c 1.120` (1996-05-01), `intr.c 1.73`, libcd `bios.c 1.71` | ≈ PsyQ 3.5 |

## Evidence

All of these were checked with `tools/scripts/probe_match.py`, which compiles a C
file and compares every function in it against the split retail assembly. Fields
that relocations fill in are ignored.

* `LIBC_Free` (5 instructions) matches on every compiler version.
* `LIBC_Calloc` matches only on **2.5.7**. Retail emits
  `mult; addiu sp; sw s1; mflo s1; nop; sw ra; sw s0`, which means the frame
  setup is scheduled together with the body and `$ra` is not saved first.
  Every 2.6.0, 2.6.3, 2.7.2 and 2.8.1 build saves registers in a different
  order. I tried each of those versions with `-O1`, `-O2` and `-O3`, with and
  without `-g`, and with and without `-fno-schedule-insns{,2}`; none matched.
* `LIBC_Realloc`: the 2.5.7 candidate is now promoted in `libc/malloc.c`.
  Its 36 instructions have Levenshtein distance zero, and the full EXE SHA-1
  matches retail. A single-iteration `do { … } while (0)` scope retains the
  retail register lifetimes; replacing it with a plain scope gives distance 14.
  The original zero-size path frees the input without defining the result.

The allocator evidence does not establish one compiler for the whole game.
The first 20 promoted engine functions match with gcc 2.6.3, including
`CORE_Main`, whose default 2.5.7 build has a different epilogue. These source
files carry `/* GCC_VERSION: 2.6.3 */`; the allocator keeps the default 2.5.7
profile. Several small leaf functions match both versions, so their bytes
alone do not distinguish the original compiler. SDK/library units may require
other per-file profiles as decompilation progresses.

`ns/texture_allocate.c` uses gcc 2.6.3 with `-O2 -fno-cse-follow-jumps`.
The stock compiler option preserves the second global zone-pointer load after
the shared return path; following that jump removes two retail instructions.
The file's 94 instructions have Levenshtein distance zero with this profile
and distance five without it. The complete EXE SHA-1 matches retail. The wrapper
recognises this option in the per-file `CC1_FLAGS` comment, and an integration
test verifies both results.

## Running the compilers on macOS

| Version | How it runs |
|---|---|
| 2.5.7 | old-gcc's Linux i386 build, run in `i386/alpine` under Docker (OrbStack). About 0.35 s per invocation. |
| 2.6.3 | Native arm64, built by `tools/toolchain/build_oldgcc_macos.sh 2.6.3`. Also provides the preprocessor. |
| 2.7.2, 2.8.1 | old-gcc's macOS releases |

To check the native 2.6.3 build, I compiled all 364 rage-pc translation units
with it and with old-gcc's Linux 2.6.3 build. 363 produced byte-identical
assembly. The remaining unit fails to compile on both builds and differs only in
error-recovery output. The fix that made the native build work: `mips.h` defines
`__PTR_TO_INT(P)` as `((int)(P))`, which truncates obstack pointers on LP64
hosts.

2.5.7 cannot be built natively without more porting work. Its diagnostics use
K&R `<varargs.h>` (`va_alist`), which the arm64 Darwin ABI cannot support until
every one of them is converted to stdarg.

## Executable layout (SCUS_949.00)

```
header   file 0x000000
.rodata  0x80010000  file 0x000800   (jump table at 0x80011760..0x8001177C)
.text    0x8001177C  file 0x001F7C
.data    0x800514DC  file 0x041CDC
.sdata   0x800563FC  file 0x046BFC   (= gp)
.sbss    0x80056598                  crt0 zeroes 0x80056598..0x80061A78
.bss     .. 0x80061A78
file padded with zeros to 0x80056800 (objcopy --pad-to 0x47000)
entry    0x8003E018 (PsyQ __SN_ENTRY_POINT: clears BSS, sets sp/gp, calls
         0x80011A18 (heap init) then 0x80011D88 (main))
```

The executable contains all native code. No code overlays have been found.
Gameplay logic is mostly GOOL bytecode inside the NSF files.

## gcc 2.6.3 code-generation notes from `NSInit` (`ns/init.c`)

These mechanisms decided the remaining instructions of the 562-instruction
`func_80015B58`. All of them can be inspected in the stock compiler's
dumps (`cc1 -dj -ds -dL -dl -dg -dS`).

* **Global register allocation priority** is
  `floor_log2(refs) * refs / live_length`, where references inside a loop
  are weighted by the loop depth. A short-lived counter can therefore
  outrank a function-wide pointer. If two variables are swapped between
  `s` registers, compare their priorities in the `.greg` and `.lreg` dumps.
* **The pre-test that `jump` duplicates** for a `for` loop is folded by
  `cse` and `combine`. `combine` re-emits the initializer of whichever
  zero-valued register `cse` substituted, right before the branch. `cse`
  keeps the equivalent register that lives longest as the canonical one.
  That moved initializer shortens the variable's life and changes both
  allocation and scheduling.
* **`sched`** schedules backwards. Before reload it raises insns that "birth"
  a register set exactly once. Ties are broken by dependence class and then
  by insn order.
* **`cse` paths** continue across a conditional jump only when the target
  label is used once and is either preceded by a barrier or the jump skips
  a label-free block. A join label ends the path. Index values such as
  `i * 44` are shared along a path, and a shared index register is only
  "replaceable" for `loop.c` if it is set on every iteration. Where an
  array index is computed decides whether a store becomes its own address
  giv or uses the common one.
* **`loop.c` combines givs** in reverse insn order. The last address giv
  with a given offset collects identical ones into one reduced register.
  A giv with a symbolic offset is absorbed by the plain index giv instead.
* **Cross-jumping** runs only after reload. It merges a jump's tail with the
  code before its target label after one matching insn, or with another
  jump's tail after two.
* **Tree `fold`** reassociates `a | (b | C)`. Assigning the inner value to a
  variable keeps the source grouping.
* **Aliasing of globals.** `cse` and `sched` assume that a store to a struct
  field at a varying address cannot touch a scalar at a fixed address. If
  retail reloads a global after such a store, the global is itself a struct
  member. For example, 0x80057914..0x80057920 is one struct (`zone.h`
  `LevelPosition`). A load that retail places before such stores was written
  before them in the source.
* **`abs`.** The builtin gives `bgez; negu`. A `(x) < 0 ? -(x) : (x)` macro
  gives the same for a plain load, but for `a - b` the fold turns `-(a - b)`
  into `b - a`, so retail shows a reversed `subu`.
* **Flags from `&&` chains.** `x = a && b && c` stores the last test with
  `sltu`/`sltiu`; `x = a || b || c` uses branches for all three tests. To
  get the inverse of an `&&` chain with the store-flag at the end (default
  1, then `sltu`), write it as `if (a && b && c) x = 0; else x = 1;`.
* **Loop entry rotation** (`stmt.c` `expand_end_loop`). If a loop does not
  end with a conditional jump, gcc moves a conditional exit found at the top
  of the loop (within 30 insns, before any call or label) to the bottom. The
  top test is then duplicated in front of the loop. A block-scoped
  declaration at the start of the loop body emits `NOTE_INSN_BLOCK_BEG` and
  stops this. So when retail keeps `if (x) break;` as the first insn of the
  loop, the body declares a local.
* **`loop.c` moves exit blocks out of loops** (`find_and_verify_loops`). A
  block reached by a conditional jump that ends in a jump out of the loop
  (`return`, `break` to an outer label) is moved behind the first BARRIER at
  the target's loop depth. The search goes backward from the jump target,
  then forward. For `return` the target is the function's return label, so
  such blocks end up near the end of the function. If retail has the block
  right after the loop instead, the source jumped to a label there (e.g.
  `goto` to code after the loop's own `return`).
* **`cse` skip-blocks and memory.** Skipping a block that stores to a fixed
  address keeps all other fixed-address values. A reload in retail after
  such a block means the two loads are different MEM rtxes. An `__asm__`
  alias declares its symbol as `"*NAME"`, a different SYMBOL_REF from plain
  `NAME`. So a struct view and a scalar extern of the same address neither
  share loads nor alias each other.
* **Loop invariants and `insn_count`.** In `move_movables`, each register
  that was already moved by an inner loop doubles `insn_count` for the
  following candidates ("halved since already moved"). The order of
  invariants inside the inner loop therefore decides which of them leave the
  outer loop. A constant that does not get moved and ends up without a hard
  register is rematerialized by reload into a `t` register at its use.
* **local-alloc with exactly 3 quantities in a block** does not sort them
  by priority. `block_alloc` hand-sorts 2 or 3 qtys with
  `qty_compare (0, 1)` / `(1, 2)`, which compares qty *numbers* while
  swapping *positions*. With 3 qtys the result depends on that bug (for 2,
  or 4 and more via qsort, it is correct). If `v0`/`v1` come out swapped in
  a short block, change the number of local qtys in it. For example, an
  explicit `if (x < 0) x = -x;` on a call result instead of `abs()` adds one.
  `find_free_reg` can be traced with lldb: cc1 has symbols, and the
  local-alloc arrays (`qty_first_reg`, `qty_n_refs`, ...) are statics next
  to `_qty_birth`.
* **A field read after a pointer variable is reassigned** reuses the address
  of the old value only if the read comes earlier in the RTL. Read it into a
  local before the assignment (`goal = p->link[i].goal; p = next;`) and the
  old base register is reused. A temporary for the new value instead costs
  a `move`.
* **Delay slots of unconditional jumps** are filled from the target thread,
  with the jump redirected past the stolen insn. If a slot stays `nop`,
  check the case order inside small `switch` statements. The order of the
  case bodies decides which jump sees which target first.
* **A store after an if/else** whose value comes from a variable set in both
  arms shows up in retail in the `j` delay slot of the first arm and again
  before the join label. `reorg` copies the join's first insn into the slot.

`tools/scripts/permute_import.sh` (also used by `make permute`) copies the
source file's compiler profile into the permuter's `compile.sh`.
`import.py` preprocesses the source and loses those comments, so without
the script every permutation of a gcc 2.6.3 unit was built with 2.5.7.

`probe_match.py` masks relocated fields, including `j` targets. A `j` into
the wrong insn of the same function (for example before or after a spill
reload) still shows MATCH, and only `make build check` catches it. When a
`goto` or a shared tail is involved, run the full check before calling a
function matched.

* **`a - (b + C)` is reassociated by `fold`** into `(a - C) - b`. Retail
  code that computes `b + 1` and then subtracts kept `b + 1` out of the
  tree, for example through an assignment `(next = b + 1)`.
* **Two separate `x &= ~A; x &= ~B;`** statements give one load, two `and`s
  and one store (cse merges the memory ops). `x & ~A & ~B` folds into a
  single mask.
* **Block-scoped locals share stack slots.** Different scopes reuse the
  same frame offsets, so a retail "spill" that lands on another variable's
  slot (e.g. comparison flags stored at the offset of a `vec` used in
  another branch) means a block-local array or struct.
* **Delay slots and 32-bit constants.** A `lui`/`ori` pair split across two
  branch delay slots means the constant was the first statement of the
  block both branches lead into. `reorg` first moves the `ori` (the insn
  just before the second branch) into that branch's slot, then copies the
  `lui` from the target thread into the earlier branch.
* **No `return` at the end of a non-void function** is visible in retail as
  an exit path that does not set `v0` (it happens to hold 0).
