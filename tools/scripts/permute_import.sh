#!/usr/bin/env bash
# Import a function into decomp-permuter and keep the source file's compiler
# profile. import.py preprocesses the C file, which drops the GCC_VERSION /
# CC1_FLAGS / ASPSX_VERSION / GNU_AS_G / GCC_CPU comments that cc.sh reads, so
# without this every permutation would build with the default compiler.
#   tools/scripts/permute_import.sh <source.c> <function.s>
set -euo pipefail
ROOT="$(cd "$(dirname "$0")/../.." && pwd)"
SRC="$1"
ASM="$2"
FUNC="$(basename "$ASM" .s)"
PY="${PY:-$ROOT/.venv/bin/python}"

"$PY" "$ROOT/tools/toolchain/decomp-permuter/import.py" "$SRC" "$ASM"

DIR="$ROOT/nonmatchings/$FUNC"
PROFILE="$(grep -hE '/\*[[:space:]]*(GCC_VERSION|CC1_FLAGS|ASPSX_VERSION|GNU_AS_G|GCC_CPU):' "$SRC" || true)"
[ -n "$PROFILE" ] || exit 0
printf '%s\n' "$PROFILE" > "$DIR/profile.h"
cat > "$DIR/compile.sh" <<SH
#!/usr/bin/env bash
set -euo pipefail
INPUT="\$(realpath "\$1")"
OUTPUT="\$(realpath "\$3")"
PROFILED="\$(mktemp -t permuter-XXXXXX).c"
trap 'rm -f "\$PROFILED"' EXIT
cat "$DIR/profile.h" "\$INPUT" > "\$PROFILED"
cd "$ROOT"
tools/scripts/cc.sh -I include -I src/main "\$PROFILED" -o "\$OUTPUT"
SH
chmod +x "$DIR/compile.sh"
# Rebuild base.o with the profile so the starting score is meaningful.
"$DIR/compile.sh" "$DIR/base.c" -o "$DIR/base.o"
echo "Applied source compiler profile: $(echo "$PROFILE" | tr '\n' ' ')"
