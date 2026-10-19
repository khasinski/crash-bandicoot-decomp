#include "common.h"

/* GCC_VERSION: 2.6.3 */
extern u8 g_gpu_mode;
extern u8 g_gpu_debug_level;
extern u8 D_80054A6F;

s32 DrawSyncCallback(s32 arg0) {
    s32 temp_v0;

    if ((u8) g_gpu_debug_level >= 2U) {
        g_gpu_ot_status(D_80011228, arg0);
    }
    temp_v0 = D_80054A78;
    D_80054A78 = arg0;
    return temp_v0;
}
