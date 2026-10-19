#include "common.h"
/* GCC_VERSION: 2.5.7 */

void SsInit(void) {
    ResetCallback();
    SpuInit();
    _SsInit();
}
