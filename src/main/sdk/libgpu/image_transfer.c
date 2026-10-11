#include "gpu.h"

/* GCC_VERSION: 2.6.3 */

s32 func_80042000(GpuRect *, void *, s32, s32);

s32 func_80041FDC(GpuRect *rect, void *data, s32 flags)
{
    return func_80042000(rect, data, 0, flags);
}
