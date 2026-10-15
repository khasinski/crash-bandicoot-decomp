#include "common.h"
#include "gpu.h"

/* GCC_VERSION: 2.6.3 */
void func_80041F60(s32 arg0);
s32 func_80041FAC(s32 arg0);
void func_80042864(void);
s32 func_80042898(void);
extern volatile s16 D_80054A70[];
extern volatile s16 D_80054A72[];
extern volatile u32 *D_80054B3C;
extern volatile u32 *D_80054B40;
extern volatile u32 *D_80054B44;
extern volatile u32 *D_80054B48;
extern volatile u32 *D_80054B4C;
extern volatile u32 *D_80054B50, *D_80054B54, *D_80054B58, *D_80054B5C;
extern u32 D_80057058[8];
extern u32 D_80057078[4];

s32 func_800416E4(u32 *table, s32 count)
{
    *D_80054B5C |= 0x08000000;
    *D_80054B58 = 0;
    *D_80054B50 = (u32)(table - 1 + count);
    *D_80054B54 = count;
    *D_80054B58 = 0x11000002;
    func_80042864();
    while (*D_80054B58 & 0x01000000) {
        if (func_80042898()) return -1;
    }
    return count;
}

s32 func_800417CC(GpuRect *rect, u32 color)
{
    rect->w = (rect->w < 0) ? 0 : ({ s32 max_x = D_80054A70[0] - 1; (rect->w > max_x) ? max_x : rect->w; });
    rect->h = (rect->h < 0) ? 0 : ({ s32 max_y = D_80054A72[0] - 1; (rect->h > max_y) ? max_y : rect->h; });

    if ((rect->x & 0x3F) || (rect->w & 0x3F)) {
        D_80057058[0] = ((u32)D_80057078 & 0xFFFFFF) | 0x07000000;
        D_80057058[1] = 0xE3000000;
        D_80057058[2] = 0xE4FFFFFF;
        D_80057058[3] = 0xE5000000;
        D_80057058[4] = 0xE6000000;
        D_80057058[5] = (color & 0xFFFFFF) | 0x60000000;
        D_80057058[6] = *(u32 *)&rect->x;
        D_80057058[7] = *(u32 *)&rect->w;
        D_80057078[0] = 0x03FFFFFF;
        D_80057078[1] = func_80041FAC(3) | 0xE3000000;
        D_80057078[2] = func_80041FAC(4) | 0xE4000000;
        D_80057078[3] = func_80041FAC(5) | 0xE5000000;
    } else {
        D_80057058[0] = 0x04FFFFFF;
        D_80057058[1] = 0xE6000000;
        D_80057058[2] = (color & 0xFFFFFF) | 0x02000000;
        D_80057058[3] = *(u32 *)&rect->x;
        D_80057058[4] = *(u32 *)&rect->w;
    }
    func_80041F60((s32)D_80057058);
    return 0;
}

s32 func_800419E4(GpuRect *rect, u32 *data)
{
    s32 total, blocks, rem, flag;

    func_80042864();
    flag = 0;
    rect->w = (rect->w < 0) ? 0 : (D_80054A70[0] < rect->w) ? D_80054A70[0] : rect->w;
    rect->h = (rect->h < 0) ? 0 : (D_80054A72[0] < rect->h) ? D_80054A72[0] : rect->h;
    total = (rect->w * rect->h + 1) / 2;
    if (total <= 0) {
        return -1;
    }
    rem = total % 16;
    blocks = total / 16;
    while (!(*D_80054B40 & 0x04000000)) {
        if (func_80042898()) {
            return -1;
        }
    }
    *D_80054B40 = 0x04000000;
    *D_80054B3C = 0x01000000;
    *D_80054B3C = flag ? 0xB0000000 : 0xA0000000;
    *D_80054B3C = *(u32 *)&rect->x;
    *D_80054B3C = *(u32 *)&rect->w;
    while (--rem != -1) {
        *D_80054B3C = *data++;
    }
    if (blocks != 0) {
        *D_80054B40 = 0x04000002;
        *D_80054B44 = (u32)data;
        *D_80054B48 = (blocks << 16) | 0x10;
        *D_80054B4C = 0x01000201;
    }
    return 0;
}

s32 func_80041C38(GpuRect *rect, u32 *data)
{
    s32 total, blocks, rem;

    func_80042864();
    rect->w = (rect->w < 0) ? 0 : (D_80054A70[0] < rect->w) ? D_80054A70[0] : rect->w;
    rect->h = (rect->h < 0) ? 0 : (D_80054A72[0] < rect->h) ? D_80054A72[0] : rect->h;
    total = (rect->w * rect->h + 1) / 2;
    if (total <= 0) {
        return -1;
    }
    rem = total % 16;
    blocks = total / 16;
    while (!(*D_80054B40 & 0x04000000)) {
        if (func_80042898()) {
            return -1;
        }
    }
    *D_80054B40 = 0x04000000;
    *D_80054B3C = 0x01000000;
    *D_80054B3C = 0xC0000000;
    *D_80054B3C = *(u32 *)&rect->x;
    *D_80054B3C = *(u32 *)&rect->w;
    while (!(*D_80054B40 & 0x08000000)) {
        if (func_80042898()) {
            return -1;
        }
    }
    while (--rem != -1) {
        *data++ = *D_80054B3C;
    }
    if (blocks != 0) {
        *D_80054B40 = 0x04000003;
        *D_80054B44 = (u32)data;
        *D_80054B48 = (blocks << 16) | 0x10;
        *D_80054B4C = 0x01000200;
    }
    return 0;
}
