#!/usr/bin/env bash
# GNU as for mipsel with the project's flags (for decomp-permuter and ad-hoc use).
if [ -z "${CROSS:-}" ]; then
    command -v mipsel-none-elf-as >/dev/null && CROSS=mipsel-none-elf- || CROSS=mipsel-linux-gnu-
fi
exec "${CROSS}as" -EL -G0 -march=r3000 -mtune=r3000 -no-pad-sections "$@"
