/* GCC_VERSION: 2.6.3 */
/* GCC_CPU: 3000 */
#include "common.h"
extern volatile u32 *D_8005390C;
extern u32 D_80053914[];
s32 func_8003E370(s32 counter) {
    volatile u32 *registers=D_8005390C;
    counter&=0xFFFF;
    registers[1]|=D_80053914[counter];
    return counter<3;
}
s32 func_8003E3A4(s32 counter) {
    volatile u32 *registers=D_8005390C;
    counter&=0xFFFF;
    registers[1]&=~D_80053914[counter];
    return 1;
}
