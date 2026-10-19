#!/usr/bin/env python3
"""Measure decompilation scaffolding and matching debt in C and header files."""

from __future__ import annotations

import argparse
import json
import re
from pathlib import Path

ROOT = Path(__file__).resolve().parents[2]
SOURCE_ROOT = ROOT / "src/main"
HEADER_ROOT = ROOT / "include"
BASELINE = ROOT / "tools/code_debt_baseline.json"

PATTERNS = {
    "include_asm_blocks": re.compile(r"\bINCLUDE_ASM\s*\("),
    "handwritten_asm_blocks": re.compile(r"\bHANDWRITTEN_ASM\s*\("),
    "sdata_size_hacks": re.compile(r"\.sdata\\n\.size\b"),
    "raw_gte_inline_asm": re.compile(
        r'\b(?:__asm__|asm)\s*(?:volatile\s*)?\(\s*"(?:mtc2|mfc2|ctc2|cfc2|lwc2|swc2|cop2)\b'
    ),
    "register_pins": re.compile(
        r'\bregister\b[^;\n]*\b(?:__asm__|asm)\s*\(\s*"(?:\$\d+|zero|at|v[01]|a[0-3]|t[0-9]|s[0-8]|k[01]|gp|sp|fp|ra)"'
    ),
    "empty_barriers": re.compile(r'\b(?:__asm__|asm)\s*(?:volatile\s*)?\(\s*""'),
    "raw_offset_dereferences": re.compile(
        r"\*\s*\([^)]*\*\s*\)\s*\("
        r"(?:[^();\n]|\([^();\n]*\))*?[+-]\s*(?:0x[0-9A-Fa-f]+|[1-9][0-9]*)"
    ),
    "byte_pointer_arithmetic": re.compile(
        r"\(\s*(?:const\s+|volatile\s+)?(?:u8|s8|char)\s*\*\s*\)"
        r"(?!\s*\()[^;=\n]*\+"
    ),
    "negative_pointer_indexing": re.compile(
        r"\b[A-Za-z_][A-Za-z0-9_]*(?:\s*->\s*[A-Za-z_][A-Za-z0-9_]*)?"
        r"\s*\[\s*-[1-9][0-9]*\s*\]"
    ),
    "raw_symbol_references": re.compile(r"\bD_[0-9A-Fa-f]{6,}\b"),
    "unnamed_function_symbols": re.compile(r"\bfunc_[0-9A-Fa-f]{6,}\b"),
    "asm_symbol_aliases": re.compile(r'\b(?:__asm__|asm)\s*\(\s*"(?:D_|func_)[0-9A-Fa-f]+'),
    "externs_in_c": re.compile(r"^\s*extern\b", re.MULTILINE),
    "func_prototypes_in_c": re.compile(
        r"^(?!\s*typedef\b)(?:extern\s+)?(?:const\s+|volatile\s+|unsigned\s+|signed\s+|struct\s+\w+\s+)*"
        r"(?!HANDWRITTEN_ASM\b|INCLUDE_ASM\b|PSYQ_BIOS_TRAMPOLINE\b)[A-Za-z_][A-Za-z0-9_]*[\s*]+"
        r"[A-Za-z_][A-Za-z0-9_]*\s*\([^;{}]*\)\s*;",
        re.MULTILINE,
    ),
    "unk_fields_in_c": re.compile(
        r"\b(?:unk|field|pad|padding)(?:_[0-9A-Fa-f_]+|[0-9A-Fa-f]+)?\b"
    ),
    "fake_control_flow": re.compile(r"\b(?:if\s*\(\s*[01]\s*\)|while\s*\(\s*0\s*\))"),
    "fake_bit_tautologies": re.compile(
        r"\b([A-Za-z_][A-Za-z0-9_]*)\s*=\s*[^;=\n]*&\s*1\s*\)*\s*;\s*if\s*\(\s*\(?\s*\1\s*>>\s*1\b"
    ),
}

HEADER_PATTERNS = {
    "header_asm_aliases": re.compile(
        r'^\s*extern\b[^;\n]*\b(?:__asm__|asm)\s*\(\s*"(?!0x)', re.MULTILINE
    ),
    "header_unk_fields": re.compile(
        r"\b(?:unk|field|pad|padding)(?:_[0-9A-Fa-f_]+|[0-9A-Fa-f]+)?\b"
    ),
}


def strip_comments(text: str) -> str:
    text = re.sub(r"/\*.*?\*/", "", text, flags=re.DOTALL)
    text = re.sub(r"//[^\n]*", "", text)
    return re.sub(r"^\s*#\s*define\b(?:\\\n|[^\\\n]|\\(?![\n]))*", "", text, flags=re.MULTILINE)


def count_debt(
    source_root: Path = SOURCE_ROOT, header_root: Path | None = None
) -> dict[str, int]:
    totals = {name: 0 for name in PATTERNS}
    totals.update({name: 0 for name in HEADER_PATTERNS})
    for path in sorted(source_root.rglob("*.c")):
        source = path.read_text(errors="ignore")
        text = strip_comments(source)
        for name, pattern in PATTERNS.items():
            if name == "register_pins" and "HANDWRITTEN_ASM" in source:
                continue
            totals[name] += len(pattern.findall(text))
    if header_root is None and source_root == SOURCE_ROOT:
        header_root = HEADER_ROOT
    if header_root is not None and header_root.exists():
        for path in sorted(header_root.rglob("*.h")):
            text = strip_comments(path.read_text(errors="ignore"))
            for name, pattern in HEADER_PATTERNS.items():
                totals[name] += len(pattern.findall(text))
    return totals


def main() -> int:
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--check", action="store_true", help="fail if any count exceeds baseline")
    parser.add_argument("--update-baseline", action="store_true", help="write current counts to baseline")
    parser.add_argument("--json", action="store_true", help="print machine-readable output")
    args = parser.parse_args()

    current = count_debt()
    if args.update_baseline:
        BASELINE.write_text(json.dumps(current, indent=2, sort_keys=True) + "\n")

    if args.json:
        print(json.dumps(current, indent=2, sort_keys=True))
    else:
        for name, count in current.items():
            print(f"{name:28} {count:5}")

    if not args.check:
        return 0

    baseline = json.loads(BASELINE.read_text())
    increases = {
        name: (baseline.get(name, 0), count)
        for name, count in current.items()
        if count > baseline.get(name, 0)
    }
    if increases:
        for name, (before, after) in increases.items():
            print(f"increased: {name}: {before} -> {after}")
        return 1
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
