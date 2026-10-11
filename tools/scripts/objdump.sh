#!/usr/bin/env bash
# mipsel objdump from whichever GNU binutils prefix is installed.
if [ -z "${CROSS:-}" ]; then
    command -v mipsel-none-elf-objdump >/dev/null && CROSS=mipsel-none-elf- || CROSS=mipsel-linux-gnu-
fi
exec "${CROSS}objdump" "$@"
