#!/usr/bin/env python3
"""Build objdiff's target objects from retail and write objdiff.json.

    tools/scripts/gen_objdiff.py [--version USA]

The target ("expected") side of every C translation unit is produced from the
retail executable, never from our own build: the splat config is copied with
each `c` subsegment turned into `asm`, splat re-splits retail into expected/,
and each unit's assembly is assembled to
expected/build/<ver>/src/main/<unit>.c.o. Symbol names come from the same
symbol files, so objdiff pairs functions by name.
"""
from __future__ import annotations

import argparse
import copy
import json
import os
import re
import shutil
import subprocess
import sys
from pathlib import Path

import yaml

ROOT = Path(__file__).resolve().parents[2]

CATEGORIES = [
    {"id": "game", "name": "Game code"},
    {"id": "psyq", "name": "PsyQ libraries"},
    {"id": "source_c", "name": "C units (header intrinsics allowed)"},
    {"id": "source_inline", "name": "C units with inline ASM or compiler constraints"},
    {"id": "source_assembly", "name": "Units with retained ASM or raw opcodes"},
    {"id": "source_data", "name": "Extracted data and BSS layout"},
]


def cross() -> str:
    if os.environ.get("CROSS"):
        return os.environ["CROSS"]
    return "mipsel-none-elf-" if shutil.which("mipsel-none-elf-as") else "mipsel-linux-gnu-"


def units_of(cfg: dict, kind: str) -> list[str]:
    units = []
    for seg in cfg["segments"]:
        if not isinstance(seg, dict):
            continue
        for sub in seg.get("subsegments", []):
            if isinstance(sub, list) and len(sub) >= 3 and sub[1] == kind:
                units.append(sub[2])
    return units


def category_of(unit: str) -> str:
    if unit.startswith(("sdk/", "libc/")) or unit in ("engine/format", "engine/format_copy"):
        return "psyq"
    return "game"


def source_form_of(c_path: Path) -> str:
    """Classify a C translation unit by its source syntax."""
    if not c_path.exists():
        return "source_assembly"
    text = c_path.read_text(errors="ignore")
    # Preserve string literals while stripping comments.
    text = re.sub(
        r'"(?:\\.|[^"\\])*"|\'(?:\\.|[^\'\\])*\'|/\*.*?\*/|//[^\n]*',
        lambda m: " " if m[0].startswith(("/*", "//")) else m[0],
        text,
        flags=re.DOTALL,
    )
    if re.search(r"\b(?:HANDWRITTEN_ASM|INCLUDE_ASM)\s*\(", text):
        return "source_assembly"
    literals = re.findall(r'"(?:\\.|[^"\\])*"', text)
    if any(re.search(r"\.(?:include|incbin|word|byte|ent)\b|\bglabel\b", lit) for lit in literals):
        return "source_assembly"
    # Strip extern symbol aliases (`extern ... __asm__("D_...");`) and .sbss
    # global visibility directives (`asm(".globl D_...");`) before checking for
    # inline assembly or compiler register constraints.
    without_symbol_metadata = re.sub(
        r"^\s*extern\b[^;\n]*\b(?:__asm__|asm)\s*\(\s*\"[^\"]*\"\s*\)\s*;",
        "",
        text,
        flags=re.MULTILINE,
    )
    without_symbol_metadata = re.sub(
        r"\b(?:__asm__|asm)\s*\(\s*\"\.globl\s+[A-Za-z0-9_,\s]+\"\s*\)\s*;",
        "",
        without_symbol_metadata,
    )
    if re.search(r"\b(?:asm|__asm__)\s*(?:volatile\s*)?\(", without_symbol_metadata):
        return "source_inline"
    return "source_c"


def retype_embedded_data_in_asm(asm_path: Path, declarations: dict[str, list[int]]) -> None:
    if not declarations or not asm_path.exists():
        return
    text = asm_path.read_text()
    for name in declarations:
        text = re.sub(rf"^nonmatching\s+{re.escape(name)}\b.*$\n?", "", text, flags=re.MULTILINE)
        text = re.sub(rf"^glabel\s+{re.escape(name)}\b", f"dlabel {name}", text, flags=re.MULTILINE)
        text = re.sub(rf"^endlabel\s+{re.escape(name)}\b", f"enddlabel {name}", text, flags=re.MULTILINE)
    asm_path.write_text(text)


