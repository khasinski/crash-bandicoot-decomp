/* GCC_VERSION: 2.6.3 */
#include "common.h"
s32 func_8003905C(s32);
s32 func_80029F04(s32 value,s32 scale) {
    return (func_8003905C((value << 10) / scale) * scale) >> 12;
}
