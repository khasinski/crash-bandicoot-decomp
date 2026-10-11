/* GCC_VERSION: 2.5.7 */
/* GCC_CPU: r4000 */
/* ASPSX_VERSION: 2.34 */
#include "common.h"
extern u8 *D_80056270;
extern u8 D_800572B0[],D_800572C7[];
void func_8004F090(s32 arg0) {
    s32 offset;
    u8 *ports;
    offset = (arg0 & 0xFF) * 0x34;
    D_800572C7[offset] = 0;
    ports = D_80056270;
    *(u16 *)(D_800572B0 + offset) = 0;
    *(u16 *)(ports + 0x194) = 0;
    *(u16 *)(ports + 0x196) = 0;
}
