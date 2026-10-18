#!/usr/bin/env python3
"""
GOOL (Game Object Oriented Lisp) Bytecode Decompiler & Assembler
for Crash Bandicoot (PS1, SCUS-949.00).

Supports:
  - Extracting etype == 11 GOOL executable entries from .NSF archives
    (handling both 0x1234 uncompressed and 0x1235 LZSS-compressed pages).
  - Decompiling binary GOOL entries into structured, human-readable .gool
    S-expressions with symbolic EIDs, object register names, state/event
    annotations, animation descriptors, and folded stack expressions.
  - Assembling/compiling .gool S-expressions back into byte-exact binary
    etype == 11 resource entries.
  - Round-trip SHA-1 verification across all GOOL entries on the retail disc.
"""

from __future__ import annotations

import argparse
import hashlib
import os
import struct
import sys
from pathlib import Path
from typing import Any, Dict, List, Optional, Sequence, Set, Tuple, Union

# ---------------------------------------------------------------------------
# 64-character Naughty Dog EID encoding table (D_80051728 in src/main/ns/)
# ---------------------------------------------------------------------------

EID_CHARSET = "0123456789abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ_!"
EID_CHAR_TO_IDX = {ch: idx for idx, ch in enumerate(EID_CHARSET)}
EID_NONE = 0x6396347F  # 'NONE!'


def decode_eid(val: int) -> Optional[str]:
    """Decode a 32-bit EID word into a 5-character string, or None if not an EID."""
    val &= 0xFFFFFFFF
    if (val & 1) == 0 or (val & 0x80000000) != 0:
        return None
    v = val >> 1
    chars: List[str] = []
    for _ in range(5):
        chars.append(EID_CHARSET[v & 0x3F])
        v >>= 6
    return "".join(reversed(chars))


def is_probable_eid(val: int) -> bool:
    """Return True if a 32-bit word is a genuine resource EID rather than a raw int."""
    s = decode_eid(val)
    if s is None:
        return False
    if s == "NONE!":
        return True
    # Valid Crash 1 EIDs have non-'0' leading char and end in a standard resource type letter
    if s[0] == "0" or "!" in s[:-1]:
        return False
    return s[-1] in "CVGWTASLZMNDPIHBR" and all(c.isalnum() or c == "_" for c in s[:4])


def encode_eid(name: str) -> int:
    """Encode a 5-character EID string into a 32-bit word (func_80012660)."""
    if len(name) != 5:
        raise ValueError(f"EID string must be exactly 5 characters: {name!r}")
    val = 0
    for ch in name:
        if ch not in EID_CHAR_TO_IDX:
            raise ValueError(f"Invalid EID character {ch!r} in {name!r}")
        val = (val << 6) | EID_CHAR_TO_IDX[ch]
    return ((val << 1) | 1) & 0xFFFFFFFF


# ---------------------------------------------------------------------------
# NSF Page Decompression (func_80013970 in src/main/ns/page_4170.c)
# ---------------------------------------------------------------------------

PAGE_SIZE = 0x10000
SECTOR_SIZE = 0x800


def decompress_nsf_chunk(src: bytes, offset: int = 0) -> Tuple[bytes, int]:
    """
    Decompress one page from `src` starting at `offset`.
    Returns `(decompressed_64kb_page, bytes_consumed_in_src)`.
    """
    magic, comp_len, skip_len = struct.unpack_from("<III", src, offset)
    low_magic = magic & 0xFFFF
    if low_magic == 0x1234:
        return src[offset : offset + PAGE_SIZE], PAGE_SIZE
    if low_magic != 0x1235:
        raise ValueError(f"Unexpected chunk magic 0x{low_magic:04X} at offset 0x{offset:X}")

    pos = offset + 12
    dst = bytearray()
    rem = PAGE_SIZE - comp_len
    while comp_len > 0:
        b = src[pos]
        pos += 1
        if b & 0x80:
            w = (b << 8) | src[pos]
            pos += 1
            back_off = (w >> 3) & 0xFFF
            ln = w & 7
            ln = 0x40 if ln == 7 else ln + 3
            comp_len -= ln
            start = len(dst) - back_off
            for i in range(ln):
                dst.append(dst[start + i])
        else:
            ln = b
            comp_len -= ln
            dst.extend(src[pos : pos + ln])
            pos += ln

    pos += skip_len
    dst.extend(src[pos : pos + rem])
    pos += rem
    if len(dst) != PAGE_SIZE:
        raise ValueError(f"Decompressed page size mismatch: {len(dst)} != {PAGE_SIZE}")
    return bytes(dst), pos - offset


def extract_gool_entries_from_nsf(nsf_bytes: bytes, source_name: str = "") -> List[Tuple[str, int, bytes]]:
    """
    Scan an .NSF file for all etype == 11 GOOL executable entries.
    Returns a list of `(eid_name, eid_word, raw_entry_bytes)`.
    """
    results: List[Tuple[str, int, bytes]] = []
    off = 0
    n = len(nsf_bytes)
    while off + 16 <= n:
        magic, kind = struct.unpack_from("<HH", nsf_bytes, off)
        if magic == 0x1235 and kind == 0:
            page, step = decompress_nsf_chunk(nsf_bytes, off)
            off += step
        elif magic == 0x1234 and kind <= 4 and off + PAGE_SIZE <= n:
            page = nsf_bytes[off : off + PAGE_SIZE]
            off += PAGE_SIZE
        else:
            off += SECTOR_SIZE
            continue

        p_magic, p_kind, _p_id, p_count, _p_crc = struct.unpack_from("<HHIII", page, 0)
        if p_kind == 1 or p_magic != 0x1234:
            continue
        if 16 + (p_count + 1) * 4 > len(page):
            continue
        offsets = struct.unpack_from(f"<{p_count + 1}I", page, 16)
        for i in range(p_count):
            e_start, e_end = offsets[i], offsets[i + 1]
            if e_start >= e_end or e_end > len(page) or e_end - e_start < 16:
                continue
            entry = page[e_start:e_end]
            e_magic, e_eid, e_kind, _e_icount = struct.unpack_from("<IIII", entry, 0)
            if e_kind == 11 and e_magic == 0x0100FFFF:
                name = decode_eid(e_eid) or f"EID_{e_eid:08X}"
                results.append((name, e_eid, entry))
    return results


# ---------------------------------------------------------------------------
# Object Links, Vectors & Register Map (0x00..0x3F at GoolObj + 0x60)
# ---------------------------------------------------------------------------

LINK_NAMES: Tuple[str, ...] = (
    "self",
    "parent",
    "sibling",
    "child",
    "creator",
    "player",
    "collider",
    "interrupter",
)
LINK_NAME_TO_IDX: Dict[str, int] = {name: i for i, name in enumerate(LINK_NAMES)}

VEC_NAMES: Tuple[str, ...] = (
    "trans",
    "rot",
    "scale",
    "vel",
    "ang-vel",
    "target-rot",
    "vec-6",
    "vec-7",
)
VEC_NAME_TO_IDX: Dict[str, int] = {name: i for i, name in enumerate(VEC_NAMES)}

REG_NAMES: Tuple[str, ...] = (
    "self",                 # 0x00 (+0x60)
    "parent",               # 0x01 (+0x64)
    "sibling",              # 0x02 (+0x68)
    "child",                # 0x03 (+0x6C)
    "creator",              # 0x04 (+0x70)
    "player",               # 0x05 (+0x74)
    "collider",             # 0x06 (+0x78)
    "interrupter",          # 0x07 (+0x7C)
    "x",                    # 0x08 (+0x80)
    "y",                    # 0x09 (+0x84)
    "z",                    # 0x0A (+0x88)
    "rot-x",                # 0x0B (+0x8C)
    "rot-y",                # 0x0C (+0x90)
    "rot-z",                # 0x0D (+0x94)
    "scale-x",              # 0x0E (+0x98)
    "scale-y",              # 0x0F (+0x9C)
    "scale-z",              # 0x10 (+0xA0)
    "vel-x",                # 0x11 (+0xA4)
    "vel-y",                # 0x12 (+0xA8)
    "vel-z",                # 0x13 (+0xAC)
    "ang-vel-x",            # 0x14 (+0xB0)
    "ang-vel-y",            # 0x15 (+0xB4)
    "ang-vel-z",            # 0x16 (+0xB8)
    "target-rot-x",         # 0x17 (+0xBC)
    "target-rot-y",         # 0x18 (+0xC0)
    "target-rot-z",         # 0x19 (+0xC4)
    "status-a",             # 0x1A (+0xC8)
    "status-b",             # 0x1B (+0xCC)
    "status-c",             # 0x1C (+0xD0)
    "subtype",              # 0x1D (+0xD4)
    "pid-flags",            # 0x1E (+0xD8)
    "tos",                  # 0x1F (+0xDC: sp push/pop in GOP/REG modes)
    "pc",                   # 0x20 (+0xE0)
    "fp",                   # 0x21 (+0xE4)
    "tp",                   # 0x22 (+0xE8)
    "ep",                   # 0x23 (+0xEC)
    "sr",                   # 0x24 (+0xF0)
    "v0",                   # 0x25 (+0xF4)
    "a0",                   # 0x26 (+0xF8)
    "stamp",                # 0x27 (+0xFC)
    "state-stamp",          # 0x28 (+0x100)
    "anim-counter",         # 0x29 (+0x104)
    "anim-seq",             # 0x2A (+0x108)
    "anim-frame",           # 0x2B (+0x10C)
    "entity",               # 0x2C (+0x110)
    "path-progress",        # 0x2D (+0x114)
    "path-length",          # 0x2E (+0x118)
    "floor-y",              # 0x2F (+0x11C)
    "state-flags",          # 0x30 (+0x120)
    "speed",                # 0x31 (+0x124)
    "invincibility-state",  # 0x32 (+0x128)
    "invincibility-time",   # 0x33 (+0x12C)
    "floor-time",           # 0x34 (+0x130)
    "floor-vel-y",          # 0x35 (+0x134)
    "cam-zoom",             # 0x36 (+0x138)
    "event",                # 0x37 (+0x13C)
    "cam-rot-x",            # 0x38 (+0x140)
    "cam-rot-y",            # 0x39 (+0x144)
    "cam-rot-z",            # 0x3A (+0x148)
    "voice-id",             # 0x3B (+0x14C)
    "reg-3c",               # 0x3C (+0x150)
    "path-radius",          # 0x3D (+0x154)
    "node-id",              # 0x3E (+0x158)
    "reg-3f",               # 0x3F (+0x15C)
)

