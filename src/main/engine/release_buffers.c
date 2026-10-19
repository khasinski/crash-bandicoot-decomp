/* GCC_VERSION: 2.6.3 */
/* GNU_AS_G: 8 */
#include "common.h"

void LIBC_Free(void *);
s32 Slst_Kill(void) {
 LIBC_Free(D_80056700);
 LIBC_Free(D_800566BC);
 return -255;
}
