#include "common.h"
#include "gpu.h"

/* GCC_VERSION: 2.6.3 */
extern u8 g_gpu_debug_level;
extern s16 D_80054A70;
extern s16 D_80054A72;

void checkRECT(const char *name, GpuRect *rect) {
    switch (g_gpu_debug_level) {
    case 1:
        if (rect->w > D_80054A70 || rect->w + rect->x > D_80054A70
            || rect->y > D_80054A72 || rect->y + rect->h > D_80054A72
            || rect->w <= 0 || rect->x < 0 || rect->y < 0 || rect->h <= 0) {
            g_gpu_ot_status(D_8001126C, name);
            g_gpu_ot_status(D_80011278, rect->x, rect->y, rect->w, rect->h);
        }
        break;
    case 2:
        g_gpu_ot_status(D_8001128C, name);
        g_gpu_ot_status(D_80011278, rect->x, rect->y, rect->w, rect->h);
        break;
    }
}

s32 ClearImage(GpuRect *rect, u8 r, u8 g, u8 b) {
    checkRECT(D_80011290, rect);
    return g_gpu_ctl->dispatch08(g_gpu_ctl->word0C, rect, 8, (b << 16) | (g << 8) | r);
}

void LoadImage(s32 arg0, s32 arg1) {
    checkRECT(D_8001129C, (GpuRect *)arg0);
    g_gpu_ctl->dispatch08(g_gpu_ctl->word20, (void *)arg0, 8, arg1);
}

void StoreImage(s32 arg0, s32 arg1) {
    checkRECT(D_800112A8, (GpuRect *)arg0);
    g_gpu_ctl->dispatch08(g_gpu_ctl->word1C, (void *)arg0, 8, arg1);
}

s32 MoveImage(s32 *rect, s32 x, s32 y) {
    s32 dst;

    checkRECT(D_800112B4, (GpuRect *)rect);
    if (((GpuRect *)rect)->w == 0 || ((GpuRect *)rect)->h == 0) {
        return -1;
    }
    dst = (y << 16) | (x & 0xFFFF);
    D_80054B14[2] = rect[0];
    D_80054B14[3] = dst;
    D_80054B14[4] = rect[1];
    return g_gpu_ctl->dispatch08(g_gpu_ctl->word18, D_80054B14, 0x14, 0);
}
