#!/usr/bin/env python3
"""Print the progress summary and category tables of an objdiff report.json."""

from __future__ import annotations

import json
import sys
from pathlib import Path

ROOT = Path(__file__).resolve().parents[2]
BADGES = ROOT / "docs" / "badges"
CATEGORY_NAMES = {"game": "Game code", "psyq": "PsyQ libraries"}


def color(percent: float) -> str:
    if percent >= 100.0:
        return "brightgreen"
    if percent >= 90.0:
        return "green"
    if percent >= 60.0:
        return "yellow"
    return "blue"


def main() -> int:
    report_path = Path(sys.argv[1] if len(sys.argv) > 1 else "build/USA/report.json")
    report = json.loads(report_path.read_text())
    m = report["measures"]
    code, matched = int(m.get("total_code", 0)), int(m.get("matched_code", 0))
    funcs, mfuncs = int(m.get("total_functions", 0)), int(m.get("matched_functions", 0))
    code_pct = 100 * matched / max(code, 1)
    func_pct = 100 * mfuncs / max(funcs, 1)

    print(f"code      {matched:7d} / {code:7d} bytes  {code_pct:6.2f}%")
    print(f"functions {mfuncs:7d} / {funcs:7d}        {func_pct:6.2f}%")

    categories = {c["id"]: c for c in report.get("categories", [])}
    if any(k in categories for k in CATEGORY_NAMES):
        print()
        print("| Scope | Functions | Code bytes | Units |")
        print("|---|---:|---:|---:|")
        for cid, label in CATEGORY_NAMES.items():
            if cid not in categories:
                continue
            cm = categories[cid]["measures"]
            cf_done, cf_tot = int(cm.get("matched_functions", 0)), int(cm.get("total_functions", 0))
            cc_done, cc_tot = int(cm.get("matched_code", 0)), int(cm.get("total_code", 0))
            cu_tot = int(cm.get("total_units", 0))
            cf_pct = 100 * cf_done / max(cf_tot, 1)
            cc_pct = 100 * cc_done / max(cc_tot, 1)
            print(f"| {label} | {cf_done} / {cf_tot} ({cf_pct:.2f}%) | {cc_done} / {cc_tot} ({cc_pct:.2f}%) | {cu_tot} |")
        tot_units = int(m.get("total_units", 0))
        print(
            f"| **Whole executable** | **{mfuncs} / {funcs} ({func_pct:.2f}%)** "
            f"| **{matched} / {code} ({code_pct:.2f}%)** | **{tot_units}** |"
        )

    source_cats = [c for c in report.get("categories", []) if c["id"].startswith("source_")]
    if source_cats:
        print()
        print("| Source form | Units | Code bytes in these units |")
        print("|---|---:|---:|")
        for c in source_cats:
            cm = c["measures"]
            cu = int(cm.get("total_units", 0))
            cc = int(cm.get("total_code", 0))
            if cu > 0 or cc > 0:
                print(f"| {c['name']} | {cu} | {cc} |")

    # Public badges contain aggregate numbers only; the retail report stays local.
    BADGES.mkdir(parents=True, exist_ok=True)
    for label, done, total in (("code", matched, code), ("functions", mfuncs, funcs)):
        pct = 100 * done / max(total, 1)
        badge = {
            "schemaVersion": 1,
            "label": label,
            "message": f"{pct:.2f}%",
            "color": color(pct),
        }
        (BADGES / f"{label}.json").write_text(json.dumps(badge, indent=2) + "\n")
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
