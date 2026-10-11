#!/usr/bin/env python3
"""Try known stock compiler profiles and rank instruction Levenshtein distance."""
import argparse
import json
import os
from pathlib import Path
import subprocess
import sys
import tempfile

import probe_match as probe

ROOT = Path(__file__).resolve().parents[2]


def main():
    profiles = json.loads((ROOT / 'configs/compiler_profiles.json').read_text())
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('source', type=Path)
    parser.add_argument('--profile', action='append', choices=list(profiles),
                        help='select profiles; default: all known profiles')
    parser.add_argument('--function', help='score only this function')
    parser.add_argument('--version', default='USA')
    args = parser.parse_args()
    source = args.source.resolve()
    if not source.is_file():
        parser.error(f'source not found: {source}')

    # Split the retail reference once for the entire matrix.
    subprocess.run([sys.executable, str(ROOT / 'tools/scripts/gen_objdiff.py'),
                    '--version', args.version], cwd=ROOT, check=True,
                   stdout=subprocess.DEVNULL)
    retail = probe.retail_functions(args.version)
    results = []
    for name in args.profile or profiles:
        env = dict(os.environ)
        # Matrix results must not depend on ambient experimental overrides.
        for key in ('CRASH_GCC_VERSION', 'CRASH_GCC_CPU', 'CRASH_ASPSX_VERSION',
                    'CRASH_GNU_AS_G', 'CRASH_G', 'CRASH_CC1_FLAGS'):
            env.pop(key, None)
        env.update(profiles[name])
        with tempfile.TemporaryDirectory() as tmp:
            obj = Path(tmp) / 'probe.o'
            compiled = subprocess.run(
                [str(ROOT / 'tools/scripts/cc.sh'), str(source), str(obj)],
                cwd=ROOT, env=env, capture_output=True, text=True,
            )
            if compiled.returncode:
                print(f'{name}: compile failed\n{compiled.stderr}', file=sys.stderr)
                continue
            functions = probe.object_functions(obj)
        if args.function:
            functions = {n: data for n, data in functions.items() if n == args.function}
        if not functions:
            print(f'{name}: ERROR: no selected functions', file=sys.stderr)
            continue
        total = 0
        valid = True
        print(f'{name}:')
        for function, (words, masks) in functions.items():
            if function not in retail:
                print(f'  {function}: ERROR: not in retail assembly')
                valid = False
                continue
            distance, _ = probe.levenshtein(words, masks, retail[function])
            total += distance
            print(f'  {function}: Levenshtein={distance}')
        if valid:
            results.append((total, name))
    print('Ranking (sum of instruction Levenshtein distances):')
    for distance, name in sorted(results):
        print(f'  {name}: {distance}')
    return 0 if any(distance == 0 for distance, _ in results) else 1


if __name__ == '__main__':
    sys.exit(main())
