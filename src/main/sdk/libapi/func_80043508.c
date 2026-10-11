#include "common.h"
/* GCC_VERSION: 2.6.3 */

extern s32 D_800555A8;

s32 func_80043508(s32 arg0) {
    s32 temp_v0;

    temp_v0 = D_800555A8;
    D_800555A8 = arg0;
    return temp_v0;
}
