#include "common.h"

/* GCC_VERSION: 2.6.3 */

void SpuSetTransferMode(s32 mode)
{
    s32 enabled;
    switch(mode) {
    case 0: enabled = 0; break;
    case 1: enabled = 1; break;
    default: enabled = 0; break;
    }
    D_8005594C = mode;
    D_800558FC = enabled;
}
