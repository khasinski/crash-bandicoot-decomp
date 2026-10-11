#include "common.h"

/* GCC_VERSION: 2.6.3 */
void func_80049404(s16);                               /* extern */
void func_80050868(s16);                               /* extern */
/* Export the real small-common channel identifier. */
asm(".globl D_80056658");
s16 D_80056658;

void func_800319DC(s16 arg0, s32 arg1) {
    if (arg0 != -1) {
        func_80049404(arg0);
    }
    if ((arg1 != 0) && (D_80056658 != -1)) {
        func_80050868(D_80056658);
    }
}
