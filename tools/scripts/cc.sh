#!/usr/bin/env bash
# Compile one C file: gcc-2.6.3-psx cpp -> cc1 -> maspsx -> GNU as.
# Usage: cc.sh <input.c> <output.o>
#
# Per-file overrides, written as a comment anywhere in the source:
#   /* GCC_VERSION: 2.6.3 */      use tools/toolchain/gcc-2.6.3-psx instead
#   /* GCC_CPU: r4000 */         select the compiler scheduling profile
#   /* CC1_FLAGS: -O1 */          replace -O2 (also -O3)
#   /* CC1_FLAGS: -O2 -fno-cse-follow-jumps */  preserve loads across jump paths
#   /* CC1_FLAGS: -O2 -fno-strength-reduce */  preserve loop address arithmetic
#   /* ASPSX_VERSION: 2.56 */     maspsx --aspsx-version
#   /* GNU_AS_G: 8 */            let GNU as address sized externs through gp
# Environment overrides: CRASH_GCC_VERSION, CRASH_GCC_CPU, CRASH_ASPSX_VERSION, CRASH_G,
# CRASH_CC1_FLAGS (replaces the whole cc1 flag set; for compiler experiments).
set -euo pipefail

# Also accepts decomp-permuter's form, cc.sh [-I dir|-D x ...] input.c -o output.o;
# -I/-D are only there for permuter's own preprocessing and are ignored here.
IN=""; OUT=""
while [ "$#" -gt 0 ]; do
    case "$1" in
        -o) OUT="$2"; shift 2 ;;
        -I|-D) shift 2 ;;
        -I*|-D*) shift ;;
        *) if [ -z "$IN" ]; then IN="$1"; elif [ -z "$OUT" ]; then OUT="$1"; else IN=""; break; fi; shift ;;
    esac
done
if [ -z "$IN" ] || [ -z "$OUT" ]; then
    echo "usage: $0 input.c output.o" >&2
    exit 2
fi
ROOT="$(cd "$(dirname "$0")/../.." && pwd)"
TC="$ROOT/tools/toolchain"

# gcc 2.5.7-psx is the only old-gcc build that reproduces the retail prologue
# (ra saved first, no scheduling into the frame setup); see docs/COMPILER.md.
GCC_VERSION="${CRASH_GCC_VERSION:-$(sed -nE 's/.*GCC_VERSION:[[:space:]]*([0-9.]+).*/\1/p' "$IN" | head -1)}"
GCC_VERSION="${GCC_VERSION:-2.5.7}"
GCC_DIR="$TC/gcc-$GCC_VERSION-psx"
GCC_CPU="${CRASH_GCC_CPU:-$(sed -nE 's/.*GCC_CPU:[[:space:]]*([A-Za-z0-9]+).*/\1/p' "$IN" | head -1)}"
GCC_CPU="${GCC_CPU:-3000}"
case "$GCC_CPU" in
    3000|r2000|r3000|r4000|r6000) ;;
    *) echo "unsupported GCC_CPU: $GCC_CPU" >&2; exit 1 ;;
esac
ASPSX_VERSION="${CRASH_ASPSX_VERSION:-$(sed -nE 's/.*ASPSX_VERSION:[[:space:]]*([0-9.]+).*/\1/p' "$IN" | head -1)}"
ASPSX_VERSION="${ASPSX_VERSION:-2.34}"
# gp-relative small data: retail code addresses .sdata/.sbss through $gp.
G="${CRASH_G:-8}"
# Keep the existing expansion profile by default. GNU as can also use the
# compiler's .extern SYMBOL,SIZE declarations when the source requests it.
GNU_AS_G="$(sed -nE 's/.*GNU_AS_G:[[:space:]]*([0-9]+).*/\1/p' "$IN" | head -1)"
GNU_AS_G="${GNU_AS_G:-0}"
case "$GNU_AS_G" in 0|8) ;; *) echo "unsupported GNU_AS_G: $GNU_AS_G" >&2; exit 1 ;; esac


