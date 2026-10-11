#include "common.h"
#include "gpu.h"

/* GCC_VERSION: 2.6.3 */

/* Set or clear the transparency and raw-texture command bits. */

void func_8003F7F0(GpuPacketHeader *packet,s32 enabled)
{
    u8 command;
    if(enabled) command=packet->command|2;
    else command=packet->command&0xFD;
    packet->command=command;
}

void func_8003F818(GpuPacketHeader *packet,s32 enabled)
{
    u8 command;
    if(enabled) command=packet->command|1;
    else command=packet->command&0xFE;
    packet->command=command;
}
