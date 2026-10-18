#include "common.h"

/* GCC_VERSION: 2.6.3 */

/* Read a packet link as a KSEG0 address, or test its 24-bit end-of-chain sentinel. */

u32 func_8003F704(u32 *packet)
{
    return (*packet & 0xFFFFFF) | 0x80000000;
}

s32 func_8003F720(u32 *packet)
{
    return (*packet & 0xFFFFFF) == 0xFFFFFF;
}
