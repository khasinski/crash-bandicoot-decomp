#include "common.h"
#include "gpu.h"

/* GCC_VERSION: 2.6.3 */

/* Four encoded fields form the GPU texture-window command. */

u32 func_8004158C(GpuRect *rect)
{
    u32 fields[4];
    if (rect != NULL) {
        fields[0] = (rect->x & 255) >> 3;
        fields[2] = (-rect->w & 255) >> 3;
        fields[1] = (rect->y & 255) >> 3;
        fields[3] = (-rect->h & 255) >> 3;
        return 0xE2000000 | (fields[1] << 15) | (fields[0] << 10) |
               (fields[3] << 5) | fields[2];
    }
    return 0;
}

extern volatile u8 D_80054A6C[];
extern u8 D_80054A6F;

s32 func_80041610(GpuRect *rect)
{
    switch (D_80054A6C[0]) {
    case 1:
        if (D_80054A6F) {
            return 0x400 - rect->x - rect->w;
        }
        return rect->x;
    case 2:
        return D_80054A6F ? 0x400 - rect->x - rect->w / 2 : rect->x / 2;
    default:
        return rect->x;
    }
}
