"""Unit tests for report denominator auditing, embedded data classification, source-form classification, and code debt."""

from __future__ import annotations

import sys
import tempfile
import unittest
from pathlib import Path

ROOT = Path(__file__).resolve().parents[1]
sys.path.insert(0, str(ROOT / "tools" / "scripts"))

from audit_report import audit, check_ranges
from classify_embedded_data import move_data
from code_debt import count_debt
from gen_objdiff import category_of, retype_embedded_data_in_asm, source_form_of


def function(name: str, address: int, size: int, match: float = 100.0) -> dict:
    return {
        "name": name,
        "address": str(address),
        "size": str(size),
        "fuzzy_match_percent": match,
    }


class ReportAuditAndDebtTests(unittest.TestCase):
    def test_missing_linked_unit_fails_before_reading_objects(self):
        with self.assertRaisesRegex(ValueError, "linked"):
            audit({"units": []}, {"src/main/missing.c"}, ROOT)

    def test_unreported_nonzero_bytes_fail_even_with_matching_function(self):
        with self.assertRaisesRegex(ValueError, "nonzero"):
            check_ranges([function("first", 0, 4)], b"ABCDhidden")

    def test_overlap_cannot_inflate_denominator(self):
        with self.assertRaisesRegex(ValueError, "overlapping"):
            check_ranges(
                [function("first", 0, 8), function("second", 4, 4)],
                b"ABCDEFGH",
            )

    def test_zero_padding_is_explicitly_counted(self):
        self.assertEqual(
            check_ranges([function("first", 4, 4)], bytes(4) + b"ABCD" + bytes(8)),
            (4, 12),
        )

    def test_embedded_data_is_covered_without_counting_as_code_or_padding(self):
        self.assertEqual(
            check_ranges(
                [function("Code", 0, 4)],
                b"codeDATA" + bytes(4),
                [function("Data", 4, 4)],
            ),
            (4, 4),
        )

    def test_move_data_reclassifies_whole_symbol_only(self):
        unit = {
            "metadata": {"complete": False},
            "measures": {
                "total_code": "12",
                "matched_code": "12",
                "complete_code": "0",
                "total_functions": 2,
                "matched_functions": 2,
                "total_data": "0",
                "matched_data": "0",
            },
            "functions": [
                function("func_80034504", 0, 8),
                function("func_80034520", 8, 4),
            ],
        }
        ranges = [{"name": "func_80034520", "address": "8", "size": "4"}]
        raw = b"\x01" * 8 + b"\x00" * 4
        move_data(unit, ranges, raw, raw)
        self.assertEqual(unit["measures"]["total_code"], "8")
        self.assertEqual(unit["measures"]["matched_code"], "8")
        self.assertEqual(unit["measures"]["total_functions"], 1)
        self.assertEqual(unit["measures"]["matched_functions"], 1)
        self.assertEqual(unit["measures"]["total_data"], "4")
        self.assertEqual(unit["measures"]["matched_data"], "4")
        self.assertEqual([f["name"] for f in unit["functions"]], ["func_80034504"])

    def test_retype_embedded_data_in_asm_replaces_glabel_with_dlabel(self):
        sample = (
            "nonmatching func_80034520, 0x4\n\n"
            "glabel func_80034520\n"
            "    nop\n"
            "endlabel func_80034520\n"
        )
        with tempfile.TemporaryDirectory() as tmp:
            p = Path(tmp) / "gte_render.s"
            p.write_text(sample)
            retype_embedded_data_in_asm(p, {"func_80034520": [4224, 4]})
            out = p.read_text()
        self.assertNotIn("nonmatching func_80034520", out)
        self.assertIn("dlabel func_80034520", out)
        self.assertIn("enddlabel func_80034520", out)

    def test_source_form_and_category_classification(self):
        self.assertEqual(category_of("engine/state"), "game")
        self.assertEqual(category_of("sdk/libspu/voice_update"), "psyq")
        with tempfile.TemporaryDirectory() as tmp:
            p = Path(tmp) / "unit.c"
            p.write_text('#include "common.h"\nextern s32 x __asm__("D_80056400");\nint f(void) { return x; }\n')
            self.assertEqual(source_form_of(p), "source_c")
            p.write_text('#include "common.h"\nvoid f(void) { register int v asm("$2"); asm volatile(""); }\n')
            self.assertEqual(source_form_of(p), "source_inline")
            p.write_text('#include "common.h"\nHANDWRITTEN_ASM("src/main/engine/gte_asm", func_800334A0);\n')
            self.assertEqual(source_form_of(p), "source_assembly")
            p.write_text('#include "common.h"\nasm(".include \\"macro.inc\\"\\nglabel foo\\njr $ra\\nnop\\nendlabel foo");\n')
            self.assertEqual(source_form_of(p), "source_assembly")

    def test_code_debt_counts_scaffolding_families(self):
        sample_c = (
            '/* comment with INCLUDE_ASM("ignored", f) */\n'
            'extern s32 alias_sym __asm__("D_80056400");\n'
            'HANDWRITTEN_ASM("src/main/engine/gte_asm", func_800334A0);\n'
            'void f(u8 *p) {\n'
            '    register s32 v asm("$4");\n'
            '    asm volatile("");\n'
            '    v = *(s32 *)(p + 0x10) + p[-1] + D_80056400;\n'
            '}\n'
        )
        sample_h = 'extern s32 hdr_alias __asm__("D_80056404");\n'
        with tempfile.TemporaryDirectory() as src_dir, tempfile.TemporaryDirectory() as hdr_dir:
            (Path(src_dir) / "sample.c").write_text(sample_c)
            (Path(hdr_dir) / "sample.h").write_text(sample_h)
            counts = count_debt(Path(src_dir), Path(hdr_dir))
        self.assertEqual(counts["include_asm_blocks"], 0)
        self.assertEqual(counts["handwritten_asm_blocks"], 1)
        self.assertEqual(counts["empty_barriers"], 1)
        self.assertEqual(counts["raw_offset_dereferences"], 1)
        self.assertEqual(counts["negative_pointer_indexing"], 1)
        self.assertEqual(counts["raw_symbol_references"], 2)
        self.assertEqual(counts["asm_symbol_aliases"], 1)
        self.assertEqual(counts["externs_in_c"], 1)
        self.assertEqual(counts["header_asm_aliases"], 1)


if __name__ == "__main__":
    unittest.main()
