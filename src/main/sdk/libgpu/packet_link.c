#include "common.h"

/* GCC_VERSION: 2.6.3 */
void checkRECT(const char *,s32);
extern u8 g_gpu_debug_level;

s32 *ClearOTagR(s32 *arg0, s32 arg1) {
    if ((u8) g_gpu_debug_level >= 2U) {
        g_gpu_ot_status(D_800112D8, arg0, arg1);
    }
    g_gpu_ctl->callback2C(arg0, arg1);
    *arg0 = (s32) D_80054B28 & 0xFFFFFF;
    return arg0;
}
