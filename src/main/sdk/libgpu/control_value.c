#include "common.h"

/* GCC_VERSION: 2.6.3 */
extern u8 g_gpu_mode;
extern u8 g_gpu_debug_level;
extern u8 g_gpu_reverse_flag;

s32 DrawSyncCallback(s32 arg0) {
    s32 temp_v0;

    if ((u8) g_gpu_debug_level >= 2U) {
        g_gpu_ot_status(g_str_control_value_drawsynccallback_08x_n, arg0);
    }
    temp_v0 = g_gpu_drawsync_cb;
    g_gpu_drawsync_cb = arg0;
    return temp_v0;
}
