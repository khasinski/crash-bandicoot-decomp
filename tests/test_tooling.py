"""Integration regressions; run after setup, toolchain and split."""
import subprocess
import sys
import tempfile
import unittest
from pathlib import Path

ROOT = Path(__file__).resolve().parents[1]


class ToolingTests(unittest.TestCase):
    def run_probe(self, source):
        return subprocess.run(
            [sys.executable, 'tools/scripts/probe_match.py', str(source)],
            cwd=ROOT, capture_output=True, text=True,
        )

    def test_shell_syntax(self):
        for script in [*ROOT.glob('tools/scripts/*.sh'), *ROOT.glob('tools/toolchain/*.sh')]:
            with self.subTest(script=script.name):
                result = subprocess.run(['bash', '-n', str(script)], capture_output=True, text=True)
                self.assertEqual(result.returncode, 0, result.stderr)

    def test_promoted_functions_have_retail_references(self):
        result = self.run_probe(ROOT / 'src/main/libc/malloc.c')
        self.assertEqual(result.returncode, 0, result.stdout + result.stderr)
        for name in ('LIBC_Free', 'LIBC_Calloc'):
            line = next(line for line in result.stdout.splitlines() if name in line)
            self.assertIn('MATCH', line)

    def test_mode_transition_uses_shared_resource_layouts(self):
        # Score the C function independently of retained assembly/data aliases
        # in the same unit; the retail reference verifies slot stride and order.
        result = subprocess.run(
            [sys.executable, 'tools/scripts/probe_profiles.py',
             'src/main/engine/state.c', '--profile', 'source',
             '--function', 'Title_LoadScreen'],
            cwd=ROOT, capture_output=True, text=True,
        )
        self.assertEqual(result.returncode, 0, result.stdout + result.stderr)
        self.assertIn('Title_LoadScreen: Levenshtein=0', result.stdout)

    def test_mode_setup_uses_verified_storage_owners(self):
        result = subprocess.run(
            [sys.executable, 'tools/scripts/probe_profiles.py',
             'src/main/engine/state.c', '--profile', 'source',
             '--function', 'Title_LoadNextState'],
            cwd=ROOT, capture_output=True, text=True,
        )
        self.assertEqual(result.returncode, 0, result.stdout + result.stderr)
        self.assertIn('Title_LoadNextState: Levenshtein=0', result.stdout)

    def test_render_mode_initialization_matches_retail(self):
        result = self.run_probe(ROOT / 'src/main/render/mode_initialize.c')
        self.assertEqual(result.returncode, 0, result.stdout + result.stderr)
        self.assertIn('Gfx_InitMatrices', result.stdout)
        self.assertIn('Levenshtein=0', result.stdout)

    def test_sized_extern_gp_assembler_profile(self):
        source = ROOT / 'src/main/engine/grid_rectangle.c'
        result = self.run_probe(source)
        self.assertEqual(result.returncode, 0, result.stdout + result.stderr)
        self.assertIn('MATCH', result.stdout)
        # The exact same C with the default assembler threshold uses a
        # two-instruction absolute load instead of the retail gp load.
        with tempfile.TemporaryDirectory(dir=ROOT) as tmp:
            trial = Path(tmp) / 'grid_rectangle.c'
            trial.write_text(source.read_text().replace('/* GNU_AS_G: 8 */', ''))
            result = self.run_probe(trial)
            self.assertEqual(result.returncode, 1, result.stdout + result.stderr)
            self.assertIn('DIFF', result.stdout)

    def test_m2c_reads_switch_tables_from_shared_rodata(self):
        # This function remains in a shared assembly unit and uses a rodata
        # jump table, exercising both the lookup fallback and table inputs.
        result = subprocess.run(
            ['tools/scripts/m2c.sh', 'Shader_ParamsUpdate'],
            cwd=ROOT, capture_output=True, text=True,
        )
        self.assertEqual(result.returncode, 0, result.stderr)
        self.assertIn('Shader_ParamsUpdate(', result.stdout)
        self.assertIn('switch (', result.stdout)
        self.assertNotIn('Decompilation failure', result.stdout)

    def test_cse_branch_compiler_profile(self):
        source = ROOT / 'src/main/ns/texture_allocate.c'
        result = self.run_probe(source)
        self.assertEqual(result.returncode, 0, result.stdout + result.stderr)
        self.assertIn('Levenshtein=0', result.stdout)
        # Following the jump reuses the earlier zone-pointer load, which
        # removes two retail instructions and changes their scheduling.
        with tempfile.TemporaryDirectory(dir=ROOT) as tmp:
            trial = Path(tmp) / 'texture_allocate.c'
            trial.write_text(source.read_text().replace('-fno-cse-follow-jumps', ''))
            result = self.run_probe(trial)
            self.assertEqual(result.returncode, 1, result.stdout + result.stderr)
            self.assertIn('Levenshtein=5', result.stdout)

    def test_cpu_scheduling_profile(self):
        source = ROOT / 'src/main/libc/malloc.c'
        result = self.run_probe(source)
        self.assertEqual(result.returncode, 0, result.stdout + result.stderr)
        with tempfile.TemporaryDirectory(dir=ROOT) as tmp:
            trial = Path(tmp) / 'malloc.c'
            trial.write_text(source.read_text().replace('/* GCC_CPU: r4000 */', ''))
            result = self.run_probe(trial)
            self.assertEqual(result.returncode, 1, result.stdout + result.stderr)
            line = next(line for line in result.stdout.splitlines() if 'LIBC_Malloc' in line)
            self.assertIn('Levenshtein=2', line)

    def test_strength_reduction_compiler_profile(self):
        source = ROOT / 'src/main/sdk/libspu/spu_initialize.c'
        result = self.run_probe(source)
        self.assertEqual(result.returncode, 0, result.stdout + result.stderr)
        self.assertIn('Levenshtein=0', result.stdout)
        with tempfile.TemporaryDirectory(dir=ROOT) as tmp:
            trial = Path(tmp) / 'spu_initialize.c'
            trial.write_text(source.read_text().replace('-fno-strength-reduce', ''))
            result = self.run_probe(trial)
            self.assertEqual(result.returncode, 1, result.stdout + result.stderr)
            self.assertIn('Levenshtein=17', result.stdout)

    def test_promoted_function_with_switch_tables_has_retail_reference(self):
        source = ROOT / 'src/main/sdk/libspu/voice_attributes_set.c'
        result = self.run_probe(source)
        self.assertEqual(result.returncode, 0, result.stdout + result.stderr)
        self.assertIn('Levenshtein=0', result.stdout)

    def test_m2c_finds_retail_reference_for_compiled_function(self):
        # Compiled functions no longer have INCLUDE_ASM files in the main
        # split; their retail instructions are available in expected/.
        result = subprocess.run(
            ['tools/scripts/m2c.sh', 'Card_EntryNameIs949'],
            cwd=ROOT, capture_output=True, text=True,
        )
        self.assertEqual(result.returncode, 0, result.stderr)
        self.assertIn('Card_EntryNameIs949(', result.stdout)
        self.assertIn('BIOS_StrNCmp(', result.stdout)
        self.assertNotIn('Decompilation failure', result.stdout)

    def test_m2c_reads_switch_table_owned_by_compiled_function(self):
        for function in ('getintr', 'Card_Update'):
            with self.subTest(function=function):
                result = subprocess.run(
                    ['tools/scripts/m2c.sh', function],
                    cwd=ROOT, capture_output=True, text=True,
                )
                self.assertEqual(result.returncode, 0, result.stderr)
                self.assertIn('switch (', result.stdout)
                self.assertNotIn('Decompilation failure', result.stdout)

    def test_probe_rejects_bad_or_unverifiable_code(self):
        sources = {
            'changed': '#include "common.h"\nvoid LIBC_Free(void *ptr) { ((int *)ptr)[-1] |= 2; }\n',
            'unknown': '#include "common.h"\nint Unknown_Probe_Function(void) { return 1; }\n',
            'empty': '#include "common.h"\n',
        }
        # Keep inputs inside the Docker-mounted project tree.
        with tempfile.TemporaryDirectory(dir=ROOT) as tmp:
            for kind, code in sources.items():
                with self.subTest(kind=kind):
                    source = Path(tmp) / (kind + '.c')
                    source.write_text(code)
                    result = self.run_probe(source)
                    self.assertEqual(result.returncode, 1, result.stdout + result.stderr)
                    self.assertIn('DIFF' if kind == 'changed' else 'ERROR', result.stdout)

    def test_asm_and_macro_changes_rebuild_c_object(self):
        for dependency, source in (
            ('src/main/engine/gte_asm/Gte_RCalcObjectRotMatrix.s',
             'src/main/engine/gte_render.c'),
            (str(ROOT / 'include/gte_macros.inc'), 'src/main/libc/malloc.c'),
        ):
            with self.subTest(dependency=dependency):
                result = subprocess.run(
                    ['make', '-n', '-W', dependency, 'build'],
                    cwd=ROOT, capture_output=True, text=True,
                )
                self.assertEqual(result.returncode, 0, result.stderr)
                self.assertIn('tools/scripts/cc.sh ' + source, result.stdout)


if __name__ == '__main__':
    unittest.main()
