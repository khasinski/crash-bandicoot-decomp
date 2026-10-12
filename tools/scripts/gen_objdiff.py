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
import shutil
import subprocess
import sys
from pathlib import Path

import yaml

ROOT = Path(__file__).resolve().parents[2]


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


def main() -> int:
    ap = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument("--version", default="USA")
    ap.add_argument("--python", default=sys.executable)
    args = ap.parse_args()
    ver = args.version

    cfg_path = ROOT / "configs" / ver / "main.yaml"
    cfg = yaml.safe_load(cfg_path.read_text())
    units = units_of(cfg, "c")

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
    subprocess.run([args.python, "-m", "splat", "split", str(exp_cfg)], cwd=ROOT, check=True,
                   stdout=subprocess.DEVNULL)

    as_ = cross() + "as"

    def assemble(src: Path, target: Path) -> None:
        target.parent.mkdir(parents=True, exist_ok=True)
        subprocess.run([as_, "-EL", "-G0", "-march=r3000", "-mtune=r3000", "-no-pad-sections",
                        "-I", str(ROOT / "include"), "-I", str(src.parent), "-o", str(target), str(src)],
                       check=True)

    objdiff_units = []
    for unit in units:
        src = ROOT / "expected" / "asm" / ver / "main" / f"{unit}.s"
        target = ROOT / "expected" / "build" / ver / "src" / "main" / f"{unit}.c.o"
        assemble(src, target)
        objdiff_units.append({
            "name": unit,
            "target_path": str(target.relative_to(ROOT)),
            "base_path": f"build/{ver}/src/main/{unit}.c.o",
            "metadata": {"source_path": f"src/main/{unit}.c", "progress_categories": ["game"]},
        })

    # Code still only in split assembly: target-only units, so progress is
    # measured against the whole executable rather than just the C units.
    for unit in units_of(cfg, "asm"):
        src = ROOT / "expected" / "asm" / ver / "main" / f"{unit}.s"
        target = ROOT / "expected" / "build" / ver / "asm" / f"{unit}.s.o"
        assemble(src, target)
        objdiff_units.append({
            "name": f"asm/{unit}",
            "target_path": str(target.relative_to(ROOT)),
            "metadata": {"progress_categories": ["game"], "auto_generated": True},
        })

    config = {
        "$schema": "https://raw.githubusercontent.com/encounter/objdiff/main/config.schema.json",
        "custom_make": "make",
        "custom_args": ["build"],
        "build_target": False,
        "build_base": True,
        "watch_patterns": ["*.c", "*.h", "*.s", "*.inc"],
        "progress_categories": [{"id": "game", "name": "Game"}],
        "units": objdiff_units,
    }
    (ROOT / "objdiff.json").write_text(json.dumps(config, indent=2) + "\n")
    print(f"objdiff.json: {len(objdiff_units)} unit(s); targets in expected/build/{ver}/")
    return 0


if __name__ == "__main__":
    sys.exit(main())