REG_NAME_TO_IDX: Dict[str, int] = {name: i for i, name in enumerate(REG_NAMES)}
# Convenient aliases for registers
REG_ALIASES: Dict[str, int] = {
    "sp": 0x1F,
    "stack": 0x1F,
    "a1": 0x27,
    "a2": 0x28,
    "a3": 0x29,
}
REG_NAME_TO_IDX.update(REG_ALIASES)


def decode_reg(reg: int) -> str:
    """Decode a 9-bit self register offset (0x000..0x1FF) into a symbolic name."""
    if 0 <= reg < len(REG_NAMES):
        return REG_NAMES[reg]
    return f"field-{reg - 0x40}" if reg >= 0x40 else f"reg-{reg:02x}"


def encode_reg(name: str) -> int:
    """Encode a symbolic register name back into its index (0x000..0x1FF)."""
    if name in REG_NAME_TO_IDX:
        return REG_NAME_TO_IDX[name]
    if name.startswith("field-"):
        return 0x40 + int(name[6:], 0)
    if name.startswith("reg-"):
        return int(name[4:], 16)
    raise ValueError(f"Unknown register name: {name!r}")


# ---------------------------------------------------------------------------
# 12-bit GOP (General Operand) Encoding & Decoding (GOOL_TranslateGop)
# ---------------------------------------------------------------------------

def _sign_extend(val: int, bits: int) -> int:
    shift = 32 - bits
    u = ((val << shift) & 0xFFFFFFFF) >> shift
    return u - (1 << bits) if (val & (1 << (bits - 1))) else u


def decode_gop(gop: int) -> str:
    """
    Decode a 12-bit GOP operand (0x000..0xFFF) into a lossless symbolic token.
      - 0x000..0x3FF: data[idx]         (self->exec->data[idx])
      - 0x400..0x7FF: ext[idx]          (self->external->data[idx])
      - 0x800..0x9FF: integer           (sign_ext(gop, 9) << 8)
      - 0xA00..0xAFF: integer / imm4[n] (sign_ext(gop, 8) << 4)
      - 0xB00..0xB7F: fp[offset]        (self->fp[sign_ext(gop, 7)])
      - 0xBE0:        null              (NULL pointer)
      - 0xBF0:        var-rate          ((s32 *)1 stack rate/target marker)
      - 0xC00..0xDFF: <link>.<reg>      (self->links[link]->reg)
      - 0xE00..0xFFF: <reg>             (self->reg, with 0xE1F == tos)
    """
    gop &= 0xFFF
    if (gop & 0x800) == 0:
        idx = gop & 0x3FF
        if gop & 0x400:
            return f"ext[{idx}]"
        return f"data[{idx}]"

    if gop & 0x400:
        if gop & 0x200:
            return decode_reg(gop & 0x1FF)
        link_idx = (gop >> 6) & 7
        reg_idx = gop & 0x3F
        reg_name = "sp" if reg_idx == 0x1F else decode_reg(reg_idx)
        return f"{LINK_NAMES[link_idx]}.{reg_name}"

    if (gop & 0x200) == 0:
        val = _sign_extend(gop & 0x1FF, 9) << 8
        return str(val)

    if (gop & 0x100) == 0:
        val = _sign_extend(gop & 0xFF, 8) << 4
        # If val is a multiple of 256, disambiguate from 0x800..0x9FF with imm4[...]
        if (val & 0xFF) == 0:
            return f"imm4[{val}]"
        return str(val)

    if (gop & 0x80) == 0:
        off = _sign_extend(gop & 0x7F, 7)
        return f"fp[{off}]"

    if gop == 0xBE0:
        return "null"
    if gop == 0xBF0:
        return "var-rate"
    return f"gop[0x{gop:03x}]"


def encode_gop(token: str) -> int:
    """Encode a symbolic GOP token back into a 12-bit integer (0x000..0xFFF)."""
    if token == "null":
        return 0xBE0
    if token == "var-rate":
        return 0xBF0
    if token.startswith("data[") and token.endswith("]"):
        idx = int(token[5:-1], 0)
        if not (0 <= idx <= 0x3FF):
            raise ValueError(f"data index out of range: {token}")
        return idx
    if token.startswith("ext[") and token.endswith("]"):
        idx = int(token[4:-1], 0)
        if not (0 <= idx <= 0x3FF):
            raise ValueError(f"ext index out of range: {token}")
        return 0x400 | idx
    if token.startswith("fp[") and token.endswith("]"):
        off = int(token[3:-1], 0)
        if not (-64 <= off <= 63):
            raise ValueError(f"fp offset out of range: {token}")
        return 0xB00 | (off & 0x7F)
    if token.startswith("imm4[") and token.endswith("]"):
        val = int(token[5:-1], 0)
        q = val >> 4
        if (val & 0xF) != 0 or not (-128 <= q <= 127):
            raise ValueError(f"imm4 value out of range: {token}")
        return 0xA00 | (q & 0xFF)
    if token.startswith("imm8[") and token.endswith("]"):
        val = int(token[5:-1], 0)
        q = val >> 8
        if (val & 0xFF) != 0 or not (-256 <= q <= 255):
            raise ValueError(f"imm8 value out of range: {token}")
        return 0x800 | (q & 0x1FF)
    if token.startswith("gop[") and token.endswith("]"):
        return int(token[4:-1], 0) & 0xFFF

    if "." in token:
        link_part, reg_part = token.split(".", 1)
        if link_part in LINK_NAME_TO_IDX:
            link_idx = LINK_NAME_TO_IDX[link_part]
            reg_idx = encode_reg(reg_part)
            if not (0 <= reg_idx <= 0x3F):
                raise ValueError(f"Link register index out of range: {token}")
            return 0xC00 | (link_idx << 6) | reg_idx

    # Integer literal -> immediate 0x800 (<<8) or 0xA00 (<<4)
    try:
        val = int(token, 0)
    except ValueError:
        pass
    else:
        if (val & 0xFF) == 0 and -256 <= (val >> 8) <= 255:
            return 0x800 | ((val >> 8) & 0x1FF)
        if (val & 0xF) == 0 and -128 <= (val >> 4) <= 127:
            return 0xA00 | ((val >> 4) & 0xFF)
        raise ValueError(f"Immediate {val} cannot fit in 12-bit GOP (must be <<8 or <<4)")

    # Direct self register (0xE00..0xFFF)
    reg_idx = encode_reg(token)
    if not (0 <= reg_idx <= 0x1FF):
        raise ValueError(f"Self register index out of range: {token}")
    return 0xE00 | reg_idx


# ---------------------------------------------------------------------------
# Opcode Tables (0x00..0x91 in src/main/gool/interpret.c)
# ---------------------------------------------------------------------------

# Pure stack-pushing binary operations: (op s d) -> *sp++ = f(s, d)
PURE_BIN_OP_NAMES: Dict[int, str] = {
    0x00: "add",
    0x01: "sub",
    0x02: "mul",
    0x03: "div",
    0x04: "equ",
    0x05: "and",
    0x06: "or",
    0x07: "bit-and",
    0x08: "bit-or",
    0x09: "gt",
    0x0A: "gte",
    0x0B: "lt",
    0x0C: "lte",
    0x0D: "mod",
    0x0E: "xor",
    0x0F: "bit-test",
    0x10: "rnd",
    0x15: "shl",
    0x1B: "scale-dt",
    0x1D: "sin",
    0x1E: "mod-frame",
    0x21: "ang-diff",
}
NAME_TO_PURE_BIN_OP: Dict[str, int] = {v: k for k, v in PURE_BIN_OP_NAMES.items()}

# Approach / seek opcodes: (seek s d) or (seek-ang s d); when s != var-rate, pure stack-push
SEEK_OP_NAMES: Dict[int, str] = {
    0x22: "seek",
    0x25: "seek-ang",
}
NAME_TO_SEEK_OP: Dict[str, int] = {v: k for k, v in SEEK_OP_NAMES.items()}

# Source-to-destination operations: (op s d); when d == tos (0xE1F), pushes result onto stack
OUT_OP_NAMES: Dict[int, str] = {
    0x11: "move",
    0x12: "not",
    0x14: "lea",
    0x17: "bit-not",
    0x19: "abs",
    0x27: "load-anim",
}
NAME_TO_OUT_OP: Dict[str, int] = {v: k for k, v in OUT_OP_NAMES.items()}

# Other two-GOP statement opcodes: (op s d)
STMT_TWO_GOP_NAMES: Dict[int, str] = {
    0x13: "oscillate",
    0x16: "push2",
    0x20: "store-global",
    0x26: "lea2",
    0x81: "debug",
    0x8B: "ns-ctrl",
    0x8C: "play-sound",
}
NAME_TO_STMT_TWO_GOP: Dict[str, int] = {v: k for k, v in STMT_TWO_GOP_NAMES.items()}
NAME_TO_STMT_TWO_GOP["min"] = 0x13  # alias

# Sub-opcodes of 0x1C: (subop_name link subarg gop)
MISC_1C_NAMES: Dict[int, str] = {
    0: "entity-field",
    1: "dist-obj",
    2: "ang-to",
    3: "read-reg-indir",
    4: "write-reg-indir",
    5: "ang-diff-y",
    6: "dist-vec",
    7: "find-obj-by-id",
    8: "pid-bit2",
    9: "set-zone",
    10: "pid-flags-op",
    11: "pid-flags-test",
    12: "level-op",
    13: "find-nearest-obj",
    14: "test-collision-box",
    15: "memcard-op",
}
NAME_TO_MISC_1C: Dict[str, int] = {v: k for k, v in MISC_1C_NAMES.items()}

