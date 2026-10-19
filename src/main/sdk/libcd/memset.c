#include "common.h"
#include "gpu.h"

/* GCC_VERSION: 2.6.3 */

/* --- memset --- */

void memset(u8 *buf, u8 val, s32 count)
{
    while (--count != -1) {
        *buf++ = val;
    }
}
