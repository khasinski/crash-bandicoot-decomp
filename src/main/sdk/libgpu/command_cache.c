/* GCC_VERSION: 2.6.3 */
#include "common.h"
void _ctl(u32 command) {
    *g_gpu_stat_reg = command;
    D_80057098[command >> 24] = command;
}
u8 _getctl(s32 index) {
    return D_80057098[index];
}
s32 _cwb(u32 *data, s32 count) {
    *g_gpu_stat_reg = 0x04000000;
    while (--count != -1) {
        *D_80054B3C = *data++;
    }
    return 0;
}
