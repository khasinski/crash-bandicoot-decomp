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
