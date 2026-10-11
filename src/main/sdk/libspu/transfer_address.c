#include "common.h"

/* GCC_VERSION: 2.6.3 */

/* Cache the encoded SPU transfer address and return the supplied address. */

extern s32 func_80046E00(s32,s32);
extern s16 D_800558E0;

s32 func_80048A18(s32 arg0) {
    D_800558E0 = func_80046E00(-1, arg0);
    return arg0;
}
