#include "gpu.h"

/* GCC_VERSION: 2.6.3 */

typedef struct {u8 next[3]; u8 length; u32 word04, word08;} Packet;

void func_80040F28(Packet *packet, GpuRect *rect)
{
    packet->length = 2;
    packet->word04 = func_8004158C(rect);
    packet->word08 = 0;
}
