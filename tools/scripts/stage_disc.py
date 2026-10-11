#!/usr/bin/env python3
"""Stage the retail executable from a local disc image.

    tools/scripts/stage_disc.py [--image PATH]

Accepts the redump .cue/.bin (single MODE2/2352 track) or a .7z containing
them. The image is looked for in disc/USA/, then ~/Documents and ~/Downloads.
Writes assets/USA/main.exe and SYSTEM.CNF, verifies the SHA-1, and extracts
the whole filesystem (NSD/NSF level data) to build/extract/USA/files/.
"""
from __future__ import annotations

import argparse
import hashlib
import shutil
import struct
import subprocess
import sys
from pathlib import Path

ROOT = Path(__file__).resolve().parents[2]
HOME = Path.home()
NAME = "Crash Bandicoot (USA)"
EXE_NAME = "SCUS_949.00"
EXE_SHA1 = "b2af088a162e046ad07f532d46b655cfcc42a05c"
# redump.org/disc/2250 (covers the original and Greatest Hits pressings)
BIN_SHA1 = "61ff4c9e8dcfb9e5d94d37f66330b69d08d6c914"
SEARCH = [ROOT / "disc" / "USA", HOME / "Documents", HOME / "Downloads"]


def sha1(path: Path) -> str:
    h = hashlib.sha1()
    with path.open("rb") as f:
        for chunk in iter(lambda: f.read(1 << 20), b""):
            h.update(chunk)
    return h.hexdigest()


def find_image(explicit: Path | None) -> Path:
    if explicit:
        return explicit
    for base in SEARCH:
        for candidate in (base / f"{NAME}.bin", base / f"{NAME}.7z", base / NAME / f"{NAME}.bin"):
            if candidate.exists():
                return candidate
    raise SystemExit(f"no disc image found; pass --image or put '{NAME}.bin' in disc/USA/")


def ensure_bin(image: Path) -> Path:
    disc_dir = ROOT / "disc" / "USA"
    disc_dir.mkdir(parents=True, exist_ok=True)
    if image.suffix == ".7z":
        subprocess.run(["7z", "e", "-y", f"-o{disc_dir}", str(image), "*.bin", "*.cue", "-r"],
                       check=True, stdout=subprocess.DEVNULL)
        return disc_dir / f"{NAME}.bin"
    return image


def bin_to_iso(track: Path, iso: Path) -> None:
    iso.parent.mkdir(parents=True, exist_ok=True)
    with track.open("rb") as src, iso.open("wb") as dst:
        while sector := src.read(2352):
            if len(sector) != 2352:
                raise SystemExit(f"{track}: partial sector")
            dst.write(sector[24:24 + 2048])  # MODE2 form 1 user data


def main() -> int:
    ap = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument("--image", type=Path)
    args = ap.parse_args()

    track = ensure_bin(find_image(args.image))
    digest = sha1(track)
    if digest != BIN_SHA1:
        print(f"warning: {track.name} SHA-1 {digest} is not the redump dump {BIN_SHA1}", file=sys.stderr)

    extract = ROOT / "build" / "extract" / "USA"
    iso = extract / "track01.iso"
    bin_to_iso(track, iso)
    files = extract / "files"
    subprocess.run(["7z", "x", "-y", f"-o{files}", str(iso)], check=True, stdout=subprocess.DEVNULL)
    iso.unlink()

    assets = ROOT / "assets" / "USA"
    assets.mkdir(parents=True, exist_ok=True)
    shutil.copy2(files / EXE_NAME, assets / "main.exe")
    shutil.copy2(files / "SYSTEM.CNF", assets / "SYSTEM.CNF")
    actual = sha1(assets / "main.exe")
    if actual != EXE_SHA1:
        raise SystemExit(f"{EXE_NAME}: SHA-1 mismatch: expected {EXE_SHA1}, got {actual}")

    hdr = (assets / "main.exe").read_bytes()[:0x800]
    pc, _gp, addr, size = struct.unpack_from("<4I", hdr, 0x10)
    print(f"staged {EXE_NAME}: SHA-1 OK, entry 0x{pc:08X}, text 0x{addr:08X}+0x{size:X}")
    print(f"disc files in {files.relative_to(ROOT)}")
    return 0


if __name__ == "__main__":
    sys.exit(main())
