#include "common.h"
/* GCC_VERSION: 2.6.3 */

void SsSetMono(s32 arg0) {
    if (arg0 == 1) {
        g_spu_trans_start_addr = 0;
        return;
    }
    g_spu_trans_start_addr = 1;
}
