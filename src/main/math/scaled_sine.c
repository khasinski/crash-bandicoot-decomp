/* GCC_VERSION: 2.6.3 */
#include "common.h"
s32 Math_SinScale(s32 value,s32 scale) {
    return (sin((value << 10) / scale) * scale) >> 12;
}
