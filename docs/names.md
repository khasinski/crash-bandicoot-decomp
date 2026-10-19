# Symbol Naming Guide & Complete Catalog (`SCUS_949.00`)

This document is the authoritative reference for function and global variable names in the `crash-pc` decompilation of *Crash Bandicoot* (NTSC-U `SCUS-949.00`). It establishes:
1. **Naming conventions** for game subsystems and Sony PsyQ 3.5/3.6 SDK library code.
2. **Defects in the current symbol table** (`configs/USA/sym.main.txt`) and misplaced translation units that must be corrected before or during a rename pass.
3. **Complete function catalogs** for all **825 functions** in `.text` (`0x8001177C..0x800514DC`: **365 game functions** and **460 Sony PsyQ SDK functions**).
4. **Global variable & data table catalogs** across `.rdata`, `.data`, `.sdata`, `.sbss`, and `.bss` (`0x80011000..0x80061A78`).

---

## 1. Sources of Evidence

Every symbol name in this catalog is backed by one or more of the following primary sources:

1. **Sony PsyQ 3.5 / 3.6 SDK Object Archives (`.lib` / `.a`)**:
   - Verified via `mipsel-linux-gnu-nm` and `mipsel-linux-gnu-objdump` against the PsyQ 3.5 library archives (`MALLOC4.O`, `LIBC.A`, `LIBSN.LIB`, `LIBAPI.A`, `LIBETC.A`, `LIBGPU.A`, `LIBGTE.A`, `LIBCD.A`, `LIBSPU.A`, `LIBSND.A`, `LIBCARD.A`).
   - Provides **exact original Sony symbol names** (both exported `T` globals and internal `t` file-static helpers) and exact `.o` archive member boundaries for `0x8001177C..0x80011D84` and `0x8003D680..0x800514DC`.
2. **PSX BIOS Vector Numbers (`A0` / `B0` / `C0` Jump Tables & Syscalls)**:
   - Every 4-instruction BIOS trampoline (`addiu $t2, $zero, 0xA0|0xB0|0xC0; jr $t2; addiu $t1, $zero, <vec>`) maps 1-to-1 to a standard PlayStation kernel vector.
3. **In-Binary Debug Strings & Format Literals (`.rdata` / `.data` / `.sdata`)**:
   - Retained `printf` / `puts` strings (`"malloc: size should be > 0.\n"`, `"reading file system\n"`, `"Crash (%d%%)"`, `"PART %d of %d"`, `"Damaged slot"`, `"bu00:BASCUS-94900"`, `"Can't Open Sequence data any more\n"`, CD command/interrupt string tables, GPU RCS IDs) directly anchor the surrounding functions.
4. **Community Reverse-Engineering Reference (`wurlyfox/c1` & `wurlyfox/c1c`)**:
   - Provides established community names, subsystem groupings (`main.c`, `ns.c`, `pad.c`, `gfx.c`, `gool.c`, `level.c`, `slst.c`, `math.c`, `cam.c`, `solid.c`, `pbak.c`, `misc.c`, `audio.c`, `midi.c`, `title.c`, `psx/init.c`, `psx/gpu.c`, `psx/cdr.c`, `psx/r3000a.c`, `psx/card.c`), and `gp`-relative global variable mappings.
   - **Important**: As documented in Section 3 below, `wurlyfox/c1c` had an off-by-one address shift around `0x8001B3F0..0x8001B6F0` that was inherited into `configs/USA/sym.main.txt`. Every entry in this document has been cross-checked against the actual decompiled C/MIPS code in `src/main/`.

---

## 2. Naming Conventions & Mechanics

### 2.1 Game vs. SDK Naming

| Code Region | Address Range | Naming Policy | Examples |
|---|---|---|---|
| **Sony PsyQ SDK (`MALLOC4.O`, `LIBC`, `LIBSN`, `LIBAPI`, `LIBETC`, `LIBGPU`, `LIBGTE`, `LIBCD`, `LIBSPU`, `LIBSND`, `LIBCARD`)** | `0x8001177C..0x80011D84`, `0x8003D680..0x800514DC` | **Exact original Sony PsyQ SDK identifier** (preserving original casing and leading underscores). Where two `.o` files define a static helper with the same name (e.g. `memclr` in `intr.o`, `intr_vb.o`, `intr_dma.o`, or `memset` in `LIBC.A:c43.o` vs. `LIBGPU.A:sys.o`), keep the internal helper `static` in its C TU or suffix the linker symbol if global. | `InitHeap`, `malloc`, `VSync`, `ResetGraph`, `DrawOTag`, `RotTransPers`, `CdControl`, `SpuSetVoiceAttr`, `SsSepOpen`, `_card_info` |
| **Game Engine Subsystems (`src/main/`)** | `0x80011D88..0x8003D67F` | Either **`Module_Action`** (recommended project-wide standard, matching `rage-pc` and `parasite-pc`) or **`c1` `ModuleAction`**. Both forms are listed side-by-side for every game function in Section 4. | `Ns_Open` (`NSOpen`), `Gool_InterpretObject` (`GoolObjectInterpret`), `Level_SpawnObjects` (`LevelSpawnObjects`), `Card_Update` (`CardUpdate`) |
| **Hand-Coded R3000A / GTE Assembly (`psx/r3000a`)** | `0x800334A0..0x8003A94B` | Prefix with `R` (`RSlstDecodeForward`, `RGteTransformWorlds`, `RZoneQueryOctree`) or `Gte_R*` / `Slst_R*` / `Solid_R*` to distinguish hardware GTE/R3000A routines from their C wrappers. | `RSlstDecodeForward`, `RMemcpy`, `RGpuResetOT`, `RGteTransformSvtx`, `RGteTransformWorldsFog`, `RZoneQueryOctree` |
| **Global Variables (`.rdata`, `.data`, `.sdata`, `.sbss`, `.bss`)** | `0x80011000..0x8001177B`, `0x800514DC..0x80061A78` | Game globals use `g_` + `PascalCase` or `snake_case` matching `c1` (`ns`, `cur_lid`, `player`, `objects`, `cam`, `title`, `card`); PsyQ SDK globals use their exact Sony names (`_AllocRestBlockTop`, `GEnv`, `_spu_memList`, `_ss_score`, `_svm_voice`). | `ns` (`D_8005C528`), `cur_lid` (`D_800563FC`), `player` (`D_80060DB0`), `_ss_score` (`D_80058EF8`) |

### 2.2 Subsystem Prefix Table

| Prefix (`Module_`) | `c1` Prefix | Current `sym.main.txt` Prefix | Subsystem / Scope | Primary Source Directory |
|---|---|---|---|---|
| `Core_` | `Core` / `init` / `kill` | `CORE_` | Entry loop, hardware init/shutdown, core HUD object creation | `src/main/core/`, `src/main/engine/` |
| `Ns_` | `NS` | `NS_` | Naughty Dog Paging System (`.NSD`/`.NSF` virtual/physical pages, EIDs, texture/audio page tables) | `src/main/ns/` |
| `Pad_` | `Pad` | — | Controller polling and button-edge detection | `src/main/engine/input.c` |
| `Gpu_` | `Gpu` / `RGpu` | — | Double-buffered `DISPENV`/`DRAWENV` context, OT management, screen fade overlay | `src/main/render/`, `src/main/engine/loop.c` |
| `Gfx_` / `Gte_` | `Gfx` / `Tgeo` / `RGte` | `RENDER_` | Matrix setup, `SVTX`/`CVTX`/sprite/fragment/font rendering, `WGEO` world shaders | `src/main/render/`, `src/main/engine/` |
| `Gool_` | `Gool` | `GOOL_` | Game Object-Oriented Lisp (GOOL) bytecode VM, object tree, events, physics, collision | `src/main/gool/`, `src/main/engine/` |
| `Level_` / `Zone_` | `Level` / `Zone` / `Ldat` / `Zdat` / `Mdat` | `LEVEL_` | Level initialization, checkpoints, zone octree queries, path progress, zone colors | `src/main/level/`, `src/main/engine/` |
| `Slst_` | `Slst` / `RSlst` | — | Polygon ID sorting list (`SLST`) double buffers and forward/backward delta decoders | `src/main/engine/slst_alloc.c`, `src/main/engine/poly_id_list.c` |
| `Math_` | `ApxDist`, `EucDist`, `randa`, `randb`, `sin`, `cos` | `MATH_` | Fixed-point distance, angles, trig tables, dual LCG random number generators | `src/main/math/` |
| `Cam_` | `Cam` | — | Camera path following, progress adjustment, pan/zoom, death camera | `src/main/engine/camera*.c` |
| `Solid_` | `Trans*`, `StopAt*`, `Plot*`, `Binf*` | — | Solid floor/ceiling/wall collision, 32x32 wall occupancy bitmap (`BINF`), octree wall plotting | `src/main/engine/collision*.c`, `src/main/engine/grid*.c` |
| `Pbak_` | `Pbak` | — | Attract-mode demo input playback (`PBAK` entries) | `src/main/engine/pbak.c`, `src/main/engine/playback.c` |
| `Shader_` | `ShaderParams*` | — | Dynamic world shader parameter updates (depth fog, ripple, lightning, darkness) | `src/main/engine/lighting.c`, `src/main/engine/oscillation.c` |
| `Cd_` | `CdReadSectors`, `CdReadFileSys` | — | ISO-9660 path-table parser building `file_map` (`D_8005E03C`) for `S*/*.NSD` and `.NSF` | `src/main/engine/cd_dir.c` |
| `Audio_` | `Audio` | `AUDIO_` | Spatial 3D SPU sound-effect voice allocator, ADSR/pitch/pan control | `src/main/engine/audio*.c` |
| `Midi_` | `Midi` | — | `MIDI`/`SEP` background music and ambient sequence controller | `src/main/engine/midi*.c`, `src/main/engine/audio*.c` |
| `Title_` | `Title` | — | Title screen, Naughty Dog/Universal splash, options/load/save/game-over menus, 3D island map | `src/main/engine/state.c` |
| `Card_` | `Card` | — | Memory card (`bu00:BASCUS-94900*`) state machine, Shift-JIS conversion, icon/save-block I/O | `src/main/engine/card.c`, `src/main/engine/bios_ctrl.c` |

### 2.3 Where a Symbol Name Lives in `crash-pc`

When renaming a `func_800XXXXX` or `D_800XXXXX` symbol (using `tools/scripts/rename_symbols.py`), the identifier may appear in up to four places:
1. **`configs/USA/sym.main.txt`**: Maps linker symbol names to fixed VRAM addresses (`Name = 0x800XXXXX;`).
   - Note: `tools/splat_ext/gen_undefined_addr_aliases.py` automatically generates linker aliases (`func_800XXXXX = Name;` and `D_800XXXXX = Name;`) whenever an assembly `.s` file still references the raw `func_800XXXXX` / `D_800XXXXX` label.
2. **`src/main/**/*.c` and `include/**/*.h`**: C function definitions, prototypes, `extern` declarations, and call sites.
   - Note: Some C files bind a human-readable variable name to a raw address symbol via GCC's `asm("D_800XXXXX")` label extension (e.g. `extern s32 g_LevelId asm("D_800563FC");`). If `D_800563FC` is renamed in `sym.main.txt`, either update or remove the `asm("...")` label.
3. **`INCLUDE_ASM("asm/USA/nonmatchings/...", func_name)`**: For the remaining non-matching functions (`src/main/engine/state.c` and `src/main/sdk/libgte/patch_gte.c`), the macro argument must match the `.s` filename in `asm/USA/nonmatchings/`. Do **not** rename an `INCLUDE_ASM` target without also renaming its `.s` file (or keep it until decompiled to C).

---

## 3. Defects in Existing `configs/USA/sym.main.txt` & Misplaced SDK Files

### 3.1 Misnamed Symbols in `configs/USA/sym.main.txt`

`configs/USA/sym.main.txt` currently defines 33 named symbols seeded from an early `c1c` dump. **Four of these are wrong** and must be corrected:

| Address | Current `sym.main.txt` Name | True Name (`Module_Action` / `c1`) | Proof from Decompiled Code |
|---|---|---|---|
| `0x8001B3F0` | `GOOL_TraverseObjectTreePreorder` | **`Gool_InitLevelSpawns`** (`GoolInitLevelSpawns`) | Defined in `src/main/gool/groups.c`. Iterates `D_8005E348` (`level_spawns`) and sets bit 3 (`|= 8`) in `D_8005FF58` (`spawns`) for entries matching `(*entry >> 9) == cur_lid`. Does not traverse any object tree. |
| `0x8001B648` | `GOOL_TraverseObjectTreePostorder` | **`Gool_TraverseObjectTreePreorder`** (`GoolObjectTraverseTreePreorder`) | Defined in `src/main/engine/tree_visit_recursive.c`. Calls `visitor(root, context)` **before** iterating `root->children`. This is **preorder** traversal. |
| `0x8001B6F0` | `func_8001B6F0` (unnamed) | **`Gool_TraverseObjectTreePostorder`** (`GoolObjectTraverseTreePostorder`) | Defined in `src/main/engine/tree_recursive.c`. Recurses over `root->children` **first** using `func_8001B6F0`, then calls `return visitor(root, context);` at the end. This is **postorder** traversal. |
| `0x8003E4F0` | `CORE_VSync` | **`VSync`** (`LIBETC.A:vsync.o`) | Defined in `src/main/sdk/libetc/vsync.c`. Byte-for-byte identical to Sony PsyQ 3.5 `LIBETC.A:vsync.o` `VSync(int mode)` (with `v_wait` at `0x8003E638`). Not a custom game function. |

### 3.2 Misplaced PsyQ SDK Translation Units

Several Sony PsyQ 3.5 library objects are currently placed in `src/main/engine/` or under the wrong `src/main/sdk/` subdirectory:

| Address Range | Function(s) | Current File in `crash-pc` | True PsyQ 3.5 Origin |
|---|---|---|---|
| `0x8003D740..0x8003DF9B` | `func_8003D740` (`sprintf`) | `src/main/engine/format.c` | **`LIBC.A:sprintf.o`** (`sprintf`) |
| `0x8003DFAC..0x8003E017` | `func_8003DFAC` (`memmove`) | `src/main/engine/format_copy.c` | **`LIBC.A:memmove.o`** (`memmove`, pulled in by `sprintf.o`) |
| `0x8003E6D4..0x8003E6E3` | `func_8003E6D4` (`puts`) | `src/main/sdk/libapi/bios_288_6d4.c` | **`LIBC.A:a63.o`** (`puts`, BIOS B0:0x3F) |
| `0x80042AE0..0x80042B0B` | `func_80042AE0` (`memset`) | `src/main/sdk/libcd/memset.c` | **`LIBGPU.A:sys.o`** (trailing static `memset` inside `sys.o`) |
| `0x800470FC..0x8004711F` | `func_800470FC` (`_SpuCallback`) | `src/main/sdk/libapi/callback_slot4.c` | **`LIBSPU.A:s_cb.o`** (`_SpuCallback`) |
| `0x80049268..0x80050867` | `LIBSND.A` sequencer & `vmanager.o` | `src/main/sdk/libspu/*` | **`LIBSND.A`** (`ssclose.o`, `vol.o`, `ssquit.o`, `ssinit.o`, `sepinit.o`, `seqread.o`, `sspause.o`, `ssplay.o`, `ssreplay.o`, `ssstart.o`, `sscall.o`, `sstable.o`, `sstick.o`, `ssvol.o`, `ut_*.o`, `vmanager.o`) |
| `0x80050868..0x800508E7`, `0x80050C64..0x8005115B` | `SsVabClose`, `SsVabFakeBody`, `SsVabOpenHead*` | `src/main/sdk/libspu/bank_*.c` | **`LIBSND.A`** (`vs_vab.o`, `vs_vfb.o`, `vs_vh.o`) |
| `0x80051424..0x800514DC` | `_card_info`, `_card_load`, `InitCARD`, `StartCARD`, `StopCARD`, `_card_read`, `_card_clear`, `_card_write`, `_new_card` | `src/main/sdk/libapi/bios_service_*.c` | **`LIBCARD.A`** (`c171.o..c173.o`, `a74.o..a80.o`, `card.o`) |

---

## 4. Complete Game Function Catalog (`0x80011D88..0x8003D67F` — 365 Functions)

All 365 Naughty Dog game functions in `SCUS_949.00`, ordered by VRAM address and grouped into their 19 logical subsystems.

### 4.1 Core & Main Loop (`main.c` — `0x80011D88..0x8001257F`) (3 functions)

| Address | Size | Current Symbol | Proposed Name (`Module_Action`) | `c1` Name | Current TU (`src/main/`) | Status | Description / Evidence |
|---|---:|---|---|---|---|---|---|
| `0x80011D88` | 18w | `CORE_Main` | **`main`** | `main` | `core/main.c` | `C` | main function |
| `0x80011DD0` | 125w | `func_80011DD0` | **`Core_ObjectsCreate`** | `CoreObjectsCreate` | `core/main.c` | `C` | create main game objects (HUDs) and preload common code entries (box code, crash code, etc.) |
| `0x80011FC4` | 367w | `CORE_Loop` | **`Core_Loop`** | `CoreLoop` | `core/main.c` | `C` | main game loop |

### 4.2 NS Paging & Virtual Memory Subsystem (`ns.c` — `0x80012580..0x8001652B`) (56 functions)

| Address | Size | Current Symbol | Proposed Name (`Module_Action`) | `c1` Name | Current TU (`src/main/`) | Status | Description / Evidence |
|---|---:|---|---|---|---|---|---|
| `0x80012580` | 33w | `func_80012580` | **`Ns_EIDToString`** | `NSEIDToString` | `ns/id_string.c` | `C` | convert an eid to a name/string |
| `0x80012604` | 23w | `func_80012604` | **`Ns_EIDValToString`** | `NSEIDValToString` | `ns/name.c` | `C` | convert an eid or entry pointer to a name/string |
| `0x80012660` | 24w | `func_80012660` | **`Ns_StringToEID`** | `NSStringToEID` | `ns/name.c` | `C` | convert a name/string to an eid |
| `0x800126C0` | 88w | `func_800126C0` | **`Ns_EIDType`** | `NSEIDType` | `ns/resource_type.c` | `C` | get the entry type from an eid |
| `0x80012820` | 5w | `func_80012820` | **`Ns_AlphaNumChar`** | `NSAlphaNumChar` | `ns/encoding.c` | `C` | get the alpha-numeric index of a character (A-Za-z0-9) |
| `0x80012834` | 19w | `func_80012834` | **`Ns_AlphaNumIndex`** | `NSAlphaNumIndex` | `ns/parse_value.c` | `C` | `c1:ns.c` `NSAlphaNumIndex` |
| `0x80012880` | 9w | `func_80012880` | **`Ns_GetFilename`** | `NSGetFilename` | `ns/encoding.c` | `C` | get the (.NSD/.NSF) filename for a given file type and level id |
| `0x800128A4` | 54w | `func_800128A4` | **`Ns_GetFilename2`** | `NSGetFilename2` | `ns/encoding.c` | `C` | `c1:ns.c` `NSGetFilename2` |
| `0x8001297C` | 66w | `func_8001297C` | **`Ns_Atoi`** | `NSAtoi` | `ns/parse_value.c` | `C` | convert a string to cid or eid or parse from a string an lid (alphanumeric index of first char) |
| `0x80012A84` | 74w | `func_80012A84` | **`Ns_GetFilenameStr`** | `NSGetFilenameStr` | `ns/parse_value.c` | `C` | get the (.NSD/.NSF) filename for the lid corresponding to the alphanumeric index of the input char |
| `0x80012BAC` | 14w | `func_80012BAC` | **`Ns_MallocPage`** | `NSMallocPage` | `ns/alloc.c` | `C` | allocate [in memory] a page object |
| `0x80012BE4` | 36w | `func_80012BE4` | **`Ns_VirtualPagePhysicalIdx`** | `NSVirtualPagePhysicalIdx` | `ns/page.c` | `C` | Find physical page index backing a virtual page entry (`c1:ns.c`) |
| `0x80012C74` | 13w | `func_80012C74` | **`Ns_EntryItemSize`** | `NSEntryItemSize` | `ns/page.c` | `C` | get the size of an entry item |
| `0x80012CA8` | 73w | `func_80012CA8` | **`Ns_ReadSectors`** | `NSReadSectors` | `ns/page.c` | `C` | Read CD sectors via `CdIntToPos` / `CdControl(CdlSetloc)` / `CdRead` / `CdReadSync` (`c1:ns.c`) |
| `0x80012DCC` | 38w | `func_80012DCC` | **`Ns_FileOpen`** | `NSFileOpen` | `ns/page.c` | `C` | Look up `.NSD`/`.NSF` sector info in `file_map` (`D_8005E03C`) by level ID (`c1:ns.c`) |
| `0x80012E64` | 43w | `func_80012E64` | **`Ns_PageTranslateOffsets`** | `NSPageTranslateOffsets` | `ns/page.c` | `C` | convert relative offsets of entries in a page to absolute pointers, and convert relative offsets of items in each entry to absolute pointers |
| `0x80012F10` | 259w | `func_80012F10` | **`Ns_PageUpdateEntries`** | `NSPageUpdateEntries` | `ns/resource_process.c` | `C` | resolve entry pointer in page table and run `on_load` callback, for each entry in the [physical] page loaded at a given index |
| `0x8001331C` | 107w | `func_8001331C` | **`Ns_PageFree`** | `NSPageFree` | `ns/page_free.c` | `C` | `c1:ns.c` `NSPageFree` |
| `0x800134C8` | 160w | `func_800134C8` | **`Ns_Update`** | `NSUpdate` | `ns/page_free.c` | `C` | `c1:ns.c` `NSUpdate` |
| `0x80013748` | 20w | `func_80013748` | **`Ns_Update2`** | `NSUpdate2` | `ns/wait.c` | `C` | `c1:ns.c` `NSUpdate2` |
| `0x80013798` | 33w | `func_80013798` | **`Ns_CdSeek`** | `NSCdSeek` | `ns/cd_seek.c` | `C` | `c1:ns.c` `NSCdSeek` |
| `0x8001381C` | 12w | `func_8001381C` | **`Ns_ReadSync`** | `NSReadSync` | `ns/cd.c` | `C` | Poll `CdReadSync(1, 0)` and update `ns.reading` state (`c1:ns.c`) |
| `0x8001384C` | 54w | `func_8001384C` | **`Ns_ReadSectorAsync`** | `NSReadSectorAsync` | `ns/cd.c` | `C` | Seek and start async `CdRead` into physical page buffer (`c1:ns.c`) |
| `0x80013924` | 19w | `func_80013924` | **`Ns_PageOnComplete`** | `NSPageOnComplete` | `ns/cd.c` | `C` | Transition physical page state after async CD read completes (`c1:ns.c`) |
| `0x80013970` | 112w | `func_80013970` | **`Ns_PageDecompress`** | `NSPageDecompress` | `ns/page_4170.c` | `C` | `c1:ns.c` `NSPageDecompress` |
| `0x80013B30` | 25w | `Ns_PageTranslate` | **`Ns_PageTranslate`** | `NSPageTranslate` | `ns/page_4170.c` | `C` | `c1:ns.c` `NSPageTranslate` |
| `0x80013B94` | 109w | `func_80013B94` | **`Ns_PageInitAlloc`** | `NSPageInitAlloc` | `ns/page_alloc.c` | `C` | Partition page memory pool into physical and virtual page slots (`NS_13B94`) |
| `0x80013D48` | 299w | `func_80013D48` | **`Ns_PageUpdate`** | `NSPageUpdate` | `ns/page_4170.c` | `C` | `c1:ns.c` `NSPageUpdate` |
| `0x800141F4` | 106w | `func_800141F4` | **`Ns_PageAllocate`** | `NSPageAllocate` | `ns/page_4170.c` | `C` | `c1:ns.c` `NSPageAllocate` |
| `0x8001439C` | 94w | `func_8001439C` | **`Ns_TexturePageAllocate`** | `NSTexturePageAllocate` | `ns/texture_allocate.c` | `C` | reserve a texture page and return the index |
| `0x80014514` | 45w | `func_80014514` | **`Ns_TexturePageFree`** | `NSTexturePageFree` | `ns/slot_release.c` | `C` | free a previously reserved texture page |
| `0x800145C8` | 31w | `func_800145C8` | **`Ns_AudioPageAllocate`** | `NSAudioPageAllocate` | `ns/slot_release.c` | `C` | `c1:ns.c` `NSAudioPageAllocate` |
| `0x80014644` | 43w | `func_80014644` | **`Ns_PageCreateVirtual`** | `NSPageCreateVirtual` | `ns/slot_4E44.c` | `C` | `c1:ns.c` `NSPageCreateVirtual` |
| `0x800146F0` | 117w | `func_800146F0` | **`Ns_PageCreatePhysical`** | `NSPageCreatePhysical` | `ns/slot_4E44.c` | `C` | `c1:ns.c` `NSPageCreatePhysical` |
| `0x800148C4` | 27w | `func_800148C4` | **`Ns_PageDecRef`** | `NSPageDecRef` | `ns/slot_unref.c` | `C` | `c1:ns.c` `NSPageDecRef` |
| `0x80014930` | 11w | `func_80014930` | **`Ns_PageDelete`** | `NSPageDelete` | `ns/release.c` | `C` | `c1:ns.c` `NSPageDelete` |
| `0x8001495C` | 68w | `func_8001495C` | **`Ns_ZoneUnload`** | `NSZoneUnload` | `ns/load_list.c` | `C` | `c1:ns.c` `NSZoneUnload` |
| `0x80014A6C` | 45w | `func_80014A6C` | **`Ns_PageCommitVirtual`** | `NSPageCommitVirtual` | `ns/load_526C.c` | `C` | Copy virtual page entries into destination buffer and free physical page (`c1:ns.c`) |
| `0x80014B20` | 58w | `func_80014B20` | **`Ns_PageVirtual`** | `NSPageVirtual` | `ns/load_526C.c` | `C` | `c1:ns.c` `NSPageVirtual` |
| `0x80014C08` | 62w | `func_80014C08` | **`Ns_PagePhysical`** | `NSPagePhysical` | `ns/load_5408.c` | `C` | create anew or get the existing physical page struct for a given page id (and eid), and page in the page with that id |
| `0x80014D00` | 77w | `func_80014D00` | **`Ns_PageOpen`** | `NSPageOpen` | `ns/load_5500.c` | `C` | page the physical or virtual page for a given page id and increment its reference counter |
| `0x80014E34` | 63w | `func_80014E34` | **`Ns_PageClose`** | `NSPageClose` | `ns/load_5C58.c` | `C` | decrement the reference counter for the physical/virtual page with the given page id |
| `0x80014F30` | 30w | `func_80014F30` | **`Ns_EntryPageStruct`** | `NSEntryPageStruct` | `ns/load_5C58.c` | `C` | search all paged-in pages for the given entry and return the corresponding page struct for the page that contains the entry |
| `0x80014FA8` | 35w | `func_80014FA8` | **`Ns_EntryPage`** | `NSEntryPage` | `ns/load_5634.c` | `C` | get the page which contains the given entry |
| `0x80015034` | 57w | `func_80015034` | **`Ns_PageStruct`** | `NSPageStruct` | `ns/load_5634.c` | `C` | get the page struct for the page that contains the given entry (uses `NSEntryPageStruct` for the initial call, storing page id in the page table, and looks up in the page table for future calls) |
| `0x80015118` | 208w | `func_80015118` | **`Ns_Open`** | `NSOpen` | `ns/load_5918.c` | `C` | page the physical or virtual page for a given eid or page table entry and return a pointer to the corresponding entry within the page data |
| `0x80015458` | 159w | `func_80015458` | **`Ns_Close`** | `NSClose` | `ns/load_5C58.c` | `C` | close the physical or virtual page for a given eid or page table entry |
| `0x800156D4` | 50w | `func_800156D4` | **`Ns_CountAvailablePages`** | `NSCountAvailablePages` | `ns/load_5C58.c` | `C` | get the number of  virtual and physical pages with a reference count of zero (and which are not in state 1) |
| `0x8001579C` | 119w | `func_8001579C` | **`Ns_CountAvailablePages2`** | `NSCountAvailablePages2` | `ns/load_5C58.c` | `C` | `c1:ns.c` `NSCountAvailablePages2` |
| `0x80015978` | 19w | `func_80015978` | **`Ns_Probe`** | `NSProbe` | `ns/hash_lookup.c` | `C` | get the page table entry for a given eid |
| `0x800159C4` | 30w | `func_800159C4` | **`Ns_ProbeSafe`** | `NSProbeSafe` | `ns/entry_lookup.c` | `C` | get the page table entry for a given eid; avoids continuing search past end of the table if an entry is not found |
| `0x80015A3C` | 23w | `func_80015A3C` | **`Ns_ProbeAndOpen`** | `NSProbeAndOpen` | `ns/resource_resolve_check.c` | `C` | Probe EID in page table and open page via `NSPageOpen` (`c1:ns.c`) |
| `0x80015A98` | 48w | `func_80015A98` | **`Ns_Lookup`** | `NSLookup` | `ns/resource_handle_resolve.c` | `C` | get a pointer to the entry data for the given eid (probe for the pte for the given eid and resolve the entry data for the pte) |
| `0x80015B58` | 562w | `func_80015B58` | **`Ns_Init`** | `NSInit` | `ns/init.c` | `C` | initialize paging subsystem for paging in pages/entries from the corresponding NSF file for the given level id |
| `0x80016420` | 54w | `func_80016420` | **`Ns_Kill`** | `NSKill` | `ns/init.c` | `C` | `c1:ns.c` `NSKill` |
| `0x800164F8` | 13w | `func_800164F8` | **`Ns_KillPage`** | `NSKillPage` | `ns/slots.c` | `C` | `c1:ns.c` `NSKillPage` |

### 4.3 Hardware Init/Kill, Joypad, and GPU Context Wrapper (`psx/init.c`, `pad.c`, `psx/gpu.c` — `0x8001652C..0x800175C7`) (17 functions)

