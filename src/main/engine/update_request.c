/* GCC_VERSION: 2.6.3 */
#include "common.h"

/* Export the real small-common state object. */
asm(".globl D_800566C0");
s32 D_800566C0;
void func_800317DC(void) {
    if (D_800566C0 == 0) D_800566C0 = 1;
}
