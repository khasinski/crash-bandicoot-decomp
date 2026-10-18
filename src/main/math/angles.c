#include "common.h"

/* GCC_VERSION: 2.6.3 */

/* Compute 12-bit angles between two points in the XZ and XY planes. */

s32 abs(s32);
s32 func_8004301C(s32, s32);

s32 func_80029E10(s32 *origin, s32 *target)
{
    return func_8004301C(target[0] - origin[0], target[2] - origin[2]) & 0xFFF;
}

s32 func_80029E48(s32 *origin, s32 *target)
{
    return func_8004301C(target[0] - origin[0], target[1] - origin[1]) & 0xFFF;
}

/* Limit the shortest 12-bit angular difference to the supplied step. */
s32 func_80029E80(s32 current, s32 target, s32 step) {
    s32 delta;
    s32 magnitude;
    s32 limited;

    current &= 0xFFF;
    target &= 0xFFF;
    delta = target - current;
    magnitude = abs(delta);
    if (magnitude >= 0x801) {
        if (delta > 0) {
            delta -= 0x1000;
        } else {
            delta += 0x1000;
        }
    }
    magnitude = abs(delta);
    if (step < magnitude) {
        magnitude = abs(step);
        if (delta <= 0) {
            limited = 0;
            if (delta != 0) {
                limited = -magnitude;
            }
        } else {
            limited = magnitude;
        }
        delta = limited;
    }
    return delta;
}
