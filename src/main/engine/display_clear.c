/* GCC_VERSION: 2.6.3 */
#include "render.h"
extern s32 D_80057960;
typedef GpuDrawing Drawing;
typedef GpuTile Tile;

typedef struct {
    s32 count;
    RenderBuffer *active[3];
    RenderBuffer buffers[2];
} RenderSystem;

extern RenderSystem D_80058400;
extern s32 D_80056710;
extern s32 frame_counter;

void *LIBC_Malloc(s32);
void LIBC_Free(void *);
void func_8003CE20(void);
void func_8003CEA8(void);
void func_8003D680(s32);
GpuDisplayEnv *func_8003F4D8(GpuDisplayEnv *, s32, s32, s32, s32);
s32 func_8003FDC0(s32);
s32 func_8004002C(s32);
s32 func_800401C0(s32);
s32 func_8004025C(s32);
void *func_80040A0C(GpuDisplayEnv *);

__inline__ void func_8001696C(void) {
    Drawing drawing;
    Tile tile;
    func_8003F408(&drawing.env,0,0,1024,512);
    drawing.env.draw_to_display = 1;
    func_80040834(&drawing);
    func_8003F7D8((u32 *)&tile);
    func_8003FA14(&tile.header);
    tile.rect.w = 1023;
    tile.rect.h = 511;
    tile.header.color[0] = 0;
    tile.header.color[1] = 0;
    tile.header.color[2] = 0;
    tile.rect.x = 0;
    tile.rect.y = 0;
    func_80040760(&tile.header);
}

void func_800169F8(void) {
    Drawing drawing;
    Tile tile;
    func_8003F7D8((u32 *)&tile);
    func_8003FA14(&tile.header);
    tile.rect.w = 512;
    tile.rect.h = 240;
    tile.header.color[0] = 0;
    tile.header.color[1] = 0;
    tile.header.color[2] = 0;
    tile.rect.x = D_80058400.active[1]->drawing.env.clip.x;
    tile.rect.y = 0;
    func_80040760(&tile.header);
    func_8004025C(0);
}

void func_80016A6C(void) {
    s32 i;
    RenderBuffer *buffer;

    D_80057960 = 0;
    func_8003FDC0(0);
    func_8004002C(0);
    func_8001696C();
    D_80058400.count = 2;
    for (i = 0; i < D_80058400.count; i++) {
        buffer = &D_80058400.buffers[i];
        buffer->word00 = i;
        *(s32 *)&buffer->pad7C[0] = 0;
        func_8003F4D8(&buffer->display, i << 9, 0, 512, 240);
        func_8003F408(&buffer->drawing.env, i << 9, 12, 512, 216);
        buffer->drawing.env.offset_x = (i << 9) + 256;
        buffer->drawing.env.offset_y = 120;
        buffer->drawing.env.dither = 1;
        if (i == 0) {
            D_80058400.active[2] = buffer;
            D_80058400.active[0] = buffer;
        }
        if (i == 1) {
            D_80058400.active[1] = buffer;
        }
        *(s32 *)&buffer->pad7C[0] = frame_counter;
        *(s32 *)&buffer->pad7C[8] = 0x22;
    }
    func_80040A0C(&D_80058400.active[0]->display);
    func_80040834(&D_80058400.active[1]->drawing);
    func_800401C0(1);
}

s32 func_80016C18(void) {
    s32 i;
    RenderBuffer *buffer;
    s32 size;

    switch (D_80056710) {
    case 0x19:
    case 0x24:
    case 0x25:
    case 0x2D:
    case 0x33:
    case 0x34:
        func_8003CE20();
        break;
    }
    for (i = 0; i < D_80058400.count; i++) {
        buffer = &D_80058400.buffers[i];
        switch (D_80056710) {
        case 0x19:
            size = 0x1E000;
            break;
        case 0x38:
            size = 0x1CC00;
            break;
        default:
            size = 0x16000;
            break;
        }
        buffer->word74 = (s32)LIBC_Malloc(size);
        if (!buffer->word74) {
            func_8003D680(-15);
        }
        func_80016DCC(buffer);
    }
    return -0xFF;
}

s32 func_80016D14(void) {
    s32 i;
    RenderBuffer *buffer;

    func_8004025C(0);
    for (i = 0; i < D_80058400.count; i++) {
        buffer = &D_80058400.buffers[i];
        LIBC_Free((void *)buffer->word74);
    }
    switch (D_80056710) {
    case 0x19:
    case 0x24:
    case 0x25:
    case 0x2D:
    case 0x33:
    case 0x34:
        func_8003CEA8();
        break;
    }
    return -0xFF;
}

