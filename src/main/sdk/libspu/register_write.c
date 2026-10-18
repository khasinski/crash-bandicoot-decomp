/* GCC_VERSION: 2.6.3 */
#include "common.h"
extern volatile u16 *D_800558E4;

void func_80046DB8(s32 reg,u32 address,s32 shift) {
    if (shift == 0) D_800558E4[reg] = address;
    else D_800558E4[reg] = address >> D_80055908;
}
