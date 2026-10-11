"""Instruction alignment must count edits, not shifted positions."""
import importlib.util
from pathlib import Path
import unittest

spec = importlib.util.spec_from_file_location(
    'probe_match', Path(__file__).resolve().parents[1] / 'tools/scripts/probe_match.py')
probe = importlib.util.module_from_spec(spec)
spec.loader.exec_module(probe)

class InstructionDistanceTests(unittest.TestCase):
    def test_insertion_does_not_count_shifted_suffix(self):
        distance, edits = probe.levenshtein([10, 20, 30], [0] * 3, [10, 99, 20, 30])
        self.assertEqual(distance, 1)
        self.assertEqual(edits, [('insert', 1, 1)])

    def test_deletion_and_substitution(self):
        self.assertEqual(probe.levenshtein([10, 99, 20], [0] * 3, [10, 20])[0], 1)
        self.assertEqual(probe.levenshtein([10, 99], [0] * 2, [10, 20])[0], 1)

    def test_relocated_instruction_matches_after_insertion(self):
        self.assertEqual(probe.levenshtein([0x0C123456], [0x03FFFFFF],
                                         [0, 0x0C654321])[0], 1)

    def test_empty_and_identical(self):
        self.assertEqual(probe.levenshtein([], [], [10])[0], 1)
        self.assertEqual(probe.levenshtein([10], [0], [10]), (0, []))
