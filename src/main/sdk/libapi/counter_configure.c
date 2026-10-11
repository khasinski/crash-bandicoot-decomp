/* GCC_VERSION: 2.6.3 */
/* GCC_CPU: 3000 */
#include "common.h"
extern volatile u16 (*D_80053910)[8];
s32 func_8003E298(s32 counter,s32 target,s32 flags) {
    s32 index=counter&0xFFFF;
    s32 mode=0x48;
    volatile u16 *registers;
    if (index>=3) return 0;
    registers=D_80053910[index];
    registers[2]=0;
    registers[4]=target;
    if ((u32)index<2) {
        if (flags&0x10) mode=0x49;
        if (!(flags&1)) mode|=0x100;
    } else if (index==2) {
        if (!(flags&1)) mode=0x248;
    }
    if (flags&0x1000) mode|=0x10;
    D_80053910[index][2]=mode;
    return 1;
}
