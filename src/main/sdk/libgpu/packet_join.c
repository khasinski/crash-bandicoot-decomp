#include "common.h"

/* GCC_VERSION: 2.6.3 */

/* Combine packet lengths within the inline limit and clear the second tag. */

#include "gpu.h"
s32 func_8003FB5C(GpuPacketHeader *first,GpuPacketHeader *second) {
    s32 length = first->length + second->length + 1;
    s32 result;
    if (length < 0x21) {
        result = 0;
        first->length = length;
        *(u32 *)second = 0;
    } else {
        result = -1;
    }
    return result;
}
