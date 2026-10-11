#include "gpu.h"

/* GCC_VERSION: 2.6.3 */

/* Insert destination after source, preserving both packet lengths. */
void func_8003F73C(GpuPacketTag *source, GpuPacketTag *destination)
{
    destination->next = source->next;
    source->next = (u32)destination;
}

/* Copy source's successor to destination, then replace source's link. */
void func_8003F778(GpuPacketTag *source, u32 address, GpuPacketTag *destination)
{
    destination->next = source->next;
    source->next = address;
}
