/* GCC_VERSION: 2.6.3 */
#include "common.h"

void Slst_Noop2(void *, void *, void *, u32);

void Slst_NoopWrapper(void *a, void *b, void *c) {
    Slst_Noop2(a, b, c, 0x808080);
}
