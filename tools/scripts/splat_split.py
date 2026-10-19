#!/usr/bin/env python3
"""Run `splat split`, treating HANDWRITTEN_ASM like INCLUDE_ASM.

splat decides which functions of a C segment get an asm file by scanning the
C source for `INCLUDE_ASM(`. Handwritten routines use `HANDWRITTEN_ASM(`
(the same expansion, but tracked separately as permanent asm), so a clean
split would not write their asm and the build would fail.
"""
import sys

from splat.__main__ import splat_main
from splat.segtypes.common.c import CommonSegC

_find_include_asm = CommonSegC.find_include_asm


def find_include_asm(text: str):
    yield from _find_include_asm(text)
    yield from CommonSegC.find_include_macro(text, "HANDWRITTEN_ASM")


CommonSegC.find_include_asm = staticmethod(find_include_asm)

if __name__ == "__main__":
    sys.argv = ["splat", "split"] + sys.argv[1:]
    splat_main()
