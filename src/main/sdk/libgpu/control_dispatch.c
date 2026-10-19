#include "common.h"

/* GCC_VERSION: 2.6.3 */
extern u8 g_gpu_mode;
extern u8 g_gpu_debug_level;
extern u8 D_80054A6F;

void DrawSync(s32 arg0) {
    if ((u8) g_gpu_debug_level >= 2U) {
        g_gpu_ot_status(D_80011258, arg0);
    }
    g_gpu_ctl->callback3C(arg0);
}
