#include "common.h"

/* GCC_VERSION: 2.6.3 */

/* Exchange the hardware interrupt mask. */

u16 func_8003E870(u16 arg0) {
    u16 temp_v0;

    temp_v0 = *D_800549C4;
    *D_800549C4 = arg0;
    return temp_v0;
}