| Address | Size | Current Symbol | Proposed Name (`Module_Action`) | `c1` Name | Current TU (`src/main/`) | Status | Description / Evidence |
|---|---:|---|---|---|---|---|---|
| `0x8001652C` | 88w | `func_8001652C` | **`Core_Init`** | `init` | `engine/shutdown.c` | `C` | Hardware & subsystem initialization (`SetVideoMode`, `InitGeom`, `CdInit`, `PadInit`, `CardInit`, `SetRCnt`, `GpuInit`, `CdReadFileSys`) (`c1:psx/init.c`) |
| `0x8001668C` | 35w | `func_8001668C` | **`Core_Kill`** | `kill` | `engine/shutdown.c` | `C` | Hardware & subsystem shutdown (`CdControl(CdlPause)`, `StopCallback`, `CardKill`, `PadStop`, `ResetGraph(3)`, `StopRCnt`) (`c1:psx/init.c`) |
| `0x80016718` | 35w | `func_80016718` | **`Pad_Init`** | `PadInit` | `engine/shutdown.c` | `C` | initialize structures for holding current joypad state and detecting changes in joypad state |
| `0x800167A4` | 114w | `func_800167A4` | **`Pad_Update`** | `PadUpdate` | `engine/shutdown.c` | `C` | update joypad state and detect changes in joypad state |
| `0x8001696C` | 35w | `func_8001696C` | **`Gpu_ClearVRAM`** | `GpuClearVRAM` | `engine/display_clear.c` | `C` | Set full-VRAM `DRAWENV` and clear with `BLK_FILL` (`DrawPrim` + `DrawSync`) |
| `0x800169F8` | 29w | `func_800169F8` | **`Gpu_FillDisplay`** | `GpuFillDisplay` | `engine/display_clear.c` | `C` | Fill active 512x240 display area with black `BLK_FILL` (`c1:psx/gpu.c`) |
| `0x80016A6C` | 107w | `func_80016A6C` | **`Gpu_Init`** | `GpuInit` | `engine/display_clear.c` | `C` | Initialize GPU, clear VRAM, set up double-buffered 512x240 `DISPENV`/`DRAWENV` contexts (`c1:psx/gpu.c`) |
| `0x80016C18` | 63w | `func_80016C18` | **`Gpu_SetupPrims`** | `GpuSetupPrims` | `engine/display_clear.c` | `C` | Allocate primitive buffers (`0x1E000`/`0x1CC00`/`0x16000` bytes) and call `CardAlloc` on title/bonus levels (`c1:psx/gpu.c`) |
| `0x80016D14` | 46w | `func_80016D14` | **`Gpu_Kill`** | `GpuKill` | `engine/display_clear.c` | `C` | Wait `DrawSync(0)`, free primitive buffers, and call `CardFree` on title level (`c1:psx/gpu.c`) |
| `0x80016DCC` | 11w | `func_80016DCC` | **`Gpu_ResetPrims`** | `GpuResetPrims` | `render/buffer.c` | `C` | Reset `gc->prims_tail = gc->prims_head` and clear 2048-entry OT via `RGpuResetOT` (`c1:psx/gpu.c`) |
| `0x80016DF8` | 8w | `func_80016DF8` | **`Gpu_GetPrimsTail`** | `GpuGetPrimsTail` | `render/buffer.c` | `C` | Return `&context.cur->prims_tail` (`c1:psx/gpu.c`) |
| `0x80016E18` | 4w | `func_80016E18` | **`Gpu_GetCurPrimsTail`** | `GpuGetCurPrimsTail` | `render/buffer.c` | `C` | Return `context.cur->prims_tail` value (`src/main/engine/loop.c`) |
| `0x80016E28` | 13w | `func_80016E28` | **`Gpu_RoundTicks`** | `GpuRoundTicks` | `engine/state_word_copy.c` | `C` | Quantize frame elapsed ticks to 17 (0.5f), 34 (1.0f), or 51 (1.5f) (`c1:psx/gpu.c`) |
| `0x80016E5C` | 291w | `func_80016E5C` | **`Gpu_Update`** | `GpuUpdate` | `render/frame_update.c` | `C` | End-of-frame GPU sync, screen fade overlay, pillarbox bars, `AudioUpdate`, `VSync`, `CardUpdate`, `DrawOTag`, and OT reset (`c1:psx/gpu.c`) |
| `0x800172E8` | 28w | `func_800172E8` | **`Gpu_SwapBuffers`** | `GpuSwapBuffers` | `render/buffer_swap.c` | `C` | Swap double-buffered `gfx_context` pointers, wait `VSync(0)`, and apply `PutDispEnv`/`PutDrawEnv` (`c1:psx/gpu.c`) |
| `0x80017358` | 60w | `func_80017358` | **`Gpu_DrawRect`** | `GpuDrawRect` | `render/tile_fade.c` | `C` | Append a `BLK_FILL` rectangle primitive to the current ordering table (`c1:psx/gpu.c`) |
| `0x80017448` | 96w | `func_80017448` | **`Gpu_DrawOverlay`** | `GpuDrawOverlay` | `render/tile_fade.c` | `C` | Append a full-screen semi-transparent `POLY_F4` + `DR_MODE` brightness/fade overlay (`c1:psx/gpu.c`) |

### 4.4 Graphics, Matrices, Model/Sprite Transforms & World Shaders (`gfx.c` — `0x800175C8..0x8001AC57`) (31 functions)

| Address | Size | Current Symbol | Proposed Name (`Module_Action`) | `c1` Name | Current TU (`src/main/`) | Status | Description / Evidence |
|---|---:|---|---|---|---|---|---|
| `0x800175C8` | 2w | `func_800175C8` | **`Gfx_Noop`** | `GfxNoop` | `engine/noop_175C8.c` | `C` | Empty stub (`jr $ra`) at start of `gfx.c` |
| `0x800175D0` | 16w | `func_800175D0` | **`Gfx_TgeoGetTexinfoArray`** | `TgeoGetTexinfoArray` | `render/value_range.c` | `C` | Compute pointer to `tgeo_texinfo` array inside a `TGEO` item |
| `0x80017610` | 27w | `func_80017610` | **`Gfx_TgeoLookupEntry`** | `TgeoLookupEntry` | `render/value_range.c` | `C` | Resolve a `TGEO` entry via `NSLookup` and cache header pointers |
| `0x8001767C` | 69w | `func_8001767C` | **`Gfx_TgeoOnLoad`** | `TgeoOnLoad` | `render/value_range.c` | `C` | probe for tpages referenced by texinfos in a tgeo entry upon load |
| `0x80017790` | 118w | `func_80017790` | **`Gfx_InitMatrices`** | `GfxInitMatrices` | `render/mode_initialize.c` | `C` | initialize all global matrices used for transformations |
| `0x80017968` | 43w | `func_80017968` | **`Gfx_ScreenProj`** | `GfxScreenProj` | `render/word_transform.c` | `C` | Convert FOV angle to GTE projection distance `H` (`c1:gfx.c`) |
| `0x80017A14` | 419w | `func_80017A14` | **`Gfx_UpdateMatrices`** | `GfxUpdateMatrices` | `render/camera_matrix.c` | `C` | recompute global matrices used for transformations and load world models |
| `0x800180A0` | 11w | `func_800180A0` | **`Gfx_ResetCam`** | `GfxResetCam` | `render/transform.c` | `C` | reset camera trans, rot, and scale vectors to default values |
| `0x800180CC` | 536w | `func_800180CC` | **`Gfx_CalcObjectMatrices`** | `GfxCalcObjectMatrices` | `render/transform_8964.c` | `C` | [re]calculate matrices for an object and replace the current modelview matrix |
| `0x8001892C` | 14w | `func_8001892C` | **`Gfx_SetGteMatrices`** | `GfxSetGteMatrices` | `render/gte.c` | `C` | Apply rotation and translation matrices via `SetRotMatrix` and `SetTransMatrix` |
| `0x80018964` | 55w | `func_80018964` | **`Gfx_LoadWorlds`** | `GfxLoadWorlds` | `render/transform_8964.c` | `C` | load info for the current zone's worlds into the reserved area of the zone header |
| `0x80018A40` | 86w | `func_80018A40` | **`Gfx_TransformCvtx`** | `GfxTransformCvtx` | `render/transform_8964.c` | `C` | transform a cvtx frame and place resulting primitives into the ot |
| `0x80018B98` | 137w | `func_80018B98` | **`Gfx_TransformFragment`** | `GfxTransformFragment` | `render/quad_draw.c` | `C` | transform a `gool_frag` and place resulting primitives into the ot |
| `0x80018DBC` | 226w | `func_80018DBC` | **`Gfx_TransformFontChar`** | `GfxTransformFontChar` | `render/quad_draw.c` | `C` | transform a `gool_glyph` and place resulting primitives into the ot |
| `0x80019144` | 58w | `func_80019144` | **`Gfx_Transform`** | `GfxTransform` | `math/matrix_vector.c` | `C` | multiply a 4:12 fractional fixed point matrix by a 20:12 fixed point vector to produce a 20:12 fixed point vector |
| `0x8001922C` | 169w | `func_8001922C` | **`Gfx_LoadWorlds`** | `GfxLoadWorlds` | `render/world_setup.c` | `C` | Resolve current zone `WGEO` world entries and freeze map textures if needed (`c1:gfx.c`) |
| `0x800194D0` | 14w | `func_800194D0` | **`Gfx_UpdateMatrices`** | `GfxUpdateMatrices` | `render/display.c` | `C` | Wrapper invoking `GfxUpdateCamMatrices` (`0x800195CC`) (`c1:gfx.c`) |
| `0x80019508` | 49w | `func_80019508` | **`Gfx_TransformWorlds`** | `GfxTransformWorlds` | `gool/entries_9D08.c` | `C` | transform wgeo models for the current zone's worlds and place resulting primitives into the ot (wraps call to the actual hardware or software world transform function) |
| `0x800195CC` | 330w | `func_800195CC` | **`Gfx_UpdateCamMatrices`** | `GfxUpdateCamMatrices` | `render/tri_draw.c` | `C` | Recompute global camera/view/light matrices and load zone worlds (`c1:gfx.c`) |
| `0x80019AF4` | 54w | `func_80019AF4` | **`Gfx_GetFar`** | `GfxGetFar` | `gool/entries_A3CC.c` | `C` | compute far and shamt values based on values in the current zone header; used as shader params |
| `0x80019BCC` | 133w | `func_80019BCC` | **`Gfx_TransformWorldsFog`** | `GfxTransformWorldsFog` | `gool/entries_A3CC.c` | `C` | `GfxTransformWorlds` variant with fog shader |
| `0x80019DE0` | 108w | `func_80019DE0` | **`Gfx_TransformWorldsRipple`** | `GfxTransformWorldsRipple` | `gool/entries_A5E0.c` | `C` | `GfxTransformWorlds` variant with ripple [vertex] shader |
| `0x80019F90` | 79w | `func_80019F90` | **`Gfx_TransformWorldsLightning`** | `GfxTransformWorldsLightning` | `gool/entries_A5E0.c` | `C` | `GfxTransformWorlds` variant with lightning shader |
| `0x8001A0CC` | 133w | `func_8001A0CC` | **`Gfx_TransformWorldsDark`** | `GfxTransformWorldsDark` | `gool/entries_A8CC.c` | `C` | `GfxTransformWorlds` variant with darkness shader |
| `0x8001A2E0` | 96w | `func_8001A2E0` | **`Gfx_TransformWorldsDark2`** | `GfxTransformWorldsDark2` | `gool/entries_AAE0.c` | `C` | `GfxTransformWorlds` variant with alternate darkness shader |
| `0x8001A460` | 101w | `func_8001A460` | **`Gfx_FreezeMapTextures`** | `GfxFreezeMapTextures` | `gool/entries_AAE0.c` | `C` | Patch `WGEO` polygon texture animation info on world map based on unlocked levels (`c1:gfx.c`) |
| `0x8001A5F4` | 88w | `func_8001A5F4` | **`Gfx_GetIconTexinfo`** | `GfxGetIconTexinfo` | `gool/entries_AAE0.c` | `C` | Look up icon texture/CLUT info from an `MDAT`/`TGEO` icon table (`c1:gfx.h`) |
| `0x8001A754` | 63w | `func_8001A754` | **`Gfx_FormatCardString`** | `GfxFormatCardString` | `gool/entries_AAE0.c` | `C` | Encode ASCII string into glyph sprite descriptors for memory card UI (`c1:gfx.h`) |
| `0x8001A850` | 162w | `func_8001A850` | **`Gfx_BlitCardIcon`** | `GfxBlitCardIcon` | `gool/entries_AAE0.c` | `C` | Copy or upload memory card icon 4bpp image & CLUT between VRAM and RAM (`c1:psx/card.c`) |
| `0x8001AAD8` | 84w | `GOOL_InitAllocTable` | **`Gool_InitAllocTable`** | `GoolInitAllocTable` | `gool/entries_AAE0.c` | `C` | allocate memory for player object and all other objects, establish linked list of free objects, and initialize object handles |
| `0x8001AC28` | 14w | `GOOL_FreeAllocTable` | **`Gool_KillAllocTable`** | `GoolKillAllocTable` | `gool/alloc.c` | `C` | free memory for player object and all other objects |

### 4.5 GOOL Virtual Machine & Object System (`gool.c` — `0x8001AC58..0x800253FF`) (55 functions)

| Address | Size | Current Symbol | Proposed Name (`Module_Action`) | `c1` Name | Current TU (`src/main/`) | Status | Description / Evidence |
|---|---:|---|---|---|---|---|---|
| `0x8001AC60` | 15w | `func_8001AC60` | **`Gool_InitLid`** | `GoolInitLid` | `gool/alloc.c` | `C` | copy current lid from nsd into the read-only current lid gool global |
| `0x8001AC9C` | 469w | `func_8001AC9C` | **`Gool_ObjectOrientOnPath`** | `GoolObjectOrientOnPath` | `—` | `C` | `c1:gool.c` `GoolObjectOrientOnPath` |
| `0x8001B3F0` | 26w | `GOOL_TraverseObjectTreePreorder` | **`Gool_InitLevelSpawns`** | `GoolInitLevelSpawns` | `gool/groups.c` | `C` | Populate `spawns` (`D_8005FF58`) bit 3 for `level_spawns` (`D_8005E348`) matching current `cur_lid` (`c1:gool.c`; misnamed `GOOL_TraverseObjectTreePreorder` in `sym.main.txt`) |
| `0x8001B458` | 38w | `func_8001B458` | **`Gool_ClearAllSpawns`** | `GoolClearAllSpawns` | `engine/tag_list.c` | `C` | Zero `spawns` (`D_8005FF58`) and `level_spawns` (`D_8005E348`) tables |
| `0x8001B4F0` | 31w | `func_8001B4F0` | **`Gool_RecordLevelSpawn`** | `GoolRecordLevelSpawn` | `engine/tag_list.c` | `C` | Append `(lid << 9) | id` entry to `level_spawns` (`D_8005E348`) |
| `0x8001B56C` | 55w | `func_8001B56C` | **`Gool_RemoveLevelSpawn`** | `GoolRemoveLevelSpawn` | `gool/interpret.c` | `C` | Remove matching `(lid << 9) | id` entry from `level_spawns` (`D_8005E348`) |
| `0x8001B648` | 42w | `GOOL_TraverseObjectTreePostorder` | **`Gool_ObjectTraverseTreePreorder`** | `GoolObjectTraverseTreePreorder` | `engine/tree_visit_recursive.c` | `C` | Preorder traversal of GOOL object tree (`c1:gool.c`; misnamed `GOOL_TraverseObjectTreePostorder` in `sym.main.txt`) |
| `0x8001B6F0` | 38w | `func_8001B6F0` | **`Gool_ObjectTraverseTreePostorder`** | `GoolObjectTraverseTreePostorder` | `gool/broadcast.c` | `C` | Postorder traversal of GOOL object tree (`c1:gool.c`) |
| `0x8001B788` | 49w | `func_8001B788` | **`Gool_ObjectSearchTree`** | `GoolObjectSearchTree` | `engine/tree_recursive.c` | `C` | find the first object in the object tree rooted at the given object that returns true for the given callback, checking objects in pre order |
| `0x8001B84C` | 56w | `func_8001B84C` | **`Gool_ObjectHandleTraverseTreePreorder`** | `GoolObjectHandleTraverseTreePreorder` | `engine/tree_visit_first.c` | `C` | run a callback for each object in the object tree rooted at the given object handle, in pre order |
| `0x8001B92C` | 59w | `func_8001B92C` | **`Gool_ObjectHandleTraverseTreePostorder`** | `GoolObjectHandleTraverseTreePostorder` | `engine/tree_walk.c` | `C` | run a callback for each object in the object tree rooted at the given object handle, in post order |
| `0x8001BA18` | 30w | `func_8001BA18` | **`Gool_ForEachObjectHandle`** | `GoolForEachObjectHandle` | `engine/tree_roots.c` | `C` | run a callback for each object handle |
| `0x8001BA90` | 8w | `func_8001BA90` | **`Gool_ObjectHasPidFlags`** | `GoolObjectHasPidFlags` | `engine/object_state_filter.c` | `C` | callback; returns the given object if it has the given pid flags |
| `0x8001BAB0` | 125w | `func_8001BAB0` | **`Gool_FindNearestObject`** | `GoolFindNearestObject` | `gool/query_nearest.c` | `C` | query for the object nearest to the given object |
| `0x8001BCA4` | 9w | `GOOL_TestObjectStateFlags` | **`Gool_ObjectTestStateFlags`** | `GoolObjectTestStateFlags` | `gool/test_state_flags.c` | `C` | callback; returns the given object if it has the given state flags |
| `0x8001BCC8` | 640w | `func_8001BCC8` | **`Gool_ObjectSpawn`** | `GoolObjectSpawn` | `gool/create_object.c` | `C` | spawn a new object for the given entity (i.e. zone and entity index) |
| `0x8001C6C8` | 302w | `GOOL_CreateObject` | **`Gool_ObjectCreate`** | `GoolObjectCreate` | `gool/create_object.c` | `C` | create a new object with the given parent, executable id, subtype, and arguments |
| `0x8001CB80` | 148w | `GOOL_InitObject` | **`Gool_ObjectInit`** | `GoolObjectInit` | `gool/create_object.c` | `C` | initialize a newly allocated object |
| `0x8001CDD0` | 211w | `func_8001CDD0` | **`Gool_ObjectKill`** | `GoolObjectKill` | `gool/create_object.c` | `C` | send TERM event (if given arg `sig` is 1), kill all child objects of, free audio voices for, clear spawn bits for, and return to the free list, a given object |
| `0x8001D11C` | 49w | `func_8001D11C` | **`Gool_ZoneObjectTerminate`** | `GoolZoneObjectTerminate` | `gool/object_release_callback.c` | `C` | send TERM event and kill the given object if it is in the given zone |
| `0x8001D1E0` | 8w | `func_8001D1E0` | **`Gool_ObjectTerminate`** | `GoolObjectTerminate` | `gool/object.c` | `C` | `GoolObjectKill` with `sig=1` |
| `0x8001D200` | 25w | `func_8001D200` | **`Gool_ZoneObjectsTerminate`** | `GoolZoneObjectsTerminate` | `gool/object.c` | `C` | terminate all objects in the given zone |
| `0x8001D264` | 54w | `func_8001D264` | **`Gool_ZoneObjectTerminate`** | `GoolZoneObjectTerminate` | `gool/object.c` | `C` | Terminate object if spawned from target zone (`c1:gool.c`) |
| `0x8001D33C` | 172w | `func_8001D33C` | **`Gool_ObjectLocalBound`** | `GoolObjectLocalBound` | `gool/change_state.c` | `C` | recompute the local bound box for given object with given scale |
| `0x8001D5EC` | 43w | `func_8001D5EC` | **`Gool_UpdateObjects`** | `GoolUpdateObjects` | `gool/change_state.c` | `C` | update all objects |
| `0x8001D698` | 159w | `GOOL_ChangeObjectState` | **`Gool_ObjectChangeState`** | `GoolObjectChangeState` | `gool/create_object.c` | `C` | change an object's state |
| `0x8001D914` | 26w | `GOOL_CreateObjectStackFrame` | **`Gool_ObjectPushFrame`** | `GoolObjectPushFrame` | `gool/update_object.c` | `C` | push a frame to an object's stack |
| `0x8001D97C` | 36w | `func_8001D97C` | **`Gool_ObjectPopFrame`** | `GoolObjectPopFrame` | `gool/interpret.c` | `C` | pop the topmost frame from an object's stack |
| `0x8001DA0C` | 283w | `GOOL_UpdateObject` | **`Gool_ObjectUpdate`** | `GoolObjectUpdate` | `gool/update_object.c` | `C` | update an object; recalculate bound, run trans block, run code block if wait time has elapsed, compute object colors, do object physics, and transform object animation frame model |
| `0x8001DE78` | 343w | `func_8001DE78` | **`Gool_ObjectTransform`** | `GoolObjectTransform` | `—` | `C` | transform an object's current animation frame according to animation type, and put result primitives in the ot |
| `0x8001E3D4` | 257w | `func_8001E3D4` | **`Gool_TextStringTransform`** | `GoolTextStringTransform` | `gool/update_object.c` | `C` | generate primitives for and transform an object's current text string (when the animation type is text), and put result primitives in the ot |
| `0x8001E7D8` | 138w | `func_8001E7D8` | **`Gool_TextObjectTransform`** | `GoolTextObjectTransform` | `—` | `C` | wrapper for `GoolTextStringTransform` which includes formatting the current string and calculating matrices for the object before transforming its formatted text string |
| `0x8001EA00` | 74w | `func_8001EA00` | **`Gool_ObjectColorByZone`** | `GoolObjectColorByZone` | `gool/physics.c` | `C` | Copy zone header object/player colors into `obj->colors` (`c1:gool.c`) |
| `0x8001EB28` | 224w | `func_8001EB28` | **`Gool_ObjectColors`** | `GoolObjectColors` | `gool/physics.c` | `C` | color an object according to invincibility state |
| `0x8001EEA8` | 281w | `func_8001EEA8` | **`Gool_ObjectControlDir`** | `GoolObjectControlDir` | `gool/physics.c` | `C` | Compute player directional control, acceleration/deceleration, and path heading (`c1:gool.c`) |
| `0x8001F30C` | 517w | `func_8001F30C` | **`Gool_ObjectPhysics`** | `GoolObjectPhysics` | `—` | `C` | handle physics for an object; includes controlling direction and rotation, stopping at solid matter, orienting on path, and falling due to gravity |
| `0x8001FB20` | 5w | `func_8001FB20` | **`Gool_SignShift`** | `GoolSignShift` | `gool/vm_operands.c` | `C` | `c1:gool.c` `GoolSignShift` |
| `0x8001FB34` | 70w | `GOOL_TranslateGop` | **`Gool_TranslateInGop`** | `GoolTranslateInGop` | `gool/translate_gop.c` | `C` | convert an input GOOL operand to an absolute pointer to data |
| `0x8001FC4C` | 94w | `func_8001FC4C` | **`Gool_TranslateOutGop`** | `GoolTranslateOutGop` | `gool/vm_operands.c` | `C` | convert an output GOOL operand to an absolute pointer to data |
| `0x8001FDC4` | 262w | `func_8001FDC4` | **`Gool_TestControls`** | `GoolTestControls` | `gool/vm_operands.c` | `C` | logic for the 'test controls' GOOL instruction, for reading joypad input |
| `0x800201DC` | 3993w | `GOOL_InterpretObject` | **`Gool_ObjectInterpret`** | `GoolObjectInterpret` | `gool/interpret.c` | `C` | run the next burst of instructions for a given object |
| `0x80024040` | 216w | `func_80024040` | **`Gool_ExecStateCode`** | `GoolExecStateCode` | `gool/send_event.c` | `C` | Execute a state transition/event code block via `GoolObjectInterpret` and `GoolObjectChangeState` |
| `0x800243A0` | 98w | `func_800243A0` | **`Gool_ObjectRotate`** | `GoolObjectRotate` | `gool/send_event.c` | `C` | seek from source angle to destination angle at a given speed |
| `0x80024528` | 50w | `func_80024528` | **`Gool_ObjectRotate2`** | `GoolObjectRotate2` | `gool/send_event.c` | `C` | alternative variant of `GoolObjectRotate` |
| `0x800245F0` | 14w | `func_800245F0` | **`Gool_AngDiff`** | `GoolAngDiff` | `math/delta.c` | `C` | gets the difference between 2 angles; result angle in the range of -180 to 180 degrees |
| `0x80024628` | 13w | `func_80024628` | **`Gool_Seek`** | `GoolSeek` | `math/delta.c` | `C` | seek source value towards destination value at a given delta |
| `0x8002465C` | 145w | `func_8002465C` | **`fixed`** | `fixed` | `gool/project.c` | `C` | `c1:gool.c` `fixed` |
| `0x800248A0` | 80w | `func_800248A0` | **`Gool_Transform2`** | `GoolTransform2` | `gool/project.c` | `C` | transform a vector with the corresponding view matrix for the camera |
| `0x800249E0` | 61w | `func_800249E0` | **`Gool_Project`** | `GoolProject` | `gool/project.c` | `C` | transform a vector with the corresponding view matrix for the camera and project to 2d screen coordinates |
| `0x80024AD4` | 125w | `func_80024AD4` | **`Gool_Collide`** | `GoolCollide` | `gool/project.c` | `C` | test for collision of source and target object bounds and set the appropriate status flags in either object when there is a collision |
| `0x80024CC8` | 283w | `func_80024CC8` | **`Gool_SendIfColliding`** | `GoolSendIfColliding` | `gool/broadcast.c` | `C` | callback to use for testing and handling collision for all objects in a given object tree; implements several test types and each is handled by sending an event from sender to recipient |
| `0x80025134` | 33w | `func_80025134` | **`Gool_SendToColliders`** | `GoolSendToColliders` | `engine/tree_message.c` | `C` | tests and handles collision for all objects in a given tree (using `GoolSendIfColliding`) |
| `0x800251B8` | 66w | `func_800251B8` | **`Gool_SendToColliders2`** | `GoolSendToColliders2` | `gool/broadcast.c` | `C` | alternative variant of `GoolSendToColliders` |
| `0x800252C0` | 56w | `func_800252C0` | **`Gool_ObjectInterrupt`** | `GoolObjectInterrupt` | `gool/broadcast.c` | `C` | interrupt an object |
| `0x800253A0` | 162w | `func_800253A0` | **`Level_LdatInit`** | `LdatInit` | `gool/broadcast.c` | `C` | initialize the level; set current zone and path to initial zone and path as specified in the current nsd |

### 4.6 Level, Zone, Path & Octree Subsystem (`level.c` — `0x80025400..0x80029A57`) (37 functions)

| Address | Size | Current Symbol | Proposed Name (`Module_Action`) | `c1` Name | Current TU (`src/main/`) | Status | Description / Evidence |
|---|---:|---|---|---|---|---|---|
| `0x80025628` | 45w | `func_80025628` | **`Level_ZdatOnLoad`** | `ZdatOnLoad` | `gool/resource.c` | `C` | onload callback for zdat entries |
| `0x800256DC` | 21w | `func_800256DC` | **`Level_MdatOnLoad`** | `MdatOnLoad` | `gool/resource.c` | `C` | onload callback for mdat entries |
| `0x80025730` | 33w | `func_80025730` | **`Level_ZdatOnLoad`** | `ZdatOnLoad` | `gool/resource.c` | `C` | Relocate relative pointers in a loaded `ZDAT` zone entry (`c1:level.c`) |
| `0x800257B4` | 20w | `func_800257B4` | **`Level_MdatOnLoad`** | `MdatOnLoad` | `gool/resource.c` | `C` | Relocate relative entity pointers in a loaded `MDAT` map/title entry (`c1:level.c`) |
| `0x80025804` | 21w | `func_80025804` | **`Zone_TerminateObjects`** | `ZoneTerminateObjects` | `gool/resource.c` | `C` | Wrapper calling `GoolZoneObjectsTerminate` for a zone (`c1:level.c`) |
| `0x80025858` | 52w | `func_80025858` | **`Level_SpawnObjects`** | `LevelSpawnObjects` | `level/update.c` | `C` | Spawn all unspawned group-3 entities in current and neighbor zones (`c1:level.c`) |
| `0x80025928` | 78w | `func_80025928` | **`Level_SpawnObjects`** | `LevelSpawnObjects` | `level/update.c` | `C` | spawn all unspawned objects in the current and neighbor zones (with an entity group of 3) |
| `0x80025A60` | 403w | `func_80025A60` | **`Level_Update`** | `LevelUpdate` | `level/update.c` | `C` | update current zone, path, progress, poly id list, and camera |
| `0x800260AC` | 35w | `func_800260AC` | **`Level_UpdateMisc`** | `LevelUpdateMisc` | `level/update.c` | `C` | perform various miscellaneous updates for level |
| `0x80026138` | 2w | `func_80026138` | **`Level_Noop`** | `LevelNoop` | `engine/noop_26138.c` | `C` | Empty stub (`jr $ra`) in `level.c` |
| `0x80026140` | 48w | `func_80026140` | **`Level_InitGlobals`** | `LevelInitGlobals` | `engine/settings_reset.c` | `C` | initialize level-engine-specific GOOL globals |
| `0x80026200` | 55w | `func_80026200` | **`Level_ResetGlobals`** | `LevelResetGlobals` | `engine/settings_reset.c` | `C` | reset level-engine-specific GOOL globals |
| `0x800262DC` | 97w | `func_800262DC` | **`Level_InitMisc`** | `LevelInitMisc` | `engine/level_start.c` | `C` | create initial objects, specific to level |
| `0x80026460` | 124w | `func_80026460` | **`Level_SaveState`** | `LevelSaveState` | `level/checkpoint.c` | `C` | save current level state; used for checkpoints |
| `0x80026650` | 252w | `func_80026650` | **`Level_Restart`** | `LevelRestart` | `level/checkpoint.c` | `C` | restart level after dying or return from bonus round |
| `0x80026A40` | 39w | `func_80026A40` | **`Level_TestPointInRect`** | `TestPointInRect` | `math/contains_point.c` | `C` | test if a point/vector is within a rect |
| `0x80026ADC` | 41w | `func_80026ADC` | **`Level_SaveState`** | `LevelSaveState` | `math/contains_point.c` | `C` | Save current level/checkpoint state into `savestate` (`c1:level.c`) |
| `0x80026B80` | 33w | `func_80026B80` | **`Level_TestPointInBound`** | `TestPointInBound` | `level/zone_query.c` | `C` | test if a point/vector is within a bound |
| `0x80026C04` | 41w | `func_80026C04` | **`Level_TestRectIntersectsBound`** | `TestRectIntersectsBound` | `level/zone_query.c` | `C` | test if a rect intersects a bound |
| `0x80026CA8` | 38w | `func_80026CA8` | **`Level_TestBoundIntersection`** | `TestBoundIntersection` | `level/zone_query.c` | `C` | test if a pair of bounds intersect |
| `0x80026D40` | 37w | `func_80026D40` | **`Level_TestBoundInBound`** | `TestBoundInBound` | `level/zone_query.c` | `C` | test if one bound is completely contained by another |
| `0x80026DD4` | 135w | `func_80026DD4` | **`Zone_FindNeighbor`** | `ZoneFindNeighbor` | `level/zone_query.c` | `C` | get the neighbor zone of the given zone which contains a given point |
| `0x80026FF0` | 511w | `func_80026FF0` | **`Zone_FindNode`** | `ZoneFindNode` | `level/zone_query.c` | `C` | find the point of intersection between a zone octree and a ray and return the node which contains the point of intersection |
| `0x800277EC` | 135w | `func_800277EC` | **`Zone_ReboundVector`** | `ZoneReboundVector` | `level/zone_query.c` | `C` | get the rebound direction of a given vector within the current zone or neighbor using `ZoneFindNode` |
| `0x80027A08` | 17w | `func_80027A08` | **`Cam_SetObjectZoom`** | `Cam_SetObjectZoom` | `engine/field138.c` | `C` | `c1:level.c` `Cam_SetObjectZoom` |
| `0x80027A4C` | 94w | `func_80027A4C` | **`Zone_ColorsScale`** | `ZoneColorsScale` | `level/light.c` | `C` | scale input `gool_colors` by the given red, green, and blue percentages |
| `0x80027BC4` | 207w | `func_80027BC4` | **`Zone_ColorsScaleByNode`** | `ZoneColorsScaleByNode` | `level/light.c` | `C` | scale input `gool_colors` per the given node subtype |
| `0x80027F00` | 20w | `func_80027F00` | **`Zone_ColorSeek`** | `ZoneColorSeek` | `math/step_halfword.c` | `C` | seek input int16 color component by step amount |
| `0x80027F50` | 247w | `func_80027F50` | **`Zone_ColorsScaleSeek`** | `ZoneColorsScaleSeek` | `level/octree.c` | `C` | scale input `gool_colors` per the given node subtype and optionally seek input obj colors towards the scaled input colors |
| `0x8002832C` | 198w | `func_8002832C` | **`Zone_FindNearestNode`** | `ZoneFindNearestNode` | `level/octree.c` | `C` | find the octree node within the current zone or a neighbor which is nearest to a given point |
| `0x80028644` | 220w | `func_80028644` | **`Zone_FindNearestObjectNode`** | `ZoneFindNearestObjectNode` | `level/octree.c` | `C` | find the octree node or object [node] within the current zone or neighbor which is nearest to a given point |
| `0x800289B4` | 290w | `func_800289B4` | **`Zone_FindNearestObjectNode2`** | `ZoneFindNearestObjectNode2` | `level/octree.c` | `C` | alternative variant of `ZoneFindNearestObjectNode` |
| `0x80028E3C` | 372w | `func_80028E3C` | **`Zone_FindNearestObjectNode3`** | `ZoneFindNearestObjectNode3` | `level/octree.c` | `C` | alternative variant of `ZoneFindNearestObjectNode` which colors the object according to node type |
| `0x8002940C` | 41w | `func_8002940C` | **`Zone_ColorsScaleSeekByEntityNode`** | `ZoneColorsScaleSeekByEntityNode` | `level/octree.c` | `C` | `c1:level.c` `ZoneColorsScaleSeekByEntityNode` |
| `0x800294B0` | 115w | `func_800294B0` | **`Zone_QueryOctrees`** | `ZoneQueryOctrees` | `level/octree.c` | `C` | query the octrees of the current zone and its neighbors |
| `0x8002967C` | 11w | `func_8002967C` | **`Zone_QueryOctrees2`** | `ZoneQueryOctrees2` | `render/object_transform.c` | `C` | `ZoneQueryOctrees` using object trans for trans |
| `0x800296A8` | 236w | `func_800296A8` | **`Zone_PathProgressToLoc`** | `ZonePathProgressToLoc` | `—` | `C` | converts a progress to a path point location given a zone path |

