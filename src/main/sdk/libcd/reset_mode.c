/* GCC_VERSION: 2.6.3 */
#include "common.h"

void func_80044E1C(void);
s32 func_80044E8C(void);
s32 func_80044D28(void);

s32 func_80043384(s32 mode) {
    if (mode == 2) {
        func_80044E1C();
        return 1;
    }
    if (func_80044E8C() != 0) {
        return 0;
    }
    if (mode == 1 && func_80044D28() != 0) {
        return 0;
    }
    return 1;
}