# Sub-opcodes of 0x85 (vector / path / transform operations):
VEC_85_NAMES: Dict[int, str] = {
    0: "path-follow",
    1: "project-3d",
    2: "vel-from-ang",
    3: "vec-op-3",
    4: "transform-local",
    5: "transform-ang-vel",
    6: "joint-transform",
    7: "project-2d",
}
NAME_TO_VEC_85: Dict[str, int] = {v: k for k, v in VEC_85_NAMES.items()}

# Control flow mnemonics for 0x82, 0x88 (event-return), 0x89 (event-accept)
CTRL_MNEMONICS: Dict[Tuple[int, int, int], str] = {
    # 0x82: standard control flow
    (0x82, 0, 0): "bra",
    (0x82, 0, 1): "bnez",
    (0x82, 0, 2): "beqz",
    (0x82, 1, 0): "change-state",
    (0x82, 1, 1): "change-state-bnez",
    (0x82, 1, 2): "change-state-beqz",
    (0x82, 2, 0): "ret",
    (0x82, 2, 1): "ret-bnez",
    (0x82, 2, 2): "ret-beqz",
    # 0x88: event handler return (flag = 0 / reject)
    (0x88, 0, 0): "event-bra-reject",
    (0x88, 0, 1): "event-bnez-reject",
    (0x88, 0, 2): "event-beqz-reject",
    (0x88, 1, 0): "event-state-reject",
    (0x88, 1, 1): "event-state-bnez-reject",
    (0x88, 1, 2): "event-state-beqz-reject",
    (0x88, 2, 0): "event-ret-reject",
    (0x88, 2, 1): "event-ret-bnez-reject",
    (0x88, 2, 2): "event-ret-beqz-reject",
    # 0x89: event handler return (flag = 1 / accept)
    (0x89, 0, 0): "event-bra-accept",
    (0x89, 0, 1): "event-bnez-accept",
    (0x89, 0, 2): "event-beqz-accept",
    (0x89, 1, 0): "event-state-accept",
    (0x89, 1, 1): "event-state-bnez-accept",
    (0x89, 1, 2): "event-state-beqz-accept",
    (0x89, 2, 0): "event-ret-accept",
    (0x89, 2, 1): "event-ret-bnez-accept",
    (0x89, 2, 2): "event-ret-beqz-accept",
}
NAME_TO_CTRL: Dict[str, Tuple[int, int, int]] = {v: k for k, v in CTRL_MNEMONICS.items()}

FLIP_NAMES: Tuple[str, ...] = ("pos", "neg", "flip", "keep")
FLIP_NAME_TO_IDX: Dict[str, int] = {name: i for i, name in enumerate(FLIP_NAMES)}


# ---------------------------------------------------------------------------
# S-Expression Parser & Formatter
# ---------------------------------------------------------------------------

SExpr = Union[str, List["SExpr"]]


def tokenize_sexpr(text: str) -> List[str]:
    """Tokenize a Lisp source string into parens, strings, and atom tokens."""
    tokens: List[str] = []
    i = 0
    n = len(text)
    while i < n:
        ch = text[i]
        if ch.isspace():
            i += 1
        elif ch == ";":
            while i < n and text[i] != "\n":
                i += 1
        elif ch in ("(", ")"):
            tokens.append(ch)
            i += 1
        elif ch == '"':
            buf = ['"']
            i += 1
            while i < n:
                c = text[i]
                i += 1
                if c == "\\":
                    if i >= n:
                        break
                    esc = text[i]
                    i += 1
                    buf.append("\\" + esc)
                elif c == '"':
                    buf.append('"')
                    break
                else:
                    buf.append(c)
            tokens.append("".join(buf))
        else:
            start = i
            while i < n and not text[i].isspace() and text[i] not in ("(", ")", ";", '"'):
                i += 1
            tokens.append(text[start:i])
    return tokens


def parse_sexpr(text: str) -> List[SExpr]:
    """Parse Lisp source text into a list of top-level S-expressions."""
    tokens = tokenize_sexpr(text)
    pos = 0

    def read_one() -> SExpr:
        nonlocal pos
        if pos >= len(tokens):
            raise ValueError("Unexpected EOF while parsing S-expression")
        tok = tokens[pos]
        pos += 1
        if tok == "(":
            lst: List[SExpr] = []
            while pos < len(tokens) and tokens[pos] != ")":
                lst.append(read_one())
            if pos >= len(tokens):
                raise ValueError("Unclosed '(' in S-expression")
            pos += 1  # consume ')'
            return lst
        if tok == ")":
            raise ValueError("Unexpected ')' in S-expression")
        return tok

    forms: List[SExpr] = []
    while pos < len(tokens):
        forms.append(read_one())
    return forms


def escape_lisp_string(raw: bytes) -> str:
    """Format raw Latin-1 bytes as a double-quoted Lisp string literal."""
    out = ['"']
    for b in raw:
        if b == 0x22:
            out.append('\\"')
        elif b == 0x5C:
            out.append("\\\\")
        elif b == 0x0A:
            out.append("\\n")
        elif b == 0x0D:
            out.append("\\r")
        elif b == 0x09:
            out.append("\\t")
        elif 0x20 <= b <= 0x7E:
            out.append(chr(b))
        else:
            out.append(f"\\x{b:02x}")
    out.append('"')
    return "".join(out)


def unescape_lisp_string(lit: str) -> bytes:
    """Decode a double-quoted Lisp string literal back into raw bytes."""
    if not (len(lit) >= 2 and lit[0] == '"' and lit[-1] == '"'):
        raise ValueError(f"Invalid string literal: {lit!r}")
    s = lit[1:-1]
    out = bytearray()
    i = 0
    while i < len(s):
        if s[i] == "\\":
            i += 1
            c = s[i]
            i += 1
            if c == "n":
                out.append(0x0A)
            elif c == "r":
                out.append(0x0D)
            elif c == "t":
                out.append(0x09)
            elif c == '"':
                out.append(0x22)
            elif c == "\\":
                out.append(0x5C)
            elif c == "x":
                out.append(int(s[i : i + 2], 16))
                i += 2
            else:
                out.append(ord(c))
        else:
            out.append(ord(s[i]))
            i += 1
    return bytes(out)


def format_word(val: int) -> str:
    """Format a 32-bit word as 'EID if it's a valid resource EID, else hex/int."""
    val &= 0xFFFFFFFF
    if is_probable_eid(val):
        return f"'{decode_eid(val)}"
    if val == 0:
        return "0"
    return f"0x{val:08X}"


def parse_word(tok: str) -> int:
    """Parse either an 'EID token or an integer/hex literal into a 32-bit unsigned int."""
    if tok.startswith("'") and len(tok) == 6:
        return encode_eid(tok[1:])
    return int(tok, 0) & 0xFFFFFFFF


def format_sexpr_inline(expr: SExpr) -> str:
    """Format an S-expression on a single line."""
    if isinstance(expr, str):
        return expr
    return "(" + " ".join(format_sexpr_inline(x) for x in expr) + ")"


# ---------------------------------------------------------------------------
# Code Disassembly, Expression Folding & Re-Assembly
# ---------------------------------------------------------------------------

def collect_code_labels(
    words: Sequence[int],
    events: Sequence[int],
    states: Sequence[Tuple[int, int, int, int, int, int]],
) -> Tuple[Set[int], Dict[int, List[str]]]:
    """
    Find all code word indices targeted by branches, jal, code-ptr, states, or events.
    Returns `(label_set, annotations_by_pc)`.
    """
    labels: Set[int] = set()
    notes: Dict[int, List[str]] = {}
    code_len = len(words)

    def add_note(pc: int, msg: str) -> None:
        if 0 <= pc <= code_len:
            labels.add(pc)
            notes.setdefault(pc, []).append(msg)

    for st_idx, (_sc, _fl, _ex, pc_ev, pc_tr, pc_cd) in enumerate(states):
        if pc_cd != 0x3FFF:
            add_note(pc_cd, f"state_{st_idx} code")
        if pc_tr != 0x3FFF:
            add_note(pc_tr, f"state_{st_idx} trans")
        if pc_ev != 0x3FFF:
            add_note(pc_ev, f"state_{st_idx} event")

    for ev_idx, ev_val in enumerate(events):
        if (ev_val & 0x8000) != 0:
            add_note(ev_val & 0x7FFF, f"event_0x{ev_idx:02X}")

    for pc, w in enumerate(words):
        op = w >> 24
        if op in (0x82, 0x88, 0x89):
            mode = (w >> 22) & 3
            if mode == 0:
                rel = _sign_extend(w & 0x3FF, 10)
                tgt = pc + 1 + rel
                if 0 <= tgt <= code_len:
                    labels.add(tgt)
        elif op in (0x86, 0x18):
            off = w & 0x3FFF
            if off != 0x3FFF and 0 <= off <= code_len:
                labels.add(off)

    return labels, notes


class AstNode:
    """Internal node for bottom-up stack expression folding."""

    __slots__ = ("is_expr", "sexpr")

    def __init__(self, is_expr: bool, sexpr: SExpr) -> None:
        self.is_expr = is_expr
        self.sexpr = sexpr


