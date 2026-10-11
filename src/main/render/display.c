#include "common.h"

/* GCC_VERSION: 2.6.3 */

/* Dispatch the display operation only when the pointed-to halfword is nonzero. */

extern u16 *D_800566B8;
extern void func_800195CC(void);

void func_800194D0(void)
{
    if (*D_800566B8)
        func_800195CC();
}