### 4.7 Sorting List (`SLST`) Subsystem (`slst.c` — `0x80029A58..0x80029B8F`) (3 functions)

| Address | Size | Current Symbol | Proposed Name (`Module_Action`) | `c1` Name | Current TU (`src/main/`) | Status | Description / Evidence |
|---|---:|---|---|---|---|---|---|
| `0x80029A58` | 32w | `func_80029A58` | **`Slst_Init`** | `SlstInit` | `engine/allocate_buffers.c` | `C` | allocate double poly id buffers |
| `0x80029AD8` | 13w | `func_80029AD8` | **`Slst_Kill`** | `SlstKill` | `engine/release_buffers.c` | `C` | `c1:slst.c` `SlstKill` |
| `0x80029B0C` | 33w | `func_80029B0C` | **`Slst_Update`** | `SlstUpdate` | `engine/stream_dispatch.c` | `C` | `c1:slst.c` `SlstUpdate` |

### 4.8 Fixed-Point Math & Distance Helpers (`math.c` Part 1 — `0x80029B90..0x80029F6B`) (8 functions)

| Address | Size | Current Symbol | Proposed Name (`Module_Action`) | `c1` Name | Current TU (`src/main/`) | Status | Description / Evidence |
|---|---:|---|---|---|---|---|---|
| `0x80029B90` | 64w | `func_80029B90` | **`Math_ApxDist`** | `ApxDist` | `math/approx_distance.c` | `C` | compute the approximate (manhattan distance) between 2 3d points |
| `0x80029C90` | 40w | `func_80029C90` | **`Math_OutOfRange`** | `OutOfRange` | `math/distance_limit.c` | `C` | test if 2 points are out of range of each other |
| `0x80029D30` | 32w | `func_80029D30` | **`Math_EucDist`** | `EucDist` | `math/vector_distance.c` | `C` | compute the (euclidean) distance between two [3d] points |
| `0x80029DB0` | 24w | `func_80029DB0` | **`Math_EucDistXZ`** | `EucDistXZ` | `math/vector_distance.c` | `C` | compute the xz plane distance between two [3d] points |
| `0x80029E10` | 14w | `func_80029E10` | **`Math_AngDistXZ`** | `AngDistXZ` | `math/angles.c` | `C` | compute the xz plane angle between two points |
| `0x80029E48` | 14w | `func_80029E48` | **`Math_AngDistXY`** | `AngDistXY` | `math/angles.c` | `C` | compute the xy plane angle between two points |
| `0x80029E80` | 33w | `func_80029E80` | **`Math_AngDiffClamp`** | `AngDiffClamp` | `math/angles.c` | `C` | Compute wrapped angle difference in `[-0x800, 0x800]` and clamp to `[-max, max]` (`c1:math.c`) |
| `0x80029F04` | 26w | `func_80029F04` | **`Math_SinScale`** | `SinScale` | `math/scaled_sine.c` | `C` | Compute `(sin((a << 10) / b) * b) >> 12` (`c1:math.c`) |

### 4.9 Camera Tracking & Progress Subsystem (`cam.c` — `0x80029F6C..0x8002BAFF`) (6 functions)

| Address | Size | Current Symbol | Proposed Name (`Module_Action`) | `c1` Name | Current TU (`src/main/`) | Status | Description / Evidence |
|---|---:|---|---|---|---|---|---|
| `0x80029F6C` | 86w | `func_80029F6C` | **`Cam_AdjustProgress`** | `CamAdjustProgress` | `—` | `C` | update current progress according to the given progress speed and camera struct and update the level |
| `0x8002A0C4` | 202w | `func_8002A0C4` | **`Cam_GetProgress`** | `CamGetProgress` | `cam/camera.c` | `C` | approximate the projected progress of the player (or a point positioned behind the player) along a particular camera path (incl possible new path, distance error of player to nearest path point, etc.), given player trans and camera path |
| `0x8002A3EC` | 272w | `func_8002A3EC` | **`Cam_GetProgress2`** | `CamGetProgress2` | `cam/camera.c` | `C` | alternate version of `CamGetProgress` |
| `0x8002A82C` | 676w | `func_8002A82C` | **`Cam_Follow`** | `CamFollow` | `cam/camera.c` | `C` | adjust current progress according to a delta calculated based on the projected progress of the player (or more correctly, a point slightly behind or left/right of the player which dynamically zooms and/or pans) along the nearest camera path and update the level |
| `0x8002B2BC` | 510w | `func_8002B2BC` | **`Cam_Update`** | `CamUpdate` | `cam/camera.c` | `C` | update progress and level according to current path's camera mode (where mode 5 and 6 use `CamFollow`) |
| `0x8002BAB4` | 246w | `func_8002BAB4` | **`Cam_Death`** | `CamDeath` | `cam/camera.c` | `C` | update camera during the spinning death sequence |

### 4.10 Solid Surface Collision & Wall Bitmap Subsystem (`solid.c` — `0x8002BB00..0x8002E8A3`) (19 functions)

| Address | Size | Current Symbol | Proposed Name (`Module_Action`) | `c1` Name | Current TU (`src/main/`) | Status | Description / Evidence |
|---|---:|---|---|---|---|---|---|
| `0x8002BE8C` | 190w | `func_8002BE8C` | **`Solid_TransSmoothStopAtSolid`** | `TransSmoothStopAtSolid` | `level/collision.c` | `C` | wrapper for `TransPullStopAtSolid` |
| `0x8002C184` | 141w | `func_8002C184` | **`Solid_TransPullStopAtSolid`** | `TransPullStopAtSolid` | `level/collision.c` | `C` | calculate the limited next trans for a given object, zone query, and current trans, by iteratively taking away from velocity, adding to trans, and limiting with `TransStopAtSolid` |
| `0x8002C3B8` | 89w | `func_8002C3B8` | **`ProcessNode`** | `ProcessNode` | `level/collision.c` | `C` | `c1:solid.c` `ProcessNode` |
| `0x8002C51C` | 81w | `func_8002C51C` | **`Solid_StopAtFloor`** | `StopAtFloor` | `level/collision.c` | `C` | Limit projected vertical position against solid floor octree nodes and objects below (`c1:solid.c`) |
| `0x8002C660` | 163w | `func_8002C660` | **`Solid_StopAtHighestObjectBelow`** | `StopAtHighestObjectBelow` | `level/collision.c` | `C` | limit the projected next trans for a given object to the top face of the nearest object bounding box with which 'it' (i.e. the collision box with center at projected next trans) would collide, if any at all |
| `0x8002C8EC` | 300w | `func_8002C8EC` | **`Solid_StopAtFloor`** | `StopAtFloor` | `level/collision.c` | `C` | limit the projected next trans for a given object to the average of top faces of the nearest solid floor(s) [node bounds] or the top face of a nearer object bounding box |
| `0x8002CD9C` | 199w | `func_8002CD9C` | **`Solid_StopAtCeil`** | `StopAtCeil` | `level/collision.c` | `C` | limit the projected next trans for a given object to the average of bottom faces of the nearest solid ceiling(s) [node bounds] or the bottom face of a nearer object bounding box |
| `0x8002D0B8` | 53w | `func_8002D0B8` | **`Solid_StopAtCeil`** | `StopAtCeil` | `level/collision.c` | `C` | Limit projected vertical position against solid ceiling octree nodes (`c1:solid.c`) |
| `0x8002D18C` | 126w | `func_8002D18C` | **`Solid_StopAtZone`** | `StopAtZone` | `level/collision.c` | `C` | limit the projected next trans for a given object to the bottom face of the current zone bound or a neighbor zone bound, if the face is solid |
| `0x8002D384` | 173w | `func_8002D384` | **`Solid_TransStopAtSolid`** | `TransStopAtSolid` | `level/collision.c` | `C` | calculate the actual [limited] next trans for a given object, current trans, and projected change in trans [velocity]; add velocity to current trans and limit the result at the faces/edges of solid floors, ceilings, walls, and zone boundaries |
| `0x8002D638` | 23w | `func_8002D638` | **`Solid_BinfInit`** | `BinfInit` | `engine/fixed_result.c` | `C` | set up pointers to (or allocate) the wall bitmap, wall cache, and circle bitmap |
| `0x8002D694` | 2w | `func_8002D694` | **`Solid_BinfKill`** | `BinfKill` | `engine/fixed_result.c` | `C` | free memory allocated by `BinfInit` |
| `0x8002D69C` | 78w | `func_8002D69C` | **`Solid_PlotWall`** | `PlotWall` | `engine/grid_rectangle.c` | `C` | set a 16 unit radius circular region of bits in the wall bitmap |
| `0x8002D7D4` | 57w | `func_8002D7D4` | **`Solid_PlotWallB`** | `PlotWallB` | `level/octree.c` | `C` | set or clear a rectangular region of bits in the wall bitmap |
| `0x8002D8B8` | 422w | `func_8002D8B8` | **`Solid_PlotObjWalls`** | `PlotObjWalls` | `level/grid_workspace.c` | `C` | plot walls in the wall bitmap at the scaled relative locations (in the xz plane) of the nearest object(s) [bound boxes] |
| `0x8002DF50` | 68w | `func_8002DF50` | **`Solid_PlotWalls`** | `PlotWalls` | `level/grid_workspace.c` | `C` | plot walls in the wall bitmap at the scaled relative locations [in the xz plane] of the nearest solid wall(s) [node bounds] and object(s) [bound boxes] |
| `0x8002E060` | 16w | `func_8002E060` | **`Solid_TestWallCell`** | `TestWallCell` | `level/grid_search.c` | `C` | Test a single bit `(x, z)` in the 32x32 solid wall occupancy bitmap (`c1:solid.c`) |
| `0x8002E0A0` | 214w | `func_8002E0A0` | **`Solid_ReplotWalls`** | `ReplotWalls` | `level/grid_search.c` | `C` | `c1:solid.c` `ReplotWalls` |
| `0x8002E3F8` | 299w | `func_8002E3F8` | **`Solid_StopAtWalls`** | `StopAtWalls` | `level/grid_search.c` | `C` | adjust input bit index (x, z) to the index of the nearest non-solid bit in the wall bitmap |

### 4.11 Demo Playback (`PBAK`) Subsystem (`pbak.c` — `0x8002E8A4..0x8002EC73`) (8 functions)

| Address | Size | Current Symbol | Proposed Name (`Module_Action`) | `c1` Name | Current TU (`src/main/`) | Status | Description / Evidence |
|---|---:|---|---|---|---|---|---|
| `0x8002E8A4` | 6w | `func_8002E8A4` | **`Pbak_Init`** | `PbakInit` | `engine/reset.c` | `C` | initialize demo playback |
| `0x8002E8BC` | 2w | `func_8002E8BC` | **`Pbak_Kill`** | `PbakKill` | `engine/reset.c` | `C` | `c1:pbak.c` `PbakKill` |
| `0x8002E8C4` | 2w | `func_8002E8C4` | **`Pbak_Noop`** | `PbakNoop` | `engine/reset.c` | `C` | Empty stub (`jr $ra`) in `pbak.c` |
| `0x8002E8CC` | 48w | `func_8002E8CC` | **`Pbak_Start`** | `PbakStart` | `engine/level_resource_initialize.c` | `C` | begin demo playback |
| `0x8002E98C` | 76w | `func_8002E98C` | **`Pbak_Play`** | `PbakPlay` | `engine/level_resource_initialize.c` | `C` | load playback entry and begin demo playback |
| `0x8002EABC` | 62w | `func_8002EABC` | **`Pbak_Choose`** | `PbakChoose` | `engine/level_resource_choose.c` | `C` | choose a random demo playback entry |
| `0x8002EBB4` | 45w | `func_8002EBB4` | **`Shader_ParamsUpdateRipple`** | `ShaderParamsUpdateRipple` | `engine/level_effects.c` | `C` | update level-specific world shader parameters; for ripple shader only |
| `0x8002EC68` | 656w | `func_8002EC68` | **`Shader_ParamsUpdate`** | `ShaderParamsUpdate` | `engine/level_effects.c` | `C` | update level-specific world shader parameters |

### 4.12 World Shader Parameter Updates (`misc.c` — `0x8002EC74..0x8002F6AF`) (1 functions)

| Address | Size | Current Symbol | Proposed Name (`Module_Action`) | `c1` Name | Current TU (`src/main/`) | Status | Description / Evidence |
|---|---:|---|---|---|---|---|---|
| `0x8002F6A8` | 2w | `func_8002F6A8` | **`Shader_Noop`** | `ShaderNoop` | `engine/noop_2F6A8.c` | `C` | Empty stub (`jr $ra`) at end of `misc.c` |

### 4.13 Dual PRNG (`randa` / `randb`) & `absdiff` (`math.c` Part 2 — `0x8002F6B0..0x8002F857`) (7 functions)

| Address | Size | Current Symbol | Proposed Name (`Module_Action`) | `c1` Name | Current TU (`src/main/`) | Status | Description / Evidence |
|---|---:|---|---|---|---|---|---|
| `0x8002F6B0` | 43w | `func_8002F6B0` | **`Math_Randa`** | `randa` | `math/random_state.c` | `C` | Generate pseudo-random integer in `[0, max)` using `seed_a` (`D_800564D8`) (`c1:math.c`) |
| `0x8002F75C` | 4w | `func_8002F75C` | **`Math_Sranda2`** | `sranda2` | `math/random_state.c` | `C` | Reset `seed_a` (`D_800564D8`) to default seed `12345` (`c1:math.c`) |
| `0x8002F76C` | 3w | `func_8002F76C` | **`Math_Sranda`** | `sranda` | `math/random_state.c` | `C` | Set `seed_a` (`D_800564D8`) to given seed (`c1:math.c`) |
| `0x8002F778` | 43w | `func_8002F778` | **`Math_Randb`** | `randb` | `math/random_state.c` | `C` | Generate pseudo-random integer in `[0, max)` using `seed_b` (`D_800564DC`) (`c1:math.c`) |
| `0x8002F824` | 4w | `func_8002F824` | **`Math_Srandb2`** | `srandb2` | `math/random_state.c` | `C` | Reset `seed_b` (`D_800564DC`) to default seed `12345` (`c1:math.c`) |
| `0x8002F834` | 3w | `func_8002F834` | **`Math_Srandb`** | `srandb` | `math/random_state.c` | `C` | Set `seed_b` (`D_800564DC`) to given seed (`c1:math.c`) |
| `0x8002F840` | 6w | `func_8002F840` | **`Math_Absdiff`** | `absdiff` | `math/distance.c` | `C` | Return `abs(a - b)` (`c1:math.c`) |

### 4.14 CD-ROM ISO-9660 Filesystem Reader & Stub Table (`psx/cdr.c` — `0x8002F858..0x8002FDDF`) (24 functions)

| Address | Size | Current Symbol | Proposed Name (`Module_Action`) | `c1` Name | Current TU (`src/main/`) | Status | Description / Evidence |
|---|---:|---|---|---|---|---|---|
| `0x8002F858` | 27w | `func_8002F858` | **`Cd_ReadSectors`** | `CdReadSectors` | `engine/cd_read.c` | `C` | `c1:psx/cdr.c` `CdReadSectors` |
| `0x8002F8C4` | 283w | `func_8002F8C4` | **`Cd_ReadFileSys`** | `CdReadFileSys` | `engine/cd_dir.c` | `C` | `c1:psx/cdr.c` `CdReadFileSys` |
| `0x8002FD30` | 2w | `func_8002FD30` | **`Cd_Stub_01`** | `CdStub_01` | `engine/noop_entries.c` | `C` | No-op stub (`jr $ra`); registered in `SsSepOpen` (`g_ss_nrpn_attr_fn_00..g_ss_nrpn_attr_fn_19`) for unused CC/NRPN handlers |
| `0x8002FD38` | 2w | `func_8002FD38` | **`Cd_Stub_02`** | `CdStub_02` | `engine/noop_entries.c` | `C` | No-op stub (`jr $ra`); registered in `SsSepOpen` (`g_ss_nrpn_attr_fn_00..g_ss_nrpn_attr_fn_19`) for unused CC/NRPN handlers |
| `0x8002FD40` | 2w | `func_8002FD40` | **`Cd_Stub_03`** | `CdStub_03` | `engine/noop_entries.c` | `C` | No-op stub (`jr $ra`); registered in `SsSepOpen` (`g_ss_nrpn_attr_fn_00..g_ss_nrpn_attr_fn_19`) for unused CC/NRPN handlers |
| `0x8002FD48` | 2w | `func_8002FD48` | **`Cd_Stub_04`** | `CdStub_04` | `engine/noop_entries.c` | `C` | No-op stub (`jr $ra`); registered in `SsSepOpen` (`g_ss_nrpn_attr_fn_00..g_ss_nrpn_attr_fn_19`) for unused CC/NRPN handlers |
| `0x8002FD50` | 2w | `func_8002FD50` | **`Cd_Stub_05`** | `CdStub_05` | `engine/noop_entries.c` | `C` | No-op stub (`jr $ra`); registered in `SsSepOpen` (`g_ss_nrpn_attr_fn_00..g_ss_nrpn_attr_fn_19`) for unused CC/NRPN handlers |
| `0x8002FD58` | 2w | `func_8002FD58` | **`Cd_Stub_06`** | `CdStub_06` | `engine/noop_entries.c` | `C` | No-op stub (`jr $ra`); registered in `SsSepOpen` (`g_ss_nrpn_attr_fn_00..g_ss_nrpn_attr_fn_19`) for unused CC/NRPN handlers |
| `0x8002FD60` | 2w | `func_8002FD60` | **`Cd_Stub_07`** | `CdStub_07` | `engine/noop_entries.c` | `C` | No-op stub (`jr $ra`); registered in `SsSepOpen` (`g_ss_nrpn_attr_fn_00..g_ss_nrpn_attr_fn_19`) for unused CC/NRPN handlers |
| `0x8002FD68` | 2w | `func_8002FD68` | **`Cd_Stub_08`** | `CdStub_08` | `engine/noop_entries.c` | `C` | No-op stub (`jr $ra`); registered in `SsSepOpen` (`g_ss_nrpn_attr_fn_00..g_ss_nrpn_attr_fn_19`) for unused CC/NRPN handlers |
| `0x8002FD70` | 2w | `func_8002FD70` | **`Cd_Stub_09`** | `CdStub_09` | `engine/noop_entries.c` | `C` | No-op stub (`jr $ra`); registered in `SsSepOpen` (`g_ss_nrpn_attr_fn_00..g_ss_nrpn_attr_fn_19`) for unused CC/NRPN handlers |
| `0x8002FD78` | 2w | `func_8002FD78` | **`Cd_Stub_10`** | `CdStub_10` | `engine/noop_entries.c` | `C` | No-op stub (`jr $ra`); registered in `SsSepOpen` (`g_ss_nrpn_attr_fn_00..g_ss_nrpn_attr_fn_19`) for unused CC/NRPN handlers |
| `0x8002FD80` | 2w | `func_8002FD80` | **`Cd_Stub_11`** | `CdStub_11` | `engine/noop_entries.c` | `C` | No-op stub (`jr $ra`); registered in `SsSepOpen` (`g_ss_nrpn_attr_fn_00..g_ss_nrpn_attr_fn_19`) for unused CC/NRPN handlers |
| `0x8002FD88` | 2w | `func_8002FD88` | **`Cd_Stub_12`** | `CdStub_12` | `engine/noop_entries.c` | `C` | No-op stub (`jr $ra`); registered in `SsSepOpen` (`g_ss_nrpn_attr_fn_00..g_ss_nrpn_attr_fn_19`) for unused CC/NRPN handlers |
| `0x8002FD90` | 2w | `func_8002FD90` | **`Cd_Stub_13`** | `CdStub_13` | `engine/noop_entries.c` | `C` | No-op stub (`jr $ra`); registered in `SsSepOpen` (`g_ss_nrpn_attr_fn_00..g_ss_nrpn_attr_fn_19`) for unused CC/NRPN handlers |
| `0x8002FD98` | 2w | `func_8002FD98` | **`Cd_Stub_14`** | `CdStub_14` | `engine/noop_entries.c` | `C` | No-op stub (`jr $ra`); registered in `SsSepOpen` (`g_ss_nrpn_attr_fn_00..g_ss_nrpn_attr_fn_19`) for unused CC/NRPN handlers |
| `0x8002FDA0` | 2w | `func_8002FDA0` | **`Cd_Stub_15`** | `CdStub_15` | `engine/noop_entries.c` | `C` | No-op stub (`jr $ra`); registered in `SsSepOpen` (`g_ss_nrpn_attr_fn_00..g_ss_nrpn_attr_fn_19`) for unused CC/NRPN handlers |
| `0x8002FDA8` | 2w | `func_8002FDA8` | **`Cd_Stub_16`** | `CdStub_16` | `engine/noop_entries.c` | `C` | No-op stub (`jr $ra`); registered in `SsSepOpen` (`g_ss_nrpn_attr_fn_00..g_ss_nrpn_attr_fn_19`) for unused CC/NRPN handlers |
| `0x8002FDB0` | 2w | `func_8002FDB0` | **`Cd_Stub_17`** | `CdStub_17` | `engine/noop_entries.c` | `C` | No-op stub (`jr $ra`); registered in `SsSepOpen` (`g_ss_nrpn_attr_fn_00..g_ss_nrpn_attr_fn_19`) for unused CC/NRPN handlers |
| `0x8002FDB8` | 2w | `func_8002FDB8` | **`Cd_Stub_18`** | `CdStub_18` | `engine/noop_entries.c` | `C` | No-op stub (`jr $ra`); registered in `SsSepOpen` (`g_ss_nrpn_attr_fn_00..g_ss_nrpn_attr_fn_19`) for unused CC/NRPN handlers |
| `0x8002FDC0` | 2w | `func_8002FDC0` | **`Cd_Stub_19`** | `CdStub_19` | `engine/noop_entries.c` | `C` | No-op stub (`jr $ra`); registered in `SsSepOpen` (`g_ss_nrpn_attr_fn_00..g_ss_nrpn_attr_fn_19`) for unused CC/NRPN handlers |
| `0x8002FDC8` | 2w | `func_8002FDC8` | **`Cd_Stub_20`** | `CdStub_20` | `engine/noop_entries.c` | `C` | No-op stub (`jr $ra`); registered in `SsSepOpen` (`g_ss_nrpn_attr_fn_00..g_ss_nrpn_attr_fn_19`) for unused CC/NRPN handlers |
| `0x8002FDD0` | 2w | `func_8002FDD0` | **`Cd_Stub_21`** | `CdStub_21` | `engine/noop_entries.c` | `C` | No-op stub (`jr $ra`); registered in `SsSepOpen` (`g_ss_nrpn_attr_fn_00..g_ss_nrpn_attr_fn_19`) for unused CC/NRPN handlers |
| `0x8002FDD8` | 2w | `func_8002FDD8` | **`Cd_Stub_22`** | `CdStub_22` | `engine/noop_entries.c` | `C` | No-op stub (`jr $ra`); registered in `SsSepOpen` (`g_ss_nrpn_attr_fn_00..g_ss_nrpn_attr_fn_19`) for unused CC/NRPN handlers |

### 4.15 Spatial Audio & SPU Voice Engine (`audio.c` — `0x8002FDE0..0x80030D97`) (10 functions)

| Address | Size | Current Symbol | Proposed Name (`Module_Action`) | `c1` Name | Current TU (`src/main/`) | Status | Description / Evidence |
|---|---:|---|---|---|---|---|---|
| `0x8002FDE0` | 120w | `func_8002FDE0` | **`Audio_Init`** | `AudioInit` | `engine/audio_reset.c` | `C` | `c1:audio.c` `AudioInit` |
| `0x8002FFC0` | 15w | `func_8002FFC0` | **`Audio_Kill`** | `AudioKill` | `engine/reverb_disable.c` | `C` | `c1:audio.c` `AudioKill` |
| `0x8002FFFC` | 3w | `func_8002FFFC` | **`Audio_SetVoiceMVol`** | `AudioSetVoiceMVol` | `engine/value_56644.c` | `C` | `c1:audio.c` `AudioSetVoiceMVol` |
| `0x80030008` | 28w | `func_80030008` | **`Audio_SetReverbAttr`** | `AudioSetReverbAttr` | `engine/reverb_set.c` | `C` | `c1:audio.c` `AudioSetReverbAttr` |
| `0x80030078` | 122w | `func_80030078` | **`Audio_Spatialize`** | `AudioSpatialize` | `engine/audio_voice.c` | `C` | `c1:audio.c` `AudioSpatialize` |
| `0x80030260` | 50w | `func_80030260` | **`Audio_VoiceFree`** | `AudioVoiceFree` | `engine/audio_voice.c` | `C` | `c1:audio.c` `AudioVoiceFree` |
| `0x80030328` | 104w | `func_80030328` | **`Audio_VoiceAlloc`** | `AudioVoiceAlloc` | `engine/audio_voice.c` | `C` | `c1:audio.c` `AudioVoiceAlloc` |
| `0x800304C8` | 222w | `func_800304C8` | **`Audio_VoiceCreate`** | `AudioVoiceCreate` | `engine/audio_voice.c` | `C` | `c1:audio.c` `AudioVoiceCreate` |
| `0x80030840` | 288w | `func_80030840` | **`Audio_Control`** | `AudioControl` | `engine/audio_voice.c` | `C` | `c1:audio.c` `AudioControl` |
| `0x80030CC0` | 316w | `func_80030CC0` | **`Audio_Update`** | `AudioUpdate` | `engine/audio_voice.c` | `C` | `c1:audio.c` `AudioUpdate` |

### 4.16 MIDI / SEP Sequencer Engine (`midi.c` — `0x80030D98..0x80031BAB`) (12 functions)

| Address | Size | Current Symbol | Proposed Name (`Module_Action`) | `c1` Name | Current TU (`src/main/`) | Status | Description / Evidence |
|---|---:|---|---|---|---|---|---|
| `0x800311B0` | 37w | `func_800311B0` | **`Midi_ResetSeqVol`** | `MidiResetSeqVol` | `engine/audio_sequence_gain.c` | `C` | reset volume of the playback sequence |
| `0x80031244` | 92w | `func_80031244` | **`Midi_Init`** | `MidiInit` | `engine/audio_initialize.c` | `C` | initialize the midi playback engine |
| `0x800313B4` | 4w | `func_800313B4` | **`Midi_ResetFadeStep`** | `MidiResetFadeStep` | `engine/value_56664.c` | `C` | reset step value for volume fade counters |
| `0x800313C4` | 64w | `func_800313C4` | **`Midi_TogglePlayback`** | `MidiTogglePlayback` | `engine/audio_mode_update.c` | `C` | toggle playback of the currently playing sequence |
| `0x800314C4` | 198w | `func_800314C4` | **`Midi_OpenAndPlay`** | `MidiOpenAndPlay` | `engine/midi_load.c` | `C` | open and begin playback of a midi entry |
| `0x800317DC` | 7w | `func_800317DC` | **`Midi_SetStateStopped`** | `MidiSetStateStopped` | `engine/update_request.c` | `C` | stop midi playback |
| `0x800317F8` | 80w | `func_800317F8` | **`Midi_Update`** | `MidiUpdate` | `engine/audio_transition_update.c` | `C` | per-frame update function for midi engine; handles changes in state between frames |
| `0x80031938` | 11w | `func_80031938` | **`Midi_Kill`** | `MidiKill` | `engine/audio_stop_current.c` | `C` | kill the midi playback engine |
| `0x80031964` | 30w | `func_80031964` | **`Midi_SeqInit`** | `MidiSeqInit` | `engine/audio_channel_initialize.c` | `C` | set initial sequence number and playback volume |
| `0x800319DC` | 25w | `func_800319DC` | **`Midi_Close`** | `MidiClose` | `engine/audio_stop.c` | `C` | close SEP and VAB |
| `0x80031A40` | 72w | `func_80031A40` | **`Midi_Control`** | `MidiControl` | `engine/audio_stop.c` | `C` | control midi playback (play, stop, pause, resume, or fade) |
| `0x80031B60` | 19w | `func_80031B60` | **`Midi_PreloadEntries`** | `MidiPreloadEntries` | `engine/resource_adjust.c` | `C` | Open or close all `MIDI` entries referenced by a zone header (`c1:midi.c`) |

### 4.17 Title Screen, Menus & World Map State Machine (`title.c` — `0x80031BAC..0x8003349F`) (18 functions)

| Address | Size | Current Symbol | Proposed Name (`Module_Action`) | `c1` Name | Current TU (`src/main/`) | Status | Description / Evidence |
|---|---:|---|---|---|---|---|---|
| `0x80031BAC` | 19w | `func_80031BAC` | **`Title_Init`** | `TitleInit` | `engine/state.c` | `C` | allocate title screen struct |
| `0x80031BF8` | 86w | `func_80031BF8` | **`Title_LoadNextState`** | `TitleLoadNextState` | `engine/state.c` | `C` | load the next title screen state |
| `0x80031D50` | 89w | `func_80031D50` | **`Title_LoadScreen`** | `TitleLoadScreen` | `engine/state.c` | `C` | load a title screen |
| `0x80031EB4` | 228w | `func_80031EB4` | **`Title_LoadState`** | `TitleLoadState` | `engine/state.c` | `C` | load a title screen state |
| `0x80032244` | 21w | `func_80032244` | **`Title_KillObjectsAndEntries`** | `TitleKillObjectsAndEntries` | `engine/state.c` | `C` | Terminate all GOOL objects and close `MDAT` entries on title exit (`c1:title.c`) |
| `0x80032298` | 13w | `func_80032298` | **`Title_Kill`** | `TitleKill` | `engine/state.c` | `C` | free memory allocated by `TitleInit` |
| `0x800322CC` | 130w | `func_800322CC` | **`Title_Loading`** | `TitleLoading` | `engine/state.c` | `C` | display loading splash screen |
| `0x800324D4` | 90w | `func_800324D4` | **`Title_LoadSingleTile`** | `TitleLoadSingleTile` | `engine/state.c` | `C` | Upload a single 16x16 `IMAG` tile texture to VRAM during title scrolling (`c1:title.c`) |
| `0x8003263C` | 39w | `func_8003263C` | **`Title_RequestState`** | `TitleRequestState` | `engine/state.c` | `C` | Dismiss pause object if active, set `fade_counter = -256`, and transition to `next_state` (`c1:title.c`) |
| `0x800326D8` | 263w | `func_800326D8` | **`Title_Update`** | `TitleUpdate` | `engine/state.c` | `C` | per-frame update function for the title screen; handles state transitions and calls to the other lower-level title screen Functions |
| `0x80032AF4` | 48w | `func_80032AF4` | **`Title_CalcUvs`** | `TitleCalcUvs` | `engine/state.c` | `C` | calculate uv coordinate indices for each imag tile |
| `0x80032BB4` | 146w | `func_80032BB4` | **`Title_CalcTiles`** | `TitleCalcTiles` | `engine/state.c` | `C` | calculate infos for each tile, set draw modes, and get tpage idx |
| `0x80032DFC` | 120w | `func_80032DFC` | **`Title_LoadImages`** | `TitleLoadImages` | `engine/state.c` | `C` | load color mode 1 textures into the appropriate locations of vram for each splash screen image tile, based on computed uv indices |
| `0x80032FDC` | 290w | `func_80032FDC` | **`Title_LoadEntries`** | `TitleLoadEntries` | `engine/state.c` | `C` | load all entries for a given mdat state |
| `0x80033464` | 2w | `func_80033464` | **`Slst_Noop1`** | `SlstNoop1` | `engine/state.c` | `C` | Empty stub (`jr $ra`) before `slst` asm |
| `0x8003346C` | 9w | `func_8003346C` | **`Slst_NoopWrapper`** | `SlstNoopWrapper` | `engine/func_8003346C.c` | `C` | Calls `func_80033490` and returns `0` |
| `0x80033490` | 2w | `func_80033490` | **`Slst_Noop2`** | `SlstNoop2` | `engine/state.c` | `C` | Empty stub (`jr $ra`) |
| `0x80033498` | 2w | `func_80033498` | **`Slst_Noop3`** | `SlstNoop3` | `engine/state.c` | `C` | Empty stub (`jr $ra`) |

