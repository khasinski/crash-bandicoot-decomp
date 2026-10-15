/* GCC_VERSION: 2.6.3 */
#include "common.h"
extern volatile u32 *D_80054B3C;
extern volatile u32 *D_80054B40;
extern u8 D_80057098[256];
void func_80041ED4(u32 command) {
    *D_80054B40 = command;
    D_80057098[command >> 24] = command;
}
u8 func_80041EFC(s32 index) {
    return D_80057098[index];
}
s32 func_80041F10(u32 *data, s32 count) {
    *D_80054B40 = 0x04000000;
    while (--count != -1) {
        *D_80054B3C = *data++;
    }
    return 0;
}
