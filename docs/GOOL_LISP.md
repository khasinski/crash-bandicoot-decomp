# GOOL (Game Object Oriented Lisp) VM & Bytecode Reference

This document specifies the **GOOL (Game Object Oriented Lisp)** virtual machine, binary resource format (`etype == 11`), 12-bit General Operand (`GOP`) encoding, object register file (`0x00..0x3F`), instruction set (`0x00..0x91`), and the round-trip verified `.gool` decompiler/assembler in [`tools/scripts/gool_lisp.py`](../tools/scripts/gool_lisp.py).

All details are derived directly from the matching decompilation of the retail `SCUS-949.00` executable:
- [`src/main/gool/interpret.c`](../src/main/gool/interpret.c) — `GOOL_InterpretObject` (`0x800201DC`)
- [`src/main/gool/translate_gop.c`](../src/main/gool/translate_gop.c) — `GOOL_TranslateGop` (`0x8001FB34`)
- [`src/main/gool/vm_operands.c`](../src/main/gool/vm_operands.c) — `func_8001FC4C` (`0x8001FC4C`) and gamepad decoder `func_8001FDC4`
- [`src/main/gool/change_state.c`](../src/main/gool/change_state.c) — `GOOL_ChangeObjectState` (`0x8001D698`)
- [`src/main/gool/create_object.c`](../src/main/gool/create_object.c) — `GOOL_CreateObject` (`0x8001C1B8`) and `GOOL_InitObject` (`0x8001C34C`)
- [`src/main/gool/send_event.c`](../src/main/gool/send_event.c) — `func_80024040` (`0x80024040`)
- [`src/main/gool/update_object.c`](../src/main/gool/update_object.c) — `GOOL_UpdateObject` (`0x8001DA00`) and `func_8001DE78`
- [`src/main/ns/page_4170.c`](../src/main/ns/page_4170.c) — `func_80013970` (`0x80013970`, LZSS `0x1235` page decompressor)

---

## 1. Binary Resource Entry Format (`etype == 11`)

Inside `.NSF` page archives, every GOOL executable is a `ResourceEntry` with `kind == 11` (`0x0B`) and a 5-character EID ending in `C` (e.g. `WillC`, `BoxsC`, `DoctC`):

| Offset | Type | Field | Description |
|---|---|---|---|
| `+0x00` | `u32` | `magic` | Always `0x0100FFFF` |
| `+0x04` | `u32` | `eid` | 32-bit encoded 5-char EID (`bit 0 == 1`, bits `1..30` = five 6-bit chars in `0123456789abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ_!`) |
| `+0x08` | `s32` | `kind` | `11` (`0x0B`, GOOL executable) |
| `+0x0C` | `s32` | `item_count` | `6` for full executables (`3` for external code/header helpers `ShabC`, `Wil9C`, `WilhC`; `5` when `anims` is omitted) |
| `+0x10` | `u32[item_count + 1]` | `item_offsets` | Byte offsets from start of entry to each item (`item_offsets[item_count] == sizeof(entry)`) |

### The 6 Items of a GOOL Executable

1. **Item 0 — `header` (`GoolCodeHeader`, 24 bytes / six `u32` words)**:
   - `word[0]` (`type`): Global object type / executable ID (`0` = `WillC` / Crash, `3` = `FruiC`, `4` = `DispC`, `5` = `DoctC`, `34` = `BoxsC`, etc.).
   - `word[1]` (`category`): Object process/update category (`0x100`, `0x200`, `0x300`, `0x400`, `0x500`, `0x600`).
   - `word[2]` (`unk08`): `1` for standalone executables, `0` for external helper executables (`icount == 3`).
   - `word[3]` (`sp_offset`): Initial stack pointer register index relative to `GoolObj + 0x60` (e.g. `64..103`). Object registers `0x40 .. sp_offset - 1` (`field-0`, `field-1`, ...) are per-object member variables below the call stack.
   - `word[4]` (`event_count`): Number of `u16` event handler slots at the start of Item 3 before the subtype-to-state map begins.
   - `word[5]` (`unk14`): Auxiliary count/metadata word.

