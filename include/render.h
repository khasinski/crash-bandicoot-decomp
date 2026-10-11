#ifndef CRASH_RENDER_H
#define CRASH_RENDER_H

#include "common.h"

/* Partial layout established by accesses at 0x74, 0x78 and 0x88.
 * Keep unidentified fields named by offset until their meaning is confirmed.
 */
typedef struct RenderBuffer {
    u8 pad00[0x74];
    s32 word74;
    s32 word78;
    u8 pad7C[0xC];
    u32 ordering_table[0x800];
} RenderBuffer;

#endif
