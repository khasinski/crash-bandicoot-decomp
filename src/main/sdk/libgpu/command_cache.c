/* GCC_VERSION: 2.6.3 */
#include "common.h"
extern volatile u32 *D_80054B40;
extern u8 D_80057098[256];
void func_80041ED4(u32 command) {
    *D_80054B40 = command;
    D_80057098[command >> 24] = command;
}
u8 func_80041EFC(s32 index) {
    return D_80057098[index];
}