2. **Item 1 — `code` (`u32[]`)**:
   - Array of 32-bit big-opcode (`ins >> 24`) VM instructions.

3. **Item 2 — `data` (`u32[]`)**:
   - Pool of 32-bit constants, fixed-point numbers, bitmasks, and resource EIDs (sound effects, textures, models, external GOOL executables).

4. **Item 3 — `events` & `subtypes` (`u16[]`)**:
   - `u16[0 .. event_count - 1]`: Maps `(event_id >> 8)` to:
     - `0x00FF`: Unhandled (`none`)
     - `0x8000 | code_word_offset`: Immediate event coroutine at `code[offset]`
     - `0x0000..0x00FE`: State index (`state_N`) to transition into when the event arrives
   - `u16[event_count .. end]`: Maps `obj->subtype` at spawn time (`GOOL_InitObject`) to its initial state index (`state_N` or `0xFF` for `none`).

5. **Item 4 — `states` (`GoolState[]`, 16 bytes per state)**:
   ```c
   typedef struct GoolState {
       u32 status_c;    // +0x00: Copied to obj->state_flags (+0x120)
       u32 flags;       // +0x04: Copied to obj->status_c (+0xD0)
       u16 extern_idx;  // +0x08: Index into Item 2 (data) for obj->external executable EID
       u16 pc_event;    // +0x0A: Code word offset for state event handler (or 0x3FFF = none) -> obj->ep (+0xEC)
       u16 pc_trans;    // +0x0C: Code word offset for per-frame trans block (or 0x3FFF = none) -> obj->tp (+0xE8)
       u16 pc_code;     // +0x0E: Code word offset for main coroutine (or 0x3FFF = none) -> obj->pc (+0xE0)
   } GoolState;
   ```

6. **Item 5 — `anims` (variable-length 4-byte-aligned animation records)**:
   Referenced by byte offset `(ins >> 5) & 0x7FC` in `anim-seq` (`0x83`) or `(*s_ptr >> 8) << 2` in `load-anim` (`0x27`). Each record begins with `u8 type, u8 pad (0), u16 count`:
   - `type == 1` (`vertex-anim`, 8 bytes): `u8 type=1, u8 pad=0, u16 frames, u32 vertex_anim_eid` (`*V` / `*I`).
   - `type == 2` (`sprite-anim`, `8 + frames * 8` bytes): `u8 type=2, u8 pad=0, u16 frames, u32 tex_eid`, followed by `frames` 8-byte sprite descriptors.
   - `type == 3` (`font`, `8 + glyphs * 12` bytes): `u8 type=3, u8 pad=0, u16 glyph_count, u32 tex_eid`, followed by `glyph_count` 12-byte `GoolGlyph` records (`u32 word0, u32 word1, s16 width, s16 height`).
   - `type == 4` (`text-anim`, `12 + aligned_strings` bytes): `u8 type=4, u8 pad=0, u16 string_count, u32 eid, u32 font_word_offset`, followed by `string_count` null-terminated ASCII/format strings padded with `0x00` to 4 bytes.
   - `type == 5` (`frag-anim`, `12 + frames * frags_per_frame * 16` bytes): `u8 type=5, u8 pad=0, u16 frames, u32 tex_eid, u32 frags_per_frame`, followed by 16-byte `GoolFrag` records (`u32 tex0, u32 tex1, s16 x1, s16 y1, s16 x2, s16 y2`).

---

## 2. 12-Bit GOP (General Operand) Encoding

Decoded by `TRANS_GOP_IN`, `TRANS_GOP_OUT`, and `GOOL_TranslateGop` (`0x8001FB34`):

