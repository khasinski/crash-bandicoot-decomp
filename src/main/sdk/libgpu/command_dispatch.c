#include "common.h"
#include "gpu.h"

/* GCC_VERSION: 2.6.3 */
typedef struct {u8 pad00[8];s32 (*dispatch08)(s32,void *,s32,s32);s32 word0C;u8 pad10[8];s32 word18,word1C,word20;u32 word24,word28;void (*callback2C)(s32 *,s32);} Api;
extern Api *D_80054A64;
extern s32 (*D_80054A68)(const char *,...);
extern u8 D_80054A6E;
extern s16 D_80054A70;
extern s16 D_80054A72;

void func_800402C8(const char *name, GpuRect *rect) {
    switch (D_80054A6E) {
    case 1:
        if (rect->w > D_80054A70 || rect->w + rect->x > D_80054A70
            || rect->y > D_80054A72 || rect->y + rect->h > D_80054A72
            || rect->w <= 0 || rect->x < 0 || rect->y < 0 || rect->h <= 0) {
            D_80054A68(D_8001126C, name);
            D_80054A68(D_80011278, rect->x, rect->y, rect->w, rect->h);
        }
        break;
    case 2:
        D_80054A68(D_8001128C, name);
        D_80054A68(D_80011278, rect->x, rect->y, rect->w, rect->h);
        break;
    }
}

s32 func_800403F0(GpuRect *rect, u8 r, u8 g, u8 b) {
    func_800402C8(D_80011290, rect);
    return D_80054A64->dispatch08(D_80054A64->word0C, rect, 8, (b << 16) | (g << 8) | r);
}

void func_80040484(s32 arg0, s32 arg1) {
    func_800402C8(D_8001129C, (GpuRect *)arg0);
    D_80054A64->dispatch08(D_80054A64->word20, (void *)arg0, 8, arg1);
}

void func_800404E8(s32 arg0, s32 arg1) {
    func_800402C8(D_800112A8, (GpuRect *)arg0);
    D_80054A64->dispatch08(D_80054A64->word1C, (void *)arg0, 8, arg1);
}

s32 func_8004054C(s32 *rect, s32 x, s32 y) {
    s32 dst;

    func_800402C8(D_800112B4, (GpuRect *)rect);
    if (((GpuRect *)rect)->w == 0 || ((GpuRect *)rect)->h == 0) {
        return -1;
    }
    dst = (y << 16) | (x & 0xFFFF);
    D_80054B14[2] = rect[0];
    D_80054B14[3] = dst;
    D_80054B14[4] = rect[1];
    return D_80054A64->dispatch08(D_80054A64->word18, D_80054B14, 0x14, 0);
}
