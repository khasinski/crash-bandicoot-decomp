# Assembly, GTE, and Progress Reporting Policy

This repository reproduces the retail Crash Bandicoot (`SCUS-949.00`) PlayStation executable byte-for-byte (`make check`, SHA-1 `b2af088a162e046ad07f532d46b655cfcc42a05c`). This is a verified binary matching claim across the entire executable, with explicit separation between:
1. **Ownership categories** (`Game code` vs `PsyQ libraries`)
2. **Source-form categories** (`C units`, `C units with inline ASM or compiler constraints`, `Units with retained ASM or raw opcodes`, `Extracted data and BSS layout`)

## Ownership & Source-Form Categories

The report accounts for every code unit placed by the linker:
- `game` (`Game code`): Naughty Dog engine, NS/paging, GOOL VM, level/camera/render/audio, and game runtime routines under `src/main/{core,ns,gool,level,render,cam,audio,engine,math,libc}/`.
- `psyq` (`PsyQ libraries`): Sony PsyQ 3.5 SDK library and BIOS/kernel wrapper units under `src/main/sdk/`.

Independently of ownership, every unit is classified by its source syntax:
- `source_c` (`C units (header intrinsics allowed)`): Plain C translation units that may use named GTE/COP2 macros from [`include/gte.h`](../include/gte.h) without direct `asm(...)` statements, register pins, or included assembly blocks.
- `source_inline` (`C units with inline ASM or compiler constraints`): C translation units that use inline `asm(...)` statements, explicit register bindings (`register ... asm("$...")`), empty compiler barriers (`asm("")`), or symbol aliases.
- `source_assembly` (`Units with retained ASM or raw opcodes`): code the original was written in as assembly, kept as `hasm` subsegments (see below). These units have `complete=false` in the report metadata while participating in all byte and function matching totals.
- `source_data` (`Extracted data and BSS layout`): Extracted `.rodata`, `.data`, `.sdata`, `.sbss`, and `.bss` segments.

## Handwritten GTE Assembly (`engine/gte_render`, `engine/gte_transform`)

The 40 polygon/SVTX/tpage/background GTE rendering routines at `0x800334A0..0x8003A94C` (`func_800334A0`..`func_8003A76C`) are hand-written MIPS/GTE assembly in the retail binary:
- They use a custom register-passing convention across internal sub-calls without C stack frames (`$t8`/`$t9`/`$gp`/`$fp` used as scratch registers across `jal` calls),
- They branch directly into the middle of sibling routines and jump tables at `0x80010E58..0x80010EC0`,
- They interleave COP2/GTE pipeline instructions (`rtps`, `rtpt`, `nclip`, `avsz3`, `avsz4`, `dpcs`, `dcpl`, `gpf`, `gpl`, `mvpva`) with hand-scheduled delay slots.

No C compiler output can reproduce them. They are two `hasm` subsegments, `engine/gte_render` (`0x800334A0..0x80034504`) and `engine/gte_transform` (`0x80034520..0x8003A94C`), around the one C function between them, `RIncTickCount` in [`src/main/engine/tick_count.c`](../src/main/engine/tick_count.c).

## Hand-Written Assembly Units (`hasm`)

Code that the original was written in as assembly stays assembly, but never as assembly text inside a C file. Each such unit is a `hasm` subsegment in `configs/USA/main.yaml`; `make split` generates its `.s` under `asm/` from the retail executable (like the data segments, it is not committed), and the build assembles it directly. objdiff compares it with the same split of retail (`tools/scripts/gen_objdiff.py`).

| Unit | Original |
|---|---|
| `engine/gte_render`, `engine/gte_transform` | Naughty Dog's hand-written GTE routines (above) |
| `sdk/kernel/crt0` | `LIBSN.LIB:snmain.o` startup (`__SN_ENTRY_POINT`, sets `$gp`/`$sp`) |
| `sdk/libgte/gte_core`, `sdk/libgte/patch_gte` | LIBGTE assembly (`InitGeom`, `_patch_gte`, saving `ra` in globals) |
| `sdk/bios/*` | BIOS veneers: `addiu $t2, $zero, 0xA0/0xB0/0xC0; jr $t2; addiu $t1, $zero, n` |

Everything else is C. The remaining assembly in C is the GTE intrinsics of [`include/gte.h`](../include/gte.h): gcc 2.x has no other way to emit COP2 instructions, and the original game used Sony's equivalent inline macros. GNU as gets the GTE mnemonics from `include/gte_macros.inc`, which `tools/scripts/cc.sh` passes to it before the compiler output.

Toolchain workarounds that used to be inline assembly are build configuration:
- Uninitialised globals: gcc emits `.comm`, which maspsx turns into a local `.sbss` label; `cc.sh` adds `.globl` for every `.comm` (`.lcomm` from `static` stays local).
- LIBGTE object padding: each library object's code is padded to 16 bytes; `configs/USA/main.yaml` declares the gaps as splat `pad` subsegments between the split objects.

## Embedded Data in `.text` (`configs/embedded_data.json`)

At `0x80034520` (offset `0` of the `engine/gte_transform` unit), immediately after `RIncTickCount` (`0x80034504..0x80034520`), the retail `.text` section contains a 4-byte mutable frame/engine tick counter (`func_80034520`, initial value `0x00000000`) incremented by `func_80034504` and read across the NS paging, GOOL, level, and memory card subsystems.

Because `objdiff` classifies symbols by their containing section (`.text`), [`configs/embedded_data.json`](../configs/embedded_data.json) records this 4-byte object and [`tools/scripts/classify_embedded_data.py`](../tools/scripts/classify_embedded_data.py) validates its `STT_OBJECT` ELF symbol type and size in both base and target objects, moving those 4 bytes from the function/code ledger into the data ledger while retaining unmodified `objdiff` output in `build/USA/report.raw.json`.

## Report Denominator Audit (`tools/scripts/audit_report.py`)

[`tools/scripts/audit_report.py`](../tools/scripts/audit_report.py) verifies that:
1. Every linked object with a non-empty `.text` section in `build/USA/main.map` is present in `build/USA/report.json`.
2. Function and embedded-data ranges within each unit are non-overlapping, strictly in-bounds, and leave no unreported non-zero `.text` bytes before, between, or after functions.
3. Unit code byte totals and function counts sum identically to the overall report totals and match 100% against the retail binary.
