/* GCC_VERSION: 2.6.3 */
#include "gpu.h"
#include "render.h"

typedef struct GpuPolyF4 {
    GpuPacketHeader header;
    s16 x0, y0;
    s16 x1, y1;
    s16 x2, y2;
    s16 x3, y3;
} GpuPolyF4;

typedef struct {
    u8 bytes[19];
} FadeTable;

extern FadeTable D_800102C0;

void func_8003F73C(void *, void *);
void func_8003F890(void *);
void func_8003F7F0(void *, s32);
u16 func_8003F514(s32, s32, s32, s32);
void func_80041054(void *, s32, s32, s32, s32);

void func_80017358(s32 x, s32 y, s32 w, s32 h, u8 r, u8 g, u8 b) {
    GpuTile *tile = (GpuTile *)D_80058404[2]->word78;

    D_80058404[2]->word78 = (s32)(tile + 1);
    func_8003FA14(&tile->header);
    tile->rect.w = w;
    tile->rect.h = h;
    tile->header.color[0] = r;
    tile->header.color[1] = g;
    tile->header.color[2] = b;
    tile->rect.x = x + D_80058404[2]->drawing.env.clip.x;
    tile->rect.y = y + D_80058404[2]->drawing.env.clip.y;
    func_8003F73C(D_80058404[2]->ordering_table, tile);
}

void func_80017448(u32 fade) {
    void *mode_packet;
    GpuPolyF4 *poly;
    FadeTable table;

    mode_packet = (void *)D_80058404[2]->word78;
    D_80058404[2]->word78 = (s32)mode_packet + 0xC;
    poly = (GpuPolyF4 *)D_80058404[2]->word78;
    D_80058404[2]->word78 = (s32)(poly + 1);
    table = D_800102C0;
    if (fade != 0) {
        fade = table.bytes[fade >> 4];
        poly->x0 = -256;
        poly->y0 = -120;
        poly->x1 = 256;
        poly->y1 = -120;
        poly->x2 = -256;
        poly->y2 = 120;
        poly->x3 = 256;
        poly->y3 = 120;
        poly->header.color[0] = fade;
        poly->header.color[1] = fade;
        poly->header.color[2] = fade;
        func_8003F890(poly);
        func_8003F7F0(poly, 1);
        func_8003F73C(&D_80058404[2]->ordering_table[0x7FF], poly);
        func_80041054(mode_packet, 1, 0, func_8003F514(0, 2, 0, 0), 0);
        func_8003F73C(&D_80058404[2]->ordering_table[0x7FF], mode_packet);
    }
}