def decompile_code_section(
    words: Sequence[int],
    events: Sequence[int],
    states: Sequence[Tuple[int, int, int, int, int, int]],
) -> List[Tuple[Optional[str], SExpr]]:
    """
    Decompile an array of 32-bit GOOL bytecode words into a list of
    `(optional_comment, sexpr)` items, folding stack-pushed `(tos)` arguments
    into nested S-expressions wherever unambiguous.
    """
    labels, notes = collect_code_labels(words, events, states)
    nodes: List[Tuple[Optional[str], AstNode]] = []
    code_len = len(words)

    def pop_expr_if_tos(gop_val: int) -> SExpr:
        if gop_val == 0xE1F and nodes and nodes[-1][1].is_expr:
            return nodes.pop()[1].sexpr
        return decode_gop(gop_val)

    def pop_expr_if_reg_tos(reg_val: int) -> SExpr:
        if reg_val == 0x1F and nodes and nodes[-1][1].is_expr:
            return nodes.pop()[1].sexpr
        return decode_reg(reg_val)

    for pc, w in enumerate(words):
        if pc in labels:
            comment = ", ".join(notes[pc]) if pc in notes else None
            nodes.append((comment, AstNode(False, ["label", f"loc_{pc:04X}"])))

        op = w >> 24

        # 1. Pure binary stack-pushing expression opcodes
        if op in PURE_BIN_OP_NAMES:
            s_gop = (w >> 12) & 0xFFF
            d_gop = w & 0xFFF
            # s is evaluated/popped first, then d
            s_expr = pop_expr_if_tos(s_gop)
            d_expr = pop_expr_if_tos(d_gop)
            nodes.append((None, AstNode(True, [PURE_BIN_OP_NAMES[op], s_expr, d_expr])))

        # 2. Seek opcodes (0x22, 0x25)
        elif op in SEEK_OP_NAMES:
            s_gop = (w >> 12) & 0xFFF
            d_gop = w & 0xFFF
            if s_gop != 0xBF0:
                s_expr = pop_expr_if_tos(s_gop)
                d_expr = pop_expr_if_tos(d_gop)
                nodes.append((None, AstNode(True, [SEEK_OP_NAMES[op], s_expr, d_expr])))
            else:
                nodes.append((None, AstNode(False, [SEEK_OP_NAMES[op], decode_gop(s_gop), decode_gop(d_gop)])))

        # 3. Source-to-destination opcodes (move, not, lea, bit-not, abs, load-anim)
        elif op in OUT_OP_NAMES:
            s_gop = (w >> 12) & 0xFFF
            d_gop = w & 0xFFF
            s_expr = pop_expr_if_tos(s_gop)
            if op == 0x11 and d_gop == 0xE1F:
                nodes.append((None, AstNode(False, ["push", s_expr])))
            else:
                is_expr = d_gop == 0xE1F
                nodes.append((None, AstNode(is_expr, [OUT_OP_NAMES[op], s_expr, decode_gop(d_gop)])))

        # 4. Two-GOP statement opcodes (oscillate, push2, store-global, lea2, debug, ns-ctrl, play-sound)
        elif op in STMT_TWO_GOP_NAMES:
            s_gop = (w >> 12) & 0xFFF
            d_gop = w & 0xFFF
            if op in (0x20, 0x8C):
                s_expr = pop_expr_if_tos(s_gop)
                d_expr = pop_expr_if_tos(d_gop)
                nodes.append((None, AstNode(False, [STMT_TWO_GOP_NAMES[op], s_expr, d_expr])))
            else:
                nodes.append((None, AstNode(False, [STMT_TWO_GOP_NAMES[op], decode_gop(s_gop), decode_gop(d_gop)])))

        # 5. 0x18: (code-ptr reg target)
        elif op == 0x18:
            top4 = (w >> 20) & 0xF
            reg = (w >> 14) & 0x3F
            off = w & 0x3FFF
            tgt_str = "null" if off == 0x3FFF else f"loc_{off:04X}"
            if top4 == 0:
                nodes.append((None, AstNode(reg == 0x1F, ["code-ptr", decode_reg(reg), tgt_str])))
            else:
                nodes.append((None, AstNode(False, ["code-ptr", decode_reg(reg), tgt_str, str(top4)])))

        # 6. 0x1A: (pad mask)
        elif op == 0x1A:
            mask = w & 0xFFFFFF
            nodes.append((None, AstNode(True, ["pad", f"0x{mask:06X}"])))

        # 7. 0x1C: misc sub-operations
        elif op == 0x1C:
            subop = (w >> 20) & 0xF
            subarg = (w >> 15) & 0x1F
            link = (w >> 12) & 7
            gop = w & 0xFFF
            is_1c_expr = subop in (0, 1, 2, 3, 5, 6, 7, 11, 13, 14)
            # subop 4 (write-reg-indir) pops stack AFTER evaluating gop, so do not fold gop for subop 4
            gop_expr = pop_expr_if_tos(gop) if subop != 4 else decode_gop(gop)
            nodes.append(
                (
                    None,
                    AstNode(
                        is_1c_expr,
                        [MISC_1C_NAMES[subop], LINK_NAMES[link], str(subarg), gop_expr],
                    ),
                )
            )

        # 8. 0x1F: (load-global idx)
        elif op == 0x1F:
            s_gop = (w >> 12) & 0xFFF
            d_gop = w & 0xFFF
            if s_gop == 0xBE0:
                d_expr = pop_expr_if_tos(d_gop)
                nodes.append((None, AstNode(True, ["load-global", d_expr])))
            else:
                nodes.append((None, AstNode(False, ["load-global-ex", decode_gop(s_gop), decode_gop(d_gop)])))

        # 9. 0x23: (load-color link idx)
        elif op == 0x23:
            top3 = (w >> 21) & 7
            idx = (w >> 15) & 0x3F
            link = (w >> 12) & 7
            low12 = w & 0xFFF
            if top3 == 0 and low12 == 0xBE0:
                nodes.append((None, AstNode(True, ["load-color", LINK_NAMES[link], str(idx)])))
            else:
                nodes.append((None, AstNode(False, ["load-color-ex", LINK_NAMES[link], str(idx), decode_gop(low12), str(top3)])))

        # 10. 0x24: (store-color link idx gop)
        elif op == 0x24:
            top3 = (w >> 21) & 7
            idx = (w >> 15) & 0x3F
            link = (w >> 12) & 7
            gop = w & 0xFFF
            if top3 == 0:
                d_expr = pop_expr_if_tos(gop)
                nodes.append((None, AstNode(False, ["store-color", LINK_NAMES[link], str(idx), d_expr])))
            else:
                nodes.append((None, AstNode(False, ["store-color-ex", LINK_NAMES[link], str(idx), decode_gop(gop), str(top3)])))

        # 11. 0x80: (nop)
        elif op == 0x80:
            payload = w & 0xFFFFFF
            if payload == 0:
                nodes.append((None, AstNode(False, ["nop"])))
            else:
                nodes.append((None, AstNode(False, ["nop", f"0x{payload:06X}"])))

        # 12. 0x82, 0x88, 0x89: branches, state transitions, returns
        elif op in (0x82, 0x88, 0x89):
            mode = (w >> 22) & 3
            ct = (w >> 20) & 3
            reg = (w >> 14) & 0x3F
            low14 = w & 0x3FFF
            key = (op, mode, ct)
            if key in CTRL_MNEMONICS and (ct != 0 or reg == 0x25) and (mode != 2 or low14 == 0):
                mnem = CTRL_MNEMONICS[key]
                if mode == 0:
                    pop_cnt = (low14 >> 10) & 0xF
                    rel = _sign_extend(low14 & 0x3FF, 10)
                    tgt = pc + 1 + rel
                    tgt_tok = f"loc_{tgt:04X}" if 0 <= tgt <= code_len else str(rel)
                    if ct == 0:
                        form: List[SExpr] = [mnem, tgt_tok]
                    else:
                        cond_expr = pop_expr_if_reg_tos(reg) if pop_cnt == 0 else decode_reg(reg)
                        form = [mnem, cond_expr, tgt_tok]
                    if pop_cnt != 0:
                        form.extend([":pop", str(pop_cnt)])
                    nodes.append((None, AstNode(False, form)))
                elif mode == 1:
                    st_tok = f"state_{low14}"
                    if ct == 0:
                        nodes.append((None, AstNode(False, [mnem, st_tok])))
                    else:
                        cond_expr = pop_expr_if_reg_tos(reg)
                        nodes.append((None, AstNode(False, [mnem, cond_expr, st_tok])))
                else:  # mode == 2
                    if ct == 0:
                        nodes.append((None, AstNode(False, [mnem])))
                    else:
                        cond_expr = pop_expr_if_reg_tos(reg)
                        nodes.append((None, AstNode(False, [mnem, cond_expr])))
            else:
                nodes.append((None, AstNode(False, ["ctrl-raw", f"0x{op:02X}", str(mode), str(ct), decode_reg(reg), f"0x{low14:04X}"])))

        # 13. 0x83: (anim-seq anim_word_off frame wait flip)
        elif op == 0x83:
            flip = (w >> 22) & 3
            wait = (w >> 16) & 0x3F
            anim_off = (w >> 5) & 0x7FC
            frame = w & 0x7F
            nodes.append(
                (
                    None,
                    AstNode(
                        False,
                        ["anim-seq", f"0x{anim_off:03X}", str(frame), str(wait), FLIP_NAMES[flip]],
                    ),
                )
            )

        # 14. 0x84: (anim-frame frame_gop wait flip)
        elif op == 0x84:
            flip = (w >> 22) & 3
            wait = (w >> 16) & 0x3F
            mid4 = (w >> 12) & 0xF
            gop = w & 0xFFF
            if mid4 == 0:
                frame_expr = pop_expr_if_tos(gop)
                nodes.append((None, AstNode(False, ["anim-frame", frame_expr, str(wait), FLIP_NAMES[flip]])))
            else:
                nodes.append((None, AstNode(False, ["anim-frame-ex", decode_gop(gop), str(wait), FLIP_NAMES[flip], str(mid4)])))

        # 15. 0x85: vector / path / transform operations
        elif op == 0x85:
            top3 = (w >> 21) & 7
            subop = (w >> 18) & 7
            vec_src = (w >> 15) & 7
            vec_dst = (w >> 12) & 7
            gop = w & 0xFFF
            mnem = VEC_85_NAMES[subop]
            if subop == 6:
                nodes.append(
                    (
                        None,
                        AstNode(
                            False,
                            [mnem, LINK_NAMES[top3], VEC_NAMES[vec_dst], VEC_NAMES[vec_src], decode_gop(gop)],
                        ),
                    )
                )
            elif top3 == 0:
                nodes.append(
                    (
                        None,
                        AstNode(
                            False,
                            [mnem, VEC_NAMES[vec_dst], VEC_NAMES[vec_src], decode_gop(gop)],
                        ),
                    )
                )
            else:
                nodes.append(
                    (
                        None,
                        AstNode(
                            False,
                            [mnem, VEC_NAMES[vec_dst], VEC_NAMES[vec_src], decode_gop(gop), str(top3)],
                        ),
                    )
                )

        # 16. 0x86: (jal argc target)
        elif op == 0x86:
            argc = (w >> 20) & 0xF
            reg = (w >> 14) & 0x3F
            off = w & 0x3FFF
            tgt_tok = "null" if off == 0x3FFF else f"loc_{off:04X}"
            if reg == 0x26:
                nodes.append((None, AstNode(False, ["jal", str(argc), tgt_tok])))
            else:
                nodes.append((None, AstNode(False, ["jal", str(argc), tgt_tok, decode_reg(reg)])))

        # 17. 0x87 (send-event), 0x8F (broadcast-event), 0x90 (send-event-tree)
        elif op in (0x87, 0x8F, 0x90):
            rec = (w >> 21) & 7
            argc = (w >> 18) & 7
            cond_reg = (w >> 12) & 0x3F
            ev_gop = w & 0xFFF
            mnem = {0x87: "send-event", 0x8F: "broadcast-event", 0x90: "send-event-tree"}[op]
            rec_tok = str(rec) if op == 0x8F else LINK_NAMES[rec]
            nodes.append(
                (
                    None,
                    AstNode(
                        False,
                        [mnem, rec_tok, decode_gop(ev_gop), str(argc), decode_reg(cond_reg)],
                    ),
                )
            )

        # 18. 0x8A (spawn), 0x91 (spawn-urgent)
        elif op in (0x8A, 0x91):
            argc = (w >> 20) & 0xF
            exec_id = (w >> 12) & 0xFF
            subtype = (w >> 6) & 0x3F
            count = w & 0x3F
            mnem = "spawn" if op == 0x8A else "spawn-urgent"
            nodes.append((None, AstNode(False, [mnem, str(exec_id), str(subtype), str(argc), str(count)])))

        # 19. 0x8D: (audio-ctrl mode flags reg gop)
        elif op == 0x8D:
            mode = (w >> 20) & 0xF
            flags = (w >> 18) & 3
            reg = (w >> 12) & 0x3F
            gop = w & 0xFFF
            reg_tok = "none" if reg == 0 else decode_reg(reg)
            gop_expr = pop_expr_if_tos(gop) if reg != 0x1F else decode_gop(gop)
            nodes.append((None, AstNode(False, ["audio-ctrl", str(mode), str(flags), reg_tok, gop_expr])))

        # 20. 0x8E: (collide subop vec_dst vec_src gop)
        elif op == 0x8E:
            top3 = (w >> 21) & 7
            subop = (w >> 18) & 7
            vec_dst = (w >> 15) & 7
            vec_src = (w >> 12) & 7
            gop = w & 0xFFF
            if top3 == 0:
                nodes.append((None, AstNode(False, ["collide", str(subop), VEC_NAMES[vec_dst], VEC_NAMES[vec_src], decode_gop(gop)])))
            else:
                nodes.append((None, AstNode(False, ["collide", str(subop), VEC_NAMES[vec_dst], VEC_NAMES[vec_src], decode_gop(gop), str(top3)])))

        else:
            nodes.append((None, AstNode(False, ["word", f"0x{w:08X}"])))

    if code_len in labels:
        comment = ", ".join(notes[code_len]) if code_len in notes else None
        nodes.append((comment, AstNode(False, ["label", f"loc_{code_len:04X}"])))

    return [(comment, node.sexpr) for comment, node in nodes]


