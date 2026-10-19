#include "common.h"
/* GCC_VERSION: 2.6.3 */

s32 CD_datasync(s32);
s32 CdReadCallback(s32 arg0) {
    return CD_datasync(arg0);
}
