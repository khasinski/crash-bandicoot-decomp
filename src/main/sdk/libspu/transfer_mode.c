#include "common.h"

/* GCC_VERSION: 2.6.3 */

/* Dispatch the transfer through the configured mode. */

void func_8004636C(s32,s32);
s32 func_80046A20(s32, ...);
extern u16 D_800558E0;
extern s32 D_800558FC;
extern s32 D_80055908;

s32 func_80046CC8(s32 arg0, s32 arg1) {
    if (D_800558FC == 0) {
        func_80046A20(2, D_800558E0 << D_80055908);
        func_80046A20(1);
        func_80046A20(3, arg0, arg1);
    } else {
        func_8004636C(arg0, arg1);
    }
    return arg1;
}