def compile_code_section(forms: Sequence[SExpr]) -> bytes:
    """
    Assemble the `(code ...)` section of a `.gool` file back into 32-bit bytecode words.
    Performs a two-pass assembly:
      Pass 1: Flattens nested S-expressions into post-order instruction tuples and records label PCs.
      Pass 2: Encodes all 32-bit instruction words and resolves relative/absolute label references.
    """
    flat_insns: List[List[str]] = []
    label_pcs: Dict[str, int] = {}

    def resolve_gop_expr(expr: SExpr) -> str:
        if isinstance(expr, list):
            emit_form(expr)
            return "tos"
        return expr

    def resolve_reg_expr(expr: SExpr) -> str:
        if isinstance(expr, list):
            emit_form(expr)
            return "tos"
        return expr

    def emit_form(form: SExpr) -> None:
        if not isinstance(form, list) or not form:
            raise ValueError(f"Invalid instruction form in (code ...): {form!r}")
        head = form[0]
        if not isinstance(head, str):
            raise ValueError(f"Instruction head must be a symbol: {form!r}")

        if head == "label":
            lbl = str(form[1])
            label_pcs[lbl] = len(flat_insns)
            return

        if head in NAME_TO_PURE_BIN_OP or head in NAME_TO_SEEK_OP or head in ("store-global", "play-sound"):
            s_arg, d_arg = form[1], form[2]
            # Because s is popped first and d is popped second at runtime,
            # d's sub-expression must be emitted BEFORE s's sub-expression!
            d_tok = resolve_gop_expr(d_arg)
            s_tok = resolve_gop_expr(s_arg)
            flat_insns.append([head, s_tok, d_tok])
            return

        if head == "push":
            s_tok = resolve_gop_expr(form[1])
            flat_insns.append(["move", s_tok, "tos"])
            return

        if head in NAME_TO_OUT_OP:
            s_tok = resolve_gop_expr(form[1])
            d_tok = str(form[2])
            flat_insns.append([head, s_tok, d_tok])
            return

        if head in NAME_TO_MISC_1C:
            g_tok = resolve_gop_expr(form[3])
            flat_insns.append([head, str(form[1]), str(form[2]), g_tok])
            return

        if head == "audio-ctrl":
            g_tok = resolve_gop_expr(form[4])
            flat_insns.append([head, str(form[1]), str(form[2]), str(form[3]), g_tok])
            return

        if head == "load-global":
            d_tok = resolve_gop_expr(form[1])
            flat_insns.append([head, d_tok])
            return

        if head == "store-color":
            d_tok = resolve_gop_expr(form[3])
            flat_insns.append([head, str(form[1]), str(form[2]), d_tok])
            return

        if head == "anim-frame":
            f_tok = resolve_gop_expr(form[1])
            flat_insns.append([head, f_tok, str(form[2]), str(form[3])])
            return

        if head in NAME_TO_CTRL:
            _op, mode, ct = NAME_TO_CTRL[head]
            if ct != 0:
                cond_tok = resolve_reg_expr(form[1])
                rest = [str(x) for x in form[2:]]
                flat_insns.append([head, cond_tok] + rest)
            else:
                flat_insns.append([str(x) for x in form])
            return

        flat_insns.append([str(x) for x in form])

    for top_form in forms:
        emit_form(top_form)

    # Pass 2: Encode flat instructions into 32-bit words
    out_words: List[int] = []
    for pc, ins in enumerate(flat_insns):
        head = ins[0]

        if head in NAME_TO_PURE_BIN_OP:
            op = NAME_TO_PURE_BIN_OP[head]
            w = (op << 24) | (encode_gop(ins[1]) << 12) | encode_gop(ins[2])

        elif head in NAME_TO_SEEK_OP:
            op = NAME_TO_SEEK_OP[head]
            w = (op << 24) | (encode_gop(ins[1]) << 12) | encode_gop(ins[2])

        elif head in NAME_TO_OUT_OP:
            op = NAME_TO_OUT_OP[head]
            w = (op << 24) | (encode_gop(ins[1]) << 12) | encode_gop(ins[2])

        elif head in NAME_TO_STMT_TWO_GOP:
            op = NAME_TO_STMT_TWO_GOP[head]
            w = (op << 24) | (encode_gop(ins[1]) << 12) | encode_gop(ins[2])

        elif head == "code-ptr":
            reg = encode_reg(ins[1]) & 0x3F
            tgt = ins[2]
            off = 0x3FFF if tgt == "null" else (label_pcs[tgt] if tgt in label_pcs else int(tgt, 0))
            top4 = int(ins[3], 0) & 0xF if len(ins) > 3 else 0
            w = (0x18 << 24) | (top4 << 20) | (reg << 14) | (off & 0x3FFF)

        elif head == "pad":
            mask = int(ins[1], 0) & 0xFFFFFF
            w = (0x1A << 24) | mask

        elif head in NAME_TO_MISC_1C:
            subop = NAME_TO_MISC_1C[head]
            link = LINK_NAME_TO_IDX[ins[1]]
            subarg = int(ins[2], 0) & 0x1F
            gop = encode_gop(ins[3])
            w = (0x1C << 24) | (subop << 20) | (subarg << 15) | (link << 12) | gop

        elif head == "load-global":
            w = (0x1F << 24) | (0xBE0 << 12) | encode_gop(ins[1])

        elif head == "load-global-ex":
            w = (0x1F << 24) | (encode_gop(ins[1]) << 12) | encode_gop(ins[2])

        elif head == "load-color":
            link = LINK_NAME_TO_IDX[ins[1]]
            idx = int(ins[2], 0) & 0x3F
            w = (0x23 << 24) | (idx << 15) | (link << 12) | 0xBE0

        elif head == "load-color-ex":
            link = LINK_NAME_TO_IDX[ins[1]]
            idx = int(ins[2], 0) & 0x3F
            low12 = encode_gop(ins[3])
            top3 = int(ins[4], 0) & 7
            w = (0x23 << 24) | (top3 << 21) | (idx << 15) | (link << 12) | low12

        elif head == "store-color":
            link = LINK_NAME_TO_IDX[ins[1]]
            idx = int(ins[2], 0) & 0x3F
            gop = encode_gop(ins[3])
            w = (0x24 << 24) | (idx << 15) | (link << 12) | gop

        elif head == "store-color-ex":
            link = LINK_NAME_TO_IDX[ins[1]]
            idx = int(ins[2], 0) & 0x3F
            gop = encode_gop(ins[3])
            top3 = int(ins[4], 0) & 7
            w = (0x24 << 24) | (top3 << 21) | (idx << 15) | (link << 12) | gop

        elif head == "nop":
            payload = int(ins[1], 0) & 0xFFFFFF if len(ins) > 1 else 0
            w = (0x80 << 24) | payload

        elif head in NAME_TO_CTRL:
            op, mode, ct = NAME_TO_CTRL[head]
            if ct == 0:
                reg = 0x25
                arg_idx = 1
            else:
                reg = encode_reg(ins[1]) & 0x3F
                arg_idx = 2

            if mode == 0:
                tgt_tok = ins[arg_idx]
                if tgt_tok in label_pcs:
                    rel = label_pcs[tgt_tok] - (pc + 1)
                else:
                    rel = int(tgt_tok, 0)
                pop_cnt = 0
                if len(ins) > arg_idx + 2 and ins[arg_idx + 1] == ":pop":
                    pop_cnt = int(ins[arg_idx + 2], 0) & 0xF
                low14 = ((pop_cnt & 0xF) << 10) | (rel & 0x3FF)
            elif mode == 1:
                st_tok = ins[arg_idx]
                st_idx = int(st_tok[6:], 0) if st_tok.startswith("state_") else int(st_tok, 0)
                low14 = st_idx & 0x3FFF
            else:
                low14 = 0
            w = (op << 24) | (mode << 22) | (ct << 20) | (reg << 14) | low14

        elif head == "ctrl-raw":
            op = int(ins[1], 0) & 0xFF
            mode = int(ins[2], 0) & 3
            ct = int(ins[3], 0) & 3
            reg = encode_reg(ins[4]) & 0x3F
            low14 = int(ins[5], 0) & 0x3FFF
            w = (op << 24) | (mode << 22) | (ct << 20) | (reg << 14) | low14

        elif head == "anim-seq":
            anim_off = int(ins[1], 0)
            frame = int(ins[2], 0) & 0x7F
            wait = int(ins[3], 0) & 0x3F
            flip = FLIP_NAME_TO_IDX[ins[4]]
            w = (0x83 << 24) | (flip << 22) | (wait << 16) | ((anim_off & 0x7FC) << 5) | frame

        elif head == "anim-frame":
            gop = encode_gop(ins[1])
            wait = int(ins[2], 0) & 0x3F
            flip = FLIP_NAME_TO_IDX[ins[3]]
            w = (0x84 << 24) | (flip << 22) | (wait << 16) | gop

        elif head == "anim-frame-ex":
            gop = encode_gop(ins[1])
            wait = int(ins[2], 0) & 0x3F
            flip = FLIP_NAME_TO_IDX[ins[3]]
            mid4 = int(ins[4], 0) & 0xF
            w = (0x84 << 24) | (flip << 22) | (wait << 16) | (mid4 << 12) | gop

        elif head in NAME_TO_VEC_85:
            subop = NAME_TO_VEC_85[head]
            if subop == 6:
                top3 = LINK_NAME_TO_IDX[ins[1]]
                vec_dst = VEC_NAME_TO_IDX[ins[2]]
                vec_src = VEC_NAME_TO_IDX[ins[3]]
                gop = encode_gop(ins[4])
            else:
                vec_dst = VEC_NAME_TO_IDX[ins[1]]
                vec_src = VEC_NAME_TO_IDX[ins[2]]
                gop = encode_gop(ins[3])
                top3 = int(ins[4], 0) & 7 if len(ins) > 4 else 0
            w = (0x85 << 24) | (top3 << 21) | (subop << 18) | (vec_src << 15) | (vec_dst << 12) | gop

        elif head == "jal":
            argc = int(ins[1], 0) & 0xF
            tgt = ins[2]
            off = 0x3FFF if tgt == "null" else (label_pcs[tgt] if tgt in label_pcs else int(tgt, 0))
            reg = encode_reg(ins[3]) & 0x3F if len(ins) > 3 else 0x26
            w = (0x86 << 24) | (argc << 20) | (reg << 14) | (off & 0x3FFF)

        elif head in ("send-event", "broadcast-event", "send-event-tree"):
            op = {"send-event": 0x87, "broadcast-event": 0x8F, "send-event-tree": 0x90}[head]
            rec = int(ins[1], 0) & 7 if ins[1] not in LINK_NAME_TO_IDX else LINK_NAME_TO_IDX[ins[1]]
            ev_gop = encode_gop(ins[2])
            argc = int(ins[3], 0) & 7
            cond_reg = encode_reg(ins[4]) & 0x3F
            w = (op << 24) | (rec << 21) | (argc << 18) | (cond_reg << 12) | ev_gop

        elif head in ("spawn", "spawn-urgent"):
            op = 0x8A if head == "spawn" else 0x91
            exec_id = int(ins[1], 0) & 0xFF
            subtype = int(ins[2], 0) & 0x3F
            argc = int(ins[3], 0) & 0xF
            count = int(ins[4], 0) & 0x3F
            w = (op << 24) | (argc << 20) | (exec_id << 12) | (subtype << 6) | count

        elif head == "audio-ctrl":
            mode = int(ins[1], 0) & 0xF
            flags = int(ins[2], 0) & 3
            reg = 0 if ins[3] == "none" else (encode_reg(ins[3]) & 0x3F)
            gop = encode_gop(ins[4])
            w = (0x8D << 24) | (mode << 20) | (flags << 18) | (reg << 12) | gop

        elif head == "collide":
            subop = int(ins[1], 0) & 7
            vec_dst = VEC_NAME_TO_IDX[ins[2]]
            vec_src = VEC_NAME_TO_IDX[ins[3]]
            gop = encode_gop(ins[4])
            top3 = int(ins[5], 0) & 7 if len(ins) > 5 else 0
            w = (0x8E << 24) | (top3 << 21) | (subop << 18) | (vec_dst << 15) | (vec_src << 12) | gop

        elif head == "word":
            w = int(ins[1], 0) & 0xFFFFFFFF

        else:
            raise ValueError(f"Unknown instruction mnemonic: {head!r}")

        out_words.append(w & 0xFFFFFFFF)

    return struct.pack(f"<{len(out_words)}I", *out_words)


