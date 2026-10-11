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

extern RenderBuffer *D_80058404[3];
extern RenderBuffer *D_8005840C;

void func_80016DCC(RenderBuffer *buffer);
void func_80016DF8(s32 amount);
s32 *func_80016E18(void);
void func_800172E8(void);
void func_80017968(RenderTransformWords *, RenderTransformWords *);

#endif
