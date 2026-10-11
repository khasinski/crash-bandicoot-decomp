#include "gpu.h"

/* GCC_VERSION: 2.6.3 */

typedef struct {u8 next[3]; u8 length; u32 word04, word08;} Packet;
s32 func_80041544(s16, s16);

void func_80040FE8(Packet *packet, s16 *offset)
{
    packet->length = 2;
    packet->word04 = func_80041544(offset[0], offset[1]);
    packet->word08 = 0;
}