### 4.18 Hand-Coded R3000A & GTE Assembly Routines (`psx/r3000a.s` — `0x800334A0..0x8003A94B`) (41 functions)

| Address | Size | Current Symbol | Proposed Name (`Module_Action`) | `c1` Name | Current TU (`src/main/`) | Status | Description / Evidence |
|---|---:|---|---|---|---|---|---|
| `0x800334A0` | 246w | `func_800334A0` | **`Slst_RDecodeForward`** | `RSlstDecodeForward` | `—` | `C` | Hand-coded R3000A forward delta-decoder for `SLST` polygon ID sorting lists (`c1:slst.c`) |
| `0x80033878` | 418w | `func_80033878` | **`Slst_RDecodeBackward`** | `RSlstDecodeBackward` | `—` | `C` | Hand-coded R3000A backward delta-decoder for `SLST` polygon ID sorting lists (`c1:slst.c`) |
| `0x80033F18` | 2w | `func_80033F18` | **`RMemcpy_0`** | `RMemcpy_0` | `—` | `C` | `RMemcpy` tail jump target for 0 words (`c1:psx/r3000a.c`) |
| `0x80033F38` | 4w | `func_80033F38` | **`RMemcpy_1`** | `RMemcpy_1` | `—` | `C` | `RMemcpy` tail jump target for 1 word (`c1:psx/r3000a.c`) |
| `0x80033F58` | 6w | `func_80033F58` | **`RMemcpy_2`** | `RMemcpy_2` | `—` | `C` | `RMemcpy` tail jump target for 2 words (`c1:psx/r3000a.c`) |
| `0x80033F78` | 8w | `func_80033F78` | **`RMemcpy_3`** | `RMemcpy_3` | `—` | `C` | `RMemcpy` tail jump target for 3 words (`c1:psx/r3000a.c`) |
| `0x80033F98` | 9w | `func_80033F98` | **`RMemcpy_4`** | `RMemcpy_4` | `—` | `C` | `RMemcpy` tail jump target for 4 words (`c1:psx/r3000a.c`) |
| `0x80033FBC` | 151w | `func_80033FBC` | **`RMemcpy`** | `RMemcpy` | `—` | `C` | Fast unrolled word-aligned memory copy `(src, dst, bytes)` (`c1:psx/r3000a.c`) |
| `0x80034230` | 2w | `func_80034230` | **`Gpu_RResetOT_0`** | `RGpuResetOT_0` | `—` | `C` | `RGpuResetOT` tail jump target for 0 entries |
| `0x80034250` | 4w | `func_80034250` | **`Gpu_RResetOT_1`** | `RGpuResetOT_1` | `—` | `C` | `RGpuResetOT` tail jump target for 1 entry |
| `0x80034270` | 6w | `func_80034270` | **`Gpu_RResetOT_2`** | `RGpuResetOT_2` | `—` | `C` | `RGpuResetOT` tail jump target for 2 entries |
| `0x80034290` | 8w | `func_80034290` | **`Gpu_RResetOT_3`** | `RGpuResetOT_3` | `—` | `C` | `RGpuResetOT` tail jump target for 3 entries |
| `0x800342B0` | 10w | `func_800342B0` | **`Gpu_RResetOT_4`** | `RGpuResetOT_4` | `—` | `C` | `RGpuResetOT` tail jump target for 4 entries |
| `0x800342D8` | 139w | `func_800342D8` | **`Gpu_RResetOT`** | `RGpuResetOT` | `—` | `C` | Fast unrolled ordering-table initializer `(ot, len)` (`c1:psx/r3000a.c`) |
| `0x80034504` | 7w | `func_80034504` | **`RIncTickCount`** | `RIncTickCount` | `engine/gte_render.c` | `C` | Root counter 2 (`RCntCNT2`) interrupt callback; increments `ticks_elapsed` (`D_800565B4`) (`c1:psx/init.c`) |
| `0x80034524` | 22w | `func_80034524` | **`RSqrMagnitude2`** | `RSqrMagnitude2` | `—` | `C` | GTE `SQR` 2D vector squared-magnitude helper `(x, z, shift)` (`c1:audio.c`) |
| `0x80034580` | 34w | `func_80034580` | **`RSqrMagnitude3`** | `RSqrMagnitude3` | `—` | `C` | GTE `SQR` 3D vector squared-magnitude helper `(x, z, y, shifts)` (`c1:audio.c`) |
| `0x8003460C` | 319w | `func_8003460C` | **`Gte_RTransformSvtx`** | `RGteTransformSvtx` | `—` | `C` | Hand-coded GTE `RTPT`/`NCLIP`/`NCCT` renderer for `SVTX` animated character meshes (`c1:psx/r3000a.c`) |
| `0x80034B08` | 431w | `func_80034B08` | **`Gte_RTransformCvtx`** | `RGteTransformCvtx` | `—` | `C` | Hand-coded GTE renderer for `CVTX` vertex-colored meshes (`c1:psx/r3000a.c`) |
| `0x800351C8` | 106w | `func_800351C8` | **`Gte_RProjectBound`** | `RGteProjectBound` | `—` | `C` | Project 3D bounding box corners with GTE `RTPT` into 2D `scratch.obj_extents` (`c1:psx/r3000a.c`) |
| `0x80035370` | 16w | `func_80035370` | **`Gte_RExtendBound3`** | `RGteExtendBound3` | `—` | `C` | Update 2D min/max extents with 3 projected vertices (`c1:psx/r3000a.c`) |
| `0x800353B0` | 34w | `func_800353B0` | **`Gte_RExtendBound2`** | `RGteExtendBound2` | `—` | `C` | Update 2D min/max extents with 2 projected vertices (`c1:psx/r3000a.c`) |
| `0x80035438` | 280w | `func_80035438` | **`Gte_RTransformWorlds`** | `RGteTransformWorlds` | `—` | `C` | Hand-coded GTE `WGEO` world polygon renderer (standard shader) (`c1:gfx.c`) |
| `0x80035898` | 350w | `func_80035898` | **`Gte_RTransformWorldsFog`** | `RGteTransformWorldsFog` | `—` | `C` | Hand-coded GTE `WGEO` world polygon renderer with depth-cue fog (`c1:gfx.c`) |
| `0x80035E10` | 332w | `func_80035E10` | **`Gte_RTransformWorldsRipple`** | `RGteTransformWorldsRipple` | `—` | `C` | Hand-coded GTE `WGEO` world polygon renderer with water-ripple vertex wave (`c1:gfx.c`) |
| `0x80036340` | 557w | `func_80036340` | **`Gte_RTransformWorldsLightning`** | `RGteTransformWorldsLightning` | `—` | `C` | Hand-coded GTE `WGEO` world polygon renderer with lightning flash illumination (`c1:gfx.c`) |
| `0x80036BF4` | 106w | `func_80036BF4` | **`Gte_RTransformWorldsDark`** | `RGteTransformWorldsDark` | `—` | `C` | Hand-coded GTE `WGEO` world polygon renderer with dynamic light-cone darkness (`c1:gfx.c`) |
| `0x80036D9C` | 532w | `func_80036D9C` | **`Gte_RTransformWorldsDarkLoop`** | `RGteTransformWorldsDarkLoop` | `—` | `C` | Inner polygon-transform loop for `RGteTransformWorldsDark` (`c1:gfx.c`) |
| `0x800375EC` | 473w | `func_800375EC` | **`Gte_RTransformWorldsDark2`** | `RGteTransformWorldsDark2` | `—` | `C` | Hand-coded GTE `WGEO` world polygon renderer with alternate darkness shader (`c1:gfx.c`) |
| `0x80037D50` | 575w | `func_80037D50` | **`Solid_RZoneQueryOctree`** | `RZoneQueryOctree` | `—` | `C` | Hand-coded R3000A recursive octree spatial query (`c1:psx/r3000a.c`) |
| `0x8003864C` | 212w | `func_8003864C` | **`Solid_RPlotQueryWalls`** | `RPlotQueryWalls` | `—` | `C` | Hand-coded R3000A wall-bitmap plotter for queried octree wall nodes (`c1:psx/r3000a.c`) |
| `0x8003899C` | 3w | `func_8003899C` | **`Solid_RPlotWallEntry`** | `RPlotWallEntry` | `—` | `C` | Alternate entry stub into `RPlotWall` (`c1:psx/r3000a.c`) |
| `0x800389A8` | 71w | `func_800389A8` | **`Solid_RPlotWall`** | `RPlotWall` | `—` | `C` | Hand-coded R3000A 16-unit circular wall-bitmap brush plotter (`c1:psx/r3000a.c`) |
| `0x80038AC4` | 205w | `func_80038AC4` | **`Solid_RFindFloorY`** | `RFindFloorY` | `—` | `C` | Hand-coded R3000A floor-node Y height resolver (`c1:psx/r3000a.c`) |
| `0x80038DF8` | 153w | `func_80038DF8` | **`Solid_RFindCeilY`** | `RFindCeilY` | `—` | `C` | Hand-coded R3000A ceiling-node Y height resolver (`c1:psx/r3000a.c`) |
| `0x8003905C` | 29w | `func_8003905C` | **`sin`** | `sin` | `—` | `C` | Fast 12-bit fixed-point sine lookup/interpolation using `D_800539A0` table (`c1:math.h`) |
| `0x800390D0` | 27w | `func_800390D0` | **`cos`** | `cos` | `—` | `C` | Fast 12-bit fixed-point cosine lookup/interpolation using `D_800539A0` table (`c1:math.h`) |
| `0x8003913C` | 678w | `func_8003913C` | **`Gte_RCalcObjectRotMatrix`** | `RGteCalcObjectRotMatrix` | `—` | `C` | Hand-coded GTE ZXY/YXZ Euler rotation & scale matrix builder (`c1:gfx.c`) |
| `0x80039BD4` | 348w | `func_80039BD4` | **`Gte_RCalcObjectMatrices`** | `RGteCalcObjectMatrices` | `—` | `C` | Hand-coded GTE object modelview, light, and color matrix calculator (`c1:gfx.c`) |
| `0x8003A144` | 394w | `func_8003A144` | **`Gte_RCalcSpriteRotMatrix`** | `RGteCalcSpriteRotMatrix` | `gool/update_object.c` | `C` | Hand-coded GTE billboard sprite rotation matrix calculator (`c1:psx/r3000a.c`) |
| `0x8003A76C` | 120w | `func_8003A76C` | **`Gte_RTransformSprite`** | `RGteTransformSprite` | `—` | `C` | Hand-coded GTE 4-corner sprite quad transformer and OT inserter (`c1:psx/r3000a.c`) |

### 4.19 Memory Card Save/Load State Machine (`psx/card.c` — `0x8003A94C..0x8003D67F`) (58 functions)

| Address | Size | Current Symbol | Proposed Name (`Module_Action`) | `c1` Name | Current TU (`src/main/`) | Status | Description / Evidence |
|---|---:|---|---|---|---|---|---|
| `0x8003A94C` | 76w | `func_8003A94C` | **`Card_Update`** | `CardUpdate` | `engine/card.c` | `C` | Per-frame memory card state-machine dispatcher (states 0..8) (`c1:psx/card.c`) |
| `0x8003AA7C` | 74w | `func_8003AA7C` | **`Card_PollEvents`** | `CardPollEvents` | `engine/card.c` | `C` | State 0: poll soft card events and initiate block `0x3F` write test on new card (`c1:psx/card.c`) |
| `0x8003ABA4` | 34w | `func_8003ABA4` | **`Card_Check`** | `CardCheck` | `engine/card.c` | `C` | State 4: test-read block 0 (`MC` magic) via `CardTestRead` (`c1:psx/card.c`) |
| `0x8003AC2C` | 86w | `func_8003AC2C` | **`Card_Load`** | `CardLoad` | `engine/card.c` | `C` | State 1: call `_card_load`, enumerate `bu00:*` directory entries, and sort Crash saves (`c1:psx/card.c`) |
| `0x8003AD84` | 13w | `func_8003AD84` | **`Card_ClearUnused`** | `CardClearUnused` | `engine/card.c` | `C` | Unreferenced helper clearing `card` fields (`c1:psx/card.c`) |
| `0x8003ADB8` | 20w | `func_8003ADB8` | **`Card_OnReadImageError`** | `CardOnReadImageError` | `engine/card.c` | `C` | Error callback for `CardPartReadImages`; increments retry count and closes file (`c1:psx/card.c`) |
| `0x8003AE08` | 52w | `func_8003AE08` | **`Card_OnWriteError`** | `CardOnWriteError` | `engine/card.c` | `C` | Error callback for `CardPartWrite`; closes and erases incomplete new save file (`c1:psx/card.c`) |
| `0x8003AED8` | 19w | `func_8003AED8` | **`Card_OnReadGlobalsError`** | `CardOnReadGlobalsError` | `engine/card.c` | `C` | Error callback for `CardPartReadGlobals`; increments retry count and closes file (`c1:psx/card.c`) |
| `0x8003AF24` | 431w | `func_8003AF24` | **`Card_PartReadImages`** | `CardPartReadImages` | `engine/card.c` | `C` | State 5: read save header, Shift-JIS title, icons, and progress bits for each card slot (`c1:psx/card.c`) |
| `0x8003B5E0` | 91w | `func_8003B5E0` | **`Card_ShiftJisToAscii`** | `CardShiftJisToAscii` | `engine/card.c` | `C` | Convert Shift-JIS save block title string to ASCII in-place (`c1:psx/card.c`) |
| `0x8003B74C` | 91w | `func_8003B74C` | **`Card_AsciiToShiftJis`** | `CardAsciiToShiftJis` | `engine/card.c` | `C` | Convert ASCII `Crash (%d%%)` save title to big-endian Shift-JIS (`c1:psx/card.c`) |
| `0x8003B8B8` | 354w | `func_8003B8B8` | **`Card_PartWrite`** | `CardPartWrite` | `engine/card.c` | `C` | States 6..8: format `bu00:BASCUS-94900%02d%06d`, write header, 3 icons, and 5 redundant save blocks (`c1:psx/card.c`) |
| `0x8003BE40` | 61w | `func_8003BE40` | **`Card_SaveGlobals`** | `CardSaveGlobals` | `engine/card.c` | `C` | Pack level, life, gem, key, volume, and item pools into 128-byte `card_globals` with checksum (`c1:psx/card.c`) |
| `0x8003BF34` | 50w | `func_8003BF34` | **`Card_LoadGlobals`** | `CardLoadGlobals` | `engine/card.c` | `C` | Verify `CardChecksum` and unpack 128-byte `card_globals` into engine globals (`c1:psx/card.c`) |
| `0x8003BFFC` | 15w | `func_8003BFFC` | **`Card_Checksum`** | `CardChecksum` | `engine/checksum.c` | `C` | Compute 32-bit rotate-left-3 additive checksum seeded with `0x12345678` (`c1:psx/card.c`) |
| `0x8003C038` | 200w | `func_8003C038` | **`Card_PartReadGlobals`** | `CardPartReadGlobals` | `engine/card.c` | `C` | State 2: open `bu00:` save file, skip header/icons, and read up to 5 save blocks (`c1:psx/card.c`) |
| `0x8003C358` | 29w | `func_8003C358` | **`Card_Format`** | `CardFormat` | `engine/card.c` | `C` | State 3: format memory card via BIOS `format("bu00:")` (`c1:psx/card.c`) |
| `0x8003C3CC` | 2w | `func_8003C3CC` | **`Card_Noop1`** | `CardNoop1` | `engine/card.c` | `C` | Empty callback stub (`jr $ra`) (`c1:psx/card.c`) |
| `0x8003C3D4` | 2w | `func_8003C3D4` | **`Card_Noop2`** | `CardNoop2` | `engine/card.c` | `C` | Empty callback stub (`jr $ra`) (`c1:psx/card.c`) |
| `0x8003C3DC` | 2w | `func_8003C3DC` | **`Card_Noop3`** | `CardNoop3` | `engine/card.c` | `C` | Empty callback stub (`jr $ra`) (`c1:psx/card.c`) |
| `0x8003C3E4` | 6w | `func_8003C3E4` | **`Card_ResetRetryCount`** | `CardResetRetryCount` | `engine/card.c` | `C` | Reset `card->retry_count = 0` and set `card->retry_max` (`c1:psx/card.c`) |
| `0x8003C3FC` | 9w | `func_8003C3FC` | **`Card_IncRetryCount`** | `CardIncRetryCount` | `engine/card.c` | `C` | Increment `card->retry_count` and return 1 if `>= card->retry_max` (`c1:psx/card.c`) |
| `0x8003C420` | 33w | `func_8003C420` | **`Card_PollSoftEvent`** | `CardPollSoftEvent` | `engine/card.c` | `C` | Test `SwCARD` events (`EvSpIOE`, `EvSpERROR`, `EvSpTIMOUT`, `EvSpNEW`) (`c1:psx/card.c`) |
| `0x8003C4A4` | 37w | `func_8003C4A4` | **`Card_WaitSoftEvent`** | `CardWaitSoftEvent` | `engine/card.c` | `C` | Busy-wait on `SwCARD` events until one fires (`c1:psx/card.c`) |
| `0x8003C538` | 18w | `func_8003C538` | **`Card_ResetSoftEvent`** | `CardResetSoftEvent` | `engine/state_event_test.c` | `C` | Clear pending `SwCARD` events via `TestEvent` (`c1:psx/card.c`) |
| `0x8003C580` | 34w | `func_8003C580` | **`Card_PollHardEvent`** | `CardPollHardEvent` | `engine/card.c` | `C` | Test `HwCARD` events (`EvSpIOE`, `EvSpERROR`, `EvSpTIMOUT`, `EvSpNEW`) (`c1:psx/card.c`) |
| `0x8003C608` | 37w | `func_8003C608` | **`Card_WaitHardEvent`** | `CardWaitHardEvent` | `engine/card.c` | `C` | Busy-wait on `HwCARD` events until one fires (`c1:psx/card.c`) |
| `0x8003C69C` | 18w | `func_8003C69C` | **`Card_ResetHardEvent`** | `CardResetHardEvent` | `engine/card.c` | `C` | Clear pending `HwCARD` events via `TestEvent` (`c1:psx/card.c`) |
| `0x8003C6E4` | 12w | `func_8003C6E4` | **`Card_EntryNameIs949`** | `CardEntryNameIs949` | `engine/card.c` | `C` | Return `strncmp("BASCUS-94900", name, 12) == 0` (`c1:psx/card.c`) |
| `0x8003C714` | 37w | `func_8003C714` | **`Card_CountFiles`** | `CardCountFiles` | `engine/card.c` | `C` | Enumerate up to 15 directory entries via `firstfile` / `nextfile` (`c1:psx/card.c`) |
| `0x8003C7A8` | 86w | `func_8003C7A8` | **`Card_SortEntries`** | `CardSortEntries` | `engine/card.c` | `C` | Sort `BASCUS-94900` entries to the front of `card->entries` (`c1:psx/card.c`) |
| `0x8003C900` | 17w | `func_8003C900` | **`Card_Close`** | `CardClose` | `engine/card.c` | `C` | Close file descriptor if `>= 0` and reset `*fd = -1` (`c1:psx/card.c`) |
| `0x8003C944` | 11w | `func_8003C944` | **`Card_WaitTicks`** | `CardWaitTicks` | `engine/card.c` | `C` | Spin-wait for `ticks` of `ticks_elapsed` (`c1:psx/card.c`) |
| `0x8003C970` | 18w | `func_8003C970` | **`Card_StrToUpper`** | `CardStrToUpper` | `engine/card.c` | `C` | Convert lowercase ASCII characters in string to uppercase (`c1:psx/card.c`) |
| `0x8003C9B8` | 19w | `func_8003C9B8` | **`Card_BeginLoadIfIdle`** | `CardBeginLoadIfIdle` | `engine/card.c` | `C` | Transition to state 1 (`CardLoad`) if no error/pending flags are set (`c1:psx/card.c`) |
| `0x8003CA04` | 19w | `func_8003CA04` | **`Card_ResetParts`** | `CardResetParts` | `engine/card.c` | `C` | Zero `card->part_count`, `card_partinfos[0..13]`, and set flags (`c1:psx/card.c`) |
| `0x8003CA50` | 24w | `func_8003CA50` | **`Card_InitEmptyStrings`** | `CardInitEmptyStrings` | `engine/card.c` | `C` | Populate 15 slot strings with `"EMPTY"` via `GfxFormatCardString` (`c1:psx/card.c`) |
| `0x8003CAB0` | 10w | `func_8003CAB0` | **`Card_SetFlags`** | `CardSetFlags` | `engine/card.c` | `C` | Set bits in `card->flags` and mirror to `card_flags_ro` (`c1:psx/card.c`) |
| `0x8003CAD8` | 8w | `func_8003CAD8` | **`Card_ClearFlags`** | `CardClearFlags` | `engine/card.c` | `C` | Clear bits in `card->flags` (`c1:psx/card.c`) |
| `0x8003CAF8` | 31w | `func_8003CAF8` | **`Card_SetState`** | `CardSetState` | `engine/card.c` | `C` | Set `card->state` and update `CARD_FLAG_PENDING_IO` (`c1:psx/card.c`) |
| `0x8003CB74` | 5w | `func_8003CB74` | **`Card_GetState`** | `CardGetState` | `engine/card.c` | `C` | Return `card->state` (`c1:psx/card.c`) |
| `0x8003CB88` | 5w | `func_8003CB88` | **`Card_GetFlags`** | `CardGetFlags` | `engine/card.c` | `C` | Return `card->flags` (`c1:psx/card.c`) |
| `0x8003CB9C` | 104w | `func_8003CB9C` | **`Card_Init`** | `CardInit` | `engine/card.c` | `C` | Open `SwCARD`/`HwCARD` events, call `InitCARD`, `StartCARD`, `_bu_init`, and enable events (`c1:psx/card.c`) |
| `0x8003CD3C` | 9w | `func_8003CD3C` | **`Card_Kill`** | `CardKill` | `engine/card.c` | `C` | Call `StopCARD` (`c1:psx/card.c`) |
| `0x8003CD60` | 48w | `func_8003CD60` | **`Card_ResetStateAndFlags`** | `CardResetStateAndFlags` | `engine/card.c` | `C` | Reset `card` parts, set state 0, and update low 6 flag bits (`c1:psx/card.c`) |
| `0x8003CE20` | 34w | `func_8003CE20` | **`Card_Alloc`** | `CardAlloc` | `engine/card.c` | `C` | Allocate `card_struct`, initialize `"~inv!"` filename, and request check (`c1:psx/card.c`) |
| `0x8003CEA8` | 18w | `func_8003CEA8` | **`Card_Free`** | `CardFree` | `engine/card.c` | `C` | Save `card_new_device` flag and free `card_struct` (`c1:psx/card.c`) |
| `0x8003CEF0` | 70w | `func_8003CEF0` | **`Card_TestRead`** | `CardTestRead` | `engine/card.c` | `C` | Read sector 0 via `_new_card` + `_card_read` and check `'M','C'` signature (`c1:psx/card.c`) |
| `0x8003D008` | 8w | `func_8003D008` | **`Card_ClearFlag20`** | `CardClearFlag20` | `engine/card.c` | `C` | Clear bit 5 (`0x20`) of `card->flags` (`c1:psx/card.c`) |
| `0x8003D028` | 27w | `func_8003D028` | **`Card_StartWritePart`** | `CardStartWritePart` | `engine/card.c` | `C` | Enter state 6 (`CardPartWrite`) for given `part_idx` (`c1:psx/card.c`) |
| `0x8003D094` | 72w | `func_8003D094` | **`Card_StartWriteNamedPart`** | `CardStartWriteNamedPart` | `engine/card.c` | `C` | Find part matching `card_filename` (`D_8005703C`) and enter state 6 (`c1:psx/card.c`) |
| `0x8003D1B4` | 15w | `func_8003D1B4` | **`Card_InvalidateFilename`** | `CardInvalidateFilename` | `engine/card.c` | `C` | Copy `"~inv!"` into `card_filename` (`D_8005703C`) (`c1:psx/card.c`) |
| `0x8003D1F0` | 70w | `func_8003D1F0` | **`Card_CheckNewDevice`** | `CardCheckNewDevice` | `engine/card.c` | `C` | Run `_card_info(0)` if new device and `card_filename != "~inv!"` (`c1:psx/card.c`) |
| `0x8003D308` | 52w | `func_8003D308` | **`Card_ProbeTimeout`** | `CardProbeTimeout` | `engine/card.c` | `C` | Run `_card_info(0)` and return 1 if `SwCARD` times out (`c1:psx/card.c`) |
| `0x8003D3D8` | 27w | `func_8003D3D8` | **`Card_StartReadPart`** | `CardStartReadPart` | `engine/card.c` | `C` | Enter state 2 (`CardPartReadGlobals`) for given `part_idx` (`c1:psx/card.c`) |
| `0x8003D444` | 26w | `func_8003D444` | **`Card_StartFormat`** | `CardStartFormat` | `engine/card.c` | `C` | Enter state 3 (`CardFormat`) (`c1:psx/card.c`) |
| `0x8003D4AC` | 16w | `func_8003D4AC` | **`Card_RequestCheck`** | `CardRequestCheck` | `engine/card.c` | `C` | Force `CARD_FLAG_CHECK_NEEDED` on `card` (`c1:psx/card.c`) |
| `0x8003D4EC` | 101w | `func_8003D4EC` | **`Card_Control`** | `CardControl` | `engine/bios_ctrl.c` | `C` | GOOL memory card command dispatcher (ops 2..10) (`c1:psx/card.c`) |

---

## 5. Complete Sony PsyQ 3.5 / 3.6 SDK Function Catalog (`0x8001177C..0x80011D84`, `0x8003D680..0x800514DC` — 460 Functions)

All 460 Sony PsyQ SDK library functions linked into `SCUS_949.00`, matched against the PsyQ 3.5/3.6 `.lib` archives.

### 5.1 `MALLOC4.O` Heap Allocator (`0x8001177C..0x80011D84`) (7 functions)

| Address | Size | Current Symbol | Exact PsyQ SDK Symbol | PsyQ Archive:Object | Linkage | Current TU (`src/main/`) | Description / Notes |
|---|---:|---|---|---|---|---|---|
| `0x8001177C` | 61w | `func_8001177C` | **`_ExpAllocArea`** | `MALLOC4.O` | `Static` | `libc/malloc.c` | Expand heap allocation area (`PsyQ 3.5 MALLOC4.O`) |
| `0x80011870` | 106w | `func_80011870` | **`_expand`** | `MALLOC4.O` | `Static` | `libc/malloc.c` | Split/coalesce heap free blocks (`PsyQ 3.5 MALLOC4.O`) |
| `0x80011A18` | 16w | `func_80011A18` | **`InitHeap`** | `MALLOC4.O` | `Global` | `libc/malloc.c` | Initialize heap arena and `max_heap` (`PsyQ 3.5 MALLOC4.O`) |
| `0x80011A58` | 141w | `LIBC_Malloc` | **`malloc`** | `MALLOC4.O` | `Global` | `ns/init.c` | Allocate heap block; prints `"malloc: size should be > 0.\n"` (`PsyQ 3.5 MALLOC4.O`) |
| `0x80011C8C` | 5w | `LIBC_Free` | **`free`** | `MALLOC4.O` | `Global` | `libc/malloc.c` | Free heap block by clearing `in_use` bit (`PsyQ 3.5 MALLOC4.O`) |
| `0x80011CA0` | 36w | `LIBC_Realloc` | **`realloc`** | `MALLOC4.O` | `Global` | `libc/malloc.c` | Resize heap block (`PsyQ 3.5 MALLOC4.O`) |
| `0x80011D30` | 22w | `LIBC_Calloc` | **`calloc`** | `MALLOC4.O` | `Global` | `libc/malloc.c` | Allocate and zero-initialize `n * size` bytes (`PsyQ 3.5 MALLOC4.O`) |

### 5.2 `LIBC.A` Standard C Library & `sprintf` (`0x8003D680..0x8003E017`) (15 functions)

| Address | Size | Current Symbol | Exact PsyQ SDK Symbol | PsyQ Archive:Object | Linkage | Current TU (`src/main/`) | Description / Notes |
|---|---:|---|---|---|---|---|---|
| `0x8003D680` | 3w | `func_8003D680` | **`abs`** | `LIBC.A:c14.o` | `Global` | `—` | BIOS A0:0x0E `abs` trampoline |
| `0x8003D690` | 3w | `BIOS_AToI` | **`atoi`** | `LIBC.A:c16.o` | `Global` | `—` | BIOS A0:0x10 `atoi` trampoline |
| `0x8003D6A0` | 3w | `BIOS_StrCat` | **`strcat`** | `LIBC.A:c21.o` | `Global` | `—` | BIOS A0:0x15 `strcat` trampoline |
| `0x8003D6B0` | 3w | `BIOS_StrCmp` | **`strcmp`** | `LIBC.A:c23.o` | `Global` | `engine/card.c` | BIOS A0:0x17 `strcmp` trampoline |
| `0x8003D6C0` | 3w | `BIOS_StrNCmp` | **`strncmp`** | `LIBC.A:c24.o` | `Global` | `engine/cd_dir.c` | BIOS A0:0x18 `strncmp` trampoline |
| `0x8003D6D0` | 3w | `BIOS_StrCpy` | **`strcpy`** | `LIBC.A:c25.o` | `Global` | `—` | BIOS A0:0x19 `strcpy` trampoline |
| `0x8003D6E0` | 3w | `BIOS_StrLen` | **`strlen`** | `LIBC.A:c27.o` | `Global` | `engine/cd_dir.c` | BIOS A0:0x1B `strlen` trampoline |
| `0x8003D6F0` | 3w | `BIOS_BCopy` | **`bcopy`** | `LIBC.A:c39.o` | `Global` | `—` | BIOS A0:0x27 `bcopy` trampoline |
| `0x8003D700` | 3w | `BIOS_BZero` | **`bzero`** | `LIBC.A:c40.o` | `Global` | `—` | BIOS A0:0x28 `bzero` trampoline |
| `0x8003D710` | 3w | `BIOS_MemCpy` | **`memcpy`** | `LIBC.A:c42.o` | `Global` | `—` | BIOS A0:0x2A `memcpy` trampoline |
| `0x8003D720` | 3w | `BIOS_MemSet` | **`memset`** | `LIBC.A:c43.o` | `Global` | `—` | BIOS A0:0x2B `memset` trampoline |
| `0x8003D730` | 3w | `func_8003D730` | **`printf`** | `LIBC.A:c63.o` | `Global` | `—` | BIOS A0:0x3F `printf` trampoline |
| `0x8003D740` | 535w | `func_8003D740` | **`sprintf`** | `LIBC.A:sprintf.o` | `Global` | `engine/format.c` | Full PsyQ `sprintf` formatter (currently in `src/main/engine/format.c`) |
| `0x8003DF9C` | 3w | `BIOS_MemChr` | **`memchr`** | `LIBC.A:c46.o` | `Global` | `—` | BIOS A0:0x2E `memchr` trampoline (pulled in by `sprintf.o`) |
| `0x8003DFAC` | 27w | `func_8003DFAC` | **`memmove`** | `LIBC.A:memmove.o` | `Global` | `engine/format_copy.c` | Overlap-safe byte copy (pulled in by `sprintf.o`; currently in `src/main/engine/format_copy.c`) |

### 5.3 `LIBSN.LIB` (`snmain.o`) C Runtime Startup (`0x8003E018..0x8003E197`) (3 functions)

