#include "common.h"

/* GCC_VERSION: 2.6.3 */

/* Forward the CD controller request with its original arguments. */

void func_80044C40(void);
s32 func_800440EC(s32,u8 *);
s32 func_80044370(s32,u8 *);
s32 func_80043498(s32 mode,u8 *result) {
    return func_800440EC(mode,result);
}
