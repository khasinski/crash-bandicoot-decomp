#include "common.h"

/* GCC_VERSION: 2.6.3 */

/* Establish the GPU operation timeout and reset its polling counter. */
s32 VSync(s32);
s32 BIOS_Printf(const char *, ...);
s32 SetIntrMask(s32);


extern volatile s32 D_80054B60[];


void set_alarm(void)
{
    D_80054B84 = VSync(-1) + 240;
    D_80054B88 = 0;
}

s32 get_alarm(void)
{
    if (VSync(-1) > D_80054B84 || D_80054B88++ > 0xF0000) {
        *g_gpu_stat_reg;
        BIOS_Printf(D_80011350, (g_gpu_q_write - g_gpu_q_read) & 0x3F, *g_gpu_stat_reg, *D_80054B4C, *D_80054B44);
        BIOS_Printf(D_80011384, D_80054B60[0], D_80054B64, D_80054B68);
        D_80054B80 = SetIntrMask(0);
        g_gpu_q_read = 0;
        g_gpu_q_write = g_gpu_q_read;
        *D_80054B4C = 0x401;
        *D_80054B5C |= 0x800;
        *g_gpu_stat_reg = 0x02000000;
        *g_gpu_stat_reg = 0x01000000;
        SetIntrMask(D_80054B80);
        return -1;
    }
    return 0;
}
