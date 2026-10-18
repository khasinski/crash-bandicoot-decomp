#include "common.h"

/* GCC_VERSION: 2.6.3 */

/* Clamp transfer size, forward buffer and size, and update completion state. */

s32 func_80046CC8(s32,u32);

extern void (*volatile D_80055918)(void);

u32 func_800489B8(s32 arg0,u32 arg1) {
    u32 var_s0;

    var_s0 = arg1;
    if (var_s0 > 0x7F000U) {
        var_s0 = 0x7F000;
    }
    func_80046CC8(arg0,var_s0);
    if (D_80055918 == 0) {
        D_80055914 = 0;
    }
    return var_s0;
}
