#!/usr/bin/env python3
"""Print the progress summary of an objdiff report.json."""
import json
import sys

report = json.load(open(sys.argv[1] if len(sys.argv) > 1 else "build/USA/report.json"))
m = report["measures"]
code, matched = int(m.get("total_code", 0)), int(m.get("matched_code", 0))
funcs, mfuncs = m.get("total_functions", 0), m.get("matched_functions", 0)
print(f"code      {matched:7d} / {code:7d} bytes  {100 * matched / max(code, 1):6.2f}%")
print(f"functions {mfuncs:7d} / {funcs:7d}        {100 * mfuncs / max(funcs, 1):6.2f}%")

# Public badges contain aggregate numbers only; the retail report stays local.
from pathlib import Path
badges = Path(__file__).resolve().parents[2] / "docs" / "badges"
badges.mkdir(parents=True, exist_ok=True)
for label, done, total in (("code", matched, code), ("functions", mfuncs, funcs)):
    badge = {"schemaVersion": 1, "label": label,
             "message": f"{100 * done / max(total, 1):.2f}%", "color": "blue"}
    (badges / f"{label}.json").write_text(json.dumps(badge, indent=2) + "\n")