| 12-Bit Range | Binary Pattern | Meaning in VM | `.gool` Lisp Syntax |
|---|---|---|---|
| `0x000..0x3FF` | `00ii iiiiiiii` | `self->exec->data[idx]` (Item 2 constant pool) | `data[idx]` |
| `0x400..0x7FF` | `01ii iiiiiiii` | `self->external->data[idx]` (External constant pool) | `ext[idx]` |
| `0x800..0x9FF` | `100i iiiiiiii` | Signed 9-bit immediate shifted left by 8 (`imm9 << 8`, `-65536..65280`) | Integer literal (e.g. `0`, `256`, `-256`) |
| `0xA00..0xAFF` | `1010 iiiiiiii` | Signed 8-bit immediate shifted left by 4 (`imm8 << 4`, `-2048..2032`) | Integer literal (e.g. `16`, `-32`) or `imm4[val]` |
| `0xB00..0xB7F` | `1011 0iiiiiii` | Stack frame relative `self->fp[sign_ext7(off)]` (`-64..63`) | `fp[off]` (e.g. `fp[-1]`, `fp[3]`) |
| `0xBE0` | `1011 11100000` | `NULL` pointer | `null` |
| `0xBF0` | `1011 11110000` | Dynamic stack `(target, rate)` pop marker for `seek` / `oscillate` | `var-rate` |
| `0xC00..0xDFF` | `110l llrrrrrr` | Indirect link register `self->links[l]->reg[r]` (`l = 0..7`, `r = 0..0x3F`) | `<link>.<reg>` (e.g. `player.x`, `parent.status-b`, `self.subtype`) |
| `0xE00..0xFFF` | `111r rrrrrrrr` | Direct `self` register (`r = 0..0x1FF`); `0xE1F` pops on read / pushes on write | `<reg>` (e.g. `x`, `vel-y`, `tos`, `field-0`) |

### Object Links (`0..7` at `GoolObj + 0x60..0x7C`)
| Index | Name | Offset | Description |
|---|---|---|---|
| `0` | `self` | `+0x60` | Pointer to this `GoolObj` |
| `1` | `parent` | `+0x64` | Parent object in hierarchy |
| `2` | `sibling` | `+0x68` | Next sibling object (`next`) |
| `3` | `child` | `+0x6C` | First child object (`children`) |
| `4` | `creator` | `+0x70` | Object that spawned this object |
| `5` | `player` | `+0x74` | Crash (`D_80060DB0[0]`) |
| `6` | `collider` | `+0x78` | Colliding object (`unk78`) |
| `7` | `interrupter` | `+0x7C` | Event sender / interrupter object (`unk7C`) |

---

## 3. Object Register Map (`0x00..0x3F` at `GoolObj + 0x60..0x15C`)

