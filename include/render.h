#ifndef CRASH_RENDER_H
#define CRASH_RENDER_H

#include "gpu.h"

/* Layout established by buffer swap (0x04, 0x18) and cursor/table access.
 * Keep unidentified fields named by offset until their meaning is confirmed.
 */
typedef struct RenderBuffer {
    u32 word00;
    GpuDisplayEnv display;
    GpuDrawing drawing;
    s32 word74;
    s32 word78;
    u8 pad7C[0xC];
    u32 ordering_table[0x800];
} RenderBuffer;

typedef struct RenderTransformWords {
    u16 word00, word02, word04;
    s16 word06, word08, word0A;
    u16 word0C, word0E, word10;
} RenderTransformWords;

/* Shared context word selected by mode update and read by func_80017790. */
typedef struct RenderContextView {
    u8 pad00[0x114];
    s32 word114;
} RenderContextView;

/* Distance plus the nine halfwords loaded into GTE controls 16..20.
 * The target's four-byte alignment provides the final halfword of padding
 * read by the setter's last 32-bit load. */
typedef struct RenderProjectionState {
    s32 distance;
    s16 matrix[9];
} RenderProjectionState;

/* Projection lies 0x6C bytes after the transform reset by func_800180A0.
 * Other words in that interval are accessed through existing named aliases. */
typedef struct RenderCameraPrefix {
    s32 transform[9];
    u8 pad24[0x48];
    RenderProjectionState projection;
} RenderCameraPrefix;

extern RenderBuffer *D_80058404[3];
extern RenderBuffer *D_8005840C;
extern RenderContextView *D_8005C53C;
extern RenderProjectionState D_800578D0;

void func_80016DCC(RenderBuffer *buffer);
void func_80016DF8(s32 amount);
s32 *func_80016E18(void);
void func_800172E8(void);
void func_80017968(RenderTransformWords *, RenderTransformWords *);
void func_80017790(void);
void func_800180A0(s32 *transform);

#endif
