#include "common.h"
/* GCC_VERSION: 2.6.3 */


s32 _param(s32 arg0) {
    *g_gpu_stat_reg = arg0 | 0x10000000;
    return *D_80054B3C & 0xFFFFFF;
}
