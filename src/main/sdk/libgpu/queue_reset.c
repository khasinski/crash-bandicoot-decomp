#include "common.h"

/* GCC_VERSION: 2.6.3 */

s32 SetIntrMask(s32);
s32 _version(s32);
void *memset(void *, s32, u32);

/* The queue consumer callback also updates this index. */

extern u8 D_8005E74C[0x1800];

/* Reset queue indices and hardware, then restore interrupt state. */
s32 _reset(s32 arg0) {
    s32 temp_v0;
    s32 temp_v1;
    s32 var_v0;

    temp_v0 = SetIntrMask(0);
    g_gpu_q_read = 0;
    D_80054B80 = temp_v0;
    g_gpu_q_write = g_gpu_q_read;
    temp_v1 = arg0 & 7;
    switch (temp_v1) {                              /* irregular */
    case 0:
        *D_80054B4C = 0x401;
        *D_80054B5C |= 0x800;
        *g_gpu_stat_reg = 0;
        memset(D_80057098, 0, 0x100);
        memset(D_8005E74C, 0, 0x1800);
        break;
    case 1:
        *D_80054B4C = 0x401;
        *D_80054B5C |= 0x800;
        *g_gpu_stat_reg = 0x02000000;
        *g_gpu_stat_reg = 0x01000000;
        break;
    }
    SetIntrMask(D_80054B80);
    if (!(arg0 & 7)) {
        var_v0 = _version(arg0);
    } else {
        var_v0 = 0;
    }
    return var_v0;
}
