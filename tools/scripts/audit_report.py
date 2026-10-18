#!/usr/bin/env python3
"""Validate the report's denominator against every linked code object's .text.

Function names and boundaries are annotations, not independent discoveries.
This gate prevents those annotations from hiding nonzero bytes or counting
the same range twice. Unreported zero padding is permitted and counted.
"""

from __future__ import annotations

import argparse
import json
import sys
from pathlib import Path

from elftools.elf.elffile import ELFFile

sys.path.insert(0, str(Path(__file__).resolve().parent))
from classify_embedded_data import checked_data_ranges, parse_map_placement

ROOT = Path(__file__).resolve().parents[2]


def check_ranges(functions: list[dict], text: bytes, data: list[dict] = ()) -> tuple[int, int]:
    cursor = total = padding = 0
    names = set()
    for function in sorted([*functions, *data], key=lambda f: int(f.get("address", 0))):
        start = int(function.get("address", 0))
        size = int(function.get("size", 0))
        end = start + size
        if function["name"] in names:
            raise ValueError(f"duplicate function name: {function['name']}")
        names.add(function["name"])
        if start < cursor or size <= 0 or end > len(text):
            raise ValueError(f"overlapping, empty or out-of-bounds function range: {function['name']}")
        if any(text[cursor:start]):
            raise ValueError(f"nonzero text bytes omitted before {function['name']} ({cursor:#x}..{start:#x})")
        padding += start - cursor
        if function not in data:
            total += size
        cursor = end
    if any(text[cursor:]):
        raise ValueError(f"nonzero text bytes omitted after final function ({cursor:#x}..{len(text):#x})")
    return total, padding + len(text) - cursor


def linked_code_sources(map_text: str, version: str) -> set[str]:
    prefix = f"build/{version}/"
    placement = parse_map_placement(map_text)
    sources = set()
    for obj, sections in placement.items():
        if not obj.startswith(prefix):
            continue
        if ".text" not in sections or sections[".text"][1] == 0:
            continue
        sources.add(obj[len(prefix) :].removesuffix(".o"))
    return sources


def audit(report: dict, expected_sources: set[str], build: Path) -> tuple[int, int, int]:
    manifest = json.loads((ROOT / "configs/embedded_data.json").read_text())
    code_units = [u for u in report["units"] if int(u["measures"].get("total_code", 0)) > 0]
    actual = [u["metadata"]["source_path"] for u in code_units]
    if len(actual) != len(set(actual)) or set(actual) != expected_sources:
        raise ValueError("report code units differ from linked .text objects")
    total_code = total_functions = padding = 0
    for unit in code_units:
        source = unit["metadata"]["source_path"]
        obj_path = build / (source + ".o")
        with obj_path.open("rb") as handle:
            elf = ELFFile(handle)
            section = elf.get_section_by_name(".text")
            text = section.data() if section else b""
        try:
            data, _ = (
                checked_data_ranges(obj_path, manifest[source])
                if source in manifest
                else ([], b"")
            )
            size, omitted = check_ranges(unit.get("functions", []), text, data)
        except ValueError as error:
            raise ValueError(f"{source}: {error}") from error
        measures = unit["measures"]
        functions = len(unit.get("functions", []))
        if size != int(measures.get("total_code", 0)) or functions != int(
            measures.get("total_functions", 0)
        ):
            raise ValueError(f"{source}: unit totals differ from function ranges")
        total_code += size
        total_functions += functions
        padding += omitted
    if total_code != int(report["measures"]["total_code"]) or total_functions != int(
        report["measures"]["total_functions"]
    ):
        raise ValueError("overall totals differ from audited units")
    if (
        int(report["measures"].get("matched_code", 0)) != total_code
        or int(report["measures"].get("matched_functions", 0)) != total_functions
    ):
        raise ValueError("report code is not an exact match; inspect raw objdiff output")
    return total_functions, total_code, padding


def main() -> None:
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--version", default="USA")
    args = parser.parse_args()
    build = ROOT / "build" / args.version
    sources = linked_code_sources((build / "main.map").read_text(), args.version)
    report = json.loads((build / "report.json").read_text())
    functions, code, padding = audit(report, sources, build)
    print(
        f"report audit: {functions} function ranges, {code} code bytes, "
        f"{padding} zero-padding bytes; all linked code units accounted for"
    )


if __name__ == "__main__":
    main()
