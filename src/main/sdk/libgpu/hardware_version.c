#include "common.h"

/* GCC_VERSION: 2.6.3 */

extern u8 g_gpu_mode;

s32 GetGraphType(void)
{
    return g_gpu_mode;
}
