#include "common.h"

/* GCC_VERSION: 2.6.3 */

/* Forward the CD controller request with its original arguments. */

void CD_initvol(void);
s32 CD_sync(s32,u8 *);
s32 CD_ready(s32,u8 *);
s32 CdSync(s32 mode,u8 *result) {
    return CD_sync(mode,result);
}
