#include "common.h"
/* GCC_VERSION: 2.6.3 */

u16 GetIntrMask(void) {
    return *g_intr_i_mask_reg;
}
