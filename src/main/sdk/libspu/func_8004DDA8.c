#include "common.h"
/* GCC_VERSION: 2.6.3 */

void SsSetMono(s32 arg0) {
    if (arg0 == 1) {
        D_80055914 = 0;
        return;
    }
    D_80055914 = 1;
}
