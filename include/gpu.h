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

u32 get_tw(GpuRect *rect);

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

/* PutDrawEnv copies exactly 0x5C bytes, including the command packet. */
typedef struct GpuDrawing {
    GpuDrawEnv env;
    u32 packet[16];
} GpuDrawing;

typedef struct GpuTile {
    GpuPacketHeader header;
    GpuRect rect;
} GpuTile;

GpuDrawEnv *SetDefDrawEnv(GpuDrawEnv *env, s32 x, s32 y, s32 w, s32 h);
void TermPrim(u32 *packet);
void SetBlockFill(GpuPacketHeader *packet);
void DrawPrim(GpuPacketHeader *packet);
void *PutDrawEnv(GpuDrawing *drawing);
void DrawOTagEnv(s32 tag, GpuDrawing *drawing);
void SetDrawEnv(u32 *packet, GpuDrawing *drawing);

#endif