# ---------------------------------------------------------------------------
# Anims Section Decompiler & Compiler (Item 5)
# ---------------------------------------------------------------------------

def decompile_anims_section(anims: bytes) -> List[str]:
    """Decompile Item 5 (`anims`) into structured Lisp forms."""
    lines: List[str] = []
    pos = 0
    n = len(anims)
    while pos < n:
        b0, b1, b2, b3 = anims[pos : pos + 4]
        cnt = b2 | (b3 << 8)
        if b1 != 0 or b0 not in (1, 2, 3, 4, 5):
            # Prototype raw words fallback (e.g. S0000004.NSF)
            rem_words = struct.unpack_from(f"<{(n - pos) // 4}I", anims, pos)
            w_strs = " ".join(f"0x{w:08X}" for w in rem_words)
            lines.append(f"    (raw-words {w_strs})")
            break

        if b0 == 1:
            eid_w = struct.unpack_from("<I", anims, pos + 4)[0]
            lines.append(
                f"    (vertex-anim :offset 0x{pos:03X} :frames {cnt} :eid {format_word(eid_w)})"
            )
            pos += 8

        elif b0 == 2:
            eid_w = struct.unpack_from("<I", anims, pos + 4)[0]
            frames: List[str] = []
            for i in range(cnt):
                w0, w1 = struct.unpack_from("<II", anims, pos + 8 + i * 8)
                frames.append(f"(0x{w0:08X} 0x{w1:08X})")
            lines.append(
                f"    (sprite-anim :offset 0x{pos:03X} :eid {format_word(eid_w)} :frames ({' '.join(frames)}))"
            )
            pos += 8 + cnt * 8

        elif b0 == 3:
            eid_w = struct.unpack_from("<I", anims, pos + 4)[0]
            glyphs: List[str] = []
            for i in range(cnt):
                w0, w1, gw, gh = struct.unpack_from("<IIhh", anims, pos + 8 + i * 12)
                glyphs.append(f"(0x{w0:08X} 0x{w1:08X} {gw} {gh})")
            lines.append(
                f"    (font :offset 0x{pos:03X} :eid {format_word(eid_w)} :glyphs ({' '.join(glyphs)}))"
            )
            pos += 8 + cnt * 12

        elif b0 == 4:
            eid_w, font_off = struct.unpack_from("<II", anims, pos + 4)
            s_pos = pos + 12
            str_lits: List[str] = []
            for _ in range(cnt):
                end = anims.index(0, s_pos)
                str_lits.append(escape_lisp_string(anims[s_pos:end]))
                s_pos = end + 1
            while s_pos % 4 != 0:
                s_pos += 1
            lines.append(
                f"    (text-anim :offset 0x{pos:03X} :eid {format_word(eid_w)} :font-offset 0x{font_off:X} :strings ({' '.join(str_lits)}))"
            )
            pos = s_pos

        elif b0 == 5:
            eid_w, frag_cnt = struct.unpack_from("<II", anims, pos + 4)
            total_frags = cnt * frag_cnt
            frags: List[str] = []
            for i in range(total_frags):
                w0, w1, x1, y1, x2, y2 = struct.unpack_from("<IIhhhh", anims, pos + 12 + i * 16)
                frags.append(f"(0x{w0:08X} 0x{w1:08X} {x1} {y1} {x2} {y2})")
            lines.append(
                f"    (frag-anim :offset 0x{pos:03X} :frames {cnt} :eid {format_word(eid_w)} :frags-per-frame {frag_cnt} :frags ({' '.join(frags)}))"
            )
            pos += 12 + total_frags * 16

    return lines


