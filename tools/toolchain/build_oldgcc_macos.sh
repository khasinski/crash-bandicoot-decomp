#!/bin/bash
# Build one of decompals/old-gcc's Linux-only PSX compilers natively on macOS.
#   tools/toolchain/build_oldgcc_macos.sh 2.6.3
#
# 2.5.7 is not supported: its sources use K&R <varargs.h> (va_alist) for every
# diagnostic function, which cannot work under the arm64 Darwin ABI without
# converting them all to stdarg. cc.sh runs old-gcc's Linux 2.5.7 in Docker.
# Follows old-gcc's gcc-<ver>-psx.Dockerfile patch set plus the host
# adaptations of its gcc-2.7.2-psx-macos.sh, and fixes LP64 pointer
# truncation in mips.h. Output: tools/toolchain/gcc-<ver>-psx/{cpp,cc1}.
#
# Validated for 2.6.3: assembly output identical to old-gcc's Linux release on
# 363/364 rage-pc translation units (the odd one is a unit that fails to
# compile on both, differing only in error recovery).
set -euo pipefail
VER="${1:?usage: $0 2.6.3}"
[ "$VER" = 2.6.3 ] || { echo "unsupported version $VER (macOS supports 2.6.3)" >&2; exit 2; }
ROOT="$(cd "$(dirname "$0")/../.." && pwd)"
OUT="$ROOT/tools/toolchain/gcc-$VER-psx"
OLDGCC_REV="${OLDGCC_REV:-master}"
WORK="${WORK:-$(mktemp -d)}"
[ -n "${KEEP_WORK:-}" ] || trap 'rm -rf "$WORK"' EXIT
export PATH="/usr/bin:/bin:/usr/sbin:/sbin:$PATH"
unset CC CXX

cd "$WORK"
git clone -q --depth 1 --branch "$OLDGCC_REV" https://github.com/decompals/old-gcc
P="$WORK/old-gcc/patches"

case "$VER" in
2.6.3)
    curl -fsSL https://mirrors.slackware.com/slackware/slackware-2.2.0/source/d/gcc/gcc-2.6.3.tar.gz | tar xz
    cd gcc-2.6.3
    chmod -R u+w .
    sed -i '' 's/include <varargs\.h>/include <stdarg\.h>/g' *.c
    patch -u -p1 obstack.h -i "$P/obstack-2.7.2.h.patch"
    patch -u -p1 cp/g++.c  -i "$P/g++-2.6.3.c.patch"
    patch -su -p1 < "$P/psx-2.5.7.patch"
    touch -c cp/parse.y cp/parse.h cp/parse.c
    ;;
*) echo "unsupported version $VER" >&2; exit 2 ;;
esac

# sdbout's <syms.h> guard (old-gcc's sdbout patch does not apply with BSD patch).
sed -i '' 's/!defined(WINNT)$/!defined(WINNT) \&\& !defined(__APPLE__)/' sdbout.c
for f in gcc.c g++.c cp/g++.c; do
    [ -f "$f" ] && sed -i '' 's/^extern int sys_nerr;/extern const int sys_nerr;/' "$f"
done
# mips.h casts obstack pointers through int, truncating them on LP64 hosts.
sed -i '' 's/define __PTR_TO_INT(P) ((int)(P))/define __PTR_TO_INT(P) ((long)(P))/; s/define __INT_TO_PTR(P) ((char \*)(P))/define __INT_TO_PTR(P) ((char *)(long)(P))/' config/mips/mips.h
touch insn-config.h

curl -fsL "https://raw.githubusercontent.com/gcc-mirror/gcc/74af13c174714dd3b9f1ded4b39955f003c16361/config.guess" -o config.guess
curl -fsL "https://raw.githubusercontent.com/gcc-mirror/gcc/6fad101f3063d722e3348d07dc93cf737f8709e4/config.sub" -o config.sub
chmod +x config.guess config.sub
sed -i '' 's/| hiux\* | abug | nacl\*/| psx* \\\
'"$(printf '\t')"'     | hiux* | abug | nacl*/' config.sub
cp "$P/xm-darwin.h" config/
awk '/^\t\*\)$/ { buf=$0; next }
     buf != "" { if (!done && /echo.*Configuration.*not supported/) {
       print "\t*-apple-darwin*)"; print "\t\txm_file=xm-darwin.h"
       print "\t\tfixincludes=Makefile.in"; print "\t\t;;"; done=1 }
       print buf; buf="" } { print }' configure > configure.tmp
mv configure.tmp configure; chmod +x configure

# gcc 2.5.7's configure takes the host to be the target unless told otherwise.
HOST="$(./config.guess)"
./configure --target=mips-sony-psx --prefix=/opt/cross --with-endian-little --with-gnu-as \
    --host="$HOST" --build="$HOST"
GCC_CFLAGS="-std=gnu89 -w -Wno-int-conversion -Wno-implicit-function-declaration -Wno-return-mismatch -Wno-incompatible-pointer-types -Dbsd4_4 -Dmips -DHAVE_STRERROR -include stdlib.h -include string.h -include unistd.h ${EXTRA_CFLAGS:-}"
# The old Makefiles race on generated insn-*.h under -j; finish serially.
make -j"$(sysctl -n hw.ncpu)" cpp cc1 CFLAGS="$GCC_CFLAGS" || make cpp cc1 CFLAGS="$GCC_CFLAGS"

T="$WORK/old-gcc/tests"
./cc1 -quiet -O2 "$T/little_endian.c" -o le.s && grep -E 'lbu\s\$2,0\(\$4\)' le.s
{ ./cc1 -quiet -help </dev/null 2>&1 || true; } | grep -q -- -msoft-float

mkdir -p "$OUT"
cp cpp cc1 "$OUT/"
echo "gcc-$VER-psx installed in $OUT"