| Reg | `GoolObj` Offset | Symbolic Name | C Struct Field / Role |
|---|---|---|---|
| `0x00..0x07` | `+0x60..+0x7C` | `self`, `parent`, `sibling`, `child`, `creator`, `player`, `collider`, `interrupter` | Object link pointers (`links[0..7]`) |
| `0x08..0x0A` | `+0x80..+0x88` | `x`, `y`, `z` | `trans` (`Vec3` world position, `vec 0`) |
| `0x0B..0x0D` | `+0x8C..+0x94` | `rot-x`, `rot-y`, `rot-z` | `rot` (`Vec3` Euler angles, `vec 1`) |
| `0x0E..0x10` | `+0x98..+0xA0` | `scale-x`, `scale-y`, `scale-z` | `scale` (`Vec3` scale, `0x1000` = 1.0, `vec 2`) |
| `0x11..0x13` | `+0xA4..+0xAC` | `vel-x`, `vel-y`, `vel-z` | `vel` (`Vec3` linear velocity, `vec 3`) |
| `0x14..0x16` | `+0xB0..+0xB8` | `ang-vel-x`, `ang-vel-y`, `ang-vel-z` | `ang_vel` (`Vec3` angular velocity / approach angles, `vec 4`) |
| `0x17..0x19` | `+0xBC..+0xC4` | `target-rot-x`, `target-rot-y`, `target-rot-z` | `target_rot` (`Vec3` initial entity angles / path error, `vec 5`) |
| `0x1A` | `+0xC8` | `status-a` | Primary runtime status flags |
| `0x1B` | `+0xCC` | `status-b` | Physics / collision / rendering behavior flags |
| `0x1C` | `+0xD0` | `status-c` | State mask flags (initialized from `GoolState.flags`) |
| `0x1D` | `+0xD4` | `subtype` | Entity subtype index |
| `0x1E` | `+0xD8` | `pid-flags` | Level entity ID (`id << 8`) and persistence flags |
| `0x1F` | `+0xDC` | `tos` / `sp` | Stack pointer (`0xE1F` / reg `0x1F` pops on input, pushes on output) |
| `0x20` | `+0xE0` | `pc` | VM program counter (`u32 *`) |
| `0x21` | `+0xE4` | `fp` | VM frame pointer (`s32 *`) |
| `0x22` | `+0xE8` | `tp` | Per-frame transition block pointer (`pc_trans`) |
| `0x23` | `+0xEC` | `ep` | Event handler block pointer (`pc_event`) |
| `0x24` | `+0xF0` | `sr` | Saved state-return block pointer |
| `0x25` | `+0xF4` | `v0` | Return / result accumulator register |
| `0x26` | `+0xF8` | `a0` | Scratch / argument register 0 |
| `0x27` | `+0xFC` | `stamp` (`a1`) | Object update frame timestamp |
| `0x28` | `+0x100` | `state-stamp` (`a2`) | Timestamp of last state change |
| `0x29` | `+0x104` | `anim-counter` (`a3`) | Frame stagger / animation counter |
| `0x2A` | `+0x108` | `anim-seq` | Current `GoolAnimSeq *` pointer |
| `0x2B` | `+0x10C` | `anim-frame` | Current animation frame index (`frame << 8`) |
| `0x2C` | `+0x110` | `entity` | Spawned `ZoneEntity *` pointer |
| `0x2D` | `+0x114` | `path-progress` | Fixed-point progress (`seg << 8 | frac`) along entity path |
| `0x2E` | `+0x118` | `path-length` | Path vertex count (`count << 8`) |
| `0x2F` | `+0x11C` | `floor-y` | Last detected floor Y coordinate |
| `0x30` | `+0x120` | `state-flags` | State category flags (initialized from `GoolState.status_c`) |
| `0x31` | `+0x124` | `speed` | Scalar horizontal speed |
| `0x32` | `+0x128` | `invincibility-state` | Invincibility / Aku Aku / font override state |
| `0x33` | `+0x12C` | `invincibility-time` | Timestamp of invincibility change |
| `0x34` | `+0x130` | `floor-time` | Timestamp of last floor contact |
| `0x35` | `+0x134` | `floor-vel-y` | Vertical velocity at impact |
| `0x36` | `+0x138` | `cam-zoom` | Depth / ordering table bias |
| `0x37` | `+0x13C` | `event` | Last received event ID |
| `0x38..0x3A` | `+0x140..+0x148` | `cam-rot-x`, `cam-rot-y`, `cam-rot-z` | Camera / auxiliary rotation registers |
| `0x3B` | `+0x14C` | `voice-id` | Active SPU voice ID |
| `0x3C` | `+0x150` | `reg-3c` | Scratch register `0x3C` |
| `0x3D` | `+0x154` | `path-radius` | Maximum path divergence radius |
| `0x3E` | `+0x158` | `node-id` | Scene graph node ID |
| `0x3F` | `+0x15C` | `reg-3f` | Scratch register `0x3F` |
| `0x40+` | `+0x160+` | `field-0`, `field-1`, ... | Object-specific local fields below `sp-offset` |

---

## 4. Complete Opcode Table (`0x00..0x91`)

In two-GOP instructions `(op s d)`, `s = (ins >> 12) & 0xFFF` is evaluated (and popped, if `s == tos`) **first**, and `d = ins & 0xFFF` is evaluated (and popped, if `d == tos`) **second**.

