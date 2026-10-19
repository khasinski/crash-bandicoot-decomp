#include "common.h"
/* GCC_VERSION: 2.6.3 */

s32 CD_getsector(s32, s32);

s32 CdGetSector(s32 arg0, s32 arg1) {
    return CD_getsector(arg0, arg1) == 0;
}
