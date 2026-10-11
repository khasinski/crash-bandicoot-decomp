#include "common.h"

/* GCC_VERSION: 2.6.3 */
extern volatile u32 *D_80054B3C;
extern volatile u32 *D_80054B40;

s32 func_80042A04(s32 arg0) {
    *D_80054B40 = 0x10000007;
    if ((*D_80054B3C & 0xFFFFFF) != 2) {
        *D_80054B3C = (*D_80054B40 & 0x3FFF) | 0xE1001000;
        /* Retail consumes this GPU data read before querying status. */
        (void)*D_80054B3C;
        if (!(*D_80054B40 & 0x1000)) {
            return 0;
        }
        if (!(arg0 & 8)) {
            return 1;
        }
        *D_80054B40 = 0x20000504;
        return 2;
    }
    if (!(arg0 & 8)) return 3;
    *D_80054B40 = 0x09000001;
    return 4;
}
