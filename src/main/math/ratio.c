#include "common.h"

/* GCC_VERSION: 2.6.3 */

s32 sin(s32);

s32 Math_SinScale(s32 arg0, s32 arg1) {
    return (s32) (sin((s32) (arg0 << 0xA) / arg1) * arg1) >> 0xC;
}