| Address | Size | Current Symbol | Exact PsyQ SDK Symbol | PsyQ Archive:Object | Linkage | Current TU (`src/main/`) | Description / Notes |
|---|---:|---|---|---|---|---|---|
| `0x8003E018` | 42w | `__SN_ENTRY_POINT` | **`__SN_ENTRY_POINT`** | `LIBSN.LIB:snmain.o` | `Global` | `sdk/kernel/crt0.c` | Program entry point (`start`); clears `.bss`, sets `$sp`/`$gp`, calls `InitHeap` and `main` |
| `0x8003E0C0` | 28w | `func_8003E0C0` | **`__main`** | `LIBSN.LIB:snmain.o` | `Global` | `—` | Run C++ global constructors (`__CTOR_LIST__`) once |
| `0x8003E130` | 26w | `func_8003E130` | **`__do_global_dtors`** | `LIBSN.LIB:snmain.o` | `Global` | `sdk/kernel/crt0.c` | Run C++ global destructors (`__DTOR_LIST__`) |

### 5.4 `LIBAPI.A` & `LIBETC.A` Kernel Events, File I/O, Root Counters, Pad, VSync & Interrupts (`0x8003E198..0x8003F24B`) (63 functions)

| Address | Size | Current Symbol | Exact PsyQ SDK Symbol | PsyQ Archive:Object | Linkage | Current TU (`src/main/`) | Description / Notes |
|---|---:|---|---|---|---|---|---|
| `0x8003E198` | 3w | `func_8003E198` | **`_bu_init`** | `LIBAPI.A:c112.o` | `Global` | `—` | BIOS A0:0x70 `_bu_init` backup unit init |
| `0x8003E1A8` | 3w | `func_8003E1A8` | **`OpenEvent`** | `LIBAPI.A:a08.o` | `Global` | `—` | BIOS B0:0x08 `OpenEvent` |
| `0x8003E1B8` | 3w | `func_8003E1B8` | **`CloseEvent`** | `LIBAPI.A:a09.o` | `Global` | `—` | BIOS B0:0x09 `CloseEvent` |
| `0x8003E1C8` | 3w | `func_8003E1C8` | **`TestEvent`** | `LIBAPI.A:a11.o` | `Global` | `engine/card.c` | BIOS B0:0x0B `TestEvent` |
| `0x8003E1D8` | 3w | `func_8003E1D8` | **`EnableEvent`** | `LIBAPI.A:a12.o` | `Global` | `—` | BIOS B0:0x0C `EnableEvent` |
| `0x8003E1E8` | 3w | `func_8003E1E8` | **`DisableEvent`** | `LIBAPI.A:a13.o` | `Global` | `—` | BIOS B0:0x0D `DisableEvent` |
| `0x8003E1F8` | 4w | `func_8003E1F8` | **`EnterCriticalSection`** | `LIBAPI.A:l01.o` | `Global` | `—` | `syscall(1)` disable interrupts |
| `0x8003E208` | 4w | `func_8003E208` | **`ExitCriticalSection`** | `LIBAPI.A:l02.o` | `Global` | `—` | `syscall(2)` enable interrupts |
| `0x8003E218` | 3w | `func_8003E218` | **`open`** | `LIBAPI.A:a50.o` | `Global` | `—` | BIOS B0:0x32 `open` |
| `0x8003E228` | 3w | `func_8003E228` | **`read`** | `LIBAPI.A:a52.o` | `Global` | `—` | BIOS B0:0x34 `read` |
| `0x8003E238` | 3w | `func_8003E238` | **`write`** | `LIBAPI.A:a53.o` | `Global` | `—` | BIOS B0:0x35 `write` |
| `0x8003E248` | 3w | `func_8003E248` | **`close`** | `LIBAPI.A:a54.o` | `Global` | `—` | BIOS B0:0x36 `close` |
| `0x8003E258` | 3w | `func_8003E258` | **`format`** | `LIBAPI.A:a65.o` | `Global` | `—` | BIOS B0:0x41 `format` |
| `0x8003E268` | 3w | `func_8003E268` | **`firstfile`** | `LIBAPI.A:a66.o` | `Global` | `—` | BIOS B0:0x42 `firstfile` |
| `0x8003E278` | 3w | `func_8003E278` | **`nextfile`** | `LIBAPI.A:a67.o` | `Global` | `—` | BIOS B0:0x43 `nextfile` |
| `0x8003E288` | 3w | `func_8003E288` | **`erase`** | `LIBAPI.A:a69.o` | `Global` | `—` | BIOS B0:0x45 `erase` / `delete` |
| `0x8003E298` | 40w | `func_8003E298` | **`SetRCnt`** | `LIBAPI.A:counter.o` | `Global` | `sdk/libapi/counter_configure.c` | PsyQ 3.5 `LIBAPI.A:counter.o` `SetRCnt` |
| `0x8003E338` | 14w | `func_8003E338` | **`GetRCnt`** | `LIBAPI.A:counter.o` | `Global` | `sdk/libapi/counter_configure.c` | PsyQ 3.5 `LIBAPI.A:counter.o` `GetRCnt` |
| `0x8003E370` | 13w | `func_8003E370` | **`StartRCnt`** | `LIBAPI.A:counter.o` | `Global` | `sdk/libapi/counter_interrupts.c` | PsyQ 3.5 `LIBAPI.A:counter.o` `StartRCnt` |
| `0x8003E3A4` | 13w | `func_8003E3A4` | **`StopRCnt`** | `LIBAPI.A:counter.o` | `Global` | `sdk/libapi/counter_interrupts.c` | PsyQ 3.5 `LIBAPI.A:counter.o` `StopRCnt` |
| `0x8003E3D8` | 14w | `func_8003E3D8` | **`ResetRCnt`** | `LIBAPI.A:counter.o` | `Global` | `sdk/libapi/counter_interrupts.c` | PsyQ 3.5 `LIBAPI.A:counter.o` `ResetRCnt` |
| `0x8003E410` | 20w | `func_8003E410` | **`PadInit`** | `LIBETC.A:pad.o` | `Global` | `sdk/libapi/event_wait_init.c` | PsyQ 3.5 `LIBETC.A:pad.o` `PadInit` |
| `0x8003E460` | 12w | `func_8003E460` | **`PadRead`** | `LIBETC.A:pad.o` | `Global` | `sdk/func_8003E460.c` | PsyQ 3.5 `LIBETC.A:pad.o` `PadRead` |
| `0x8003E490` | 8w | `func_8003E490` | **`PadStop`** | `LIBETC.A:pad.o` | `Global` | `sdk/func_8003E490.c` | PsyQ 3.5 `LIBETC.A:pad.o` `PadStop` |
| `0x8003E4B0` | 3w | `func_8003E4B0` | **`StopPAD`** | `LIBAPI.A:a20.o` | `Global` | `—` | BIOS B0:0x14 `StopPAD` |
| `0x8003E4C0` | 3w | `func_8003E4C0` | **`PAD_init`** | `LIBAPI.A:a21.o` | `Global` | `—` | BIOS B0:0x15 `PAD_init` |
| `0x8003E4D0` | 3w | `func_8003E4D0` | **`PAD_dr`** | `LIBAPI.A:a22.o` | `Global` | `—` | BIOS B0:0x16 `PAD_dr` |
| `0x8003E4E0` | 3w | `func_8003E4E0` | **`ChangeClearPAD`** | `LIBAPI.A:a91.o` | `Global` | `—` | BIOS B0:0x5B `ChangeClearPAD` |
| `0x8003E4F0` | 82w | `CORE_VSync` | **`VSync`** | `LIBETC.A:vsync.o` | `Global` | `sdk/libgpu/timeout_init.c` | PsyQ 3.5 `LIBETC.A:vsync.o` `VSync` (misnamed `CORE_VSync` in `sym.main.txt`) |
| `0x8003E638` | 39w | `func_8003E638` | **`v_wait`** | `LIBETC.A:vsync.o` | `Static` | `sdk/libapi/vsync.c` | PsyQ 3.5 `LIBETC.A:vsync.o` `v_wait` |
| `0x8003E6D4` | 3w | `func_8003E6D4` | **`puts`** | `LIBC.A:a63.o` | `Global` | `—` | BIOS B0:0x3F `puts` |
| `0x8003E6E4` | 3w | `func_8003E6E4` | **`ChangeClearRCnt`** | `LIBAPI.A:chclear.o` | `Global` | `—` | BIOS C0:0x0A `ChangeClearRCnt` |
| `0x8003E6F4` | 12w | `func_8003E6F4` | **`ResetCallback`** | `LIBETC.A:intr.o` | `Global` | `sdk/libapi/callback_dispatch.c` | PsyQ 3.5 `LIBETC.A:intr.o` `ResetCallback` |
| `0x8003E724` | 12w | `func_8003E724` | **`InterruptCallback`** | `LIBETC.A:intr.o` | `Global` | `sdk/libapi/callback_dispatch.c` | PsyQ 3.5 `LIBETC.A:intr.o` `InterruptCallback` |
| `0x8003E754` | 12w | `func_8003E754` | **`DMACallback`** | `LIBETC.A:intr.o` | `Global` | `sdk/libapi/callback_dispatch.c` | PsyQ 3.5 `LIBETC.A:intr.o` `DMACallback` |
| `0x8003E784` | 13w | `func_8003E784` | **`VSyncCallback`** | `LIBETC.A:intr.o` | `Global` | `sdk/libapi/callback_dispatch.c` | PsyQ 3.5 `LIBETC.A:intr.o` `VSyncCallback` |
| `0x8003E7B8` | 12w | `func_8003E7B8` | **`VSyncCallbacks`** | `LIBETC.A:intr.o` | `Global` | `sdk/libapi/callback_dispatch.c` | PsyQ 3.5 `LIBETC.A:intr.o` `VSyncCallbacks` |
| `0x8003E7E8` | 12w | `func_8003E7E8` | **`StopCallback`** | `LIBETC.A:intr.o` | `Global` | `sdk/libapi/callback_dispatch.c` | PsyQ 3.5 `LIBETC.A:intr.o` `StopCallback` |
| `0x8003E818` | 12w | `func_8003E818` | **`RestartCallback`** | `LIBETC.A:intr.o` | `Global` | `sdk/libapi/callback_dispatch.c` | PsyQ 3.5 `LIBETC.A:intr.o` `RestartCallback` |
| `0x8003E848` | 4w | `func_8003E848` | **`CheckCallback`** | `LIBETC.A:intr.o` | `Global` | `sdk/libcd/bios_sync.c` | PsyQ 3.5 `LIBETC.A:intr.o` `CheckCallback` |
| `0x8003E858` | 6w | `func_8003E858` | **`GetIntrMask`** | `LIBETC.A:intr.o` | `Global` | `sdk/libapi/func_8003E858.c` | PsyQ 3.5 `LIBETC.A:intr.o` `GetIntrMask` |
| `0x8003E870` | 7w | `func_8003E870` | **`SetIntrMask`** | `LIBETC.A:intr.o` | `Global` | `sdk/libapi/irq_mask.c` | PsyQ 3.5 `LIBETC.A:intr.o` `SetIntrMask` |
| `0x8003E88C` | 55w | `func_8003E88C` | **`startIntr`** | `LIBETC.A:intr.o` | `Static` | `sdk/kernel/intr_init.c` | PsyQ 3.5 `LIBETC.A:intr.o` `startIntr` |
| `0x8003E968` | 122w | `func_8003E968` | **`trapIntr`** | `LIBETC.A:intr.o` | `Static` | `sdk/libapi/root_interrupt.c` | PsyQ 3.5 `LIBETC.A:intr.o` `trapIntr` |
| `0x8003EB50` | 85w | `func_8003EB50` | **`setIntr`** | `LIBETC.A:intr.o` | `Static` | `sdk/libapi/root_interrupt.c` | PsyQ 3.5 `LIBETC.A:intr.o` `setIntr` |
| `0x8003ECA4` | 43w | `func_8003ECA4` | **`stopIntr`** | `LIBETC.A:intr.o` | `Static` | `sdk/libapi/root_interrupt.c` | PsyQ 3.5 `LIBETC.A:intr.o` `stopIntr` |
| `0x8003ED50` | 34w | `func_8003ED50` | **`restartIntr`** | `LIBETC.A:intr.o` | `Static` | `sdk/libapi/resume.c` | PsyQ 3.5 `LIBETC.A:intr.o` `restartIntr` |
| `0x8003EDD8` | 11w | `func_8003EDD8` | **`memclr`** | `LIBETC.A:intr.o` | `Static` | `sdk/libapi/resume.c` | PsyQ 3.5 `LIBETC.A:intr.o` `memclr` |
| `0x8003EE04` | 3w | `func_8003EE04` | **`setjmp`** | `LIBC.A:c19.o` | `Global` | `sdk/libetc/setjmp_trampoline.c` | BIOS A0:0x13 `setjmp` |
| `0x8003EE14` | 3w | `func_8003EE14` | **`_96_remove`** | `LIBAPI.A:c114.o` | `Global` | `—` | BIOS A0:0x72 `_96_remove` |
| `0x8003EE24` | 3w | `func_8003EE24` | **`ReturnFromException`** | `LIBAPI.A:a23.o` | `Global` | `—` | BIOS B0:0x17 `ReturnFromException` |
| `0x8003EE34` | 3w | `func_8003EE34` | **`ResetEntryInt`** | `LIBAPI.A:a24.o` | `Global` | `—` | BIOS B0:0x18 `ResetEntryInt` |
| `0x8003EE44` | 3w | `func_8003EE44` | **`HookEntryInt`** | `LIBAPI.A:a25.o` | `Global` | `—` | BIOS B0:0x19 `HookEntryInt` |
| `0x8003EE54` | 22w | `func_8003EE54` | **`startIntrVSync`** | `LIBETC.A:intr_vb.o` | `Global` | `sdk/libapi/timer_callback_init.c` | PsyQ 3.5 `LIBETC.A:intr_vb.o` `startIntrVSync` |
| `0x8003EEAC` | 30w | `func_8003EEAC` | **`trapIntrVSync`** | `LIBETC.A:intr_vb.o` | `Static` | `sdk/libapi/timer_callback_dispatch.c` | PsyQ 3.5 `LIBETC.A:intr_vb.o` `trapIntrVSync` |
| `0x8003EF24` | 11w | `func_8003EF24` | **`setIntrVSync`** | `LIBETC.A:intr_vb.o` | `Static` | `sdk/libapi/table_slot_exchange.c` | PsyQ 3.5 `LIBETC.A:intr_vb.o` `setIntrVSync` |
| `0x8003EF50` | 11w | `func_8003EF50` | **`memclr`** | `LIBETC.A:intr_vb.o` | `Static` | `sdk/libapi/table_clear.c` | PsyQ 3.5 `LIBETC.A:intr_vb.o` `memclr` |
| `0x8003EF7C` | 20w | `func_8003EF7C` | **`startIntrDMA`** | `LIBETC.A:intr_dma.o` | `Global` | `sdk/libapi/interrupt_callback_init.c` | PsyQ 3.5 `LIBETC.A:intr_dma.o` `startIntrDMA` |
| `0x8003EFCC` | 97w | `func_8003EFCC` | **`trapIntrDMA`** | `LIBETC.A:intr_dma.o` | `Static` | `sdk/libapi/dma_callback_dispatch.c` | PsyQ 3.5 `LIBETC.A:intr_dma.o` `trapIntrDMA` |
| `0x8003F150` | 42w | `func_8003F150` | **`setIntrDMA`** | `LIBETC.A:intr_dma.o` | `Static` | `sdk/libapi/dma_callback_dispatch.c` | PsyQ 3.5 `LIBETC.A:intr_dma.o` `setIntrDMA` |
| `0x8003F1F8` | 11w | `func_8003F1F8` | **`memclr`** | `LIBETC.A:intr_dma.o` | `Static` | `sdk/libapi/dma_callback_dispatch.c` | PsyQ 3.5 `LIBETC.A:intr_dma.o` `memclr` |
| `0x8003F224` | 6w | `func_8003F224` | **`SetVideoMode`** | `LIBETC.A:vmode.o` | `Global` | `sdk/libgpu/func_8003F224.c` | PsyQ 3.5 `LIBETC.A:vmode.o` `SetVideoMode` |
| `0x8003F23C` | 4w | `func_8003F23C` | **`GetVideoMode`** | `LIBETC.A:vmode.o` | `Global` | `sdk/libgpu/video_mode.c` | PsyQ 3.5 `LIBETC.A:vmode.o` `GetVideoMode` |

### 5.5 `LIBGPU.A` (`ext.o`, `prim.o`, `sys.o`) Graphics Processing Unit Library (`0x8003F24C..0x80042B1B`) (101 functions)

| Address | Size | Current Symbol | Exact PsyQ SDK Symbol | PsyQ Archive:Object | Linkage | Current TU (`src/main/`) | Description / Notes |
|---|---:|---|---|---|---|---|---|
| `0x8003F24C` | 59w | `func_8003F24C` | **`LoadTPage`** | `LIBGPU.A:ext.o` | `Global` | `sdk/libgpu/texture_upload_rect.c` | PsyQ 3.5 `LIBGPU.A:ext.o` `LoadTPage` |
| `0x8003F338` | 26w | `func_8003F338` | **`LoadClut`** | `LIBGPU.A:ext.o` | `Global` | `sdk/libgpu/palette.c` | PsyQ 3.5 `LIBGPU.A:ext.o` `LoadClut` |
| `0x8003F3A0` | 26w | `func_8003F3A0` | **`LoadClut2`** | `LIBGPU.A:ext.o` | `Global` | `sdk/libgpu/palette.c` | PsyQ 3.5 `LIBGPU.A:ext.o` `LoadClut2` |
| `0x8003F408` | 52w | `func_8003F408` | **`SetDefDrawEnv`** | `LIBGPU.A:ext.o` | `Global` | `sdk/libgpu/environment.c` | PsyQ 3.5 `LIBGPU.A:ext.o` `SetDefDrawEnv` |
| `0x8003F4D8` | 15w | `func_8003F4D8` | **`SetDefDispEnv`** | `LIBGPU.A:ext.o` | `Global` | `sdk/libgpu/environment.c` | PsyQ 3.5 `LIBGPU.A:ext.o` `SetDefDispEnv` |
| `0x8003F514` | 50w | `func_8003F514` | **`GetTPage`** | `LIBGPU.A:prim.o` | `Global` | `sdk/libgpu/environment.c` | PsyQ 3.5 `LIBGPU.A:prim.o` `GetTPage` |
| `0x8003F5DC` | 6w | `func_8003F5DC` | **`GetClut`** | `LIBGPU.A:prim.o` | `Global` | `sdk/libgpu/clut.c` | PsyQ 3.5 `LIBGPU.A:prim.o` `GetClut` |
| `0x8003F5F4` | 52w | `func_8003F5F4` | **`DumpTPage`** | `LIBGPU.A:prim.o` | `Global` | `sdk/libgpu/tpage_print.c` | PsyQ 3.5 `LIBGPU.A:prim.o` `DumpTPage` |
| `0x8003F6C4` | 16w | `func_8003F6C4` | **`DumpClut`** | `LIBGPU.A:prim.o` | `Global` | `sdk/libgpu/clut_print.c` | PsyQ 3.5 `LIBGPU.A:prim.o` `DumpClut` |
| `0x8003F704` | 7w | `func_8003F704` | **`NextPrim`** | `LIBGPU.A:prim.o` | `Global` | `sdk/libgpu/tag_query.c` | PsyQ 3.5 `LIBGPU.A:prim.o` `NextPrim` |
| `0x8003F720` | 7w | `func_8003F720` | **`IsEndPrim`** | `LIBGPU.A:prim.o` | `Global` | `sdk/libgpu/tag_query.c` | PsyQ 3.5 `LIBGPU.A:prim.o` `IsEndPrim` |
| `0x8003F73C` | 15w | `func_8003F73C` | **`AddPrim`** | `LIBGPU.A:prim.o` | `Global` | `sdk/libgpu/packet_insert.c` | PsyQ 3.5 `LIBGPU.A:prim.o` `AddPrim` |
| `0x8003F778` | 15w | `func_8003F778` | **`AddPrims`** | `LIBGPU.A:prim.o` | `Global` | `sdk/libgpu/packet_insert.c` | PsyQ 3.5 `LIBGPU.A:prim.o` `AddPrims` |
| `0x8003F7B4` | 9w | `func_8003F7B4` | **`CatPrim`** | `LIBGPU.A:prim.o` | `Global` | `sdk/libgpu/tag_update.c` | PsyQ 3.5 `LIBGPU.A:prim.o` `CatPrim` |
| `0x8003F7D8` | 6w | `func_8003F7D8` | **`TermPrim`** | `LIBGPU.A:prim.o` | `Global` | `sdk/libgpu/tag_update.c` | PsyQ 3.5 `LIBGPU.A:prim.o` `TermPrim` |
| `0x8003F7F0` | 10w | `func_8003F7F0` | **`SetSemiTrans`** | `LIBGPU.A:prim.o` | `Global` | `sdk/libgpu/attributes.c` | PsyQ 3.5 `LIBGPU.A:prim.o` `SetSemiTrans` |
| `0x8003F818` | 10w | `func_8003F818` | **`SetShadeTex`** | `LIBGPU.A:prim.o` | `Global` | `sdk/libgpu/attributes.c` | PsyQ 3.5 `LIBGPU.A:prim.o` `SetShadeTex` |
| `0x8003F840` | 5w | `func_8003F840` | **`SetPolyF3`** | `LIBGPU.A:prim.o` | `Global` | `sdk/libgpu/primitives.c` | PsyQ 3.5 `LIBGPU.A:prim.o` `SetPolyF3` |
| `0x8003F854` | 5w | `func_8003F854` | **`SetPolyFT3`** | `LIBGPU.A:prim.o` | `Global` | `sdk/libgpu/primitives.c` | PsyQ 3.5 `LIBGPU.A:prim.o` `SetPolyFT3` |
| `0x8003F868` | 5w | `func_8003F868` | **`SetPolyG3`** | `LIBGPU.A:prim.o` | `Global` | `sdk/libgpu/primitives.c` | PsyQ 3.5 `LIBGPU.A:prim.o` `SetPolyG3` |
| `0x8003F87C` | 5w | `func_8003F87C` | **`SetPolyGT3`** | `LIBGPU.A:prim.o` | `Global` | `sdk/libgpu/primitives.c` | PsyQ 3.5 `LIBGPU.A:prim.o` `SetPolyGT3` |
| `0x8003F890` | 5w | `func_8003F890` | **`SetPolyF4`** | `LIBGPU.A:prim.o` | `Global` | `sdk/libgpu/primitives.c` | PsyQ 3.5 `LIBGPU.A:prim.o` `SetPolyF4` |
| `0x8003F8A4` | 5w | `func_8003F8A4` | **`SetPolyFT4`** | `LIBGPU.A:prim.o` | `Global` | `sdk/libgpu/primitives.c` | PsyQ 3.5 `LIBGPU.A:prim.o` `SetPolyFT4` |
| `0x8003F8B8` | 5w | `func_8003F8B8` | **`SetPolyG4`** | `LIBGPU.A:prim.o` | `Global` | `sdk/libgpu/primitives.c` | PsyQ 3.5 `LIBGPU.A:prim.o` `SetPolyG4` |
| `0x8003F8CC` | 5w | `func_8003F8CC` | **`SetPolyGT4`** | `LIBGPU.A:prim.o` | `Global` | `sdk/libgpu/primitives.c` | PsyQ 3.5 `LIBGPU.A:prim.o` `SetPolyGT4` |
| `0x8003F8E0` | 5w | `func_8003F8E0` | **`SetSprt8`** | `LIBGPU.A:prim.o` | `Global` | `sdk/libgpu/primitives.c` | PsyQ 3.5 `LIBGPU.A:prim.o` `SetSprt8` |
| `0x8003F8F4` | 5w | `func_8003F8F4` | **`SetSprt16`** | `LIBGPU.A:prim.o` | `Global` | `sdk/libgpu/primitives.c` | PsyQ 3.5 `LIBGPU.A:prim.o` `SetSprt16` |
| `0x8003F908` | 5w | `func_8003F908` | **`SetSprt`** | `LIBGPU.A:prim.o` | `Global` | `sdk/libgpu/primitives.c` | PsyQ 3.5 `LIBGPU.A:prim.o` `SetSprt` |
| `0x8003F91C` | 5w | `func_8003F91C` | **`SetTile1`** | `LIBGPU.A:prim.o` | `Global` | `sdk/libgpu/primitives.c` | PsyQ 3.5 `LIBGPU.A:prim.o` `SetTile1` |
| `0x8003F930` | 5w | `func_8003F930` | **`SetTile8`** | `LIBGPU.A:prim.o` | `Global` | `sdk/libgpu/primitives.c` | PsyQ 3.5 `LIBGPU.A:prim.o` `SetTile8` |
| `0x8003F944` | 5w | `func_8003F944` | **`SetTile16`** | `LIBGPU.A:prim.o` | `Global` | `sdk/libgpu/primitives.c` | PsyQ 3.5 `LIBGPU.A:prim.o` `SetTile16` |
| `0x8003F958` | 5w | `func_8003F958` | **`SetTile`** | `LIBGPU.A:prim.o` | `Global` | `sdk/libgpu/primitives.c` | PsyQ 3.5 `LIBGPU.A:prim.o` `SetTile` |
| `0x8003F96C` | 5w | `func_8003F96C` | **`SetLineF2`** | `LIBGPU.A:prim.o` | `Global` | `sdk/libgpu/primitives.c` | PsyQ 3.5 `LIBGPU.A:prim.o` `SetLineF2` |
| `0x8003F980` | 5w | `func_8003F980` | **`SetLineG2`** | `LIBGPU.A:prim.o` | `Global` | `sdk/libgpu/primitives.c` | PsyQ 3.5 `LIBGPU.A:prim.o` `SetLineG2` |
| `0x8003F994` | 8w | `func_8003F994` | **`SetLineF3`** | `LIBGPU.A:prim.o` | `Global` | `sdk/libgpu/primitives.c` | PsyQ 3.5 `LIBGPU.A:prim.o` `SetLineF3` |
| `0x8003F9B4` | 8w | `func_8003F9B4` | **`SetLineG3`** | `LIBGPU.A:prim.o` | `Global` | `sdk/libgpu/primitives.c` | PsyQ 3.5 `LIBGPU.A:prim.o` `SetLineG3` |
| `0x8003F9D4` | 8w | `func_8003F9D4` | **`SetLineF4`** | `LIBGPU.A:prim.o` | `Global` | `sdk/libgpu/primitives.c` | PsyQ 3.5 `LIBGPU.A:prim.o` `SetLineF4` |
| `0x8003F9F4` | 8w | `func_8003F9F4` | **`SetLineG4`** | `LIBGPU.A:prim.o` | `Global` | `sdk/libgpu/primitives.c` | PsyQ 3.5 `LIBGPU.A:prim.o` `SetLineG4` |
| `0x8003FA14` | 5w | `func_8003FA14` | **`SetBlockFill`** | `LIBGPU.A:prim.o` | `Global` | `sdk/libgpu/primitives.c` | PsyQ 3.5 `LIBGPU.A:prim.o` `SetBlockFill` |
| `0x8003FA28` | 7w | `func_8003FA28` | **`SetDrawMove`** | `LIBGPU.A:prim.o` | `Global` | `sdk/libgpu/primitives.c` | PsyQ 3.5 `LIBGPU.A:prim.o` `SetDrawMove` |
| `0x8003FA44` | 45w | `func_8003FA44` | **`SetDrawTPage`** | `LIBGPU.A:prim.o` | `Global` | `sdk/libgpu/mode_packet.c` | PsyQ 3.5 `LIBGPU.A:prim.o` `SetDrawTPage` |
| `0x8003FAF8` | 25w | `func_8003FAF8` | **`SetDrawLoad`** | `LIBGPU.A:prim.o` | `Global` | `sdk/libgpu/image_packet.c` | PsyQ 3.5 `LIBGPU.A:prim.o` `SetDrawLoad` |
| `0x8003FB5C` | 14w | `func_8003FB5C` | **`MargePrim`** | `LIBGPU.A:prim.o` | `Global` | `sdk/libgpu/packet_join.c` | PsyQ 3.5 `LIBGPU.A:prim.o` `MargePrim` |
| `0x8003FB94` | 96w | `func_8003FB94` | **`DumpDrawEnv`** | `LIBGPU.A:prim.o` | `Global` | `sdk/libgpu/environment_print.c` | PsyQ 3.5 `LIBGPU.A:prim.o` `DumpDrawEnv` |
| `0x8003FD14` | 43w | `func_8003FD14` | **`DumpDispEnv`** | `LIBGPU.A:prim.o` | `Global` | `sdk/libgpu/environment_print.c` | PsyQ 3.5 `LIBGPU.A:prim.o` `DumpDispEnv` |
| `0x8003FDC0` | 86w | `func_8003FDC0` | **`ResetGraph`** | `LIBGPU.A:sys.o` | `Global` | `sdk/libgpu/reset.c` | PsyQ 3.5 `LIBGPU.A:sys.o` `ResetGraph` |
| `0x8003FF18` | 69w | `func_8003FF18` | **`SetGraphReverse`** | `LIBGPU.A:sys.o` | `Global` | `sdk/libgpu/debug_mode.c` | PsyQ 3.5 `LIBGPU.A:sys.o` `SetGraphReverse` |
| `0x8004002C` | 27w | `func_8004002C` | **`SetGraphDebug`** | `LIBGPU.A:sys.o` | `Global` | `sdk/libgpu/debug_mode.c` | PsyQ 3.5 `LIBGPU.A:sys.o` `SetGraphDebug` |
| `0x80040098` | 43w | `func_80040098` | **`SetGraphQueue`** | `LIBGPU.A:sys.o` | `Global` | `sdk/libgpu/debug_mode.c` | PsyQ 3.5 `LIBGPU.A:sys.o` `SetGraphQueue` |
| `0x80040144` | 4w | `func_80040144` | **`GetGraphType`** | `LIBGPU.A:sys.o` | `Global` | `sdk/libgpu/tpage_print.c` | PsyQ 3.5 `LIBGPU.A:sys.o` `GetGraphType` |
| `0x80040154` | 4w | `func_80040154` | **`GetGraphDebug`** | `LIBGPU.A:sys.o` | `Global` | `sdk/libgpu/func_80040154.c` | PsyQ 3.5 `LIBGPU.A:sys.o` `GetGraphDebug` |
| `0x80040164` | 23w | `func_80040164` | **`DrawSyncCallback`** | `LIBGPU.A:sys.o` | `Global` | `sdk/libgpu/control_value.c` | PsyQ 3.5 `LIBGPU.A:sys.o` `DrawSyncCallback` |
| `0x800401C0` | 39w | `func_800401C0` | **`SetDispMask`** | `LIBGPU.A:sys.o` | `Global` | `sdk/libgpu/display_enable.c` | PsyQ 3.5 `LIBGPU.A:sys.o` `SetDispMask` |
| `0x8004025C` | 27w | `func_8004025C` | **`DrawSync`** | `LIBGPU.A:sys.o` | `Global` | `sdk/libgpu/control_dispatch.c` | PsyQ 3.5 `LIBGPU.A:sys.o` `DrawSync` |
| `0x800402C8` | 74w | `func_800402C8` | **`checkRECT`** | `LIBGPU.A:sys.o` | `Static` | `sdk/libgpu/command_dispatch.c` | PsyQ 3.5 `LIBGPU.A:sys.o` `checkRECT` |
| `0x800403F0` | 37w | `func_800403F0` | **`ClearImage`** | `LIBGPU.A:sys.o` | `Global` | `sdk/libgpu/command_dispatch.c` | PsyQ 3.5 `LIBGPU.A:sys.o` `ClearImage` |
| `0x80040484` | 25w | `func_80040484` | **`LoadImage`** | `LIBGPU.A:sys.o` | `Global` | `sdk/libgpu/command_dispatch.c` | PsyQ 3.5 `LIBGPU.A:sys.o` `LoadImage` |
| `0x800404E8` | 25w | `func_800404E8` | **`StoreImage`** | `LIBGPU.A:sys.o` | `Global` | `sdk/libgpu/command_dispatch.c` | PsyQ 3.5 `LIBGPU.A:sys.o` `StoreImage` |
| `0x8004054C` | 49w | `func_8004054C` | **`MoveImage`** | `LIBGPU.A:sys.o` | `Global` | `sdk/libgpu/command_dispatch.c` | PsyQ 3.5 `LIBGPU.A:sys.o` `MoveImage` |
| `0x80040610` | 46w | `func_80040610` | **`ClearOTag`** | `LIBGPU.A:sys.o` | `Global` | `sdk/libgpu/ordering_table.c` | PsyQ 3.5 `LIBGPU.A:sys.o` `ClearOTag` |
| `0x800406C8` | 38w | `func_800406C8` | **`ClearOTagR`** | `LIBGPU.A:sys.o` | `Global` | `sdk/libgpu/packet_link.c` | PsyQ 3.5 `LIBGPU.A:sys.o` `ClearOTagR` |
| `0x80040760` | 24w | `func_80040760` | **`DrawPrim`** | `LIBGPU.A:sys.o` | `Global` | `sdk/libgpu/packet_send.c` | PsyQ 3.5 `LIBGPU.A:sys.o` `DrawPrim` |
| `0x800407C0` | 29w | `func_800407C0` | **`DrawOTag`** | `LIBGPU.A:sys.o` | `Global` | `sdk/libgpu/api_dispatch.c` | PsyQ 3.5 `LIBGPU.A:sys.o` `DrawOTag` |
| `0x80040834` | 49w | `func_80040834` | **`PutDrawEnv`** | `LIBGPU.A:sys.o` | `Global` | `sdk/libgpu/draw_submit.c` | PsyQ 3.5 `LIBGPU.A:sys.o` `PutDrawEnv` |
| `0x800408F8` | 55w | `func_800408F8` | **`DrawOTagEnv`** | `LIBGPU.A:sys.o` | `Global` | `sdk/libgpu/draw_submit.c` | PsyQ 3.5 `LIBGPU.A:sys.o` `DrawOTagEnv` |
| `0x800409D4` | 14w | `func_800409D4` | **`GetDrawEnv`** | `LIBGPU.A:sys.o` | `Global` | `sdk/libgpu/draw_environment_read.c` | PsyQ 3.5 `LIBGPU.A:sys.o` `GetDrawEnv` |
| `0x80040A0C` | 300w | `func_80040A0C` | **`PutDispEnv`** | `LIBGPU.A:sys.o` | `Global` | `—` | PsyQ 3.5 `LIBGPU.A:sys.o` `PutDispEnv` |
| `0x80040EBC` | 14w | `func_80040EBC` | **`GetDispEnv`** | `LIBGPU.A:sys.o` | `Global` | `sdk/libgpu/display_environment_read.c` | PsyQ 3.5 `LIBGPU.A:sys.o` `GetDispEnv` |
| `0x80040EF4` | 13w | `func_80040EF4` | **`GetODE`** | `LIBGPU.A:sys.o` | `Global` | `sdk/libgpu/status_sign.c` | PsyQ 3.5 `LIBGPU.A:sys.o` `GetODE` |
| `0x80040F28` | 15w | `func_80040F28` | **`SetTexWindow`** | `LIBGPU.A:sys.o` | `Global` | `sdk/libgpu/texture_window_packet.c` | PsyQ 3.5 `LIBGPU.A:sys.o` `SetTexWindow` |
| `0x80040F64` | 33w | `func_80040F64` | **`SetDrawArea`** | `LIBGPU.A:sys.o` | `Global` | `sdk/libgpu/clip_packet.c` | PsyQ 3.5 `LIBGPU.A:sys.o` `SetDrawArea` |
| `0x80040FE8` | 17w | `func_80040FE8` | **`SetDrawOffset`** | `LIBGPU.A:sys.o` | `Global` | `sdk/libgpu/draw_offset_packet.c` | PsyQ 3.5 `LIBGPU.A:sys.o` `SetDrawOffset` |
| `0x8004102C` | 10w | `func_8004102C` | **`SetPriority`** | `LIBGPU.A:sys.o` | `Global` | `sdk/libgpu/mask_packet.c` | PsyQ 3.5 `LIBGPU.A:sys.o` `SetPriority` |
| `0x80041054` | 22w | `func_80041054` | **`SetDrawMode`** | `LIBGPU.A:sys.o` | `Global` | `sdk/libgpu/two_word_packet.c` | PsyQ 3.5 `LIBGPU.A:sys.o` `SetDrawMode` |
| `0x800410AC` | 169w | `func_800410AC` | **`SetDrawEnv`** | `LIBGPU.A:sys.o` | `Global` | `sdk/libgpu/texture_window_encode.c` | PsyQ 3.5 `LIBGPU.A:sys.o` `SetDrawEnv` |
| `0x80041350` | 23w | `func_80041350` | **`get_mode`** | `LIBGPU.A:sys.o` | `Static` | `sdk/libgpu/texture_window_encode.c` | PsyQ 3.5 `LIBGPU.A:sys.o` `get_mode` |
| `0x800413AC` | 51w | `func_800413AC` | **`get_cs`** | `LIBGPU.A:sys.o` | `Static` | `sdk/libgpu/texture_window_encode.c` | PsyQ 3.5 `LIBGPU.A:sys.o` `get_cs` |
| `0x80041478` | 51w | `func_80041478` | **`get_ce`** | `LIBGPU.A:sys.o` | `Static` | `sdk/libgpu/texture_window_encode.c` | PsyQ 3.5 `LIBGPU.A:sys.o` `get_ce` |
| `0x80041544` | 18w | `func_80041544` | **`get_ofs`** | `LIBGPU.A:sys.o` | `Static` | `sdk/libgpu/texture_window_encode.c` | PsyQ 3.5 `LIBGPU.A:sys.o` `get_ofs` |
| `0x8004158C` | 33w | `func_8004158C` | **`get_tw`** | `LIBGPU.A:sys.o` | `Static` | `sdk/libgpu/texture_window_encode.c` | PsyQ 3.5 `LIBGPU.A:sys.o` `get_tw` |
| `0x80041610` | 47w | `func_80041610` | **`get_dx`** | `LIBGPU.A:sys.o` | `Static` | `sdk/libgpu/texture_window_encode.c` | PsyQ 3.5 `LIBGPU.A:sys.o` `get_dx` |
| `0x800416CC` | 6w | `func_800416CC` | **`_status`** | `LIBGPU.A:sys.o` | `Static` | `sdk/libgpu/func_800416CC.c` | PsyQ 3.5 `LIBGPU.A:sys.o` `_status` |
| `0x800416E4` | 58w | `func_800416E4` | **`_otc`** | `LIBGPU.A:sys.o` | `Static` | `sdk/libgpu/ordering_table_dma.c` | PsyQ 3.5 `LIBGPU.A:sys.o` `_otc` |
| `0x800417CC` | 134w | `func_800417CC` | **`_clr`** | `LIBGPU.A:sys.o` | `Static` | `sdk/libgpu/ordering_table_dma.c` | PsyQ 3.5 `LIBGPU.A:sys.o` `_clr` |
| `0x800419E4` | 149w | `func_800419E4` | **`_dws`** | `LIBGPU.A:sys.o` | `Static` | `sdk/libgpu/ordering_table_dma.c` | PsyQ 3.5 `LIBGPU.A:sys.o` `_dws` |
| `0x80041C38` | 167w | `func_80041C38` | **`_drs`** | `LIBGPU.A:sys.o` | `Static` | `sdk/libgpu/ordering_table_dma.c` | PsyQ 3.5 `LIBGPU.A:sys.o` `_drs` |
| `0x80041ED4` | 10w | `func_80041ED4` | **`_ctl`** | `LIBGPU.A:sys.o` | `Static` | `sdk/libgpu/command_cache.c` | PsyQ 3.5 `LIBGPU.A:sys.o` `_ctl` |
| `0x80041EFC` | 5w | `func_80041EFC` | **`_getctl`** | `LIBGPU.A:sys.o` | `Static` | `sdk/libgpu/command_cache.c` | PsyQ 3.5 `LIBGPU.A:sys.o` `_getctl` |
| `0x80041F10` | 20w | `func_80041F10` | **`_cwb`** | `LIBGPU.A:sys.o` | `Static` | `sdk/libgpu/command_cache.c` | PsyQ 3.5 `LIBGPU.A:sys.o` `_cwb` |
| `0x80041F60` | 19w | `func_80041F60` | **`_cwc`** | `LIBGPU.A:sys.o` | `Static` | `sdk/libgpu/dma_start.c` | PsyQ 3.5 `LIBGPU.A:sys.o` `_cwc` |
| `0x80041FAC` | 12w | `func_80041FAC` | **`_param`** | `LIBGPU.A:sys.o` | `Static` | `sdk/libgpu/func_80041FAC.c` | PsyQ 3.5 `LIBGPU.A:sys.o` `_param` |
| `0x80041FDC` | 9w | `func_80041FDC` | **`_addque`** | `LIBGPU.A:sys.o` | `Static` | `sdk/libgpu/image_transfer.c` | PsyQ 3.5 `LIBGPU.A:sys.o` `_addque` |
| `0x80042000` | 185w | `func_80042000` | **`_addque2`** | `LIBGPU.A:sys.o` | `Static` | `sdk/libgpu/queue.c` | PsyQ 3.5 `LIBGPU.A:sys.o` `_addque2` |
| `0x800422E4` | 191w | `func_800422E4` | **`_exeque`** | `LIBGPU.A:sys.o` | `Static` | `sdk/libgpu/queue.c` | PsyQ 3.5 `LIBGPU.A:sys.o` `_exeque` |
| `0x800425E0` | 79w | `func_800425E0` | **`_reset`** | `LIBGPU.A:sys.o` | `Static` | `sdk/libgpu/queue_reset.c` | PsyQ 3.5 `LIBGPU.A:sys.o` `_reset` |
| `0x8004271C` | 82w | `func_8004271C` | **`_sync`** | `LIBGPU.A:sys.o` | `Static` | `sdk/libgpu/queue_wait.c` | PsyQ 3.5 `LIBGPU.A:sys.o` `_sync` |
| `0x80042864` | 13w | `func_80042864` | **`set_alarm`** | `LIBGPU.A:sys.o` | `Static` | `sdk/libgpu/timeout_init.c` | PsyQ 3.5 `LIBGPU.A:sys.o` `set_alarm` |
| `0x80042898` | 91w | `func_80042898` | **`get_alarm`** | `LIBGPU.A:sys.o` | `Static` | `sdk/libgpu/timeout_init.c` | PsyQ 3.5 `LIBGPU.A:sys.o` `get_alarm` |
| `0x80042A04` | 55w | `func_80042A04` | **`_version`** | `LIBGPU.A:sys.o` | `Static` | `sdk/libgpu/hardware_query.c` | PsyQ 3.5 `LIBGPU.A:sys.o` `_version` |
| `0x80042AE0` | 11w | `func_80042AE0` | **`memset`** | `LIBGPU.A:sys.o` | `Static` | `sdk/libcd/memset.c` | PsyQ 3.5 `LIBGPU.A:sys.o` `memset` (currently in `src/main/sdk/libcd/memset.c`) |
| `0x80042B0C` | 3w | `func_80042B0C` | **`GPU_cw`** | `LIBAPI.A:c73.o` | `Global` | `—` | BIOS A0:0x49 `GPU_cw` |

