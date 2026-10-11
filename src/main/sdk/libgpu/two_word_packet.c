#include "gpu.h"

/* GCC_VERSION: 2.6.3 */
typedef struct {u8 next[3];u8 length;u32 word04,word08;} Packet;
extern s32 func_80041350(s32,s32,s32);
void func_80041054(Packet *packet,s32 arg1,s32 arg2,s32 arg3,GpuRect *arg4) {
    packet->length=2;
    packet->word04=func_80041350(arg1,arg2,arg3&0xFFFF);
    packet->word08=func_8004158C(arg4);
}
