#include "common.h"

/* GCC_VERSION: 2.6.3 */

extern s32 abs(s32);

s32 func_800245F0(s32 current,s32 target) {
    s32 delta;
    current &= 0xFFF;
    target &= 0xFFF;
    delta = target - current;
    if (abs(delta) < 0x801) return delta;
    return delta > 0 ? delta - 0x1000 : delta + 0x1000;
}

s32 func_80024628(s32 current, s32 target, s32 step) {
    s32 delta = target - current;
    if (step > 0 && abs(delta) < step) return target;
    return delta > 0 ? current + step : current - step;
}
