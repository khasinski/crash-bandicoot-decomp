#ifndef CRASH_GPU_H
#define CRASH_GPU_H

#include "common.h"

/* Word view used when inserting packets into a DMA chain. */
typedef struct GpuPacketTag {
    u32 next : 24;
    u32 length : 8;
} GpuPacketTag;

/* Little-endian DMA tag followed by the GPU colour/command word.
 * length counts the 32-bit words following the tag, excluding the tag itself.
 */
typedef struct GpuPacketHeader {
    u8 next[3];
    u8 length;
    u8 color[3];
    u8 command;
} GpuPacketHeader;

/* Layouts reconstructed from accesses in the retail environment initialisers. */
typedef struct GpuRect {
    s16 x, y, w, h;
} GpuRect;

u32 func_8004158C(GpuRect *rect);

typedef struct GpuDrawEnv {
    GpuRect clip;
    s16 offset_x, offset_y;
    GpuRect texture_window;
    u16 texture_page;
    u8 dither, draw_to_display, clear_background;
    u8 r, g, b;
} GpuDrawEnv;

typedef struct GpuDisplayEnv {
    GpuRect display;
    GpuRect screen;
    u8 interlaced, rgb24, pad12, pad13;
} GpuDisplayEnv;

#endif