| Opcode | `.gool` Lisp Form | Semantics in `GOOL_InterpretObject` |
|---|---|---|
| `0x00` | `(add s d)` | `*sp++ = d + s` |
| `0x01` | `(sub s d)` | `*sp++ = d - s` |
| `0x02` | `(mul s d)` | `*sp++ = d * s` |
| `0x03` | `(div s d)` | `*sp++ = d / s` |
| `0x04` | `(equ s d)` | `*sp++ = (s == d)` |
| `0x05` | `(and s d)` | `*sp++ = (d && s)` |
| `0x06` | `(or s d)` | `*sp++ = (d \|\| s)` |
| `0x07` | `(bit-and s d)` | `*sp++ = s & d` |
| `0x08` | `(bit-or s d)` | `*sp++ = s \| d` |
| `0x09` | `(gt s d)` | `*sp++ = (s > d)` (`d < s`) |
| `0x0A` | `(gte s d)` | `*sp++ = (s >= d)` (`d <= s`) |
| `0x0B` | `(lt s d)` | `*sp++ = (s < d)` (`d > s`) |
| `0x0C` | `(lte s d)` | `*sp++ = (s <= d)` (`d >= s`) |
| `0x0D` | `(mod s d)` | `*sp++ = d % s` |
| `0x0E` | `(xor s d)` | `*sp++ = s ^ d` |
| `0x0F` | `(bit-test s d)` | `*sp++ = !((s & d) ^ s)` (tests if all bits of `s` are set in `d`) |
| `0x10` | `(rnd s d)` | `*sp++ = rand(s - d) + d` |
| `0x11` | `(move s d)` / `(push s)` | `*d = s` (rendered as `(push s)` when `d == tos`) |
| `0x12` | `(not s d)` | `*d = (s == 0)` |
| `0x13` | `(oscillate s d)` | Triangle-wave oscillation of `d` within limit `s`, writes `d` and pushes clamped value |
| `0x14` | `(lea s d)` | `*d = (s32)&s` (load effective address of GOP `s`) |
| `0x15` | `(shl s d)` | `*sp++ = (s < 0) ? (d >> -s) : (d << s)` |
| `0x16` | `(push2 s d)` | Pushes `*d` then `*s` onto stack |
| `0x17` | `(bit-not s d)` | `*d = ~s` |
| `0x18` | `(code-ptr reg loc_XXXX)` | `*reg = &exec->code[offset]` (`null` if `0x3FFF`) |
| `0x19` | `(abs s d)` | `*d = ABS(s)` |
| `0x1A` | `(pad mask)` | `*sp++ = func_8001FDC4(mask, 0)` (controller button/direction test) |
| `0x1B` | `(scale-dt s d)` | `*sp++ = d + SCALE_DT(s)` |
| `0x1C` | `(<misc-subop> link subarg gop)` | 16 sub-opcodes (`0..15`): `entity-field`, `dist-obj`, `ang-to`, `read-reg-indir`, `write-reg-indir`, `ang-diff-y`, `dist-vec`, `find-obj-by-id`, `pid-bit2`, `set-zone`, `pid-flags-op`, `pid-flags-test`, `level-op`, `find-nearest-obj`, `test-collision-box`, `memcard-op` |
| `0x1D` | `(sin s d)` | `*sp++ = sin_wave(period=s, phase=d)` |
| `0x1E` | `(mod-frame s d)` | `*sp++ = (s + global_frame) % d` |
| `0x1F` | `(load-global idx)` | `*sp++ = D_8006188C[idx >> 8]` |
| `0x20` | `(store-global s d)` | `D_8006188C[d >> 8] = s` |
| `0x21` | `(ang-diff s d)` | `*sp++ = func_800245F0(d, s)` |
| `0x22` | `(seek s d)` | `*sp++ = func_80024628(d, target=s, rate)` (linear value seek) |
| `0x23` | `(load-color link idx)` | `*sp++ = link->defaults[idx]` |
| `0x24` | `(store-color link idx d)` | `link->defaults[idx] = (u16)d` |
| `0x25` | `(seek-ang s d)` | `*sp++ = func_800243A0(d, target=s, rate, 0)` (angular seek) |
| `0x26` | `(lea2 s d)` | Pushes `&d` then `&s` onto stack |
| `0x27` | `(load-anim s d)` | `*d = (s32)&exec->anims[(s >> 8) << 2]` |
| `0x80` | `(nop)` | No operation |
| `0x81` | `(debug s d)` | Retail no-op (two 12-bit GOP operands) |
| `0x82` | `(bra\|bnez\|beqz ...)`, `(change-state ...)`, `(ret ...)` | Control flow: `mode 0` = relative branch (with optional `:pop N`), `mode 1` = `GOOL_ChangeObjectState`, `mode 2` = return from frame |
| `0x83` | `(anim-seq off frame wait flip)` | Sets `anim_seq = anims + off`, `anim_frame = frame << 8`, pushes wait entry, applies X-scale flip (`pos`/`neg`/`flip`/`keep`), yields coroutine |
| `0x84` | `(anim-frame gop wait flip)` | Sets `anim_frame = gop`, pushes wait entry, updates bounding box, yields coroutine |
| `0x85` | `(<vec-subop> ...)` | Vector/path operations (`0..7`): `path-follow`, `project-3d`, `vel-from-ang`, `transform-local`, `transform-ang-vel`, `joint-transform`, `project-2d` |
| `0x86` | `(jal argc loc_XXXX)` | Pushes stack frame with `argc` args and jumps to `exec->code[offset]` |
| `0x87` | `(send-event link ev argc cond)` | Sends `ev` with `argc` stack args to `link` if `cond != 0` (`func_80024040`) |
| `0x88` | `(event-*-reject ...)` | Event handler return/branch/state transition with `out_state->flag = 0` |
| `0x89` | `(event-*-accept ...)` | Event handler return/branch/state transition with `out_state->flag = 1` |
| `0x8A` | `(spawn exec_id sub argc count)` | Spawns `count` child object(s) (`flag = 0`) via `GOOL_CreateObject` |
| `0x8B` | `(ns-ctrl s d)` | Resource subsystem page/entry load/unload (`func_80015118` / `func_80015458` / `func_800156D4` / `func_8001579C`) |
| `0x8C` | `(play-sound s d)` | `voice_id = func_800304C8(obj, d, (s16)s)` |
| `0x8D` | `(audio-ctrl mode flags reg gop)` | Voice pitch/volume/pan/fade control (`func_80030840`) |
| `0x8E` | `(collide subop dst src gop)` | Terrain/wall/ceiling/water collision probes (`func_800277EC`, `func_80028644`, `func_80028E3C`, `func_8002940C`) |
| `0x8F` | `(broadcast-event mode ev argc cond)` | Broadcasts `ev` across object tree (`func_80025134`) |
| `0x90` | `(send-event-tree link ev argc cond)` | Sends `ev` to `link` and its descendants (`func_800251B8`) |
| `0x91` | `(spawn-urgent exec_id sub argc count)` | Spawns `count` child object(s) (`flag = 1`, evicting disposable objects if pool is full) |

