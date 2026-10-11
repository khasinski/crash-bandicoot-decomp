/* GCC_VERSION: 2.6.3 */
/* GNU_AS_G: 8 */
#include "common.h"
extern void *D_80056700,*D_800566BC;
void LIBC_Free(void *);
s32 func_80029AD8(void) {
 LIBC_Free(D_80056700);
 LIBC_Free(D_800566BC);
 return -255;
}
