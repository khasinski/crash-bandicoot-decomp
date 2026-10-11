#!/usr/bin/env python3
"""Compile C and compare retail using instruction Levenshtein distance.

    tools/scripts/probe_match.py scratch/foo.c [--gcc 2.6.3 --gcc 2.7.2] [-v]

Each function symbol in the object is looked up by name in the split assembly
(`glabel NAME` followed by `/* OFFSET VRAM WORD */` lines), so the C names must
match the names splat uses (func_XXXXXXXX or names from configs/USA/sym.main.txt).
Retail assembly is regenerated in expected/ before each probe. Missing
reference functions fail the check. Fields filled in by relocations (jal targets, %hi/%lo, gp offsets) are masked
on both sides; everything else must be identical.
"""
from __future__ import annotations

import argparse
import os
import re
import subprocess
import sys
import tempfile
from pathlib import Path

from elftools.elf.elffile import ELFFile
from elftools.elf.relocation import RelocationSection

ROOT = Path(__file__).resolve().parents[2]
GLABEL_RE = re.compile(r"^\s*glabel\s+(\S+)")
INSN_RE = re.compile(r"/\*\s*([0-9A-F]+)\s+([0-9A-F]{8})\s+([0-9A-F]{8})\s*\*/")

# R_MIPS_26, R_MIPS_HI16, R_MIPS_LO16, R_MIPS_GPREL16, R_MIPS_PC16.
# Included assembly can leave local branch targets for the linker to resolve.
# Mask PC16 only where an actual relocation exists, not ordinary branch offsets.
MASKS = {4: 0x03FFFFFF, 5: 0xFFFF, 6: 0xFFFF, 7: 0xFFFF, 10: 0xFFFF}


def retail_functions(version: str) -> dict[str, list[int]]:
    funcs: dict[str, list[int]] = {}
    asm_dir = ROOT / "expected" / "asm" / version / "main"
    for path in asm_dir.rglob("*.s"):
        current = None
        for line in path.read_text(errors="replace").splitlines():
            m = GLABEL_RE.match(line)
            if m:
                current = funcs.setdefault(m.group(1), [])
                continue
            if line.strip().startswith("endlabel"):
                current = None
                continue
            if current is not None:
                im = INSN_RE.search(line)
                if im:
                    word = bytes.fromhex(im.group(3))
                    current.append(int.from_bytes(word, "little"))
    return {k: v for k, v in funcs.items() if v}