---

## 5. Catalog of All 60 Retail GOOL Executables (`SCUS-949.00`)

Across the 44 `.NSF` archives on the `SCUS-949.00` disc, there are **60 unique GOOL object classes** (`*C`), **193 unique binary variants**, and **837 total entry instances**:

| Name | EID (`u32`) | Type ID | Category | Items | `sp-offset` | States | Instructions | Data Words | Disc Variants |
|---|---|---|---|---|---|---|---|---|---|
| `AsciC` | `0x48E1894D` | `60` | `0x500` | `6` | `67` | `3` | `68` | `7` | `1` |
| `BaraC` | `0x4A53654D` | `16` | `0x300` | `6` | `69` | `5` | `208` | `42` | `1` |
| `BeaOC` | `0x4A71594D` | `27` | `0x500` | `6` | `68` | `3` | `148` | `25` | `1` |
| `BonoC` | `0x4AC2EC4D` | `56` | `0x300` | `6` | `67` | `10` | `6191` | `103` | `4` |
| `BoxsC` | `0x4AC42E4D` | `34` | `0x400` | `6` | `82` | `33` | `1845` | `90` | `13` |
| `BriOC` | `0x4ADA594D` | `41` | `0x500` | `6` | `67` | `7` | `305` | `47` | `1` |
| `BridC` | `0x4ADA46CD` | `23` | `0x500` | `6` | `71` | `9` | `355` | `47` | `1` |
| `BrioC` | `0x4ADA4C4D` | `40` | `0x300` | `6` | `73` | `9` | `1032` | `79` | `1` |
| `CardC` | `0x4C5366CD` | `57` | `0x500` | `6` | `80` | `66` | `6089` | `137` | `3` |
| `CasOC` | `0x4C53994D` | `53` | `0x500` | `6` | `84` | `26` | `888` | `83` | `3` |
| `CheOC` | `0x4C89D94D` | `21` | `0x500` | `6` | `68` | `1` | `86` | `13` | `1` |
| `ChefC` | `0x4C89C7CD` | `20` | `0x300` | `6` | `68` | `4` | `721` | `64` | `1` |
| `CorOC` | `0x4CC3794D` | `50` | `0x500` | `6` | `68` | `15` | `838` | `62` | `1` |
| `CortC` | `0x4CC36ECD` | `49` | `0x300` | `6` | `72` | `7` | `2294` | `64` | `1` |
| `CrabC` | `0x4CD945CD` | `31` | `0x300` | `6` | `65` | `4` | `168` | `27` | `1` |
| `DispC` | `0x4E938CCD` | `4` | `0x200` | `6` | `80` | `18` | `668` | `38` | `12` |
| `DoctC` | `0x4EC18ECD` | `5` | `0x100` | `6` | `82` | `10` | `779` | `66` | `6` |
| `Dog_C` | `0x4EC21F4D` | `13` | `0x300` | `6` | `66` | `7` | `215` | `27` | `1` |
| `FatsC` | `0x5253AE4D` | `17` | `0x300` | `6` | `64` | `4` | `243` | `31` | `1` |
| `FruiC` | `0x52DBC94D` | `3` | `0x400` | `6` | `75` | `17` | `1138` | `89` | `12` |
| `GamOC` | `0x5452D94D` | `52` | `0x300` | `6` | `85` | `30` | `3044` | `263` | `4` |
| `GemsC` | `0x5472CE4D` | `58` | `0x400` | `6` | `80` | `5` | `490` | `49` | `7` |
| `IsldC` | `0x58E2A6CD` | `59` | `0x100` | `6` | `89` | `5` | `874` | `83` | `1` |
| `JunOC` | `0x5AF2F94D` | `22` | `0x500` | `6` | `76` | `12` | `657` | `96` | `5` |
| `KonOC` | `0x5CC2F94D` | `30` | `0x300` | `6` | `67` | `12` | `532` | `51` | `1` |
| `KongC` | `0x5CC2E84D` | `45` | `0x300` | `6` | `67` | `7` | `416` | `34` | `3` |
| `LabAC` | `0x5E51724D` | `54` | `0x300` | `6` | `73` | `16` | `946` | `75` | `2` |
| `LizaC` | `0x5E94654D` | `47` | `0x300` | `6` | `77` | `4` | `524` | `41` | `1` |
| `MafiC` | `0x6051E94D` | `12` | `0x300` | `6` | `68` | `9` | `399` | `52` | `2` |
| `MonkC` | `0x60C2EA4D` | `1` | `0x300` | `6` | `66` | `6` | `375` | `41` | `1` |
| `Opt0C` | `0x64CBA04D` | `48` | `0x500` | `6` | `70` | `4` | `328` | `27` | `1` |
| `PillC` | `0x6692AACD` | `35` | `0x300` | `6` | `70` | `5` | `312` | `34` | `2` |
| `PinOC` | `0x6692F94D` | `18` | `0x500` | `6` | `67` | `6` | `271` | `29` | `1` |
| `PinsC` | `0x6692EE4D` | `15` | `0x300` | `6` | `76` | `11` | `806` | `61` | `1` |
| `PlanC` | `0x66A94BCD` | `25` | `0x300` | `6` | `68` | `6` | `339` | `32` | `4` |
| `PoDoC` | `0x66C4EC4D` | `8` | `0x500` | `6` | `67` | `13` | `204` | `26` | `2` |
| `PoObC` | `0x66C645CD` | `14` | `0x500` | `6` | `68` | `8` | `197` | `25` | `1` |
| `PoPlC` | `0x66C66ACD` | `11` | `0x600` | `6` | `77` | `12` | `591` | `45` | `12` |
| `PoREC` | `0x66C6B44D` | `10` | `0x300` | `6` | `68` | `4` | `125` | `22` | `2` |
| `PoRoC` | `0x66C6AC4D` | `9` | `0x300` | `6` | `77` | `19` | `922` | `77` | `6` |
| `RRooC` | `0x6BAB0C4D` | `37` | `0x300` | `6` | `78` | `5` | `318` | `36` | `1` |
| `RWaOC` | `0x6BD1594D` | `46` | `0x600` | `6` | `103` | `19` | `1191` | `77` | `2` |
| `RivOC` | `0x6A93F94D` | `28` | `0x600` | `6` | `79` | `17` | `1012` | `72` | `2` |
| `RooOC` | `0x6AC3194D` | `39` | `0x500` | `6` | `71` | `9` | `375` | `53` | `1` |
| `RuiOC` | `0x6AF2594D` | `42` | `0x600` | `6` | `101` | `22` | `1245` | `86` | `3` |
| `ShabC` | `0x6C8945CD` | `29` | `0x100` | `3` | `81` | `0` | `146` | `0` | `1` |
| `ShadC` | `0x6C8946CD` | `29` | `0x100` | `6` | `81` | `7` | `159` | `22` | `9` |
| `SheNC` | `0x6C89D8CD` | `38` | `0x300` | `6` | `76` | `7` | `372` | `36` | `2` |
| `SpidC` | `0x6CCA46CD` | `43` | `0x300` | `6` | `76` | `12` | `601` | `56` | `1` |
| `TurtC` | `0x6EF36ECD` | `19` | `0x300` | `6` | `70` | `5` | `460` | `51` | `4` |
| `VilOC` | `0x7292B94D` | `51` | `0x500` | `6` | `64` | `6` | `159` | `18` | `2` |
| `WalOC` | `0x7452B94D` | `33` | `0x600` | `6` | `76` | `21` | `723` | `68` | `2` |
| `WarpC` | `0x74536CCD` | `32` | `0x500` | `6` | `64` | `6` | `323` | `34` | `2` |
| `WartC` | `0x74536ECD` | `7` | `0x300` | `6` | `67` | `5` | `154` | `24` | `1` |
| `WateC` | `0x7453A74D` | `55` | `0x500` | `6` | `66` | `2` | `89` | `15` | `5` |
| `Wil9C` | `0x7492A4CD` | `0` | `0x100` | `3` | `84` | `0` | `162` | `0` | `1` |
| `WilhC` | `0x7492A8CD` | `0` | `0x100` | `3` | `84` | `0` | `549` | `0` | `1` |
| `WillC` | `0x7492AACD` | `0` | `0x100` | `6` | `84` | `42` | `2832` | `223` | `23` |
| `WinGC` | `0x7492F54D` | `61` | `0x300` | `6` | `71` | `36` | `2628` | `274` | `3` |
| `frogC` | `0x1EDB084D` | `36` | `0x300` | `6` | `78` | `10` | `592` | `57` | `2` |

---

## 6. Usage of `tools/scripts/gool_lisp.py`

```bash
# 1. Extract and decompile all 60 GOOL executables from .NSF archives into build/gool/
python3 tools/scripts/gool_lisp.py decompile-nsf build/extract/USA/files -o build/gool

# Include all 193 per-level binary variants (<Name>_<sha8>.gool)
python3 tools/scripts/gool_lisp.py decompile-nsf build/extract/USA/files -o build/gool --all-variants

# 2. Decompile a single raw etype == 11 binary entry to .gool Lisp
python3 tools/scripts/gool_lisp.py decompile entry.bin -o WillC.gool

# 3. Compile/assemble a .gool Lisp file back into a binary etype == 11 entry
python3 tools/scripts/gool_lisp.py compile build/gool/WillC.gool -o WillC.bin

# 4. Run full round-trip SHA-1 verification across all .NSF archives
python3 tools/scripts/gool_lisp.py verify --nsf-dir build/extract/USA/files
```
