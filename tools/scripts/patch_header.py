#!/usr/bin/env python3
"""Make the split PS-X EXE header refer to symbols instead of fixed numbers.

splat writes the initial PC, the load address and the payload size as
literal words. Pointing them at the entry symbol, the start of the image and
a linker-computed size keeps the header correct when code or data move.
"""
import re
import sys
from pathlib import Path

REPLACEMENTS = {
    "Initial PC": "__SN_ENTRY_POINT",
    ".text start": "main_VRAM",
    ".text size": "main_EXE_TEXT_SIZE",
}

path = Path(sys.argv[1])
text = path.read_text()
for comment, symbol in REPLACEMENTS.items():
    pattern = re.compile(r"\.word 0x[0-9A-Fa-f]+(\s+/\* " + re.escape(comment) + r" \*/)")
    text, count = pattern.subn(rf".word {symbol}\1", text)
    if count != 1:
        sys.exit(f"{path}: expected one '{comment}' word, found {count}")
path.write_text(text)
