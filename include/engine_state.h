#ifndef CRASH_ENGINE_STATE_H
#define CRASH_ENGINE_STATE_H

#include "common.h"

/* Partial prefix of the 0x6F4-byte allocation in func_8003CE20.
 * The allocation size is not evidence for the unknown trailing fields. */
typedef struct EngineState {
    s32 word00, word04, word08, word0C, word10, word14, word18;
} EngineState;

typedef struct EngineTileCoords {
    s32 x, y, page;
} EngineTileCoords;

typedef struct EngineTileCell {
    u32 x : 4;
    u32 y : 4;
    s32 tile_x : 9;
    s32 tile_y : 8;
    u32 page : 2;
    u32 pad0 : 5;
    u32 clut : 9;
    s32 off_y : 14;
    u32 pad1 : 9;
    s32 off_x : 14;
    u32 pad2 : 18;
} EngineTileCell;

typedef struct EngineDrawModePacket {
    u32 words[3];
} EngineDrawModePacket;

/* Separate allocation in func_80031BAC; last observed word is at 0x35D4. */
typedef struct EngineMode25State {
    /* Encoded map reference, derived words, and metadata copied by 31EB4. */
    u32 word00;
    s32 word04, word08, word0C, word10, word14, word18;
    EngineTileCoords coords[528];
    EngineTileCell cells[528];
    u32 word319C;
    u16 cluts[480];
    u16 word3560, word3562, word3564, word3566;
    EngineDrawModePacket draw_modes[4];
    s32 word3598, word359C;
    /* func_80031BF8 copies the word at D_8006194C into both fields.
     * The instructions establish word width, not pointer semantics. */
    u32 word35A0, word35A4;
    u8 pad35A8[0x28];
    s32 word35D0, word35D4;
} EngineMode25State;

/* File I/O cleanup: descriptor address, creation flag, and path to remove
 * when an operation fails. The writer stores its path in the third word. */
typedef struct EngineFileRequest {
    s32 *resource;
    s32 *pending;
    char *path;
} EngineFileRequest;
typedef EngineFileRequest EngineEventRequest;

typedef struct EngineByteRecord {
    u8 data[6];
} EngineByteRecord;

/* Both save routines process exactly 0x80 bytes. The checksum covers the
 * whole record with its final word cleared; unknown payload bytes stay opaque. */
typedef struct EngineSaveRecord {
    u32 word00, word04, word08, word0C, word10, word14;
    u32 word18, word1C, word20, word24;
    u8 pad28[0x54];
    u32 checksum;
} EngineSaveRecord;

/* The writer emits a 0x80-byte file header, followed by three 0x80-byte
 * icon images. Its title is converted to 32 two-byte characters. */
typedef struct EngineCardHeader {
    u8 magic[2], icons, blocks;
    char title[64];
    u8 reserved[0x1C];
    u16 palette[16];
} EngineCardHeader;

/* The same working block is reused for the file header and saved state. */
typedef union EngineCardBlock {
    EngineCardHeader header;
    EngineSaveRecord record;
    u8 bytes[0x80];
} EngineCardBlock;

/* Directory enumeration advances by 0x28. Only the record stride and its
 * use as the filename passed to the BIOS are currently recovered. */
typedef struct EngineDirectoryRecord {
    u8 bytes[0x28];
} EngineDirectoryRecord;

/* Selected file slots advance by 0x4C; +8 indexes the directory records. */
typedef struct EngineDirectorySlot {
    s32 word00;
    u32 word04;
    s32 record_index;
    u8 pad0C[0x40];
} EngineDirectorySlot;

/* These arrays end at the 0x6F4-byte lifecycle allocation's boundary. Keep
 * this view separate from the independent 0x35D8-byte mode-25 allocation. */
typedef struct EngineDirectoryState {
    EngineState prefix;
    s32 empty_scan_count, record_count, record_cursor;
    EngineDirectorySlot slots[15];
    EngineDirectoryRecord records[15];
} EngineDirectoryState;

/* GCC 2.6.3 emits tentative storage in declaration order. The owner defines
 * these globals in retail order instead of declaring them ahead of that list. */
#ifndef CRASH_ENGINE_STATE_STORAGE
extern s32 D_80056500, D_80056678;
extern char D_80056504[8], D_8005650C[8], D_80056514[8], D_8005651C[8];
extern char D_80056524[8], D_8005652C[8], D_80056534[8], D_8005653C[8];
extern char D_80056544[8], D_8005654C[8], D_80056554[8], D_8005655C[8];
extern EngineState *D_80056564;
extern EngineMode25State *D_800566E0;
#endif
void func_8003AE08(EngineFileRequest *request);
void func_8003AED8(EngineFileRequest *request);
void func_80031D50(s32 *reference, s32 mode);
s32 func_80031BF8(void);
void func_8003BE40(EngineSaveRecord *record);
s32 func_8003BF34(EngineSaveRecord *record);
s32 func_8003C714(const char *path, EngineDirectoryRecord *entries);

#endif
