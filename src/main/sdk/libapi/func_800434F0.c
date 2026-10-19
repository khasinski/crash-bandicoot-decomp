#include "common.h"
/* GCC_VERSION: 2.6.3 */


s32 CdReadyCallback(s32 arg0) {
    s32 temp_v0;

    temp_v0 = D_800555A4;
    D_800555A4 = arg0;
    return temp_v0;
}