### 5.6 `LIBGTE.A` Geometry Transformation Engine Library (`0x80042B1C..0x8004324B`) (19 functions)

| Address | Size | Current Symbol | Exact PsyQ SDK Symbol | PsyQ Archive:Object | Linkage | Current TU (`src/main/`) | Description / Notes |
|---|---:|---|---|---|---|---|---|
| `0x80042B1C` | 32w | `func_80042B1C` | **`InitGeom`** | `LIBGTE.A:geo_00.o` | `Global` | `—` | Initialize GTE CP2 control registers and call `_patch_gte` |
| `0x80042B9C` | 33w | `func_80042B9C` | **`SquareRoot0`** | `LIBGTE.A:sqrt0.o` | `Global` | `level/grid_workspace.c` | Fast integer square root via `LZCS`/`LZCR` and `D_80054DA4` LUT |
| `0x80042C2C` | 67w | `func_80042C2C` | **`MulMatrix`** | `LIBGTE.A:mtx_000.o` | `Global` | `—` | GTE `MVMVA` 3x3 matrix multiplication `m0 = m0 * m1` |
| `0x80042D3C` | 9w | `func_80042D3C` | **`TransMatrix`** | `LIBGTE.A:mtx_010.o` | `Global` | `—` | Set translation vector `m->t[0..2]` from `VECTOR` |
| `0x80042D6C` | 73w | `func_80042D6C` | **`ScaleMatrix`** | `LIBGTE.A:mtx_011.o` | `Global` | `—` | Scale rows/columns of 3x3 `MATRIX` by `VECTOR` |
| `0x80042E9C` | 12w | `func_80042E9C` | **`SetRotMatrix`** | `LIBGTE.A:mtx_10.o` | `Global` | `—` | Load 3x3 rotation matrix into GTE `R11R12..R33` |
| `0x80042ECC` | 12w | `func_80042ECC` | **`SetLightMatrix`** | `LIBGTE.A:mtx_11.o` | `Global` | `—` | Load 3x3 light direction matrix into GTE `L11L12..L33` |
| `0x80042EFC` | 12w | `func_80042EFC` | **`SetColorMatrix`** | `LIBGTE.A:mtx_12.o` | `Global` | `—` | Load 3x3 light color matrix into GTE `LR1LR2..LB3` |
| `0x80042F2C` | 8w | `func_80042F2C` | **`SetTransMatrix`** | `LIBGTE.A:mtx_13.o` | `Global` | `—` | Load translation vector into GTE `TRX`, `TRY`, `TRZ` |
| `0x80042F4C` | 5w | `func_80042F4C` | **`ReadSZfifo3`** | `LIBGTE.A:fgo_03.o` | `Global` | `—` | Read GTE `SZ1`, `SZ2`, `SZ3` screen Z FIFO registers |
| `0x80042F6C` | 8w | `func_80042F6C` | **`SetBackColor`** | `LIBGTE.A:fgo_04.o` | `Global` | `—` | Set GTE background color `RBK`, `GBK`, `BBK` |
| `0x80042F8C` | 6w | `func_80042F8C` | **`SetGeomOffset`** | `LIBGTE.A:fgo_05.o` | `Global` | `—` | Set GTE screen offset `OFX`, `OFY` |
| `0x80042FAC` | 3w | `func_80042FAC` | **`SetGeomScreen`** | `LIBGTE.A:fgo_06.o` | `Global` | `—` | Set GTE projection distance `H` |
| `0x80042FBC` | 11w | `func_80042FBC` | **`RotTransPers`** | `LIBGTE.A:oko_00.o` | `Global` | `—` | GTE `RTPS` perspective transform single vertex |
| `0x80042FEC` | 10w | `func_80042FEC` | **`RotTrans`** | `LIBGTE.A:oko_02.o` | `Global` | `—` | GTE `RT` rotate and translate single vertex |
| `0x8004301C` | 96w | `func_8004301C` | **`ratan2`** | `LIBGTE.A:ratan.o` | `Global` | `sdk/libgte/atan.c` | 12-bit fixed-point `atan2(y, x)` using `D_80054FA4` LUT |
| `0x8004319C` | 26w | `func_8004319C` | **`_patch_gte`** | `LIBGTE.A:patch.o` | `Global` | `sdk/libgte/patch_gte.c` | Patch BIOS exception handler for GTE `cop2` hazard on early R3000A |
| `0x8004320C` | 11w | `func_8004320C` | **`_patch_gte_helper`** | `LIBGTE.A:patch.o` | `Static` | `sdk/libgte/patch_gte.c` | Internal helper inside `patch.o` |
| `0x8004323C` | 3w | `func_8004323C` | **`FlushCache`** | `LIBAPI.A:c68.o` | `Global` | `sdk/libgte/patch_gte.c` | BIOS A0:0x44 `FlushCache` |

### 5.7 `LIBCD.A` (`event.o`, `sys.o`, `bios.o`, `cdread.o`) CD-ROM Library (`0x8004324C..0x80045D6F`) (45 functions)

| Address | Size | Current Symbol | Exact PsyQ SDK Symbol | PsyQ Archive:Object | Linkage | Current TU (`src/main/`) | Description / Notes |
|---|---:|---|---|---|---|---|---|
| `0x8004324C` | 36w | `func_8004324C` | **`CdInit`** | `LIBCD.A:event.o` | `Global` | `sdk/libcd/start_retry.c` | Initialize CD-ROM subsystem (`CD_init`, `CD_initvol`) |
| `0x800432DC` | 10w | `func_800432DC` | **`def_cbsync`** | `LIBCD.A:event.o` | `Static` | `sdk/libcd/event_callbacks.c` | Default `CdlCB` sync event handler (`DeliverEvent(HwCdRom, EvSpCOMP)`) |
| `0x80043304` | 10w | `func_80043304` | **`def_cbready`** | `LIBCD.A:event.o` | `Static` | `sdk/libcd/event_callbacks.c` | Default `CdlCB` ready event handler (`DeliverEvent(HwCdRom, EvSpDR)`) |
| `0x8004332C` | 10w | `func_8004332C` | **`def_cbread`** | `LIBCD.A:event.o` | `Static` | `sdk/libcd/event_callbacks.c` | Default `CdlCB` read event handler (`DeliverEvent(HwCdRom, EvSpTIMOUT)`) |
| `0x80043354` | 8w | `func_80043354` | **`CdStatus`** | `LIBCD.A:sys.o` | `Global` | `sdk/libcd/event_callbacks.c` | Return cached CD status byte |
| `0x80043374` | 4w | `func_80043374` | **`CdMode`** | `LIBCD.A:sys.o` | `Global` | `sdk/libapi/func_80043374.c` | Return cached CD mode byte |
| `0x80043384` | 27w | `func_80043384` | **`CdReset`** | `LIBCD.A:sys.o` | `Global` | `sdk/libcd/start_retry.c` | Reset CD-ROM drive and state (`CD_reset`) |
| `0x800433F0` | 8w | `func_800433F0` | **`CdFlush`** | `LIBCD.A:sys.o` | `Global` | `sdk/libcd/reset_wrapper.c` | Flush CD-ROM command queue (`CD_flush`) |
| `0x80043410` | 6w | `func_80043410` | **`CdSetDebug`** | `LIBCD.A:sys.o` | `Global` | `sdk/libapi/func_80043410.c` | Set `CD_debug` verbosity level |
| `0x80043428` | 14w | `func_80043428` | **`CdComstr`** | `LIBCD.A:sys.o` | `Global` | `sdk/libcd/names.c` | Return debug string name for CD command byte |
| `0x80043460` | 14w | `func_80043460` | **`CdIntstr`** | `LIBCD.A:sys.o` | `Global` | `sdk/libcd/names.c` | Return debug string name for CD interrupt byte |
| `0x80043498` | 8w | `func_80043498` | **`CdSync`** | `LIBCD.A:sys.o` | `Global` | `sdk/libcd/sync_wrapper.c` | Wait or poll CD command completion (`CD_sync`) |
| `0x800434B8` | 8w | `func_800434B8` | **`CdReady`** | `LIBCD.A:sys.o` | `Global` | `sdk/libcd/ready_wrapper.c` | Wait or poll CD data ready (`CD_ready`) |
| `0x800434D8` | 6w | `func_800434D8` | **`CdSyncCallback`** | `LIBCD.A:sys.o` | `Global` | `sdk/libapi/func_800434D8.c` | Register `CD_cbsync` callback |
| `0x800434F0` | 6w | `func_800434F0` | **`CdReadyCallback`** | `LIBCD.A:sys.o` | `Global` | `sdk/libapi/func_800434F0.c` | Register `CD_cbready` callback |
| `0x80043508` | 6w | `func_80043508` | **`CdDataCallback`** | `LIBCD.A:sys.o` | `Global` | `sdk/libapi/func_80043508.c` | Register CD DMA data callback via `DMACallback(3, cb)` |
| `0x80043520` | 82w | `func_80043520` | **`CdControl`** | `LIBCD.A:sys.o` | `Global` | `sdk/libcd/command_retry.c` | Issue CD command and wait for acknowledge (`CD_cw` + `CD_sync`) |
| `0x80043668` | 79w | `func_80043668` | **`CdControlF`** | `LIBCD.A:sys.o` | `Global` | `sdk/libcd/command_retry.c` | Issue fast unacknowledged CD command (`CD_cw`) |
| `0x800437A4` | 85w | `func_800437A4` | **`CdControlB`** | `LIBCD.A:sys.o` | `Global` | `sdk/libcd/command_retry.c` | Issue blocking CD command (`CD_cw` + `CD_sync(0, result)`) |
| `0x800438F8` | 9w | `func_800438F8` | **`CdMix`** | `LIBCD.A:sys.o` | `Global` | `sdk/libcd/func_800438F8.c` | Set CD audio attenuation matrix (`CD_vol`) |
| `0x8004391C` | 9w | `func_8004391C` | **`CdGetSector`** | `LIBCD.A:sys.o` | `Global` | `sdk/libcd/func_8004391C.c` | Transfer sector words from CD FIFO via DMA3 (`CD_getsector`) |
| `0x80043940` | 9w | `func_80043940` | **`CdDataSync`** | `LIBCD.A:sys.o` | `Global` | `sdk/libcd/func_80043940.c` | Wait or poll CD DMA3 completion (`CD_datasync`) |
| `0x80043964` | 8w | `func_80043964` | **`CdReadCallback`** | `LIBCD.A:cdread.o` | `Global` | `sdk/libcd/func_80043964.c` | Register `cd_read` completion callback |
| `0x80043984` | 8w | `func_80043984` | **`CdReadSync`** | `LIBCD.A:cdread.o` | `Global` | `sdk/libcd/func_80043984.c` | Poll or wait for multi-sector `CdRead` completion |
| `0x800439A4` | 32w | `func_800439A4` | **`CdRead`** | `LIBCD.A:cdread.o` | `Global` | `sdk/libcd/read_retry.c` | Start multi-sector read with retry (`CD_read`) |
| `0x80043A24` | 65w | `func_80043A24` | **`CdIntToPos`** | `LIBCD.A:sys.o` | `Global` | `sdk/libcd/frames_position.c` | Convert logical sector number to BCD `CdlLOC` (`minute:second:sector`) |
| `0x80043B28` | 32w | `func_80043B28` | **`CdPosToInt`** | `LIBCD.A:sys.o` | `Global` | `sdk/libcd/position_frames.c` | Convert BCD `CdlLOC` (`minute:second:sector`) to logical sector number |
| `0x80043BA8` | 337w | `func_80043BA8` | **`getintr`** | `LIBCD.A:bios.o` | `Static` | `sdk/libcd/interrupt_dispatch.c` | Poll CD hardware status/interrupt registers and read response FIFO |
| `0x800440EC` | 161w | `func_800440EC` | **`CD_sync`** | `LIBCD.A:bios.o` | `Global` | `sdk/libcd/bios_com.c` | Low-level CD command sync wait/poll |
| `0x80044370` | 180w | `func_80044370` | **`CD_ready`** | `LIBCD.A:bios.o` | `Global` | `sdk/libcd/bios_com.c` | Low-level CD data-ready wait/poll |
| `0x80044640` | 282w | `func_80044640` | **`CD_cw`** | `LIBCD.A:bios.o` | `Global` | `sdk/libcd/sync.c` | Write CD command & parameters to `0x1F801800..0x1F801803` |
| `0x80044AA8` | 34w | `func_80044AA8` | **`CD_vol`** | `LIBCD.A:bios.o` | `Global` | `sdk/libcd/volume.c` | Write `CdlATV` CD-XA/CD-DA mixer volumes to CD registers |
| `0x80044B30` | 68w | `func_80044B30` | **`CD_flush`** | `LIBCD.A:bios.o` | `Global` | `sdk/libcd/sync.c` | Acknowledge pending CD interrupt and clear state |
| `0x80044C40` | 58w | `func_80044C40` | **`CD_initvol`** | `LIBCD.A:bios.o` | `Global` | `sdk/libcd/reset.c` | Initialize default CD audio volume registers |
| `0x80044D28` | 61w | `func_80044D28` | **`CD_initintr`** | `LIBCD.A:bios.o` | `Global` | `sdk/libcd/reset_mode.c` | Clear pending CD hardware interrupts |
| `0x80044E1C` | 28w | `func_80044E1C` | **`CD_init`** | `LIBCD.A:bios.o` | `Global` | `sdk/libcd/callbacks.c` | Register CD IRQ2 `InterruptCallback` and reset drive |
| `0x80044E8C` | 196w | `func_80044E8C` | **`CD_reset`** | `LIBCD.A:bios.o` | `Global` | `sdk/libcd/reset_mode.c` | Hardware CD-ROM reset sequence (`CdlNop`, `CdlInit`, `CdlDemute`) |
| `0x8004519C` | 223w | `func_8004519C` | **`CD_read`** | `LIBCD.A:cdread.o` | `Static` | `sdk/libcd/bios_init.c` | Set up `cb_read` ready callback and issue `CdlReadN`/`CdlReadS` |
| `0x80045518` | 62w | `func_80045518` | **`cd_read_retry`** | `LIBCD.A:cdread.o` | `Static` | `sdk/libcd/read_setup.c` | Retry failed sector read by re-seeking and re-issuing `CD_read` |
| `0x80045610` | 174w | `func_80045610` | **`CD_readsync`** | `LIBCD.A:cdread.o` | `Static` | `sdk/libcd/bios_sync.c` | Wait or poll for `CdRead` sector count completion |
| `0x800458C8` | 91w | `func_800458C8` | **`CD_datasync`** | `LIBCD.A:bios.o` | `Global` | `sdk/libcd/bios_sync.c` | Wait or poll for CD DMA3 channel (`0x1F8010B8`) completion |
| `0x80045A34` | 56w | `func_80045A34` | **`CD_getsector`** | `LIBCD.A:bios.o` | `Global` | `sdk/libcd/dma.c` | Start CD DMA3 transfer (`0x1F8010B0..0x1F8010B8`) into RAM buffer |
| `0x80045B14` | 4w | `func_80045B14` | **`CD_set_test_parmnum`** | `LIBCD.A:bios.o` | `Global` | `sdk/libcd/func_80045B14.c` | Set parameter count for `CdlTest` command (`0x19`) |
| `0x80045B24` | 56w | `func_80045B24` | **`callback`** | `LIBCD.A:bios.o` | `Static` | `sdk/libcd/interrupt_callbacks.c` | CD-ROM IRQ2 interrupt handler; calls `getintr` and dispatches `CD_cbsync`/`CD_cbready` |
| `0x80045C04` | 91w | `func_80045C04` | **`cb_read`** | `LIBCD.A:cdread.o` | `Static` | `sdk/libcd/read_callback.c` | `CD_cbready` handler during `CdRead`; transfers each sector and issues `CdlPause` at end |

### 5.8 `LIBSPU.A` Sound Processing Unit Low-Level Library (`0x80045D70..0x80049267`) (38 functions)

| Address | Size | Current Symbol | Exact PsyQ SDK Symbol | PsyQ Archive:Object | Linkage | Current TU (`src/main/`) | Description / Notes |
|---|---:|---|---|---|---|---|---|
| `0x80045D70` | 21w | `func_80045D70` | **`SpuInitMalloc`** | `LIBSPU.A:s_m_init.o` | `Global` | `sdk/libspu/heap_init.c` | Initialize SPU RAM allocator table (`_spu_memList`) at `0x1010` |
| `0x80045DC4` | 35w | `func_80045DC4` | **`_spu_reset`** | `LIBSPU.A:spu.o` | `Static` | `sdk/libspu/control_disable.c` | Reset SPU control register and wait for DMA status clear |
| `0x80045E50` | 327w | `func_80045E50` | **`_spu_init`** | `LIBSPU.A:spu.o` | `Global` | `sdk/libspu/hardware_init.c` | Initialize SPU hardware registers, zero voice attributes, and configure DMA4 |
| `0x8004636C` | 205w | `func_8004636C` | **`_spu_writeByIO`** | `LIBSPU.A:spu.o` | `Static` | `sdk/libspu/fifo_write.c` | Write data to SPU RAM via PIO FIFO (`0x1F801DA8`) |
| `0x800466A0` | 104w | `func_800466A0` | **`_spu_FiDMA`** | `LIBSPU.A:spu.o` | `Static` | `sdk/libspu/transfer_complete.c` | SPU DMA4 completion interrupt handler |
| `0x80046840` | 120w | `func_80046840` | **`_spu_r_`** | `LIBSPU.A:spu.o` | `Static` | `sdk/libspu/dma_start.c` | Start SPU DMA4 read/write transfer (`0x1F8010C0..0x1F8010C8`) |
| `0x80046A20` | 170w | `func_80046A20` | **`_spu_t`** | `LIBSPU.A:spu.o` | `Global` | `sdk/libspu/dma_command.c` | Core SPU transfer state machine (set addr, wait, or start DMA) |
| `0x80046CC8` | 34w | `func_80046CC8` | **`_spu_write`** | `LIBSPU.A:spu.o` | `Global` | `sdk/libspu/transfer_mode.c` | Write buffer to SPU RAM via DMA or PIO (`_spu_t` / `_spu_writeByIO`) |
| `0x80046D50` | 26w | `func_80046D50` | **`_spu_read`** | `LIBSPU.A:spu.o` | `Global` | `sdk/libspu/transfer_command.c` | Read buffer from SPU RAM via DMA (`_spu_t`) |
| `0x80046DB8` | 18w | `func_80046DB8` | **`_spu_FsetRXX`** | `LIBSPU.A:spu.o` | `Global` | `sdk/libspu/register_write.c` | Write SPU register at offset `reg` (optionally shifted `>> 3`) |
| `0x80046E00` | 41w | `func_80046E00` | **`_spu_FsetRXXa`** | `LIBSPU.A:spu.o` | `Global` | `sdk/libspu/address_register.c` | Convert SPU byte address to 8-byte unit and write/return SPU register |
| `0x80046EA4` | 15w | `func_80046EA4` | **`_spu_FgetRXXa`** | `LIBSPU.A:spu.o` | `Global` | `sdk/libspu/address_register.c` | Read SPU address register and shift `<< 3` to byte address |
| `0x80046EE0` | 52w | `func_80046EE0` | **`SpuSetReverb`** | `LIBSPU.A:s_sr.o` | `Global` | `sdk/libspu/address_register.c` | Enable or disable SPU master reverb (`SPU_CTRL` bit 7) |
| `0x80046FB0` | 50w | `func_80046FB0` | **`_SpuInit`** | `LIBSPU.A:s_ini.o` | `Global` | `sdk/libspu/init.c` | Internal SPU initialization (`ResetCallback`, `_spu_init`, `SpuStart`) |
| `0x80047078` | 33w | `func_80047078` | **`SpuStart`** | `LIBSPU.A:s_ini.o` | `Global` | `sdk/libspu/event_init.c` | Open SPU DMA completion event (`HwSPU`, `EvSpCOMP`) |
| `0x800470FC` | 9w | `func_800470FC` | **`_SpuCallback`** | `LIBSPU.A:s_cb.o` | `Global` | `sdk/libapi/callback_slot4.c` | Register SPU DMA4 callback via `DMACallback(4, cb)` |
| `0x80047120` | 28w | `func_80047120` | **`_SpuIsInAllocateArea`** | `LIBSPU.A:s_m_util.o` | `Global` | `sdk/libspu/heap_query.c` | Check if SPU address falls inside allocated SPU heap or reverb work area |
| `0x80047190` | 30w | `func_80047190` | **`_SpuIsInAllocateArea_`** | `LIBSPU.A:s_m_util.o` | `Global` | `sdk/libspu/reverb_attr_set.c` | Check if SPU `(addr >> 3)` falls inside allocated SPU heap or reverb work area |
| `0x80047208` | 324w | `func_80047208` | **`SpuSetReverbModeParam`** | `LIBSPU.A:s_srmp.o` | `Global` | `sdk/libspu/reverb_attr_set.c` | Configure SPU reverb mode, work area start address, depth, delay, and feedback |
| `0x80047718` | 308w | `func_80047718` | **`_spu_setReverbAttr`** | `LIBSPU.A:s_srmp.o` | `Global` | `sdk/libspu/reverb_registers.c` | Write `SpuReverbAttr` preset parameters to SPU reverb registers (`0x1F801DC0..0x1F801DFE`) |
| `0x80047BE8` | 30w | `func_80047BE8` | **`SpuSetReverbDepth`** | `LIBSPU.A:s_srd.o` | `Global` | `sdk/libspu/cd_volume.c` | Set SPU reverb wet output depth (`vLout`, `vRout`) |
| `0x80047C60` | 9w | `func_80047C60` | **`SpuSetReverbVoice`** | `LIBSPU.A:s_srv.o` | `Global` | `sdk/libspu/func_80047C60.c` | Enable/disable reverb on 24 SPU voices via `_SpuSetAnyVoice` |
| `0x80047C84` | 45w | `func_80047C84` | **`_SpuSetAnyVoice`** | `LIBSPU.A:s_sav.o` | `Global` | `sdk/libspu/voice_mask.c` | Set/clear per-voice bitmask across a pair of 16-bit SPU voice registers (reverb/noise/pitch LFO) |
| `0x80047D38` | 103w | `func_80047D38` | **`SpuClearReverbWorkArea`** | `LIBSPU.A:s_crwa.o` | `Global` | `sdk/libspu/region_transfer.c` | Zero-fill SPU reverb work area in SPU RAM via DMA |
| `0x80047ED4` | 3w | `func_80047ED4` | **`_spu_crwa_cb`** | `LIBSPU.A:s_crwa.o` | `Static` | `sdk/libspu/region_transfer.c` | Completion callback stub clearing transfer-in-progress flag for `SpuClearReverbWorkArea` |
| `0x80047EE4` | 30w | `func_80047EE4` | **`SpuSetKey`** | `LIBSPU.A:s_sk.o` | `Global` | `sdk/libspu/voice_key.c` | Write 24-bit voice mask to SPU `SPU_KEYON` (`0x1F801D88`) or `SPU_KEYOFF` (`0x1F801D8C`) |
| `0x80047F5C` | 10w | `func_80047F5C` | **`SpuSetVoiceAttr`** | `LIBSPU.A:s_sva.o` | `Global` | `sdk/libspu/func_80047F5C.c` | Wrapper calling `_SpuSetVoiceAttr(arg, 0)` |
| `0x80047F84` | 407w | `func_80047F84` | **`_SpuSetVoiceAttr`** | `LIBSPU.A:s_sva.o` | `Global` | `sdk/libspu/voice_attributes_set.c` | Apply `SpuVoiceAttr` (volume, pitch/note, addr, ADSR) to selected SPU voices |
| `0x800485E0` | 246w | `func_800485E0` | **`SpuGetVoiceAttr`** | `LIBSPU.A:s_gva.o` | `Global` | `sdk/libspu/voice_attributes_get.c` | Read current `SpuVoiceAttr` from SPU voice hardware registers |
| `0x800489B8` | 24w | `func_800489B8` | **`SpuWrite`** | `LIBSPU.A:s_w.o` | `Global` | `sdk/libspu/transfer_buffer.c` | Transfer `size` bytes from main RAM to SPU RAM (`_spu_write`) |
| `0x80048A18` | 15w | `func_80048A18` | **`SpuSetTransferStartAddr`** | `LIBSPU.A:s_stsa.o` | `Global` | `sdk/libspu/transfer_address.c` | Set SPU RAM target address (`_spu_tsa`) for subsequent `SpuWrite`/`SpuRead` |
| `0x80048A54` | 13w | `func_80048A54` | **`SpuSetTransferMode`** | `LIBSPU.A:s_stm.o` | `Global` | `sdk/libspu/transfer_option.c` | Set SPU transfer mode (`SPU_TRANSFER_BY_DMA` or `SPU_TRANSFER_BY_IO`) |
| `0x80048A88` | 42w | `func_80048A88` | **`SpuIsTransferCompleted`** | `LIBSPU.A:s_itc.o` | `Global` | `sdk/libspu/transfer_wait.c` | Poll or wait for SPU DMA transfer completion event (`TestEvent`) |
| `0x80048B30` | 229w | `func_80048B30` | **`SpuSetCommonAttr`** | `LIBSPU.A:s_sca.o` | `Global` | `sdk/libspu/common_attributes_set.c` | Apply `SpuCommonAttr` (master volume, CD volume/reverb/mix, ext volume/reverb/mix) |
| `0x80048EC4` | 60w | `func_80048EC4` | **`_spu_note2pitch`** | `LIBSPU.A:s_n2p.o` | `Global` | `sdk/libspu/pitch_forward.c` | Convert MIDI note + fine tune to 16-bit SPU sample rate pitch |
| `0x80048FB4` | 87w | `func_80048FB4` | **`_spu_pitch2note`** | `LIBSPU.A:s_n2p.o` | `Global` | `sdk/libspu/pitch_reverse.c` | Convert 16-bit SPU sample rate pitch to MIDI note + fine tune |
| `0x80049110` | 52w | `func_80049110` | **`SpuRGetAllKeysStatus`** | `LIBSPU.A:sr_gaks.o` | `Global` | `sdk/libspu/voice_status.c` | Read key status and envelope volume for voice range `[min_, max_]` |
| `0x800491E0` | 34w | `func_800491E0` | **`SpuGetAllKeysStatus`** | `LIBSPU.A:sr_gaks.o` | `Global` | `sdk/libspu/voice_status.c` | Read key status and envelope volume for all 24 SPU voices |

