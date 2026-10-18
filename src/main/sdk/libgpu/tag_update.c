#include "common.h"

/* GCC_VERSION: 2.6.3 */

/* Replace or terminate the 24-bit packet link while preserving the high length byte. */

void func_8003F7B4(u32 *packet, u32 address)
{
    *packet = (*packet & 0xFF000000) | (address & 0xFFFFFF);
}

void func_8003F7D8(u32 *packet)
{
    *packet |= 0xFFFFFF;
}
