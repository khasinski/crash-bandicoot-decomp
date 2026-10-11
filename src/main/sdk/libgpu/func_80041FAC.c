#include "common.h"
/* GCC_VERSION: 2.6.3 */

extern volatile s32 *D_80054B3C;
extern volatile s32 *D_80054B40;

s32 func_80041FAC(s32 arg0) {
    *D_80054B40 = arg0 | 0x10000000;
    return *D_80054B3C & 0xFFFFFF;
}