def object_functions(obj: Path) -> dict[str, tuple[list[int], list[int]]]:
    with obj.open("rb") as f:
        elf = ELFFile(f)
        text = elf.get_section_by_name(".text")
        data = text.data()
        text_idx = elf.get_section_index(".text")
        masks = [0] * (len(data) // 4)
        for sec in elf.iter_sections():
            if isinstance(sec, RelocationSection) and sec.name in (".rel.text", ".rela.text"):
                for rel in sec.iter_relocations():
                    i = rel["r_offset"] // 4
                    if i < len(masks):
                        masks[i] |= MASKS.get(rel["r_info_type"], 0)
        symtab = elf.get_section_by_name(".symtab")
        out = {}
        for sym in symtab.iter_symbols():
            if sym["st_info"]["type"] != "STT_FUNC" or sym["st_shndx"] != text_idx:
                continue
            if sym.name.startswith("__maspsx_include_asm_hack"):
                continue
            start, size = sym["st_value"], sym["st_size"]
            words = [int.from_bytes(data[o:o + 4], "little") for o in range(start, start + size, 4)]
            out[sym.name] = (words, masks[start // 4:(start + size) // 4])
        return out


def disasm(word: int) -> str:
    with tempfile.NamedTemporaryFile(suffix=".bin", delete=False) as t:
        t.write(word.to_bytes(4, "little"))
    cross = os.environ.get("CROSS") or (
        "mipsel-none-elf-" if subprocess.run(["sh", "-c", "command -v mipsel-none-elf-objdump"],
                                             capture_output=True).returncode == 0 else "mipsel-linux-gnu-")
    res = subprocess.run([cross + "objdump", "-D", "-b", "binary", "-m", "mips:3000", "-EL", t.name],
                         capture_output=True, text=True)
    os.unlink(t.name)
    lines = [l for l in res.stdout.splitlines() if re.match(r"\s+0:", l)]
    return lines[0].split("\t", 2)[-1].strip() if lines else f"{word:08x}"


def levenshtein(got, mask, exp):
    """Instruction edit distance; source relocations are ignored when aligning."""
    if len(got) == len(exp) and all(
            (word & ~mask[i]) == (exp[i] & ~mask[i])
            for i, word in enumerate(got)):
        return 0, []
    from array import array
    rows = [array("I", range(len(exp) + 1))]
    for i, word in enumerate(got):
        row = array("I", [i + 1])
        previous = rows[-1]
        for j, expected in enumerate(exp):
            equal = (word & ~mask[i]) == (expected & ~mask[i])
            row.append(min(previous[j + 1] + 1, row[j] + 1,
                           previous[j] + (not equal)))
        rows.append(row)
    i, j = len(got), len(exp)
    edits = []
    while i or j:
        if i and j:
            equal = (got[i - 1] & ~mask[i - 1]) == (exp[j - 1] & ~mask[i - 1])
            if rows[i][j] == rows[i - 1][j - 1] + (not equal):
                if not equal:
                    edits.append(("replace", i - 1, j - 1))
                i -= 1
                j -= 1
                continue
        if i and rows[i][j] == rows[i - 1][j] + 1:
            edits.append(("delete", i - 1, j))
            i -= 1
        else:
            edits.append(("insert", i, j - 1))
            j -= 1
    return rows[-1][-1], list(reversed(edits))


def compare(name, got, mask, exp, verbose) -> bool:
    distance, edits = levenshtein(got, mask, exp)
    status = "MATCH" if distance == 0 else "DIFF"
    print(f"  {name:32s} {len(got):4d}/{len(exp):<4d} {status}  Levenshtein={distance}")
    if distance and verbose:
        for kind, i, j in edits[:8]:
            a = disasm(got[i]) if kind != "insert" else "-"
            b = disasm(exp[j]) if kind != "delete" else "-"
            print(f"      {kind:7s} ours[{i}]: {a:32s} retail[{j}]: {b}")
    return distance == 0


def main() -> int:
    ap = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument("source", type=Path)
    ap.add_argument("--gcc", action="append", help="gcc version(s) to try (default: cc.sh default)")
    ap.add_argument("--version", default="USA")
    ap.add_argument("-v", "--verbose", action="store_true")
    args = ap.parse_args()

    # Always regenerate from retail: promoted C functions disappear from the
    # working nonmatchings tree, and cached references can have stale names.
    subprocess.run([sys.executable, str(ROOT / "tools/scripts/gen_objdiff.py"),
                    "--version", args.version], cwd=ROOT, check=True,
                   stdout=subprocess.DEVNULL)
    args.source = args.source.resolve()
    retail = retail_functions(args.version)
    all_ok = True
    for gcc in args.gcc or [None]:
        env = dict(os.environ)
        if gcc:
            env["CRASH_GCC_VERSION"] = gcc
        with tempfile.TemporaryDirectory() as tmp:
            obj = Path(tmp) / "probe.o"
            subprocess.run([str(ROOT / "tools/scripts/cc.sh"), str(args.source), str(obj)], check=True, env=env, cwd=ROOT)
            funcs = object_functions(obj)
        print(f"gcc {gcc or 'default'}:")
        if not funcs:
            print("  ERROR: no functions found in compiled object")
            all_ok = False
        for name, (words, mask) in funcs.items():
            if name not in retail:
                print(f"  {name:32s} ERROR: not in retail asm")
                all_ok = False
                continue
            all_ok &= compare(name, words, mask, retail[name], args.verbose)
    return 0 if all_ok else 1


if __name__ == "__main__":
    sys.exit(main())