def compile_anims_section(forms: Sequence[SExpr]) -> bytes:
    """Compile structured `(anims ...)` forms back into binary bytes."""
    out = bytearray()
    for form in forms:
        if not isinstance(form, list) or not form:
            raise ValueError(f"Invalid anim form: {form!r}")
        kind = form[0]
        if kind == "raw-words":
            words = [int(str(x), 0) & 0xFFFFFFFF for x in form[1:]]
            out.extend(struct.pack(f"<{len(words)}I", *words))
            continue

        # Parse keyword arguments (:offset, :frames, :eid, etc.)
        kv: Dict[str, SExpr] = {}
        i = 1
        while i < len(form):
            k = str(form[i])
            v = form[i + 1]
            kv[k] = v
            i += 2

        if kind == "vertex-anim":
            cnt = int(str(kv[":frames"]), 0)
            eid_w = parse_word(str(kv[":eid"]))
            out.extend(struct.pack("<BBHI", 1, 0, cnt, eid_w))

        elif kind == "sprite-anim":
            eid_w = parse_word(str(kv[":eid"]))
            frame_list = kv[":frames"]
            assert isinstance(frame_list, list)
            out.extend(struct.pack("<BBHI", 2, 0, len(frame_list), eid_w))
            for fr in frame_list:
                assert isinstance(fr, list) and len(fr) == 2
                w0 = int(str(fr[0]), 0) & 0xFFFFFFFF
                w1 = int(str(fr[1]), 0) & 0xFFFFFFFF
                out.extend(struct.pack("<II", w0, w1))

        elif kind == "font":
            eid_w = parse_word(str(kv[":eid"]))
            glyph_list = kv[":glyphs"]
            assert isinstance(glyph_list, list)
            out.extend(struct.pack("<BBHI", 3, 0, len(glyph_list), eid_w))
            for gl in glyph_list:
                assert isinstance(gl, list) and len(gl) == 4
                w0 = int(str(gl[0]), 0) & 0xFFFFFFFF
                w1 = int(str(gl[1]), 0) & 0xFFFFFFFF
                gw = int(str(gl[2]), 0)
                gh = int(str(gl[3]), 0)
                out.extend(struct.pack("<IIhh", w0, w1, gw, gh))

        elif kind == "text-anim":
            eid_w = parse_word(str(kv[":eid"]))
            font_off = int(str(kv[":font-offset"]), 0) & 0xFFFFFFFF
            str_list = kv[":strings"]
            assert isinstance(str_list, list)
            out.extend(struct.pack("<BBHII", 4, 0, len(str_list), eid_w, font_off))
            for s_lit in str_list:
                out.extend(unescape_lisp_string(str(s_lit)))
                out.append(0)
            while len(out) % 4 != 0:
                out.append(0)

        elif kind == "frag-anim":
            cnt = int(str(kv[":frames"]), 0)
            eid_w = parse_word(str(kv[":eid"]))
            frag_cnt = int(str(kv[":frags-per-frame"]), 0)
            frag_list = kv[":frags"]
            assert isinstance(frag_list, list)
            out.extend(struct.pack("<BBHII", 5, 0, cnt, eid_w, frag_cnt))
            for fg in frag_list:
                assert isinstance(fg, list) and len(fg) == 6
                w0 = int(str(fg[0]), 0) & 0xFFFFFFFF
                w1 = int(str(fg[1]), 0) & 0xFFFFFFFF
                x1, y1, x2, y2 = (int(str(fg[j]), 0) for j in range(2, 6))
                out.extend(struct.pack("<IIhhhh", w0, w1, x1, y1, x2, y2))

        else:
            raise ValueError(f"Unknown anim record type: {kind!r}")

    return bytes(out)


# ---------------------------------------------------------------------------
# Full Entry Decompiler & Assembler (etype == 11)
# ---------------------------------------------------------------------------

def decompile_gool_entry(entry: bytes) -> str:
    """
    Decompile a binary `etype == 11` GOOL resource entry into a complete,
    human-readable `.gool` Lisp document.
    """
    e_magic, e_eid, e_kind, e_icount = struct.unpack_from("<IIII", entry, 0)
    if e_kind != 11 or e_magic != 0x0100FFFF:
        raise ValueError(f"Not a valid GOOL entry (magic=0x{e_magic:08X}, kind={e_kind})")

    ioffs = struct.unpack_from(f"<{e_icount + 1}I", entry, 16)
    items = [entry[ioffs[i] : ioffs[i + 1]] for i in range(e_icount)]

    eid_name = decode_eid(e_eid) or f"0x{e_eid:08X}"
    eid_tok = f"'{eid_name}" if not eid_name.startswith("0x") else eid_name

    # Item 0: Header (6 u32 words)
    hdr = struct.unpack_from("<6I", items[0], 0)
    obj_type, category, unk08, sp_offset, event_count, unk14 = hdr

    # Item 1: Code (u32 words)
    code_words = struct.unpack_from(f"<{len(items[1]) // 4}I", items[1], 0)

    # Item 2: Data pool (u32 words)
    data_words = struct.unpack_from(f"<{len(items[2]) // 4}I", items[2], 0)

    # Item 3: Events + Subtypes (u16 words, present when e_icount >= 5)
    events: Sequence[int] = ()
    subtypes: Sequence[int] = ()
    if e_icount >= 5:
        all_u16 = struct.unpack_from(f"<{len(items[3]) // 2}H", items[3], 0)
        events = all_u16[:event_count]
        subtypes = all_u16[event_count:]

    # Item 4: States (16-byte GoolState structs, present when e_icount >= 5)
    states: List[Tuple[int, int, int, int, int, int]] = []
    if e_icount >= 5:
        num_states = len(items[4]) // 16
        for i in range(num_states):
            states.append(struct.unpack_from("<IIHHHH", items[4], i * 16))

    lines: List[str] = [
        f";; GOOL Executable: {eid_name} (EID 0x{e_eid:08X}, {len(entry)} bytes, {e_icount} items)",
        f"(defgool {eid_name} :eid {eid_tok} :items {e_icount}",
        "  (header",
        f"    (type {obj_type})",
        f"    (category 0x{category:X})",
        f"    (unk08 {unk08})",
        f"    (sp-offset {sp_offset})",
        f"    (event-count {event_count})",
        f"    (unk14 {unk14}))",
    ]

    # Data section
    lines.append(f"  (data ; {len(data_words)} words")
    for idx, w in enumerate(data_words):
        lines.append(f"    ({idx} {format_word(w)})")
    lines.append("  )")

    # Events & Subtypes section (Item 3)
    if e_icount >= 5:
        lines.append(f"  (events ; {len(events)} event slots")
        for ev_idx, ev_val in enumerate(events):
            if ev_val == 0xFF:
                continue
            if ev_val & 0x8000:
                lines.append(f"    (0x{ev_idx:02X} (code loc_{ev_val & 0x7FFF:04X}))")
            else:
                lines.append(f"    (0x{ev_idx:02X} state_{ev_val})")
        lines.append("  )")

        sub_toks: List[str] = []
        for st_val in subtypes:
            if st_val == 0xFF:
                sub_toks.append("none")
            else:
                sub_toks.append(f"state_{st_val}")
        lines.append(f"  (subtypes {' '.join(sub_toks)})")

        # States section (Item 4)
        lines.append(f"  (states ; {len(states)} states")
        for st_idx, (status_c, flags, extern_idx, pc_ev, pc_tr, pc_cd) in enumerate(states):
            ev_s = "none" if pc_ev == 0x3FFF else f"loc_{pc_ev:04X}"
            tr_s = "none" if pc_tr == 0x3FFF else f"loc_{pc_tr:04X}"
            cd_s = "none" if pc_cd == 0x3FFF else f"loc_{pc_cd:04X}"
            lines.append(
                f"    (defstate state_{st_idx}"
                f" :status-c 0x{status_c:08X}"
                f" :flags 0x{flags:08X}"
                f" :extern {extern_idx}"
                f" :event {ev_s}"
                f" :trans {tr_s}"
                f" :code {cd_s})"
            )
        lines.append("  )")

    # Anims section (Item 5)
    if e_icount >= 6:
        lines.append(f"  (anims ; {len(items[5])} bytes")
        lines.extend(decompile_anims_section(items[5]))
        lines.append("  )")

    # Code section (Item 1)
    lines.append(f"  (code ; {len(code_words)} instructions")
    code_items = decompile_code_section(code_words, events, states)
    for comment, sexpr in code_items:
        if comment:
            lines.append(f"    ;; --- {comment} ---")
        if isinstance(sexpr, list) and sexpr and sexpr[0] == "label":
            lines.append(f"  {format_sexpr_inline(sexpr)}")
        else:
            lines.append(f"    {format_sexpr_inline(sexpr)}")
    lines.append("  )")
    lines.append(")")
    return "\n".join(lines) + "\n"


