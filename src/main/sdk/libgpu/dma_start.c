#include "common.h"

/* GCC_VERSION: 2.6.3 */

/* Configure GPU DMA address, block count and control registers. */


void _cwc(s32 arg0) {
    *g_gpu_stat_reg = 0x04000002;
    *D_80054B44 = arg0;
    *D_80054B48 = 0;
    *D_80054B4C = 0x01000401;
}
