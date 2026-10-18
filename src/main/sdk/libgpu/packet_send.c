#include "gpu.h"

/* GCC_VERSION: 2.6.3 */
typedef struct {u8 pad00[0x14];void (*send14)(void *,s32);u8 pad18[0x24];void (*callback3C)(s32);} Api;
extern Api *D_80054A64;
void func_80040760(GpuPacketHeader *packet) {
    u8 length;
    length=packet->length;
    D_80054A64->callback3C(0);
    D_80054A64->send14(&packet->color,length);
}
