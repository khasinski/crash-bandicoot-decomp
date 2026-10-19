#include "common.h"

/* GCC_VERSION: 2.6.3 */

/* Clamp transfer size, forward buffer and size, and update completion state. */

s32 _spu_write(s32,u32);


u32 SpuWrite(s32 arg0,u32 arg1) {
    u32 var_s0;

    var_s0 = arg1;
    if (var_s0 > 0x7F000U) {
        var_s0 = 0x7F000;
    }
    _spu_write(arg0,var_s0);
    if (D_80055918 == 0) {
        D_80055914 = 0;
    }
    return var_s0;
}
