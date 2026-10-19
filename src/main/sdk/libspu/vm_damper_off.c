#include "common.h"
/* GCC_VERSION: 2.6.3 */


void SpuVmDamperOff(void) {
    g_spu_vm_damper_mask = 0;
}
