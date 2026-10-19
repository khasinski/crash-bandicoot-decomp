#include "common.h"
/* GCC_VERSION: 2.6.3 */

s32 CdSetDebug(s32 arg0) {
    s32 temp_v0;

    temp_v0 = D_800555AC;
    D_800555AC = arg0;
    return temp_v0;
}
