"""Verify recovered layouts with the PS1 compiler, not the host ABI."""
from pathlib import Path
import subprocess
import importlib.util
import os
import shutil
import sys
import tempfile
import unittest

ROOT = Path(__file__).resolve().parents[1]


class LayoutTests(unittest.TestCase):
    def test_recovered_layouts_on_target_abi(self):
        with tempfile.TemporaryDirectory() as tmp:
            result = subprocess.run(
                [str(ROOT / 'tools/scripts/cc.sh'),
                 str(ROOT / 'tests/layout_assertions.c'), str(Path(tmp) / 'layout.o')],
                cwd=ROOT, capture_output=True, text=True,
            )
            self.assertEqual(result.returncode, 0, result.stdout + result.stderr)

    def test_pc_relative_relocation_masks_only_branch_target(self):
        spec = importlib.util.spec_from_file_location(
            'probe_match', ROOT / 'tools/scripts/probe_match.py')
        probe = importlib.util.module_from_spec(spec)
        spec.loader.exec_module(probe)
        cross = os.environ.get('CROSS') or (
            'mipsel-none-elf-' if shutil.which('mipsel-none-elf-as') else 'mipsel-linux-gnu-')
        with tempfile.TemporaryDirectory() as tmp:
            source = Path(tmp) / 'branch.s'
            obj = Path(tmp) / 'branch.o'
            source.write_text(
                '.text\n.set noreorder\n.globl probe_branch\n'
                '.type probe_branch,@function\nprobe_branch:\n'
                'beq $2,$0,external_target\nnop\n.size probe_branch,.-probe_branch\n')
            subprocess.run([cross + 'as', '-EL', '-march=r3000',
                            '-o', str(obj), str(source)], check=True)
            words, masks = probe.object_functions(obj)['probe_branch']
        self.assertEqual(probe.levenshtein(words, masks, [0x10400005, 0])[0], 0)
        self.assertEqual(probe.levenshtein(words, masks, [0x14400005, 0])[0], 1)
        self.assertEqual(probe.levenshtein(words, [0, 0], [0x10400005, 0])[0], 1)

    def test_profile_matrix_finds_sized_extern_profile(self):
        result = subprocess.run(
            [sys.executable, str(ROOT / 'tools/scripts/probe_profiles.py'),
             str(ROOT / 'src/main/engine/grid_rectangle.c'),
             '--profile', 'engine', '--profile', 'engine-gp'],
            cwd=ROOT, capture_output=True, text=True,
        )
        self.assertEqual(result.returncode, 0, result.stdout + result.stderr)
        ranking = result.stdout.split('Ranking (sum of instruction Levenshtein distances):')[1]
        self.assertIn('engine-gp: 0', ranking)
        self.assertNotIn('engine: 0', ranking)

    def test_profile_matrix_rejects_missing_selected_function(self):
        result = subprocess.run(
            [sys.executable, str(ROOT / 'tools/scripts/probe_profiles.py'),
             str(ROOT / 'src/main/engine/grid_rectangle.c'),
             '--profile', 'engine-gp', '--function', 'Unknown_Function'],
            cwd=ROOT, capture_output=True, text=True,
        )
        self.assertEqual(result.returncode, 1, result.stdout + result.stderr)
        self.assertIn('ERROR: no selected functions', result.stderr)
