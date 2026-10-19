#include "common.h"

/* GCC_VERSION: 2.6.3 */
void checkRECT(const char *,s32);
extern u8 g_gpu_debug_level;

void DrawOTag(s32 arg0) {
    if ((u8) g_gpu_debug_level >= 2U) {
        g_gpu_ot_status(D_800112F0, arg0);
    }
    g_gpu_ctl->dispatch08(g_gpu_ctl->word18, arg0, 0, 0);
}
