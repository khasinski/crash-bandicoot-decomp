#!/usr/bin/env bash
# Fetch local, unpublished decompilation tooling into tools/toolchain/.
# Nothing fetched here is committed (see .gitignore).
set -euo pipefail
ROOT="$(cd "$(dirname "$0")/../.." && pwd)"
TC="$ROOT/tools/toolchain"
OLDGCC_REL="https://github.com/decompals/old-gcc/releases/download/0.17"
OBJDIFF_VER="v3.8.2"
mkdir -p "$TC/bin"

fetch_gcc() {  # fetch_gcc <version> <asset>
    local dir="$TC/gcc-$1"
    [ -x "$dir/cc1" ] && return
    mkdir -p "$dir"
    curl -fsSL "$OLDGCC_REL/$2" | tar xz -C "$dir"
    chmod +x "$dir"/*
    echo "installed gcc-$1"
}

clone() {  # clone <url> <dir>
    [ -d "$TC/$2/.git" ] && return
    git clone -q --depth 1 "$1" "$TC/$2"
    echo "cloned $2"
}

# gcc-2.5.7-psx is the compiler that reproduces retail (see docs/COMPILER.md).
# old-gcc only builds it for Linux i386; on macOS cc.sh runs it under Docker.
fetch_gcc 2.5.7-psx gcc-2.5.7-psx.tar.gz

case "$(uname -s)" in
  Darwin)
    fetch_gcc 2.7.2-psx gcc-2.7.2-psx-macos.tar.gz
    fetch_gcc 2.8.1-psx gcc-2.8.1-psx-macos.tar.gz
    # Native 2.6.3: also supplies the preprocessor cc.sh uses on macOS.
    if [ ! -x "$TC/gcc-2.6.3-psx/cc1" ]; then
        echo "gcc-2.6.3-psx: no macOS release; building from source (~1 min)"
        "$TC/build_oldgcc_macos.sh" 2.6.3
    fi
    if ! docker version >/dev/null 2>&1; then
        echo "WARNING: Docker (e.g. OrbStack) is needed to run gcc-2.5.7-psx on macOS" >&2
    else
        docker image inspect i386/alpine:3.20 >/dev/null 2>&1 || docker pull -q --platform linux/386 i386/alpine:3.20
    fi
    case "$(uname -m)" in arm64) OD=objdiff-cli-macos-arm64 ;; *) OD=objdiff-cli-macos-x86_64 ;; esac
    ;;
  Linux)
    fetch_gcc 2.6.3-psx gcc-2.6.3-psx.tar.gz
    fetch_gcc 2.7.2-psx gcc-2.7.2-psx.tar.gz
    fetch_gcc 2.8.1-psx gcc-2.8.1-psx.tar.gz
    case "$(uname -m)" in aarch64) OD=objdiff-cli-linux-aarch64 ;; *) OD=objdiff-cli-linux-x86_64 ;; esac
    ;;
  *) echo "unsupported OS" >&2; exit 1 ;;
esac

if [ ! -x "$TC/bin/objdiff-cli" ]; then
    curl -fsSL -o "$TC/bin/objdiff-cli" \
        "https://github.com/encounter/objdiff/releases/download/$OBJDIFF_VER/$OD"
    chmod +x "$TC/bin/objdiff-cli"
    echo "installed objdiff-cli $OBJDIFF_VER"
fi

clone https://github.com/mkst/maspsx.git maspsx
clone https://github.com/simonlindholm/asm-differ.git asm-differ
clone https://github.com/simonlindholm/decomp-permuter.git decomp-permuter

# GNU binutils for mipsel: prefer mipsel-none-elf-, accept mipsel-linux-gnu-.
if ! command -v mipsel-none-elf-as >/dev/null && ! command -v mipsel-linux-gnu-as >/dev/null; then
    echo "WARNING: no mipsel binutils on PATH; on macOS: brew install mipsel-linux-gnu-binutils" >&2
fi
echo "toolchain ready in $TC"
