#!/usr/bin/env python3
"""Check that the build is shiftable: link it once as is and once with
padding inserted in .text and .data, then compare every symbol's bytes.

A word that differs between the two links must carry a relocation in the
shifted link; a difference without one is a hard-coded address (or code that
depends on its own position) and would break once code or data move.

    tools/scripts/check_shiftable.py            # uses build/USA objects
"""
from __future__ import annotations

import argparse
import re
import subprocess
import sys
import tempfile
from pathlib import Path

from elftools.elf.elffile import ELFFile
from elftools.elf.relocation import RelocationSection

ROOT = Path(__file__).resolve().parents[2]


def link(script: Path, out: Path, version: str) -> None:
    subprocess.run(
        ["mipsel-linux-gnu-ld", "-EL", "-T", str(script),
         "-T", f"configs/{version}/undefined_syms_manual.txt",
         "-T", f"build/{version}/undefined_addr_aliases.main.txt",
         "--no-check-sections", "--emit-relocs", "-o", str(out)],
        cwd=ROOT, check=True)


def load(path: Path):
    elf = ELFFile(open(path, "rb"))
    secs = [s for s in elf.iter_sections()
            if s["sh_flags"] & 0x2 and s["sh_type"] == "SHT_PROGBITS"]
    def read(addr: int, size: int) -> bytes | None:
        for s in secs:
            base = s["sh_addr"]
            if base <= addr and addr + size <= base + s["sh_size"]:
                off = addr - base
                return s.data()[off:off + size]
        return None
    syms = {}
    for sym in elf.get_section_by_name(".symtab").iter_symbols():
        if sym["st_shndx"] in ("SHN_UNDEF", "SHN_ABS") or not sym.name:
            continue
        if sym["st_info"]["type"] in ("STT_FUNC", "STT_OBJECT", "STT_NOTYPE"):
            syms.setdefault(sym.name, (sym["st_value"], sym["st_size"]))
    relocs = set()
    for s in elf.iter_sections():
        if isinstance(s, RelocationSection):
            target = elf.get_section(s["sh_info"])
            for r in s.iter_relocations():
                relocs.add(target["sh_addr"] + r["r_offset"] if elf.header["e_type"] == "ET_REL" else r["r_offset"])
    image = []
    for s in secs:
        image.append((s["sh_addr"], s.data()))
    return syms, read, relocs, image


def main() -> int:
    ap = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument("--version", default="USA")
    ap.add_argument("--text-pad", type=lambda x: int(x, 0), default=0x40)
    ap.add_argument("--data-pad", type=lambda x: int(x, 0), default=0x20)
    args = ap.parse_args()

    script = ROOT / f"linkers/{args.version}/main.ld"
    text = script.read_text()
    first_text = re.search(r"main_TEXT_START = \.;\n(\s+\S+\(\.text\);\n)", text)
    if not first_text:
        print("cannot find the first .text input in the linker script", file=sys.stderr)
        return 2
    shifted = text.replace(first_text.group(1), first_text.group(1) + f"        . += {args.text_pad:#x};\n", 1)
    shifted = shifted.replace("main_DATA_START = .;\n", f"main_DATA_START = .;\n        . += {args.data_pad:#x};\n", 1)

    with tempfile.TemporaryDirectory() as tmp:
        tmp = Path(tmp)
        (tmp / "shift.ld").write_text(shifted)
        link(script, tmp / "a.elf", args.version)
        link(tmp / "shift.ld", tmp / "b.elf", args.version)
        syms_a, read_a, relocs_a, image_a = load(tmp / "a.elf")
        syms_b, read_b, relocs_b, _ = load(tmp / "b.elf")

    bad = []
    checked = 0
    for name, (addr_a, size) in sorted(syms_a.items(), key=lambda kv: kv[1][0]):
        if name not in syms_b or size == 0:
            continue
        addr_b = syms_b[name][0]
        a = read_a(addr_a, size)
        b = read_b(addr_b, size)
        if a is None or b is None:
            continue
        checked += 1
        for off in range(0, size - size % 4, 4):
            if a[off:off + 4] != b[off:off + 4] and (addr_b + off) not in relocs_b:
                bad.append((name, addr_a + off, a[off:off + 4].hex(), b[off:off + 4].hex()))
    # Words that look like addresses inside the image but are not relocated:
    # identical in both links, so the comparison above cannot see them.
    lo = syms_a["main_RODATA_START"][0] if "main_RODATA_START" in syms_a else 0x80010000
    hi = syms_a["g_bss_end"][0] if "g_bss_end" in syms_a else 0x80200000
    raw = []
    for base, data in image_a:
        for off in range(0, len(data) - 3, 4):
            addr = base + off
            if addr in relocs_a:
                continue
            word = int.from_bytes(data[off:off + 4], "little")
            if lo <= word < hi:
                raw.append((addr, word, "pointer"))
            elif word >> 26 == 0x0F and ((word & 0xFFFF) << 16) and lo <= (word & 0xFFFF) << 16 < hi:
                raw.append((addr, word, "lui"))
    for addr, word, kind in raw[:50]:
        print(f"{addr:#010x}: {word:#010x} ({kind} into the image, no relocation)")
    print(f"{len(raw)} unrelocated address-like words")

    for name, addr, wa, wb in bad[:50]:
        print(f"{name} @ {addr:#010x}: {wa} -> {wb} (no relocation)")
    print(f"{checked} symbols checked, {len(bad)} unrelocated differences")
    return 1 if bad or raw else 0


if __name__ == "__main__":
    sys.exit(main())
