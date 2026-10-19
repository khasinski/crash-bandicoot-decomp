#include "common.h"
/* GCC_VERSION: 2.6.3 */
void PAD_dr(void);

s32 PadRead(void) {
    PAD_dr();
    return ~D_80057054;
}