OPT="-O2"
if grep -qE 'CC1_FLAGS:.*-O1' "$IN"; then OPT="-O1"; fi
if grep -qE 'CC1_FLAGS:.*-O3' "$IN"; then OPT="-O3"; fi
EXTRA_CC1_FLAGS=""
if grep -qE 'CC1_FLAGS:.*-fno-cse-follow-jumps([[:space:]]|$)' "$IN"; then
    EXTRA_CC1_FLAGS="-fno-cse-follow-jumps"
fi
if grep -qE 'CC1_FLAGS:.*-fno-strength-reduce([[:space:]]|$)' "$IN"; then
    EXTRA_CC1_FLAGS="$EXTRA_CC1_FLAGS -fno-strength-reduce"
fi

if [ -n "${CROSS:-}" ]; then :
elif command -v mipsel-none-elf-as >/dev/null; then CROSS=mipsel-none-elf-
else CROSS=mipsel-linux-gnu-
fi
PYTHON="${PYTHON:-$ROOT/.venv/bin/python}"
[ -x "$PYTHON" ] || PYTHON=python3

for tool in "$GCC_DIR/cpp" "$GCC_DIR/cc1" "$TC/maspsx/maspsx.py"; do
    if [ ! -e "$tool" ]; then
        echo "crash-pc: missing $tool; run tools/toolchain/setup.sh" >&2
        exit 1
    fi
done
mkdir -p "$(dirname "$OUT")"

# Linux-only compiler builds (old-gcc ships no macOS 2.5.7/2.6.0) run in an
# i386 container; the native Mach-O builds are used whenever they exist.
run_tool() {
    local tool="$1"; shift
    if "$tool" --version </dev/null >/dev/null 2>&1 || file "$tool" | grep -q Mach-O; then
        "$tool" "$@"
    elif command -v docker >/dev/null 2>&1; then
        docker run --rm -i --platform linux/386 -v "$ROOT:$ROOT" -w "$PWD" \
            i386/alpine:3.20 "$tool" "$@"
    else
        echo "crash-pc: $tool is not runnable here and Docker is unavailable" >&2
        exit 1
    fi
}

# Preprocess with a native cpp: everything is -undef'd and spelled out, so the
# 2.x cpp builds behave the same and the Linux-only ones need no container.
CPP="$GCC_DIR/cpp"
file "$CPP" | grep -q Mach-O || [ "$(uname -s)" != Darwin ] || CPP="$TC/gcc-2.6.3-psx/cpp"

# -MD writes "$OUT.d" so the Makefile rebuilds dependents of an edited header.
# gcc 2.x cpp has no -MT; its rule names "<basename>.o", fixed up below.
"$CPP" -undef -D__GNUC__=2 -D__OPTIMIZE__ -Dmips -D__mips__ \
    -D__LANGUAGE_C -D_LANGUAGE_C -DLANGUAGE_C -Dpsx -D__psx__ \
    -I"$ROOT/include" -I"$ROOT/src/main" -MD "$OUT.d" "$IN" \
  | run_tool "$GCC_DIR/cc1" ${CRASH_CC1_FLAGS:--quiet -mcpu=$GCC_CPU -mgas -msoft-float -g -gcoff $OPT $EXTRA_CC1_FLAGS -G$G -funsigned-char -w} -o - \
  | "$PYTHON" "$TC/maspsx/maspsx.py" --expand-div --aspsx-version="$ASPSX_VERSION" \
        --force-stdin -G"$G" \
  | "${CROSS}as" -EL -march=r3000 -mtune=r3000 -no-pad-sections -G"$GNU_AS_G" \
        -I"$ROOT" -I"$ROOT/include" --MD "$OUT.asm.d" -o "$OUT" -
sed -i.bak "1s|^[^:]*:|$OUT:|" "$OUT.d" && rm -f "$OUT.d.bak"
