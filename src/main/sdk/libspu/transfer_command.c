#include "common.h"

/* GCC_VERSION: 2.6.3 */

/* Configure the SPU transfer address and issue a transfer command. */

s32 func_80046A20(s32, ...);
extern u16 D_800558E0;
extern s32 D_80055908;

s32 func_80046D50(s32 arg0, s32 arg1) {
    func_80046A20(2, D_800558E0 << D_80055908);
    func_80046A20(0);
    func_80046A20(3, arg0, arg1);
    return arg1;
}
