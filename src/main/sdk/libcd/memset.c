#include "common.h"
#include "gpu.h"

/* GCC_VERSION: 2.6.3 */


/* --- func_80042AE0 --- */

void func_80042AE0(u8 *buf, u8 val, s32 count)
{
    while (--count != -1) {
        *buf++ = val;
    }
}
