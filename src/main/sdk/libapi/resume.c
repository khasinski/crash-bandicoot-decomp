#include "common.h"

/* GCC_VERSION: 2.6.3 */

/* Restore the saved interrupt context and hardware masks if callbacks are paused.
 * The partial state view begins at its flag and includes context bytes at 0x38.
 */
s32 func_8003E208(void);
s32 func_8003EE44(void *);
extern u16 D_80053934[];

u16 *func_8003ED50(void)
{
    u16 *result;

    if (*D_80053934 == 0) {
        func_8003EE44(&D_80053934[0x1C]);
        *D_80053934 = 1;
        *D_800549C4 = D_80053966;
        *D_800549C8 = D_80053968;
        func_8003E208();
        result = D_80053934;
    } else {
        result = NULL;
    }
    return result;
}

void func_8003EDD8(s32 *table, s32 count)
{
    while (--count != -1) {
        *table++ = 0;
    }
}

