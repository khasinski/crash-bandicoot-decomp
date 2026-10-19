# Crash Bandicoot Decompilation

Work-in-progress matching decompilation of the North American PlayStation
release of Crash Bandicoot (1996), target `SCUS-94900`.

This repository is source-only. It does not contain disc images, extracted game
data, Sony PsyQ SDK files, compiler binaries, or generated split output.
Contributors must provide their own legally obtained copy of the game.

## Target

| Field | Value |
|---|---|
| Executable | `SCUS_949.00` → `assets/USA/main.exe` |
| SHA-1 | `b2af088a162e046ad07f532d46b655cfcc42a05c` |
| Disc (redump 2250) | track 1 SHA-1 `61ff4c9e8dcfb9e5d94d37f66330b69d08d6c914` |
| Entry / gp | `0x8003E018` / `0x800563FC` |
| Compiler | gcc 2.5.7-psx (allocator), 2.6.3-psx (current engine units), `-O2 -G8`, maspsx/ASPSX 2.34 — see [docs/COMPILER.md](docs/COMPILER.md) |

## Progress

![functions](https://img.shields.io/endpoint?url=https%3A%2F%2Fraw.githubusercontent.com%2Fkhasinski%2Fcrash-bandicoot-decomp%2Fmain%2Fdocs%2Fbadges%2Ffunctions.json)
![code](https://img.shields.io/endpoint?url=https%3A%2F%2Fraw.githubusercontent.com%2Fkhasinski%2Fcrash-bandicoot-decomp%2Fmain%2Fdocs%2Fbadges%2Fcode.json)

Regenerate the badges with `make report`. They summarize fully matching code
in the objdiff report across both Game code and PsyQ libraries, audited against
every linked `.text` object by `tools/scripts/audit_report.py` and
`tools/scripts/classify_embedded_data.py` — see
[docs/ASM_AND_GTE_POLICY.md](docs/ASM_AND_GTE_POLICY.md).

Candidate functions are scored exclusively by instruction Levenshtein distance,
with relocation fields masked. Acceptance requires distance zero and a rebuilt
executable matching the retail SHA-1. See [CONTRIBUTING.md](CONTRIBUTING.md).
Shared layouts and the automatic stock-profile comparison tool are documented
in [docs/STRUCTURES.md](docs/STRUCTURES.md), the complete 825-function symbol
catalog in [docs/names.md](docs/names.md), and the round-trip verified GOOL
Lisp bytecode decompiler and assembler (`tools/scripts/gool_lisp.py`) in
[docs/GOOL_LISP.md](docs/GOOL_LISP.md).

## Quick start

```sh
make setup                 # .venv with splat, spimdisasm, m2c, ...
make toolchain             # old-gcc builds, maspsx, objdiff-cli, asm-differ, permuter
make stage                 # disc image -> assets/USA/main.exe (+ all disc files)
make split                 # splat -> asm/, linkers/, new src/ stubs
make build check           # build/USA/main.exe, SHA-1 against retail
make report                # objdiff progress + embedded-data & denominator audit
make audit-code            # verify C scaffolding / code debt ratchet
make gool gool-check       # decompile & round-trip verify all 60 .NSF GOOL Lisp scripts
make test                  # tooling & GOOL Lisp regressions
```

Requirements: Python 3.12, 7-Zip (`7z`), GNU binutils for mipsel
(`mipsel-none-elf-*` or Homebrew's `mipsel-linux-gnu-*`), and on macOS Docker
(OrbStack works well), because gcc 2.5.7 exists only as a Linux i386 binary.
`make stage` looks for `Crash Bandicoot (USA).bin` or `.7z` in `disc/USA/`,
`~/Documents`, and `~/Downloads`.

## Workflow

1. Carve a translation unit: in `configs/USA/main.yaml`, split an `asm`
   subsegment and give the new piece the type `c`, e.g.
   `[0x1F7C, c, libc/malloc]`. Then run `make split`. splat writes
   `src/main/libc/malloc.c` with one `INCLUDE_ASM` per function.
2. `make m2c FUNC=name` gives a first pass. Replace the `INCLUDE_ASM` line with C.
3. `make probe FILE=src/main/libc/malloc.c` checks each function
   against retail using instruction Levenshtein distance. Require distance zero
   before promoting a candidate; `make objdiff-config` prepares progress inputs.
4. `make permute FUNC=name` prepares a decomp-permuter run. Keep the attempt
   under `#ifdef NON_MATCHING … #else INCLUDE_ASM(…) #endif`, then run
   `tools/toolchain/decomp-permuter/permuter.py nonmatchings/name -j8`.
5. `make build check` must report `OK` before a commit.

The probe regenerates reference assembly from retail in `expected/`, including
functions already written in C. A missing reference or an empty object fails the
probe. Relocation fields are masked, so the final authority is always the full
`make build check` SHA-1 comparison.

C objects track both header dependencies and assembler `.include` dependencies.
After changing the compiler or environment flags, force a rebuild with
`make -B build check`. Plain `make` also builds and checks the executable.
Run `make test` after modifying build tooling, and `make report` to refresh
progress. `make split` deletes generated build and assembly output; keep C
attempts in `src/` or the ignored `scratch/` directory.

The build is shiftable: code and data can grow or move and the result still
links correctly. `make shiftcheck` relinks with padding inserted in `.text` and
`.data` and fails if a word changed without a relocation, or if an
unrelocated word points into the image. Name data in `configs/USA/sym.main.txt`
(hand edits to `asm/` are lost on the next `make split`), give fixed points
relative to sections in `configs/USA/undefined_syms_manual.txt`, and never write
image addresses as numbers. Struct views that span several globals (for example
the state block at 0x80060DF0) still assume the original relative data layout.

Per-file compiler overrides go in a comment in the C file:
`/* GCC_VERSION: 2.6.3 */`, `/* CC1_FLAGS: -O1 */`,
`/* CC1_FLAGS: -O2 -fno-cse-follow-jumps */`, `/* ASPSX_VERSION: 2.56 */`.

## Layout

- `configs/USA/` - splat config, symbols (`sym.main.txt`), relocs, manual linker symbols.
- `src/main/` - decompiled translation units.
- `include/` - project headers, `INCLUDE_ASM`, assembler macros.
- `tools/scripts/` - build wrapper (`cc.sh`), staging, probing, objdiff/report helpers.
- `tools/toolchain/` - setup scripts; the fetched tools themselves are not committed.
- `docs/` - compiler and layout findings.

## Prior work used as reference

- [wurlyfox/c1](https://github.com/wurlyfox/c1): a non-matching C reimplementation
  of the engine. Its function names and memory map are the best naming source.
- [wurlyfox/c1c](https://github.com/wurlyfox/c1c): 639 function entry points with
  33 names. Those names seed `configs/USA/sym.main.txt`.
- [cbhacks/CrashEdit](https://github.com/cbhacks/CrashEdit): NSD/NSF and entry formats.

Neither c1 nor c1c has a license, so only facts (addresses, names) are taken from
them, never code.

Source publication follows [rage-racer-decomp](https://github.com/khasinski/rage-racer-decomp)
and [parasite-eve-decomp](https://github.com/khasinski/parasite-eve-decomp).
See [LICENSE.md](LICENSE.md) and [THIRD_PARTY_NOTICES.md](THIRD_PARTY_NOTICES.md).