def compile_gool_source(source: str) -> bytes:
    """Compile a `.gool` Lisp document back into a binary `etype == 11` GOOL resource entry."""
    top_forms = parse_sexpr(source)
    if len(top_forms) != 1 or not isinstance(top_forms[0], list) or top_forms[0][0] != "defgool":
        raise ValueError("Expected a single top-level (defgool ...) form")

    root = top_forms[0]
    name_sym = str(root[1])

    # Parse top-level options (:eid, :items) and section lists
    eid_word: Optional[int] = None
    icount = 6
    sections: Dict[str, List[SExpr]] = {}

    idx = 2
    while idx < len(root):
        elem = root[idx]
        if isinstance(elem, str) and elem.startswith(":"):
            val = str(root[idx + 1])
            if elem == ":eid":
                eid_word = parse_word(val)
            elif elem == ":items":
                icount = int(val, 0)
            idx += 2
        elif isinstance(elem, list) and elem:
            sec_name = str(elem[0])
            sections[sec_name] = elem[1:]
            idx += 1
        else:
            raise ValueError(f"Unexpected element in defgool: {elem!r}")

    if eid_word is None:
        eid_word = encode_eid(name_sym)

    # 1. Header section (Item 0)
    hdr_map: Dict[str, int] = {}
    for entry in sections.get("header", []):
        assert isinstance(entry, list) and len(entry) == 2
        hdr_map[str(entry[0])] = int(str(entry[1]), 0) & 0xFFFFFFFF
    event_count = hdr_map.get("event-count", 0)
    item0 = struct.pack(
        "<6I",
        hdr_map.get("type", 0),
        hdr_map.get("category", 0),
        hdr_map.get("unk08", 0),
        hdr_map.get("sp-offset", 0),
        event_count,
        hdr_map.get("unk14", 0),
    )

    # 2. Code section (Item 1) + label table for states/events
    code_forms = sections.get("code", [])
    item1 = compile_code_section(code_forms)

    # Also build label_pcs so states/events can resolve symbolic `loc_XXXX` labels
    label_pcs: Dict[str, int] = {}
    pc_counter = 0

    def count_form(f: SExpr) -> None:
        nonlocal pc_counter
        if not isinstance(f, list) or not f:
            return
        h = str(f[0])
        if h == "label":
            label_pcs[str(f[1])] = pc_counter
            return
        for sub in f[1:]:
            if isinstance(sub, list):
                count_form(sub)
        pc_counter += 1

    for cf in code_forms:
        count_form(cf)

    def resolve_pc_tok(tok: str) -> int:
        if tok == "none" or tok == "null":
            return 0x3FFF
        if tok in label_pcs:
            return label_pcs[tok]
        if tok.startswith("loc_"):
            return int(tok[4:], 16)
        return int(tok, 0)

    # 3. Data section (Item 2)
    data_entries = sections.get("data", [])
    data_words: List[int] = [0] * len(data_entries)
    for pos_i, d_item in enumerate(data_entries):
        if isinstance(d_item, list) and len(d_item) == 2:
            d_idx = int(str(d_item[0]), 0)
            data_words[d_idx] = parse_word(str(d_item[1]))
        else:
            data_words[pos_i] = parse_word(str(d_item))
    item2 = struct.pack(f"<{len(data_words)}I", *data_words)

    items: List[bytes] = [item0, item1, item2]

    # 4. Events & Subtypes (Item 3) + States (Item 4) when icount >= 5
    if icount >= 5:
        ev_u16: List[int] = [0xFF] * event_count
        for ev_entry in sections.get("events", []):
            assert isinstance(ev_entry, list) and len(ev_entry) == 2
            ev_idx = int(str(ev_entry[0]), 0)
            target = ev_entry[1]
            if isinstance(target, list) and target[0] == "code":
                ev_u16[ev_idx] = 0x8000 | (resolve_pc_tok(str(target[1])) & 0x7FFF)
            else:
                st_str = str(target)
                st_num = int(st_str[6:], 0) if st_str.startswith("state_") else int(st_str, 0)
                ev_u16[ev_idx] = st_num & 0xFFFF

        for sub_tok in sections.get("subtypes", []):
            s_str = str(sub_tok)
            if s_str == "none":
                ev_u16.append(0xFF)
            elif s_str.startswith("state_"):
                ev_u16.append(int(s_str[6:], 0) & 0xFFFF)
            else:
                ev_u16.append(int(s_str, 0) & 0xFFFF)

        item3 = struct.pack(f"<{len(ev_u16)}H", *ev_u16)
        items.append(item3)

        state_buf = bytearray()
        for st_form in sections.get("states", []):
            assert isinstance(st_form, list) and st_form[0] == "defstate"
            kv: Dict[str, str] = {}
            j = 2
            while j < len(st_form):
                kv[str(st_form[j])] = str(st_form[j + 1])
                j += 2
            status_c = int(kv.get(":status-c", "0"), 0) & 0xFFFFFFFF
            flags = int(kv.get(":flags", "0"), 0) & 0xFFFFFFFF
            extern_idx = int(kv.get(":extern", "0"), 0) & 0xFFFF
            pc_ev = resolve_pc_tok(kv.get(":event", "none")) & 0xFFFF
            pc_tr = resolve_pc_tok(kv.get(":trans", "none")) & 0xFFFF
            pc_cd = resolve_pc_tok(kv.get(":code", "none")) & 0xFFFF
            state_buf.extend(struct.pack("<IIHHHH", status_c, flags, extern_idx, pc_ev, pc_tr, pc_cd))
        items.append(bytes(state_buf))

    # 5. Anims (Item 5) when icount >= 6
    if icount >= 6:
        item5 = compile_anims_section(sections.get("anims", []))
        items.append(item5)

    # Assemble full ResourceEntry (kind = 11)
    header_size = 16 + (len(items) + 1) * 4
    offsets: List[int] = []
    cur = header_size
    for it in items:
        offsets.append(cur)
        cur += len(it)
    offsets.append(cur)

    entry_hdr = struct.pack("<IIII", 0x0100FFFF, eid_word & 0xFFFFFFFF, 11, len(items))
    offs_packed = struct.pack(f"<{len(offsets)}I", *offsets)
    return entry_hdr + offs_packed + b"".join(items)


# ---------------------------------------------------------------------------
# CLI Commands
# ---------------------------------------------------------------------------

def _iter_nsf_files(path: Path) -> List[Path]:
    if path.is_file():
        return [path]
    return sorted(p for p in path.rglob("*.NSF") if p.is_file())


def cmd_decompile_nsf(args: argparse.Namespace) -> int:
    in_path = Path(args.nsf_or_dir)
    out_dir = Path(args.output)
    out_dir.mkdir(parents=True, exist_ok=True)

    nsf_files = _iter_nsf_files(in_path)
    if not nsf_files:
        print(f"No .NSF files found in {in_path}", file=sys.stderr)
        return 1

    canonical_written: Dict[str, str] = {}
    canonical_lower_written: Set[str] = set()
    variants_written: Set[Tuple[str, str]] = set()
    total_entries = 0

    for nsf_file in nsf_files:
        entries = extract_gool_entries_from_nsf(nsf_file.read_bytes(), str(nsf_file))
        for name, eid, raw in entries:
            total_entries += 1
            sha = hashlib.sha1(raw).hexdigest()[:8]
            if name not in canonical_written:
                gool_text = decompile_gool_entry(raw)
                stem = name if name.lower() not in canonical_lower_written else f"{name}_{eid:08x}"
                (out_dir / f"{stem}.gool").write_text(gool_text, encoding="utf-8")
                canonical_written[name] = sha
                canonical_lower_written.add(name.lower())
                variants_written.add((name, sha))
            elif (name, sha) not in variants_written:
                if args.all_variants:
                    gool_text = decompile_gool_entry(raw)
                    (out_dir / f"{name}_{sha}.gool").write_text(gool_text, encoding="utf-8")
                variants_written.add((name, sha))

    print(
        f"Decompiled {len(canonical_written)} unique GOOL executables "
        f"({len(variants_written)} unique binary variants across {total_entries} instances "
        f"in {len(nsf_files)} NSF files) -> {out_dir}"
    )
    return 0


def cmd_decompile(args: argparse.Namespace) -> int:
    raw = Path(args.input).read_bytes()
    text = decompile_gool_entry(raw)
    if args.output:
        Path(args.output).write_text(text, encoding="utf-8")
    else:
        sys.stdout.write(text)
    return 0


def cmd_compile(args: argparse.Namespace) -> int:
    text = Path(args.input).read_text(encoding="utf-8")
    raw = compile_gool_source(text)
    Path(args.output).write_bytes(raw)
    return 0


def cmd_verify(args: argparse.Namespace) -> int:
    nsf_dir = Path(args.nsf_dir)
    nsf_files = _iter_nsf_files(nsf_dir)
    if not nsf_files:
        print(f"No .NSF files found in {nsf_dir}", file=sys.stderr)
        return 1

    unique_blobs: Dict[str, Tuple[str, str, bytes]] = {}
    unique_names: Set[str] = set()
    total_instances = 0

    for nsf_file in nsf_files:
        for name, _eid, raw in extract_gool_entries_from_nsf(nsf_file.read_bytes(), str(nsf_file)):
            total_instances += 1
            unique_names.add(name)
            sha = hashlib.sha1(raw).hexdigest()
            if sha not in unique_blobs:
                unique_blobs[sha] = (name, nsf_file.name, raw)

    passed = 0
    for sha, (name, nsf_name, raw) in sorted(unique_blobs.items(), key=lambda kv: (kv[1][0], kv[0])):
        gool_src = decompile_gool_entry(raw)
        recompiled = compile_gool_source(gool_src)
        re_sha = hashlib.sha1(recompiled).hexdigest()
        if recompiled != raw or re_sha != sha:
            print(
                f"FAIL: {name} ({nsf_name}): expected SHA-1 {sha}, got {re_sha} "
                f"(len {len(raw)} vs {len(recompiled)})",
                file=sys.stderr,
            )
            return 1
        passed += 1

    print(
        f"VERIFIED 100% byte-for-byte SHA-1 match across all {len(unique_names)} unique GOOL "
        f"object classes, {passed}/{len(unique_blobs)} unique binary variants, and "
        f"{total_instances} total instances in {len(nsf_files)} NSF files!"
    )
    return 0


def build_arg_parser() -> argparse.ArgumentParser:
    parser = argparse.ArgumentParser(
        description="Crash Bandicoot (SCUS-949.00) GOOL Bytecode Decompiler & Assembler"
    )
    sub = parser.add_subparsers(dest="command", required=True)

    p_dnsf = sub.add_parser("decompile-nsf", help="Extract and decompile GOOL entries from .NSF file(s)")
    p_dnsf.add_argument("nsf_or_dir", help="Path to an .NSF file or directory containing .NSF files")
    p_dnsf.add_argument("-o", "--output", required=True, help="Output directory for .gool files")
    p_dnsf.add_argument(
        "--all-variants",
        action="store_true",
        help="Also write per-level variant .gool files (<Name>_<sha8>.gool)",
    )
    p_dnsf.set_defaults(func=cmd_decompile_nsf)

    p_dec = sub.add_parser("decompile", help="Decompile a single raw etype == 11 binary entry to .gool")
    p_dec.add_argument("input", help="Input binary GOOL entry (.bin)")
    p_dec.add_argument("-o", "--output", help="Output .gool file (default: stdout)")
    p_dec.set_defaults(func=cmd_decompile)

    p_cmp = sub.add_parser("compile", help="Compile/assemble a .gool file back to a binary etype == 11 entry")
    p_cmp.add_argument("input", help="Input .gool file")
    p_cmp.add_argument("-o", "--output", required=True, help="Output binary entry (.bin)")
    p_cmp.set_defaults(func=cmd_compile)

    p_ver = sub.add_parser(
        "verify",
        help="Verify 100% round-trip byte-for-byte identity across all GOOL entries in .NSF files",
    )
    p_ver.add_argument(
        "--nsf-dir",
        default="build/extract/USA/files",
        help="Directory containing extracted .NSF files (default: build/extract/USA/files)",
    )
    p_ver.set_defaults(func=cmd_verify)

    return parser


def main(argv: Optional[Sequence[str]] = None) -> int:
    parser = build_arg_parser()
    args = parser.parse_args(argv)
    return args.func(args)


if __name__ == "__main__":
    sys.exit(main())
