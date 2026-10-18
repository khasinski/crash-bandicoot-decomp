import hashlib
import struct
import tempfile
import unittest
from pathlib import Path

from tools.scripts.gool_lisp import (
    EID_CHARSET,
    EID_NONE,
    LINK_NAMES,
    REG_NAMES,
    compile_gool_source,
    decode_eid,
    decode_gop,
    decode_reg,
    decompile_gool_entry,
    encode_eid,
    encode_gop,
    encode_reg,
    extract_gool_entries_from_nsf,
    is_probable_eid,
    main as gool_cli_main,
)


class TestGoolLisp(unittest.TestCase):
    def test_eid_roundtrip(self) -> None:
        known = {
            "WillC": 0x7492AACD,
            "BoxsC": 0x4AC42E4D,
            "DoctC": 0x4EC18ECD,
            "FruiC": 0x52DBC94D,
            "NONE!": EID_NONE,
        }
        for name, expected in known.items():
            encoded = encode_eid(name)
            self.assertEqual(encoded, expected)
            self.assertEqual(decode_eid(encoded), name)
            self.assertTrue(is_probable_eid(encoded))

        # Test all 64 characters in 5-char windows
        for i in range(0, len(EID_CHARSET) - 5):
            sample = EID_CHARSET[i : i + 5]
            w = encode_eid(sample)
            self.assertEqual(decode_eid(w), sample)

        # Even integers are not EIDs
        self.assertIsNone(decode_eid(0))
        self.assertIsNone(decode_eid(0x100))
        self.assertFalse(is_probable_eid(1))

    def test_reg_and_gop_roundtrip(self) -> None:
        for reg_idx in range(0x80):
            name = decode_reg(reg_idx)
            self.assertEqual(encode_reg(name), reg_idx)

        # Test all valid 12-bit GOP values used by the VM
        test_gops = (
            list(range(0x000, 0x010))       # data[idx]
            + list(range(0x400, 0x410))     # ext[idx]
            + list(range(0x800, 0xA00, 7))  # 9-bit signed imm << 8
            + list(range(0xA00, 0xB00, 5))  # 8-bit signed imm << 4
            + list(range(0xB00, 0xB80, 3))  # 7-bit signed fp[off]
            + [0xBE0, 0xBF0]                # null, var-rate
            + list(range(0xC00, 0xE00, 9))  # <link>.<reg>
            + list(range(0xE00, 0xEA0))     # direct self reg / field-N
        )
        for gop in test_gops:
            sym = decode_gop(gop)
            re_encoded = encode_gop(sym)
            self.assertEqual(
                re_encoded,
                gop,
                f"GOP 0x{gop:03X} decoded to {sym!r} but re-encoded to 0x{re_encoded:03X}",
            )

    def test_synthetic_gool_roundtrip_and_folding(self) -> None:
        source = """\
(defgool TestC :eid 'WillC :items 6
  (header
    (type 0)
    (category 0x100)
    (unk08 1)
    (sp-offset 70)
    (event-count 8)
    (unk14 2))
  (data
    (0 'WillC)
    (1 'fs50A)
    (2 0x00019000)
    (3 0x00000010)
  )
  (events
    (0x01 state_1)
    (0x03 (code loc_000D))
  )
  (subtypes state_0 state_1 none)
  (states
    (defstate state_0 :status-c 0x00000001 :flags 0x00000000 :extern 0 :event none :trans loc_000B :code loc_0000)
    (defstate state_1 :status-c 0x00000002 :flags 0x00000010 :extern 0 :event none :trans none :code loc_0009)
  )
  (anims
    (vertex-anim :offset 0x000 :frames 10 :eid 'WW10V)
    (sprite-anim :offset 0x008 :eid 'WillT :frames ((0x80808080 0x04910110) (0x80808080 0x04910108)))
    (font :offset 0x020 :eid 'Fon0T :glyphs ((0x00000000 0x00000000 400 420)))
    (text-anim :offset 0x034 :eid '1038I :font-offset 0x8 :strings ("HELLO" "CRASH"))
    (frag-anim :offset 0x04C :frames 1 :eid 'WillT :frags-per-frame 1 :frags ((0x80808080 0x04910110 -10 -10 10 10)))
  )
  (code
  (label loc_0000)
    (move (add (mul 16 data[2]) x) x)
    (beqz (and (equ subtype 0) (gt y player.y)) loc_0009)
    (anim-seq 0x000 0 1 pos)
    (play-sound 256 data[1])
  (label loc_0009)
    (spawn 34 0 0 1)
    (ret)
  (label loc_000B)
    (path-follow trans rot path-progress)
    (ret)
  (label loc_000D)
    (event-ret-accept)
  )
)
"""
        binary1 = compile_gool_source(source)
        decompiled = decompile_gool_entry(binary1)
        self.assertIn("(move (add (mul 16 data[2]) x) x)", decompiled)
        self.assertIn("(beqz (and (equ subtype 0) (gt y player.y)) loc_0009)", decompiled)
        binary2 = compile_gool_source(decompiled)
        self.assertEqual(binary1, binary2)

        # Also test CLI decompile, compile, and decompile-nsf on a synthetic 64KB 0x1234 NSF page
        with tempfile.TemporaryDirectory() as tmp:
            tmp_path = Path(tmp)
            bin_file = tmp_path / "TestC.bin"
            gool_file = tmp_path / "TestC.gool"
            rebin_file = tmp_path / "TestC_re.bin"
            bin_file.write_bytes(binary1)

            self.assertEqual(gool_cli_main(["decompile", str(bin_file), "-o", str(gool_file)]), 0)
            self.assertEqual(gool_cli_main(["compile", str(gool_file), "-o", str(rebin_file)]), 0)
            self.assertEqual(rebin_file.read_bytes(), binary1)

            # Build a synthetic 64KB uncompressed NSF page containing binary1
            page = bytearray(0x10000)
            struct.pack_into("<HHIII", page, 0, 0x1234, 0, 1, 1, 0)
            e_start = 24
            e_end = e_start + len(binary1)
            struct.pack_into("<II", page, 16, e_start, e_end)
            page[e_start:e_end] = binary1
            nsf_file = tmp_path / "S0000001.NSF"
            nsf_file.write_bytes(page)

            extracted = extract_gool_entries_from_nsf(bytes(page))
            self.assertEqual(len(extracted), 1)
            self.assertEqual(extracted[0][0], "WillC")
            self.assertEqual(extracted[0][2], binary1)

            out_dir = tmp_path / "out_gool"
            self.assertEqual(gool_cli_main(["decompile-nsf", str(nsf_file), "-o", str(out_dir)]), 0)
            self.assertTrue((out_dir / "WillC.gool").is_file())

    def test_retail_disc_all_gool_entries_roundtrip(self) -> None:
        nsf_dir = Path(__file__).resolve().parents[1] / "build" / "extract" / "USA" / "files"
        if not nsf_dir.is_dir():
            self.skipTest("Retail extracted NSF files not present")

        nsf_files = sorted(nsf_dir.rglob("*.NSF"))
        if not nsf_files:
            self.skipTest("No .NSF files found in build/extract/USA/files")

        unique_names = set()
        unique_blobs = {}
        for nsf_file in nsf_files:
            for name, _eid, raw in extract_gool_entries_from_nsf(nsf_file.read_bytes(), str(nsf_file)):
                unique_names.add(name)
                sha = hashlib.sha1(raw).hexdigest()
                if sha not in unique_blobs:
                    unique_blobs[sha] = (name, raw)

        self.assertEqual(len(unique_names), 60)
        for sha, (name, raw) in unique_blobs.items():
            gool_text = decompile_gool_entry(raw)
            recompiled = compile_gool_source(gool_text)
            self.assertEqual(
                hashlib.sha1(recompiled).hexdigest(),
                sha,
                f"Round-trip SHA-1 mismatch on {name}",
            )


if __name__ == "__main__":
    unittest.main()