### 5.9 `LIBSND.A` & `LIBSPU.A` (`Ss*`, `SpuVm*`, `SpuMalloc`/`SpuFree`) Sound Sequencer, Voice Manager & VAB Bank Library (`0x80049268..0x80051423`) (111 functions)

| Address | Size | Current Symbol | Exact PsyQ SDK Symbol | PsyQ Archive:Object | Linkage | Current TU (`src/main/`) | Description / Notes |
|---|---:|---|---|---|---|---|---|
| `0x80049268` | 94w | `func_80049268` | **`_SsClose`** | `LIBSND.A:ssclose.o` | `Global` | `sdk/libspu/func_800493E0.c` | Stop sequence, release voices, and free `_ss_score[sep_no]` slot |
| `0x800493E0` | 9w | `func_800493E0` | **`SsSeqClose`** | `LIBSND.A:ssclose.o` | `Global` | `sdk/libspu/func_800493E0.c` | Close opened SEQ slot (`_SsClose(seq_access_num)`) |
| `0x80049404` | 9w | `func_80049404` | **`SsSepClose`** | `LIBSND.A:ssclose.o` | `Global` | `sdk/libspu/func_80049404.c` | Close opened SEP slot (`_SsClose(sep_access_num)`) |
| `0x80049428` | 42w | `func_80049428` | **`_SsSndSetCres`** | `LIBSND.A:vol.o` | `Global` | `sdk/libspu/sequence_tempo_flags.c` | Configure crescendo volume ramp on sequence (`_SsSndSetVolData`) |
| `0x800494D0` | 13w | `func_800494D0` | **`SsSeqSetCrescendo`** | `LIBSND.A:vol.o` | `Global` | `sdk/libspu/func_800494D0.c` | Start crescendo volume ramp on SEQ (`_SsSndSetCres(seq, 0, vol, v_time)`) |
| `0x80049504` | 13w | `func_80049504` | **`SsSepSetCrescendo`** | `LIBSND.A:vol.o` | `Global` | `sdk/libspu/func_80049504.c` | Start crescendo volume ramp on SEP track (`_SsSndSetCres(sep, seq, vol, v_time)`) |
| `0x80049538` | 42w | `func_80049538` | **`_SsSndSetDecres`** | `LIBSND.A:vol.o` | `Global` | `sdk/libspu/sequence_tempo_reverse.c` | Configure decrescendo volume ramp on sequence (`_SsSndSetVolData`) |
| `0x800495E0` | 13w | `func_800495E0` | **`SsSeqSetDecrescendo`** | `LIBSND.A:vol.o` | `Global` | `sdk/libspu/func_800495E0.c` | Start decrescendo volume ramp on SEQ (`_SsSndSetDecres(seq, 0, vol, v_time)`) |
| `0x80049614` | 13w | `func_80049614` | **`SsSepSetDecrescendo`** | `LIBSND.A:vol.o` | `Global` | `sdk/libspu/func_80049614.c` | Start decrescendo volume ramp on SEP track (`_SsSndSetDecres(sep, seq, vol, v_time)`) |
| `0x80049648` | 49w | `func_80049648` | **`SsQuit`** | `LIBSND.A:ssquit.o` | `Global` | `sdk/libspu/callback_release.c` | Unregister sequencer VSync/RCnt callbacks and shut down `LIBSND` |
| `0x8004970C` | 58w | `func_8004970C` | **`_SsInit`** | `LIBSND.A:ssinit.o` | `Global` | `sdk/libspu/spu_initialize.c` | Initialize `LIBSND` voice manager (`SpuVmInit`) and score tables |
| `0x800497F4` | 12w | `func_800497F4` | **`SsInit`** | `LIBSND.A:ssinit_c.o` | `Global` | `sdk/libspu/func_800497F4.c` | Cold-start `LIBSND` (`ResetCallback`, `SpuInit`, `_SsInit`) |
| `0x80049824` | 8w | `func_80049824` | **`SpuInit`** | `LIBSPU.A:s_i.o` | `Global` | `sdk/libspu/func_80049824.c` | Cold-start SPU (`_SpuInit(0)`) |
| `0x80049844` | 215w | `func_80049844` | **`SsSepOpen`** | `LIBSND.A:sepinit.o` | `Global` | `sdk/libspu/sequence_open.c` | Register `Snd_FnTable` (`D_80058360..g_ss_nrpn_attr_fn_19`) and open multi-track SEP sequence |
| `0x80049BA0` | 32w | `func_80049BA0` | **`_SsSetProgramChange`** | `LIBSND.A:seqread.o` | `Global` | `sdk/libspu/sequence_value_read.c` | SMF/SEP Program Change (`0xC0`) event handler |
| `0x80049C20` | 272w | `func_80049C20` | **`_SsSetControlChange`** | `LIBSND.A:seqread.o` | `Global` | `sdk/libspu/sequence_event_note_on.c` | SMF/SEP Control Change (`0xB0`) dispatcher via `Snd_FnTable` |
| `0x8004A060` | 50w | `func_8004A060` | **`_SsContModulation`** | `LIBSND.A:seqread.o` | `Global` | `sdk/libspu/sequence_event_velocity.c` | CC#1 Modulation Depth handler |
| `0x8004A128` | 49w | `func_8004A128` | **`_SsContPortaTime`** | `LIBSND.A:seqread.o` | `Global` | `sdk/libspu/sequence_event_parameter.c` | CC#5 Portamento Time handler |
| `0x8004A1EC` | 43w | `func_8004A1EC` | **`_SsContPortamento`** | `LIBSND.A:seqread.o` | `Global` | `sdk/libspu/sequence_event_reverb.c` | CC#65 Portamento On/Off handler |
| `0x8004A298` | 35w | `func_8004A298` | **`_SsContResetAll`** | `LIBSND.A:seqread.o` | `Global` | `sdk/libspu/sequence_event_reverb_depth.c` | CC#121 Reset All Controllers handler |
| `0x8004A324` | 74w | `func_8004A324` | **`_SsContNrpn1`** | `LIBSND.A:seqread.o` | `Global` | `sdk/libspu/sequence_event_control.c` | CC#98 NRPN LSB handler |
| `0x8004A44C` | 82w | `func_8004A44C` | **`_SsContNrpn2`** | `LIBSND.A:seqread.o` | `Global` | `sdk/libspu/sequence_event_loop.c` | CC#99 NRPN MSB (loop markers) handler |
| `0x8004A594` | 29w | `func_8004A594` | **`_SsContRpn1`** | `LIBSND.A:seqread.o` | `Global` | `sdk/libspu/sequence_event_parameters.c` | CC#100 RPN LSB handler |
| `0x8004A608` | 29w | `func_8004A608` | **`_SsContRpn2`** | `LIBSND.A:seqread.o` | `Global` | `sdk/libspu/sequence_event_parameters.c` | CC#101 RPN MSB handler |
| `0x8004A67C` | 49w | `func_8004A67C` | **`_SsContDataEntry`** | `LIBSND.A:seqread.o` | `Global` | `sdk/libspu/sequence_event_reset.c` | CC#6 Data Entry MSB handler |
| `0x8004A740` | 42w | `func_8004A740` | **`_SsSetPitchBend`** | `LIBSND.A:seqread.o` | `Global` | `sdk/libspu/sequence_event_pitch.c` | SMF/SEP Pitch Bend (`0xE0`) event handler |
| `0x8004A7E8` | 133w | `func_8004A7E8` | **`_SsGetSeqData`** | `LIBSND.A:seqread.o` | `Global` | `sdk/libspu/sequence_controller_dispatch.c` | Read and dispatch next SMF/SEP status byte (`0x80..0xFF`) via `Snd_FnTable` |
| `0x8004A9FC` | 218w | `func_8004A9FC` | **`_SsGetMetaEvent`** | `LIBSND.A:seqread.o` | `Global` | `sdk/libspu/sequence_meta_event.c` | SMF/SEP Meta Event (`0xFF`: tempo `0x51`, end-of-track `0x2F`) handler |
| `0x8004AD64` | 56w | `func_8004AD64` | **`_SsNoteOn`** | `LIBSND.A:seqread.o` | `Global` | `sdk/libspu/sequence_note_event.c` | SMF/SEP Note On (`0x90`) event handler (`SpuVmKeyOn` / `SpuVmKeyOff`) |
| `0x8004AE44` | 29w | `func_8004AE44` | **`_SsNoteOff`** | `LIBSND.A:seqread.o` | `Global` | `sdk/libspu/sequence_event_selected.c` | SMF/SEP Note Off (`0x80`) event handler |
| `0x8004AEB8` | 46w | `func_8004AEB8` | **`_SsReadDeltaValue`** | `LIBSND.A:seqread.o` | `Global` | `sdk/libspu/sequence_delta_read.c` | Decode variable-length SMF/SEP delta-time quantity |
| `0x8004AF70` | 66w | `func_8004AF70` | **`_SsSndNextSep`** | `LIBSND.A:next.o` | `Global` | `sdk/libspu/sequence_channel_restart.c` | Reset SEP track read pointers and loop state for next iteration |
| `0x8004B078` | 245w | `func_8004B078` | **`_SsInitSoundSep`** | `LIBSND.A:sepinit.o` | `Global` | `sdk/libspu/sequence_channel_open.c` | Parse `pBAV` / SEP track header, tempo, and initial delta time |
| `0x8004B44C` | 52w | `func_8004B44C` | **`_SsSndSetPauseMode`** | `LIBSND.A:sspause.o` | `Global` | `sdk/libspu/sequence_channel_resume.c` | Set pause bit (`SNS_PAUSE`) on sequence track |
| `0x8004B51C` | 10w | `func_8004B51C` | **`SsSeqPause`** | `LIBSND.A:sspause.o` | `Global` | `sdk/libspu/func_8004B51C.c` | Pause SEQ playback (`_SsSndSetPauseMode(seq, 0)`) |
| `0x8004B544` | 11w | `func_8004B544` | **`SsSepPause`** | `LIBSND.A:sspause.o` | `Global` | `sdk/libspu/func_8004B544.c` | Pause SEP track playback (`_SsSndSetPauseMode(sep, seq)`) |
| `0x8004B570` | 14w | `func_8004B570` | **`SsSeqPlay`** | `LIBSND.A:ssplay.o` | `Global` | `sdk/libspu/func_8004B570.c` | Start SEQ playback (`Snd_SetPlayMode(seq, 0, mode, l_count)`) |
| `0x8004B5A8` | 14w | `func_8004B5A8` | **`SsSepPlay`** | `LIBSND.A:ssplay.o` | `Global` | `sdk/libspu/func_8004B5A8.c` | Start SEP track playback (`Snd_SetPlayMode(sep, seq, mode, l_count)`) |
| `0x8004B5E0` | 41w | `func_8004B5E0` | **`_SsSndSetReplayMode`** | `LIBSND.A:ssreplay.o` | `Global` | `sdk/libspu/sequence_flag_start.c` | Set replay bit (`SNS_REPLAY`) on paused sequence track |
| `0x8004B684` | 10w | `func_8004B684` | **`SsSeqReplay`** | `LIBSND.A:ssreplay.o` | `Global` | `sdk/libspu/func_8004B684.c` | Resume paused SEQ playback (`_SsSndSetReplayMode(seq, 0)`) |
| `0x8004B6AC` | 11w | `func_8004B6AC` | **`SsSepReplay`** | `LIBSND.A:ssreplay.o` | `Global` | `sdk/libspu/func_8004B6AC.c` | Resume paused SEP track playback (`_SsSndSetReplayMode(sep, seq)`) |
| `0x8004B6D8` | 64w | `func_8004B6D8` | **`Snd_SetPlayMode`** | `LIBSND.A:ssplay.o` | `Global` | `sdk/libspu/sequence_play_mode.c` | Configure play mode (`SSPLAY_PLAY`/`SSPLAY_PAUSE`) and loop count on track |
| `0x8004B7D8` | 20w | `func_8004B7D8` | **`SsSetMVol`** | `LIBSND.A:scsmvol.o` | `Global` | `sdk/libspu/master_volume.c` | Set SPU master volume (`SpuSetCommonAttr` with `SPU_COMMON_MVOLL | SPU_COMMON_MVOLR`) |
| `0x8004B828` | 16w | `func_8004B828` | **`_SsTrapIntrVSync`** | `LIBSND.A:ssstart.o` | `Static` | `sdk/libspu/sequence_callbacks.c` | Sequencer VSync/RCnt tick callback invoking `_snd_ev_flag` + `SsSeqCalledTbyT` |
| `0x8004B868` | 20w | `func_8004B868` | **`_SsSeqCalledTbyT_1per2`** | `LIBSND.A:ssstart.o` | `Static` | `sdk/libspu/sequence_toggle.c` | Half-rate (30Hz) wrapper calling `SsSeqCalledTbyT` every 2nd tick |
| `0x8004B8B8` | 161w | `func_8004B8B8` | **`_SsStart`** | `LIBSND.A:ssstart.o` | `Static` | `sdk/libspu/sequence_event_dispatch.c` | Install sequencer tick callback on `VSyncCallback` or `RCntCNT2` |
| `0x8004BB3C` | 8w | `func_8004BB3C` | **`SsStart`** | `LIBSND.A:ssstart.o` | `Global` | `sdk/libspu/sequence_mode.c` | Start sequencer tick processing (`_SsStart(1)`) |
| `0x8004BB5C` | 8w | `func_8004BB5C` | **`SsStart2`** | `LIBSND.A:ssstart.o` | `Global` | `sdk/libspu/sequence_mode.c` | Start sequencer tick processing without waiting (`_SsStart(0)`) |
| `0x8004BB7C` | 142w | `func_8004BB7C` | **`SsSeqCalledTbyT`** | `LIBSND.A:sscall.o` | `Global` | `sdk/libsnd/ss_tick.c` | Main sequencer tick driver; flushes voices and advances all active `_ss_score` tracks |
| `0x8004BDB4` | 176w | `func_8004BDB4` | **`_SsSndCrescendo`** | `LIBSND.A:cres.o` | `Global` | `sdk/libsnd/ss_tick.c` | Per-tick crescendo volume step processor |
| `0x8004C074` | 163w | `func_8004C074` | **`_SsSndDecrescendo`** | `LIBSND.A:decre.o` | `Global` | `sdk/libsnd/ss_tick.c` | Per-tick decrescendo volume step processor (stops track if volume reaches 0) |
| `0x8004C300` | 39w | `func_8004C300` | **`_SsSndPause`** | `LIBSND.A:pause.o` | `Global` | `sdk/libspu/sequence_flag_clear.c` | Per-tick pause transition handler (`SpuVmSeqKeyOff`) |
| `0x8004C39C` | 11w | `func_8004C39C` | **`_SsSndPlay`** | `LIBSND.A:play.o` | `Global` | `sdk/libspu/func_8004C39C.c` | Per-tick active track playback step (`_SsSeqPlay`) |
| `0x8004C3C8` | 67w | `func_8004C3C8` | **`_SsSeqPlay`** | `LIBSND.A:seqread.o` | `Global` | `sdk/libspu/sequence_channel_tick.c` | Advance track delta counter and process all due MIDI events (`_SsGetSeqData`) |
| `0x8004C4D4` | 164w | `func_8004C4D4` | **`_SsSndTempo`** | `LIBSND.A:tempo.o` | `Global` | `sdk/libspu/sequence_channel_tick.c` | Per-tick accelerando/ritardando tempo transition step |
| `0x8004C764` | 26w | `func_8004C764` | **`_SsSndReplay`** | `LIBSND.A:replay.o` | `Global` | `sdk/libspu/sequence_flag_resume.c` | Per-tick replay transition handler |
| `0x8004C7CC` | 92w | `func_8004C7CC` | **`_SsSndStop`** | `LIBSND.A:stop.o` | `Global` | `sdk/libspu/sequence_channel_reset.c` | Stop sequence track (`SpuVmSeqKeyOff`) and reset read pointers to start |
| `0x8004C93C` | 10w | `func_8004C93C` | **`SsSeqStop`** | `LIBSND.A:stop.o` | `Global` | `sdk/libspu/func_8004C93C.c` | Stop SEQ playback (`_SsSndStop(seq, 0)`) |
| `0x8004C964` | 11w | `func_8004C964` | **`SsSepStop`** | `LIBSND.A:stop.o` | `Global` | `sdk/libspu/func_8004C964.c` | Stop SEP track playback (`_SsSndStop(sep, seq)`) |
| `0x8004C990` | 119w | `func_8004C990` | **`SsSetTableSize`** | `LIBSND.A:sstable.o` | `Global` | `sdk/libspu/sequence_table_size.c` | Initialize `_ss_score` table buffer for `seq` x `sep` tracks |
| `0x8004CB6C` | 92w | `func_8004CB6C` | **`SsSetTickMode`** | `LIBSND.A:sstick.o` | `Global` | `sdk/libspu/sequence_timing.c` | Configure sequencer tick rate (`SS_TICK60`, `SS_TICK240`, `SS_TICK120`, `SS_TICKVSYNC`, etc.) |
| `0x8004CCDC` | 17w | `func_8004CCDC` | **`_SsSndSetVol`** | `LIBSND.A:ssvol.o` | `Global` | `sdk/libspu/channel_dispatch.c` | Wrapper calling `SpuVmSetSeqVol` |
| `0x8004CD20` | 14w | `func_8004CD20` | **`SsSeqSetVol`** | `LIBSND.A:ssvol.o` | `Global` | `sdk/libspu/channel_dispatch.c` | Set SEQ playback volume (`_SsSndSetVol(seq, 0, voll, volr)`) |
| `0x8004CD58` | 15w | `func_8004CD58` | **`SsSepSetVol`** | `LIBSND.A:ssvol.o` | `Global` | `sdk/libspu/channel_dispatch.c` | Set SEP track playback volume (`_SsSndSetVol(sep, seq, voll, volr)`) |
| `0x8004CD94` | 14w | `func_8004CD94` | **`SsSeqGetVol`** | `LIBSND.A:ssvol.o` | `Global` | `sdk/libspu/channel_dispatch.c` | Get SEQ/SEP track playback volume (`SpuVmGetSeqVol`) |
| `0x8004CDCC` | 121w | `func_8004CDCC` | **`_SsSndSetRit`** | `LIBSND.A:ssrit.o` | `Global` | `sdk/libspu/sequence_tempo_ramp.c` | Configure ritardando/accelerando tempo ramp on track |
| `0x8004CFB0` | 52w | `func_8004CFB0` | **`_SsSndSetVolData`** | `LIBSND.A:vol.o` | `Global` | `sdk/libspu/sequence_tempo_ramp_setup.c` | Store target volume and ramp time in `_ss_score[sep][seq]` |
| `0x8004D080` | 65w | `func_8004D080` | **`SsUtGetProgAtr`** | `LIBSND.A:ut_gpa.o` | `Global` | `sdk/libspu/bank_program_get.c` | Read `ProgAtr` program attribute from opened VAB header |
| `0x8004D184` | 142w | `func_8004D184` | **`SsUtGetVagAtr`** | `LIBSND.A:ut_gva.o` | `Global` | `sdk/libspu/bank_tone_get.c` | Read `VagAtr` tone attribute from opened VAB header |
| `0x8004D3BC` | 47w | `func_8004D3BC` | **`SsUtSetReverbDepth`** | `LIBSND.A:ut_rdep.o` | `Global` | `sdk/libspu/reverb_depth_set.c` | Set reverb depth via `SpuSetReverbModeParam` |
| `0x8004D478` | 8w | `func_8004D478` | **`SsUtReverbOff`** | `LIBSND.A:ut_roff.o` | `Global` | `sdk/libspu/func_8004D478.c` | Disable SPU master reverb (`SpuSetReverb(SPU_OFF)`) |
| `0x8004D498` | 113w | `func_8004D498` | **`SsUtSetVagAtr`** | `LIBSND.A:ut_sva.o` | `Global` | `sdk/libspu/bank_tone_set.c` | Write `VagAtr` tone attribute into opened VAB header |
| `0x8004D65C` | 4w | `func_8004D65C` | **`SpuVmDamperOff`** | `LIBSND.A:vm_doff.o` | `Global` | `sdk/libspu/func_8004D65C.c` | Set `_svm_damper = 0` |
| `0x8004D66C` | 5w | `func_8004D66C` | **`SpuVmDamperOn`** | `LIBSND.A:vm_don.o` | `Global` | `sdk/libspu/func_8004D66C.c` | Set `_svm_damper = 2` |
| `0x8004D680` | 254w | `func_8004D680` | **`SpuVmFlush`** | `LIBSND.A:vmanager.o` | `Global` | `sdk/libspu/voice_adsr_table.c` | Commit pending voice key-on / key-off masks and envelope states to SPU hardware |
| `0x8004DA78` | 9w | `func_8004DA78` | **`_SpuVmSetNoiseVoice`** | `LIBSND.A:vmanager.o` | `Static` | `sdk/libspu/func_8004DA78.c` | Wrapper calling `_SpuSetAnyVoice(on_off, voice_bit, 0xCA, 0xCB)` (noise voice mask) |
| `0x8004DA9C` | 195w | `func_8004DA9C` | **`SpuVmInit`** | `LIBSND.A:vmanager.o` | `Global` | `sdk/libspu/voice_state_init.c` | Initialize 24-voice `_svm_voice` table, SPU heap, and SPU registers |
| `0x8004DDA8` | 11w | `func_8004DDA8` | **`SsSetMono`** | `LIBSND.A:vs_mono.o` | `Global` | `sdk/libspu/func_8004DDA8.c` | Set `_svm_stereo_mono` mode (`0` = mono, `1` = stereo) |
| `0x8004DDD4` | 4w | `func_8004DDD4` | **`KeyOnCheck`** | `LIBSND.A:vmanager.o` | `Global` | `sdk/libspu/func_8004DDD4.c` | No-op stub (`return 0`) in `vmanager.o` |
| `0x8004DDE4` | 339w | `func_8004DDE4` | **`SpuVmKeyOn`** | `LIBSND.A:vmanager.o` | `Global` | `sdk/libspu/voice_note.c` | Trigger all layered tones for `(vab_id, prog, note, pitch, voll, volr)` |
| `0x8004E330` | 82w | `func_8004E330` | **`SpuVmKeyOff`** | `LIBSND.A:vmanager.o` | `Global` | `sdk/libspu/voice_note.c` | Release all voices matching `(vab_id, prog, note)` |
| `0x8004E478` | 60w | `func_8004E478` | **`SpuVmSeKeyOn`** | `LIBSND.A:vmanager.o` | `Global` | `sdk/libspu/stereo_gain_pan.c` | Trigger sound-effect note with stereo pan calculation (`SpuVmKeyOn`) |
| `0x8004E568` | 13w | `func_8004E568` | **`SpuVmSeKeyOff`** | `LIBSND.A:vmanager.o` | `Global` | `sdk/libspu/voice_stop_forward.c` | Release sound-effect note (`SpuVmKeyOff(0x21, vab_id, prog, note)`) |
| `0x8004E59C` | 156w | `func_8004E59C` | **`SpuVmAlloc`** | `LIBSND.A:vmanager.o` | `Global` | `sdk/libsnd/svm_voice_alloc.c` | Allocate best available SPU hardware voice by priority and envelope level |
| `0x8004E80C` | 134w | `func_8004E80C` | **`SpuVmDoAllocate`** | `LIBSND.A:vmanager.o` | `Global` | `sdk/libsnd/svm_kon.c` | Populate `_svm_voice[v]` state from `_svm_cur` and `_svm_tn` tone attributes |
| `0x8004EA24` | 46w | `func_8004EA24` | **`note2pitch`** | `LIBSND.A:vmanager.o` | `Global` | `sdk/libspu/tone_pitch_cached.c` | Convert `_svm_cur` note + tone center/shift to SPU pitch value |
| `0x8004EADC` | 64w | `func_8004EADC` | **`note2pitch2`** | `LIBSND.A:vmanager.o` | `Global` | `sdk/libspu/tone_pitch.c` | Convert explicit `(note, fine)` + tone center/shift to SPU pitch value |
| `0x8004EBDC` | 301w | `func_8004EBDC` | **`vmNoiseOn`** | `LIBSND.A:vmanager.o` | `Global` | `sdk/libspu/noise_voice.c` | Configure and trigger SPU noise generator on allocated voice |
| `0x8004F090` | 17w | `func_8004F090` | **`vmNoiseOff`** | `LIBSND.A:vmanager.o` | `Global` | `sdk/libspu/func_8004F090.c` | Disable SPU noise generator on voice (`v`) |
| `0x8004F0D4` | 52w | `func_8004F0D4` | **`SpuVmKeyOffNow`** | `LIBSND.A:vmanager.o` | `Global` | `sdk/libspu/voice_release.c` | Queue voice `v` bit in `_svm_okon1`/`_svm_okof1` for key-off |
| `0x8004F1A4` | 311w | `func_8004F1A4` | **`SpuVmKeyOnNow`** | `LIBSND.A:vmanager.o` | `Global` | `sdk/libspu/voice_trigger.c` | Write volume, pitch, sample start/loop addr, and ADSR to SPU voice registers and queue key-on |
| `0x8004F680` | 139w | `func_8004F680` | **`SpuVmPBVoice`** | `LIBSND.A:vmanager.o` | `Global` | `sdk/libspu/sequence_pitch_bend.c` | Apply pitch-bend offset to active voice `v` and write SPU pitch register |
| `0x8004F8AC` | 59w | `func_8004F8AC` | **`SpuVmPitchBend`** | `LIBSND.A:vmanager.o` | `Global` | `sdk/libspu/sequence_pitch_bend.c` | Apply pitch-bend across all active voices matching `(seq_sep_no, vab_id, prog)` |
| `0x8004F998` | 367w | `func_8004F998` | **`SpuVmSetSeqVol`** | `LIBSND.A:vmanager.o` | `Global` | `sdk/libspu/sequence_volume.c` | Set sequence master volume `(voll, volr)` and update all active voices on that sequence |
| `0x8004FF54` | 27w | `func_8004FF54` | **`SpuVmGetSeqVol`** | `LIBSND.A:vmanager.o` | `Global` | `sdk/libspu/sequence_volume_get.c` | Read sequence volume `(voll, volr)` from `_ss_score[sep][seq]` |
| `0x8004FFC0` | 20w | `func_8004FFC0` | **`SpuVmGetSeqLVol`** | `LIBSND.A:vmanager.o` | `Global` | `sdk/libspu/sequence_volume_channels_get.c` | Return sequence left volume (`voll`) |
| `0x80050010` | 20w | `func_80050010` | **`SpuVmGetSeqRVol`** | `LIBSND.A:vmanager.o` | `Global` | `sdk/libspu/sequence_volume_channels_get.c` | Return sequence right volume (`volr`) |
| `0x80050060` | 38w | `func_80050060` | **`SpuVmSeqKeyOff`** | `LIBSND.A:vmanager.o` | `Global` | `sdk/libspu/sequence_voice_stop.c` | Release all active voices belonging to `seq_sep_no` |
| `0x800500F8` | 44w | `func_800500F8` | **`SpuVmSelectToneAndVag`** | `LIBSND.A:vmanager.o` | `Global` | `sdk/libspu/voice_tone_list.c` | Select `VagAtr` tone entry and test `[min, max]` key range |
| `0x800501A8` | 352w | `func_800501A8` | **`SpuVmSetVol`** | `LIBSND.A:vmanager.o` | `Global` | `sdk/libspu/voice_update.c` | Update stereo volume/pan on active voices matching `(seq_sep_no, vab_id, prog)` |
| `0x80050728` | 49w | `func_80050728` | **`SpuVmVSetUp`** | `LIBSND.A:vm_vsu.o` | `Global` | `sdk/libspu/voice_note.c` | Load VAB header/program/tone table pointers into `_svm_vh`, `_svm_pg`, `_svm_tn` |
| `0x800507EC` | 31w | `func_800507EC` | **`SsSetReservedVoice`** | `LIBSND.A:vs_srv.o` | `Global` | `sdk/libspu/voice_count_set.c` | Set number of voices (`_Spu_voice_num`) managed by `LIBSND` (1..24) |
| `0x80050868` | 32w | `func_80050868` | **`SsVabClose`** | `LIBSND.A:vs_vab.o` | `Global` | `sdk/libspu/bank_release.c` | Free SPU RAM (`SpuFree`) and close VAB slot (`vab_id`) |
| `0x800508E8` | 31w | `func_800508E8` | **`SpuFree`** | `LIBSPU.A:s_m_f.o` | `Global` | `sdk/libspu/heap_free.c` | Mark SPU RAM block at `addr` as free and coalesce (`_spu_gcSPU`) |
| `0x80050964` | 192w | `func_80050964` | **`_spu_gcSPU`** | `LIBSPU.A:s_m_int.o` | `Global` | `sdk/libspu/heap_gc.c` | Garbage-collect and sort SPU RAM allocation table (`_spu_memList`) |
| `0x80050C64` | 27w | `func_80050C64` | **`SsVabFakeBody`** | `LIBSND.A:vs_vfb.o` | `Global` | `sdk/libspu/bank_reactivate.c` | Mark VAB body as already resident in SPU RAM and return `vab_id` |
| `0x80050CD0` | 12w | `func_80050CD0` | **`SsVabOpenHead`** | `LIBSND.A:vs_vh.o` | `Global` | `sdk/libspu/bank_open_wrappers.c` | Open VAB header and allocate SPU RAM via `SpuMalloc` (`SsVabOpenHeadWithMode`) |
| `0x80050D00` | 12w | `func_80050D00` | **`SsVabOpenHeadSticky`** | `LIBSND.A:vs_vh.o` | `Global` | `sdk/libspu/bank_open_wrappers.c` | Open VAB header at fixed SPU RAM `sbaddr` (`SsVabOpenHeadWithMode`) |
| `0x80050D30` | 12w | `func_80050D30` | **`SsVabFakeHead`** | `LIBSND.A:vs_vh.o` | `Global` | `sdk/libspu/bank_open_wrappers.c` | Open VAB header without allocating SPU RAM (`SsVabOpenHeadWithMode`) |
| `0x80050D60` | 255w | `func_80050D60` | **`SsVabOpenHeadWithMode`** | `LIBSND.A:vs_vh.o` | `Global` | `sdk/libspu/bank_transfer.c` | Parse `pBAV` VAB header, allocate SPU RAM, and build master VAG address table |
| `0x8005115C` | 178w | `func_8005115C` | **`SpuMalloc`** | `LIBSPU.A:s_m_m.o` | `Global` | `sdk/libspu/heap_malloc.c` | Allocate `size` bytes of SPU RAM from `_spu_memList` |

