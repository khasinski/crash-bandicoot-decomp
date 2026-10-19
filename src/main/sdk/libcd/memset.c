#include "common.h"
#include "gpu.h"

/* GCC_VERSION: 2.6.3 */

void memset(buf, val, count)
u8 *buf;
u8 val;
s32 count;
{
    while (--count != -1) {
        *buf++ = val;
    }
}
