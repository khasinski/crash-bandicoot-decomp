#include "common.h"
#include "gpu.h"

/* GCC_VERSION: 2.6.3 */

/* Upload a 256- or 16-colour palette and return its CLUT ID. */

u16 func_8003F5DC(s32,s32);
void func_80040484(GpuRect *, void *);

u16 func_8003F338(void *image, s32 x, s32 y)
{
    GpuRect rect;
    rect.w = 0x100;
    rect.x = x;
    rect.y = y;
    rect.h = 1;
    func_80040484(&rect,image);
    return func_8003F5DC(x,y) & 0xFFFF;
}

u16 func_8003F3A0(void *image, s32 x, s32 y)
{
    GpuRect rect;
    rect.w = 0x10;
    rect.x = x;
    rect.y = y;
    rect.h = 1;
    func_80040484(&rect,image);
    return func_8003F5DC(x,y) & 0xFFFF;
}
