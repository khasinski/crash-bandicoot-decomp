#include "common.h"
/* GCC_VERSION: 2.6.3 */


void SpuVmDamperOn(void) {
    g_spu_vm_damper_mask = 2;
}
