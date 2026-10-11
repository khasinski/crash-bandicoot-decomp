#include "common.h"

/* GCC_VERSION: 2.6.3 */

/* Configure GPU DMA address, block count and control registers. */

extern volatile s32 *D_80054B40;
extern volatile s32 *D_80054B44;
extern volatile s32 *D_80054B48;
extern volatile s32 *D_80054B4C;

void func_80041F60(s32 arg0) {
    *D_80054B40 = 0x04000002;
    *D_80054B44 = arg0;
    *D_80054B48 = 0;
    *D_80054B4C = 0x01000401;
}
