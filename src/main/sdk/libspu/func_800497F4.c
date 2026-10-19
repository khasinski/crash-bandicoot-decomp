#include "common.h"
/* GCC_VERSION: 2.5.7 */
void ResetCallback();
void _SsInit();
void SpuInit();

void SsInit(void) {
    ResetCallback();
    SpuInit();
    _SsInit();
}
