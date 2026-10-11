# Third-party tools and references

External tools are installed locally, not vendored: splat/spimdisasm, m2c,
decompals/old-gcc, maspsx, GNU binutils, objdiff, asm-differ and
decomp-permuter. Their licenses remain with their upstream distributions.
Python dependencies are listed in `requirements.txt`; tool sources and release
URLs are recorded in `tools/toolchain/setup.sh` and
`tools/toolchain/build_oldgcc_macos.sh`.

[c1](https://github.com/wurlyfox/c1) and
[c1c](https://github.com/wurlyfox/c1c) provide naming and behavioral evidence.
They have no declared license; their source is not copied into this project.
[CrashEdit](https://github.com/cbhacks/CrashEdit) provides format references.
Retail disassembly is generated only from the contributor's local game copy.

PsyQ-compatible declarations and reconstructed library functions are part of
the reverse-engineering work; no proprietary SDK archives are shipped.
