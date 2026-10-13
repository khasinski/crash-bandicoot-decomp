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

`tools/scripts/permute_import.sh` (also used by `make permute`) copies the
source file's compiler profile into the permuter's `compile.sh`.
`import.py` preprocesses the source and loses those comments, so without
the script every permutation of a gcc 2.6.3 unit was built with 2.5.7.
