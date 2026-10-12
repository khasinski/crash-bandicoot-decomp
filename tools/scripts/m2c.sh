#!/usr/bin/env bash
# First-pass C for a function still in assembly: tools/scripts/m2c.sh <FUNC> [m2c flags]
# The project headers are passed as m2c context, so known types/prototypes are used.
set -euo pipefail
ROOT="$(cd "$(dirname "$0")/../.." && pwd)"
FUNC="${1:?usage: $0 <function> [m2c flags]}"; shift
ASM="$(find "$ROOT/asm/USA/main/nonmatchings" -name "$FUNC.s" | head -1)"
if [ -z "$ASM" ]; then
    ASM="$(rg -l --glob '*.s' "^[[:space:]]*glabel[[:space:]]+$FUNC([[:space:]]|$)" "$ROOT/asm/USA/main" | head -1 || true)"
    if [ -z "$ASM" ] && [ -d "$ROOT/expected/asm/USA/main" ]; then
        ASM="$(rg -l --glob '*.s' "^[[:space:]]*glabel[[:space:]]+$FUNC([[:space:]]|$)" "$ROOT/expected/asm/USA/main" | head -1 || true)"
    fi
    if [ -z "$ASM" ]; then
        echo "m2c: no retail assembly for $FUNC; run make split and make report" >&2
        exit 1
    fi
fi
# Switch tables stay in the executable's shared rodata rather than in the
# per-function assembly. Pass them alongside the selected function.
RODATA=()
while IFS= read -r path; do
    RODATA+=("$path")
done < <(find "$ROOT/asm/USA/main" -name '*.rodata.s' | sort)
# C-owned tables have no working assembly file. The retail reference exports
# them separately; avoid passing shared data that is already present above.
EXPECTED_ASM="$ROOT/expected/asm/USA/main"
if [ -d "$EXPECTED_ASM" ]; then
    while IFS= read -r path; do
        relative="${path#"$EXPECTED_ASM"/}"
        if [ ! -f "$ROOT/asm/USA/main/$relative" ]; then
            RODATA+=("$path")
        fi
    done < <(find "$EXPECTED_ASM" -name '*.rodata.s' | sort)
fi
CTX="$(mktemp -t crash-m2c-ctx).c"
trap 'rm -f "$CTX"' EXIT
"$ROOT/tools/toolchain/gcc-2.6.3-psx/cpp" -undef -P -DM2CTX -I"$ROOT/include" -I"$ROOT/src/main" \
    "$ROOT/include/m2c_context.h" > "$CTX"
"$ROOT/.venv/bin/m2c" --target mipsel-gcc-c --context "$CTX" --function "$FUNC" "$@" "$ASM" "${RODATA[@]}"
