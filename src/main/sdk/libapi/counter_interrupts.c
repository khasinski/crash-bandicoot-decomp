/* GCC_VERSION: 2.6.3 */
/* GCC_CPU: 3000 */
#include "common.h"


s32 StartRCnt(s32 counter) {
    volatile u32 *registers=D_8005390C;
    counter&=0xFFFF;
    registers[1]|=D_80053914[counter];
    return counter<3;
}
s32 StopRCnt(s32 counter) {
    volatile u32 *registers=D_8005390C;
    counter&=0xFFFF;
    registers[1]&=~D_80053914[counter];
    return 1;
}
s32 ResetRCnt(s32 counter) {
    s32 index=counter&0xFFFF;
    if (index>=3) return 0;
    D_80053910[index][0]=0;
    return 1;
}

