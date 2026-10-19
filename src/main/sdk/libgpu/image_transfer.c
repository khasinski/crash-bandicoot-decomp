#include "gpu.h"

/* GCC_VERSION: 2.6.3 */

s32 _addque2(GpuRect *, void *, s32, s32);

s32 _addque(GpuRect *rect, void *data, s32 flags)
{
    return _addque2(rect, data, 0, flags);
}
