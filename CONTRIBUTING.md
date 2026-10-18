# Contributing

Provide your own USA copy of Crash Bandicoot (`SCUS_949.00`). Follow the
README setup, toolchain, staging and split steps before building.

Keep C under `src/main/<subsystem>/`, shared declarations under `include/`,
and target symbols, relocations and split boundaries under `configs/USA/`.
Use names supported by strings, call graphs or other evidence; retain address
names when the purpose is uncertain. Translation-unit boundaries are provisional.
Recovered layouts and the stock-profile search tool are described in
[docs/STRUCTURES.md](docs/STRUCTURES.md), assembly/GTE and progress reporting
conventions in [docs/ASM_AND_GTE_POLICY.md](docs/ASM_AND_GTE_POLICY.md),
verified symbol names in [docs/names.md](docs/names.md), and the GOOL Lisp
bytecode decompiler/assembler in [docs/GOOL_LISP.md](docs/GOOL_LISP.md).

Score candidates with `make probe FILE=src/main/<subsystem>/<unit>.c`.
Instruction Levenshtein distance is the matching metric; relocation fields are
masked. A zero-distance probe alone does not verify the linked addresses.
Run `make verify` to build, verify the retail SHA-1 and run integration tests,
and `make audit-code` to ensure C scaffolding debt does not increase.
After changing split boundaries, first run `make split`. Run `make report`
and commit updated `docs/badges/` when progress changes.

Use the stock GCC → maspsx → GNU assembler pipeline. Per-file compiler and
assembler profiles must describe real stock options. Do not patch compiler
output or objects to manufacture a match. Keep unsuccessful candidates in
ignored `scratch/`; retained handwritten assembly uses `HANDWRITTEN_ASM`.
Register pins, dummy temporaries and single-iteration loop tricks require
explicit review and must not be silently presented as finished semantic
reconstruction.

Never commit retail inputs, extracted assets, SDK or compiler binaries,
generated assembly, build output, or local experiments. `make test-source`
checks instruction scoring, report/debt auditing, GOOL Lisp round-trip logic,
and shell syntax without game data; public CI runs this subset. Full build and
integration validation require local retail inputs.