def main() -> int:
    ap = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument("--version", default="USA")
    ap.add_argument("--python", default=sys.executable)
    args = ap.parse_args()
    ver = args.version

    cfg_path = ROOT / "configs" / ver / "main.yaml"
    cfg = yaml.safe_load(cfg_path.read_text())
    units = units_of(cfg, "c")
    embedded_manifest_path = ROOT / "configs" / "embedded_data.json"
    embedded_manifest = (
        json.loads(embedded_manifest_path.read_text())
        if embedded_manifest_path.exists()
        else {}
    )

    exp = copy.deepcopy(cfg)
    opts = exp["options"]
    opts["asm_path"] = f"expected/asm/{ver}/main"
    opts["src_path"] = f"expected/src/{ver}"
    opts["build_path"] = f"expected/build/{ver}"
    opts["ld_script_path"] = f"expected/linkers/{ver}/main.ld"
    opts["undefined_funcs_auto_path"] = f"expected/linkers/{ver}/undefined_funcs_auto.txt"
    opts["undefined_syms_auto_path"] = f"expected/linkers/{ver}/undefined_syms_auto.txt"
    for seg in exp["segments"]:
        if isinstance(seg, dict):
            for sub in seg.get("subsegments", []):
                if isinstance(sub, list) and len(sub) >= 3 and sub[1] == "c":
                    sub[1] = "asm"
                elif isinstance(sub, list) and len(sub) >= 3 and sub[1] == ".rodata" and sub[2] in units:
                    # An asm reference needs a separate raw-data file: splat
                    # only migrates a .rodata subsegment into a C owner.
                    sub[1] = "rodata"

    shutil.rmtree(ROOT / "expected", ignore_errors=True)
    exp_cfg = ROOT / "build" / ver / "expected.yaml"  # base_path ../.. still resolves to ROOT
    exp_cfg.parent.mkdir(parents=True, exist_ok=True)
    exp_cfg.write_text(yaml.safe_dump(exp, sort_keys=False))
    subprocess.run(
        [args.python, "-m", "splat", "split", str(exp_cfg)],
        cwd=ROOT,
        check=True,
        stdout=subprocess.DEVNULL,
    )

    as_ = cross() + "as"

    def assemble(src: Path, target: Path) -> None:
        target.parent.mkdir(parents=True, exist_ok=True)
        subprocess.run(
            [
                as_,
                "-EL",
                "-G0",
                "-march=r3000",
                "-mtune=r3000",
                "-no-pad-sections",
                "-I",
                str(ROOT / "include"),
                "-I",
                str(src.parent),
                "-o",
                str(target),
                str(src),
            ],
            check=True,
        )

    objdiff_units = []
    for unit in units:
        source_rel = f"src/main/{unit}.c"
        src = ROOT / "expected" / "asm" / ver / "main" / f"{unit}.s"
        if source_rel in embedded_manifest:
            retype_embedded_data_in_asm(src, embedded_manifest[source_rel])
        target = ROOT / "expected" / "build" / ver / "src" / "main" / f"{unit}.c.o"
        assemble(src, target)
        owner_cat = category_of(unit)
        form_cat = source_form_of(ROOT / source_rel)
        objdiff_units.append(
            {
                "name": unit,
                "target_path": str(target.relative_to(ROOT)),
                "base_path": f"build/{ver}/{source_rel}.o",
                "metadata": {
                    "complete": form_cat in ("source_c", "source_inline"),
                    "source_path": source_rel,
                    "progress_categories": [owner_cat, form_cat],
                },
            }
        )

    # Code still only in split assembly: target-only units, so progress is
    # measured against the whole executable rather than just the C units.
    for unit in units_of(cfg, "asm"):
        src = ROOT / "expected" / "asm" / ver / "main" / f"{unit}.s"
        target = ROOT / "expected" / "build" / ver / "asm" / f"{unit}.s.o"
        assemble(src, target)
        owner_cat = category_of(unit)
        objdiff_units.append(
            {
                "name": f"asm/{unit}",
                "target_path": str(target.relative_to(ROOT)),
                "metadata": {
                    "complete": False,
                    "progress_categories": [owner_cat, "source_assembly"],
                    "auto_generated": True,
                },
            }
        )

    config = {
        "$schema": "https://raw.githubusercontent.com/encounter/objdiff/main/config.schema.json",
        "min_version": "2.0.0",
        "custom_make": "make",
        "custom_args": ["build"],
        "build_target": False,
        "build_base": True,
        "watch_patterns": ["*.c", "*.h", "*.s", "*.inc"],
        "progress_categories": CATEGORIES,
        "units": objdiff_units,
    }
    (ROOT / "objdiff.json").write_text(json.dumps(config, indent=2) + "\n")
    counts: dict[str, int] = {}
    for u in objdiff_units:
        for cat in u["metadata"]["progress_categories"]:
            if cat in ("game", "psyq"):
                counts[cat] = counts.get(cat, 0) + 1
    summary = ", ".join(f"{k} {v}" for k, v in sorted(counts.items()))
    print(f"objdiff.json: {len(objdiff_units)} unit(s) ({summary}); targets in expected/build/{ver}/")
    return 0


if __name__ == "__main__":
    sys.exit(main())