### 5.10 `LIBCARD.A` Memory Card BIOS Interface Library (`0x80051424..0x800514DC`) (9 functions)

| Address | Size | Current Symbol | Exact PsyQ SDK Symbol | PsyQ Archive:Object | Linkage | Current TU (`src/main/`) | Description / Notes |
|---|---:|---|---|---|---|---|---|
| `0x80051424` | 3w | `func_80051424` | **`_card_info`** | `LIBCARD.A:c171.o` | `Global` | `sdk/libapi/bios_service_table.c` | BIOS A0:0xAB `_card_info` |
| `0x80051434` | 3w | `func_80051434` | **`_card_load`** | `LIBCARD.A:c172.o` | `Global` | `sdk/libapi/bios_service_table.c` | BIOS A0:0xAC `_card_load` |
| `0x80051444` | 3w | `func_80051444` | **`_card_auto`** | `LIBCARD.A:c173.o` | `Global` | `sdk/libapi/bios_service_table.c` | BIOS A0:0xAD `_card_auto` |
| `0x80051454` | 3w | `func_80051454` | **`InitCARD`** | `LIBCARD.A:a74.o` | `Global` | `sdk/libapi/bios_service_table.c` | BIOS B0:0x4A `InitCARD` |
| `0x80051464` | 3w | `func_80051464` | **`StartCARD`** | `LIBCARD.A:a75.o` | `Global` | `sdk/libapi/bios_service_table.c` | BIOS B0:0x4B `StartCARD` |
| `0x80051474` | 3w | `func_80051474` | **`StopCARD`** | `LIBCARD.A:a76.o` | `Global` | `sdk/libapi/bios_service_table.c` | BIOS B0:0x4C `StopCARD` |
| `0x80051484` | 3w | `func_80051484` | **`_card_read`** | `LIBCARD.A:a79.o` | `Global` | `sdk/libapi/bios_service_table.c` | BIOS B0:0x4F `_card_read` |
| `0x80051494` | 14w | `func_80051494` | **`_card_clear`** | `LIBCARD.A:card.o` | `Global` | `sdk/libapi/bios_service_pair.c` | Call `_new_card()` and `_card_write(chan, 0x3F, 0)` (test-write block 63) |
| `0x800514CC` | 3w | `func_800514CC` | **`_new_card`** | `LIBCARD.A:a80.o` | `Global` | `sdk/libapi/bios_service_pair.c` | BIOS B0:0x50 `_new_card` (preceded at `0x800514BC` by `_card_write` B0:0x4E) |

---

## 6. Global Variables & Data Tables Catalog (`0x80011000..0x8001177B`, `0x800514DC..0x80061A78`)

### 6.1 Memory Map of Data & BSS Sections

| Section | Address Range | Size | Contents |
|---|---|---|---|
| `.rdata` | `0x80011000..0x8001177B` | `0x77C` | Read-only string literals and jump tables (`jtbl_800112C0`..`jtbl_800116B0`) |
| `.data` | `0x800514DC..0x800563F3` | `0x4F18` | Initialized tables: GTE trig/sqrt/atan LUTs, SPU reverb presets, Shift-JIS table, font/glyph tables, SDK data |
| `.sdata` | `0x800563F4..0x800565B3` | `0x1C0` | `$gp`-relative (`gp[0x00..0x6F]`) initialized small globals and short string constants |
| `.sbss` | `0x800565B4..0x80056753` | `0x1A0` | `$gp`-relative (`gp[0x70..0xD7]`) zero-initialized small globals |
| `.bss` | `0x80056754..0x80061A77` | `0xB324` | Large engine state structures (`context`, `ns`, `file_map`, `level_spawns`, `spawns`, `player`, `objects`, `handles`, GOOL globals `0x8006188C..0x80061A5F`) |

### 6.2 `.sdata` & `.sbss` `$gp`-Relative Game & SDK Globals (`0x800563F4..0x80056753`)

The R3000A global pointer is initialized by `__SN_ENTRY_POINT` to `_gp = 0x800563F8`. All variables in `.sdata` and `.sbss` are accessed via `lw/sw reg, offset($gp)`.

| Address | Current Symbol | Verified Name (`c1` / SDK) | Type | Subsystem | Description |
|---|---|---|---|---|---|
| `0x800563FC` | `D_800563FC` | **`cur_lid`** | `lid_t (s32)` | `core / main.c` | Current level ID (`LID_*`), initialized to `-1` |
| `0x80056400` | `D_80056400` | **`next_lid`** | `lid_t (s32)` | `core / main.c` | Next level ID to transition to (`-1` = none, `-2` = title) |
| `0x80056404` | `D_80056404` | **`paused`** | `s32` | `core / main.c` | Game pause state (`0` = unpaused, `1` = paused) |
| `0x8005640C` | `D_8005640C` | **`use_cd`** | `s32` | `core / main.c` | Enable CD-ROM filesystem & paging (`1` in retail) |
| `0x80056410` | `D_80056410` | **`pause_B_pressed`** | `s32` | `core / main.c` | Button state flag during pause screen |
| `0x80056420` | `D_80056420` | **`ns_StringTable`** | `char[64]` | `ns / ns.c` | Base-64 EID character alphabet (`0..9A..Za..z_`) |
| `0x80056428` | `D_80056428` | **`bonus_return`** | `s32` | `core / main.c` | Returning from Tawna/Brio/Cortex bonus round flag |
| `0x8005642C` | `D_8005642C` | **`rcnt_stopped`** | `s32` | `gpu / psx/gpu.c` | Flag indicating `RCntCNT2` is stopped during memory card I/O |
| `0x80056440` | `D_80056440` | **`fade_step`** | `s32` | `gfx / misc.c` | Screen brightness fade step per frame (default `32`) |
| `0x8005644C` | `D_8005644C` | **`ripple_amp`** | `s32` | `shader / misc.c` | Water-ripple vertex shader amplitude |
| `0x80056450` | `D_80056450` | **`ripple_freq`** | `s32` | `shader / misc.c` | Water-ripple vertex shader frequency |
| `0x8005645C` | `D_8005645C` | **`lightning_state`** | `s32` | `shader / misc.c` | Lightning shader state counter |
| `0x80056460` | `D_80056460` | **`dark_cone_rot`** | `s32` | `shader / misc.c` | Darkness shader light-cone angle |
| `0x80056480` | `D_80056480` | **`crash`** | `gool_object*` | `gool / gool.c` | Pointer to active Crash (player) GOOL object |
| `0x80056488` | `D_80056488` | **`obj_zone_colors`** | `s32` | `gool / gool.c` | Zone color inheritance mode |
| `0x80056490` | `D_80056490` | **`cur_zone`** | `entry*` | `level / level.c` | Pointer to currently active `ZDAT` zone entry |
| `0x80056494` | `D_80056494` | **`cur_path`** | `zone_path*` | `level / level.c` | Pointer to currently active camera `zone_path` |
| `0x80056498` | `D_80056498` | **`cur_progress`** | `s32` | `level / level.c` | Current fixed-point progress along `cur_path` |
| `0x800564A4` | `D_800564A4` | **`cam_speed`** | `s32` | `cam / cam.c` | Current camera path movement speed |
| `0x800564BC` | `D_800564BC` | **`wall_bitmap`** | `u32*` | `solid / solid.c` | Pointer to 32x32 solid wall occupancy bitmap (`BinfInit`) |
| `0x800564D8` | `D_800564D8` | **`seed_a`** | `u32` | `math / math.c` | LCG random number generator A state (`randa` / `sranda`, default `12345`) |
| `0x800564DC` | `D_800564DC` | **`seed_b`** | `u32` | `math / math.c` | LCG random number generator B state (`randb` / `srandb`, default `12345`) |
| `0x800564E0` | `D_800564E0` | **`cd_name`** | `char[8]` | `cd / psx/cdr.c` | ISO-9660 primary volume magic `"CD001"` |
| `0x800564E8` | `D_800564E8` | **`iso_dot_rec_name`** | `char[4]` | `cd / psx/cdr.c` | ISO-9660 current directory string `"."` |
| `0x800564EC` | `D_800564EC` | **`iso_ddot_rec_name`** | `char[8]` | `cd / psx/cdr.c` | ISO-9660 parent directory string `".."` |
| `0x800564F4` | `D_800564F4` | **`midi_state`** | `s32` | `midi / midi.c` | Current MIDI/SEP playback state |
| `0x800564F8` | `D_800564F8` | **`midi_seq_num`** | `s16` | `midi / midi.c` | Active `LIBSND` `sep_access_num` handle |
| `0x800564FC` | `D_800564FC` | **`midi_vab_id`** | `s16` | `midi / midi.c` | Active `LIBSND` `vab_id` handle |
| `0x80056500` | `D_80056500` | **`title_once`** | `s32` | `title / title.c` | First-boot flag (`1` until SCEA/Universal splash shown) |
| `0x80056504` | `D_80056504` | **`game_over_zone_name`** | `char[8]` | `title / title.c` | `"0b_pZ"` Game Over screen zone EID string |
| `0x8005650C` | `D_8005650C` | **`main_menu_zone_name`** | `char[8]` | `title / title.c` | `"0c_pZ"` Main Menu zone EID string |
| `0x80056514` | `D_80056514` | **`naughty_dog_zone_name`** | `char[8]` | `title / title.c` | `"0d_pZ"` Naughty Dog logo zone EID string |
| `0x8005651C` | `D_8005651C` | **`load_menu_zone_name`** | `char[8]` | `title / title.c` | `"0e_pZ"` Password / Load Game zone EID string |
| `0x80056524` | `D_80056524` | **`options_menu_zone_name`** | `char[8]` | `title / title.c` | `"0f_pZ"` Options Menu zone EID string |
| `0x8005652C` | `D_8005652C` | **`island_1b_zone_name`** | `char[8]` | `title / title.c` | `"1e_pZ"` Island 1 (late) map zone EID string |
| `0x80056534` | `D_80056534` | **`island_1a_zone_name`** | `char[8]` | `title / title.c` | `"1a_pZ"` Island 1 (early) map zone EID string |
| `0x8005653C` | `D_8005653C` | **`island_2_zone_name`** | `char[8]` | `title / title.c` | `"2b_pZ"` Island 2 map zone EID string |
| `0x80056544` | `D_80056544` | **`island_3_zone_name`** | `char[8]` | `title / title.c` | `"3a_pZ"` Island 3 map zone EID string |
| `0x8005654C` | `D_8005654C` | **`scea_universal_zone_name`** | `char[8]` | `title / title.c` | `"0a_pZ"` SCEA / Universal splash zone EID string |
| `0x80056554` | `D_80056554` | **`mdat_fmt_name`** | `char[8]` | `title / title.c` | `"%cMapP"` format string for `MDAT` EIDs |
| `0x8005655C` | `D_8005655C` | **`mdat_default_name`** | `char[8]` | `title / title.c` | `"0MapP"` template string for `MDAT` EIDs |
| `0x80056564` | `D_80056564` | **`card`** | `card_struct*` | `card / psx/card.c` | Pointer to allocated memory card state structure |
| `0x80056568` | `D_80056568` | **`card_new_device`** | `s32` | `card / psx/card.c` | New memory card inserted flag (initialized to `1`) |
| `0x8005656C` | `D_8005656C` | **`prev_card_flags`** | `u32` | `card / psx/card.c` | Previous frame `card->flags` (`-1` initial) |
| `0x80056570` | `D_80056570` | **`prev_card_state`** | `s32` | `card / psx/card.c` | Previous frame `card->state` (`-1` initial) |
| `0x80056598` | `D_80056598` | **`_AllocRestBlockTop`** | `void*` | `sdk / MALLOC4.O` | Top of unallocated heap arena |
| `0x800565A0` | `D_800565A0` | **`_AllocMaxBlockSize`** | `u32` | `sdk / MALLOC4.O` | Remaining bytes in heap arena |
| `0x800565A8` | `D_800565A8` | **`max_heap`** | `u32` | `sdk / MALLOC4.O` | Total heap size passed to `InitHeap` |
| `0x800565B0` | `D_800565B0` | **`AllocAreaFlag`** | `s32` | `sdk / MALLOC4.O` | Heap initialized flag |
| `0x800565B4` | `D_800565B4` | **`ticks_elapsed`** | `u32` | `gpu / psx/init.c` | Global `RCntCNT2` tick counter incremented by `RIncTickCount` |
| `0x800565B8` | `D_800565B8` | **`rcnt_event`** | `s32` | `core / psx/init.c` | `RCntCNT2` event descriptor returned by `OpenEvent` |
| `0x800565DC` | `D_800565DC` | **`wall_cache`** | `void*` | `solid / solid.c` | Plotted wall cache pointer (`BinfInit`) |
| `0x8005663C` | `D_8005663C` | **`sfx_vol`** | `u32` | `audio / audio.c` | Sound effects master volume (`0..255`) |
| `0x80056640` | `D_80056640` | **`mus_vol`** | `u32` | `audio / midi.c` | Music master volume (`0..255`) |
| `0x80056678` | `D_80056678` | **`title_not_seen`** | `s32` | `title / title.c` | Cached `title_once` flag during `TitleLoadNextState` |
| `0x8005668C` | `D_8005668C` | **`save_id`** | `u32` | `card / psx/card.c` | Random 6-digit major save ID (`0..999998`) from `randb` |
| `0x80056690` | `D_80056690` | **`file_is_new`** | `s32` | `card / psx/card.c` | Flag indicating newly created save file in `CardPartWrite` |
| `0x800566A8` | `D_800566A8` | **`cur_pbak_header`** | `pbak_header*` | `pbak / pbak.c` | Pointer to currently active demo `pbak_header` |
| `0x800566C4` | `D_800566C4` | **`edesc_s_end_io`** | `s32` | `card / psx/card.c` | `SwCARD` `EvSpIOE` (`0x0004`) event descriptor |
| `0x800566C8` | `D_800566C8` | **`edesc_s_error`** | `s32` | `card / psx/card.c` | `SwCARD` `EvSpERROR` (`0x8000`) event descriptor |
| `0x800566CC` | `D_800566CC` | **`edesc_s_timeout`** | `s32` | `card / psx/card.c` | `SwCARD` `EvSpTIMOUT` (`0x0100`) event descriptor |
| `0x800566D0` | `D_800566D0` | **`edesc_s_newdev`** | `s32` | `card / psx/card.c` | `SwCARD` `EvSpNEW` (`0x2000`) event descriptor |
| `0x800566E0` | `D_800566E0` | **`title`** | `title_struct*` | `title / title.c` | Pointer to allocated `title_struct` (`TitleInit`) |
| `0x800566EC` | `D_800566EC` | **`edesc_h_end_io`** | `s32` | `card / psx/card.c` | `HwCARD` `EvSpIOE` (`0x0004`) event descriptor |
| `0x800566F0` | `D_800566F0` | **`edesc_h_error`** | `s32` | `card / psx/card.c` | `HwCARD` `EvSpERROR` (`0x8000`) event descriptor |
| `0x800566F8` | `D_800566F8` | **`edesc_h_timeout`** | `s32` | `card / psx/card.c` | `HwCARD` `EvSpTIMOUT` (`0x0100`) event descriptor |
| `0x800566FC` | `D_800566FC` | **`edesc_h_newdev`** | `s32` | `card / psx/card.c` | `HwCARD` `EvSpNEW` (`0x2000`) event descriptor |
| `0x80056704` | `D_80056704` | **`cur_pbak_frame`** | `pbak_frame*` | `pbak / pbak.c` | Pointer to current demo playback frame |

### 6.3 Major `.data` & `.bss` Structures and GOOL Engine Globals (`0x80052B64..0x80061A78`)

| Address | Current Symbol | Verified Name (`c1` / SDK) | Type / Size | Subsystem | Description |
|---|---|---|---|---|---|
| `0x80052B64` | `D_80052B64` | **`move_states`** | `gool_move_state[16]` | `gool / gool.c` | Player movement state table (accel, decel, max speed, tangent speed) |
| `0x80052C24` | `D_80052C24` | **`accel_states`** | `gool_accel_state[7]` | `gool / gool.c` | Player acceleration state parameters |
| `0x80053890` | `D_80053890` | **`sjis_ascii_table`** | `u8[]` | `card / psx/card.c` | Shift-JIS `0x81xx` punctuation to ASCII lookup table (`CardShiftJisToAscii`) |
| `0x800539A0` | `D_800539A0` | **`sin_table`** | `u16[1024]` | `math / r3000a.s` | Fixed-point sine/cosine lookup table used by `sin` (`0x8003905C`) and `cos` (`0x800390D0`) |
| `0x80054754` | `D_80054754` | **`GEnv`** | `DRAWENV/DISPENV` | `sdk / LIBGPU:sys.o` | Internal `LIBGPU` graphics environment state |
| `0x80054DA4` | `D_80054DA4` | **`sq_table`** | `u8[512]` | `sdk / LIBGTE:sqrt0.o` | `SquareRoot0` mantissa lookup table |
| `0x80054FA4` | `D_80054FA4` | **`atan_table`** | `s16[1025]` | `sdk / LIBGTE:ratan.o` | `ratan2` arctangent lookup table |
| `0x80055960` | `D_80055960` | **`_spu_rev_param`** | `SpuReverbAttr[]` | `sdk / LIBSPU:s_srmp.o` | Sony SPU hardware reverb preset table (Room, Studio, Hall, Space, Echo, Delay, Pipe) |
| `0x80056804` | `D_80056804` | **`voices`** | `audio_voice[24]` | `audio / audio.c` | Active spatial 3D sound-effect voice array (`0x6DC` bytes) |
| `0x8005703C` | `D_8005703C` | **`card_filename`** | `char[24]` | `card / psx/card.c` | Active memory card save filename buffer (initialized to `"~inv!"`) |
| `0x8005726C` | `D_8005726C` | **`cams`** | `cam_struct[3]` | `cam / gfx.c` | Camera transform/matrix state array |
| `0x800577BC` | `D_800577BC` | **`SearchPoint`** | `void*` | `sdk / MALLOC4.O` | Next-fit free-listrover pointer in `malloc` |
| `0x800577C4` | `D_800577C4` | **`m_rot`** | `MATRIX` | `gfx / gfx.c` | Global rotation matrix (`32` bytes) |
| `0x800577E4` | `D_800577E4` | **`m_view`** | `MATRIX` | `gfx / gfx.c` | Global camera view matrix (`32` bytes) |
| `0x80057804` | `D_80057804` | **`m_light`** | `MATRIX` | `gfx / gfx.c` | Global directional light matrix (`32` bytes) |
| `0x80057824` | `D_80057824` | **`m_color`** | `MATRIX` | `gfx / gfx.c` | Global light color matrix (`32` bytes) |
| `0x80057914` | `D_80057914` | **`pads`** | `pad[2]` | `pad / pad.c` | Joypad state and button-edge structures for ports 1 and 2 |
| `0x80057F38` | `D_80057F38` | **`TopAllocArea`** | `void*` | `sdk / MALLOC4.O` | Base pointer of `MALLOC4.O` heap block list |
| `0x80058360` | `D_80058360` | **`Snd_FnTable`** | `void*[37]` | `sdk / LIBSND:sepinit.o` | SMF/SEP status & Control Change handler function pointer table populated by `SsSepOpen` |
| `0x80058400` | `D_80058400` | **`context`** | `gfx_context_db` | `gpu / psx/gpu.c` | Double-buffered GPU `DISPENV`/`DRAWENV`, primitive buffer pointers, and 2048-entry ordering tables (`0x4128` bytes) |
| `0x80058EF8` | `D_80058EF8` | **`_ss_score`** | `ss_score*[32]` | `sdk / LIBSND` | `LIBSND` active sequence/SEP track table pointers |
| `0x80059100` | `D_80059100` | **`_svm_voice`** | `SpuVmVoice[24]` | `sdk / LIBSND:vmanager.o` | `LIBSND` 24-voice virtual voice manager state array |
| `0x8005C528` | `D_8005C528` | **`ns`** | `ns_struct` | `ns / ns.h` | Primary Naughty Dog paging system (`NS`) state structure (`ldat_eid`, `nsd`, `nsf`, `cur_ps`, physical/virtual page pools) |
| `0x8005CF68` | `D_8005CF68` | **`texture_pages`** | `page_struct[16]` | `ns / ns.c` | VRAM texture page allocation and reference table |
| `0x8005D388` | `D_8005D388` | **`audio_pages`** | `page_struct[16]` | `ns / ns.c` | SPU audio page allocation and reference table |
| `0x8005E03C` | `D_8005E03C` | **`file_map`** | `ns_fileinfo[65]` | `cd / psx/cdr.c` | ISO-9660 sector number and byte length table for `S0000000.NSD`/`.NSF`..`S0000040.NSD`/`.NSF` |
| `0x8005E348` | `D_8005E348` | **`level_spawns`** | `u16[1784]` | `gool / gool.c` | Cross-level persistent `(lid << 9) | entity_id` spawn history table |
| `0x8005FF58` | `D_8005FF58` | **`spawns`** | `u8[3664]` | `gool / gool.c` | Per-entity spawn status bitflags for the current level (`spawns[entity_id]`) |
| `0x80060DB0` | `D_80060DB0` | **`player`** | `gool_object*` | `gool / gool.c` | Pointer to allocated Crash Bandicoot player object (`sizeof(gool_object) + 0x100`) |
| `0x80060DB4` | `D_80060DB4` | **`objects`** | `gool_object*` | `gool / gool.c` | Pointer to pool of 96 GOOL objects allocated by `GoolInitAllocTable` |
| `0x80060DB8` | `D_80060DB8` | **`free_objects`** | `gool_handle` | `gool / gool.c` | Root handle of the free GOOL object list |
| `0x80060DC0` | `D_80060DC0` | **`handles`** | `gool_handle[8]` | `gool / gool.c` | 8 root GOOL object-tree handles (process groups 0..7) |
| `0x80060E00` | `D_80060E00` | **`savestate`** | `level_state` | `level / level.c` | Saved checkpoint/bonus-round state (`LevelSaveState` / `LevelRestart`, `0xA8C` bytes) |
| `0x8006188C` | `D_8006188C` | **`cur_display_flags`** | `u32` | `gool / globals.h` | Current frame display/animate/render bitflags (`gp_global[0]`) |
| `0x80061890` | `D_80061890` | **`next_display_flags`** | `u32` | `gool / globals.h` | Next frame display/animate/render bitflags |
| `0x8006189C` | `D_8006189C` | **`fade_counter`** | `s32` | `gool / globals.h` | Screen fade counter (`< 0` fading out, `> 0` fading in, `0` steady) |
| `0x800618B0` | `D_800618B0` | **`cur_lid_ro`** | `lid_t` | `gool / globals.h` | Read-only mirror of `cur_lid` exposed to GOOL bytecode |
| `0x800618B4` | `D_800618B4` | **`bool_one`** | `s32` | `gool / globals.h` | Constant `1` exposed to GOOL bytecode |
| `0x800618C8` | `D_800618C8` | **`ticks_cur_frame`** | `u32` | `gool / globals.h` | Elapsed ticks in current frame (`17` = 60Hz, `34` = 30Hz) |
| `0x800618D8` | `D_800618D8` | **`pbak_state`** | `s32` | `gool / globals.h` | Demo playback state (`0` = off, `1` = recording, `2` = playing) |
| `0x800618E0` | `D_800618E0` | **`life_count`** | `s32` | `gool / globals.h` | Player current extra lives count (shifted `<< 8` in GOOL) |
| `0x800618E4` | `D_800618E4` | **`health`** | `s32` | `gool / globals.h` | Aku Aku mask / health count |
| `0x800618E8` | `D_800618E8` | **`fruit_count`** | `s32` | `gool / globals.h` | Wumpa fruit count (`0..99`, shifted `<< 8` in GOOL) |
| `0x800618EC` | `D_800618EC` | **`cortex_count`** | `s32` | `gool / globals.h` | Collected Cortex bonus tokens in current level |
| `0x800618F0` | `D_800618F0` | **`brio_count`** | `s32` | `gool / globals.h` | Collected Brio bonus tokens in current level |
| `0x800618F4` | `D_800618F4` | **`tawna_count`** | `s32` | `gool / globals.h` | Collected Tawna bonus tokens in current level |
| `0x800618F8` | `D_800618F8` | **`checkpoint_id`** | `u32` | `gool / globals.h` | Entity ID of last activated checkpoint box (`-1` if none) |
| `0x80061900` | `D_80061900` | **`mono`** | `s32` | `gool / globals.h` | Audio output mode (`0` = stereo, `1` = mono) |
| `0x80061904` | `D_80061904` | **`game_state`** | `s32` | `gool / globals.h` | High-level game state (`0` = playing, `0x100` = game over, `0x200` = title, `0x300` = cutscene) |
| `0x80061908` | `D_80061908` | **`new_gem_flag`** | `s32` | `gool / globals.h` | Flag set when a new gem is earned on level completion |
| `0x80061914` | `D_80061914` | **`cur_map_level`** | `s32` | `gool / globals.h` | Currently selected level node on the 3D island map |
| `0x80061918` | `D_80061918` | **`levels_unlocked`** | `u32` | `gool / globals.h` | Number/bitmask of levels unlocked on the island map |
| `0x8006191C` | `D_8006191C` | **`title_state`** | `s32` | `gool / globals.h` | Active title/menu screen state (`5` = main menu, `6` = options, `8` = ND logo, `10` = SCEA, `12` = game over, `13/14` = load/save, `15` = map) |
| `0x80061920` | `D_80061920` | **`title_pause_state`** | `s32` | `gool / globals.h` | Title menu sub-state |
| `0x8006192C` | `D_8006192C` | **`saved_item_pool1`** | `u32` | `gool / globals.h` | Saved bitmask of collected gems/keys (low word) |
| `0x80061930` | `D_80061930` | **`saved_item_pool2`** | `u32` | `gool / globals.h` | Saved bitmask of collected gems/keys (high word) |
| `0x80061938` | `D_80061938` | **`box_count`** | `s32` | `gool / globals.h` | Boxes smashed in current level (shifted `<< 8`) |
| `0x80061940` | `D_80061940` | **`item_pool1`** | `u32` | `gool / globals.h` | Current bitmask of collected gems/keys (low word) |
| `0x80061944` | `D_80061944` | **`item_pool2`** | `u32` | `gool / globals.h` | Current bitmask of collected gems/keys (high word) |
| `0x8006195C` | `D_8006195C` | **`island_cam_rot_x`** | `s32` | `gool / globals.h` | World map camera X rotation angle |
| `0x80061964` | `D_80061964` | **` pause_obj`** | `gool_object*` | `gool / globals.h` | Pointer to spawned pause-menu HUD GOOL object |
| `0x80061984` | `D_80061984` | **`death_count`** | `s32` | `gool / globals.h` | Deaths since last checkpoint (used for dynamic Aku Aku assistance) |
| `0x8006198C` | `D_8006198C` | **`init_life_count`** | `s32` | `gool / globals.h` | Initial life count (`4 << 8`) |
| `0x80061994` | `D_80061994` | **`level_count`** | `u32` | `gool / globals.h` | Completed levels count (`CardSaveGlobals`) |
| `0x800619B0` | `D_800619B0` | **`gem_count`** | `u32` | `gool / globals.h` | Collected gems count (`CardSaveGlobals`) |
| `0x800619B4` | `D_800619B4` | **`key_count`** | `u32` | `gool / globals.h` | Collected keys count (`CardSaveGlobals`) |
| `0x800619C8` | `D_800619C8` | **`percent_complete`** | `u32` | `gool / globals.h` | Completion percentage (`0..100`) formatted into `"Crash (%d%%)"` save title |
| `0x800619CC` | `D_800619CC` | **`card_icon`** | `entry*` | `gool / globals.h` | Pointer to `MDAT`/`TGEO` entry holding memory card save icons |
| `0x800619EC` | `D_800619EC` | **`card_str`** | `void*` | `gool / globals.h` | Pointer to 15-slot string buffer for memory card UI (`"EMPTY"`, `"PART %d of %d"`) |
| `0x800619F0` | `D_800619F0` | **`card_partinfos`** | `u32[14]` | `gool / globals.h` | Per-slot status/progress bitfields for memory card screen |
| `0x80061A28` | `D_80061A28` | **`card_flags_ro`** | `u32` | `gool / globals.h` | Read-only mirror of `card->flags` exposed to GOOL |
| `0x80061A2C` | `D_80061A2C` | **`card_part_count_ro`** | `u32` | `gool / globals.h` | Read-only mirror of `card->part_count` exposed to GOOL |
| `0x80061A5C` | `D_80061A5C` | **`doctor_cortex_obj`** | `gool_object*` | `gool / globals.h` | Boss / cutscene object reference slot |

