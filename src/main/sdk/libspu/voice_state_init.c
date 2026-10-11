/* GCC_VERSION: 2.5.7 */
/* GCC_CPU: r4000 */
/* ASPSX_VERSION: 2.34 */
#include "common.h"
void func_8004DDA8(s32);
void func_80045D70(s32,void *);
/* Retail passes 1; this callee does not consume incoming arguments. */
void func_8004F0D4();
void func_8004D680(void);
extern volatile u8 *D_80056270;
extern u8 D_800571C4[];
extern s16 D_8005724C;
extern s16 D_80057254;
extern s16 D_8005725C;
extern s16 D_80057264;
extern s32 D_8005778C;
extern s32 D_80057790;
extern s16 D_80057794;
extern s16 D_80057796;
extern s16 D_80057EF0;
extern s16 D_800583F8;
extern s16 D_8005CFC4;
extern u8 D_8005E340;
extern s16 D_8005E572;
extern s8 D_8005E710;
extern s16 D_80060CE8;
extern s16 D_80061A68;
extern u8 D_800572AC[];
extern u8 D_800572AE[];
extern u8 D_800572B0[];
extern u8 D_800572B2[];
extern u8 D_800572B4[];
extern u8 D_800572B6[];
extern u8 D_800572BA[];
extern u8 D_800572BC[];
extern u8 D_800572BE[];
extern u8 D_800572C0[];
extern u8 D_800572C7[];
extern u8 D_800572C8[];
extern u8 D_800572CA[];
extern u8 D_800572CC[];
extern u8 D_800572CE[];
extern u8 D_800572D0[];
extern u8 D_800572D4[];
extern u8 D_800572D6[];
extern u8 D_800572D8[];
extern u8 D_800572DA[];
extern u8 D_800572DC[];
extern u8 D_800577A4[];
extern u8 D_8005E578[];
extern u16 D_8005E588[];
void func_8004DA9C(s32 arg0) {
    u32 index;
    u16 register_offset;
    s32 temp_v0;
    u32 temp_a0;
    u16 *temp_a1;

    func_8004DDA8(0);
    D_80057EF0 = 0;
    func_80045D70(0x20, &D_800571C4);
    index = 0;
    do {
        D_8005E588[(index & 0xFFFF)] = 0;
        index += 1;
    } while ((u32) (index & 0xFFFF) < 0xC0U);
    index = 0;
    do {
        D_800577A4[(index & 0xFFFF)] = 0;
        index += 1;
    } while ((u32) (index & 0xFFFF) < 0x18U);
    D_80060CE8 = 0;
    index = 0;
    do {
        D_8005E578[(index & 0xFFFF)] = 0;
        index += 1;
    } while ((u32) (index & 0xFFFF) < 0x10U);
    temp_a0 = arg0 & 0xFF;
    if (temp_a0 >= 0x18U) {
        D_8005E340 = 0x18;
    } else {
        D_8005E340 = temp_a0;
    }
    index = 0;
    if (D_8005E340 != 0) {
        do {
            register_offset = (index & 0xFFFF) * 8;
            temp_v0 = (index & 0xFFFF) * 0x34;
            *(s16 *)(D_800572AE + temp_v0) = 0x18;
            *(s16 *)(D_800572AC + temp_v0) = 0xFF;
            D_800572C7[temp_v0] = 0;
            *(s16 *)(D_800572B0 + temp_v0) = 0;
            *(s16 *)(D_800572B2 + temp_v0) = 0;
            *(s16 *)(D_800572BA + temp_v0) = -1;
            *(s16 *)(D_800572BC + temp_v0) = 0;
            *(s16 *)(D_800572BE + temp_v0) = 0;
            *(s16 *)(D_800572C0 + temp_v0) = 0xFF;
            *(s16 *)(D_800572B4 + temp_v0) = 0;
            D_800572B6[temp_v0] = 0x40;
            *(s16 *)(D_800572C8 + temp_v0) = 0;
            *(s16 *)(D_800572CA + temp_v0) = 0;
            *(s16 *)(D_800572CC + temp_v0) = 0;
            *(s16 *)(D_800572CE + temp_v0) = 0;
            *(s16 *)(D_800572D4 + temp_v0) = 0;
            *(s16 *)(D_800572D6 + temp_v0) = 0;
            *(s16 *)(D_800572D8 + temp_v0) = 0;
            *(s16 *)(D_800572DA + temp_v0) = 0;
            *(s16 *)(D_800572DC + temp_v0) = 0;
            *(s16 *)(D_800572D0 + temp_v0) = 0;
            temp_a1 = (u16 *)(((register_offset & 0xFFFF) * 2) + (u32)D_80056270);
            temp_a1[0] = 0;
            temp_a1[1] = 0;
            temp_a1[3] = 0x200;
            temp_a1[2] = 0x1000;
            temp_a1[4] = 0x80FF;
            temp_a1[5] = 0x4000;
            D_8005E572 = index;
            func_8004F0D4(1);
            index += 1;
            } while ((u32) (index & 0xFFFF) < (u8) D_8005E340);
    }
    D_8005724C = 0;
    D_80057254 = 0;
    D_80061A68 = 0;
    D_8005725C = 0;
    D_80057264 = 0;
    D_8005778C = 0;
    D_80057794 = 0x3FFF;
    D_80057796 = 0x3FFF;
    D_80057790 = 0;
    D_8005E710 = 0;
    D_800583F8 = 0;
    D_8005CFC4 = 0x80;
    func_8004D680();
}
