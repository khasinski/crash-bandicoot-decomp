/* GCC_VERSION: 2.6.3 */
#include "common.h"

void rcnt_memclr(s32 *table, s32 count) {
    while (--count != -1) {
        *table++ = 0;
    }
}
