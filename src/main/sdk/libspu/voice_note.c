/* GCC_VERSION: 2.5.7 */
/* GCC_CPU: r4000 */
/* ASPSX_VERSION: 2.34 */
#include "common.h"
s32 func_8004E330(s16,s16,s16,s32);
/* The retail call passes an unused mode value; allocation returns an index. */
s32 func_8004E59C(s32);
void func_8004E80C(void);
s32 func_8004EA24(void);
void func_8004EBDC(s16);
void func_8004F1A4(u8,u16);
s32 func_800500F8(u8 *,u8 *);
s32 func_80050728(s16,s16);
extern u8 D_800572AC[],D_800572AE[],D_800572B4[],D_800572B6[],D_800572B8[],D_800572BA[],D_800572BC[],D_800572BE[],D_800572C0[],D_800572C2[],D_800572C4[],D_800572C7[];
extern u8 *D_8005CFCC,*D_8005CFDC,*D_8005CFE4;
extern u8 D_8005E340,D_8005E55A,D_8005E55B,D_8005E55C,D_8005E55F,D_8005E562,D_8005E563;
/* Shared note context; the sample cursor points 24 bytes into it. */
extern u8 D_8005E558[32];
extern s16 D_8005E56E,D_8005E572;
extern u8 *D_80060418[];
s32 func_8004DDE4(s16 arg0, s16 arg1, s16 arg2, u16 arg3, u16 arg4, u16 arg5) {
    /* The selector writes parallel byte lists of samples and tone indices. */
    u8 sp10[128];
    u8 sp90[128];
    s16 temp_v0_3;
    s32 temp_v0_2;
    s32 var_s1;
    s32 var_s2;
    s32 var_v1;
    u8 *temp_s0;
    u8 *temp_s0_2;
    u8 *temp_v0;
    u8 *temp_v1;

    var_s2 = 0;
    temp_s0 = ((((u32) arg0 << 0x10) >> 0x18) * 0xAC) + D_80060418[arg0&255];
    if (func_80050728(arg1, arg2) != 0) {
        return -1;
    }
    {
        D_8005E56E = arg0;
        D_8005E55A = arg3;
        D_8005E55B = 0;
        if (arg0 == 0x21) {
            D_8005E55C = (s8) arg4;
        } else {
            D_8005E55C = (s8) ((s32) (arg4 * *(s16*)(temp_s0 + temp_s0[0x12]*2 + 0x4E)) / 127);
        }
        D_8005E558[5] = (s8) arg5;
        temp_v0 = (arg2 * 0x10) + D_8005CFCC;
        D_8005E562 = temp_v0[1];
        D_8005E563 = temp_v0[4];
        D_8005E558[0] = temp_v0[0];
        if ((u8)D_8005E55F >= *(u16*)(D_8005CFDC+0x12)) {
            return -1;
        }
        {
            if (arg4 == 0) {
                var_s2 = func_8004E330(arg0, arg1, arg2, arg3 & 0xFFFF);
            } else {
                temp_v0_2 = func_800500F8(sp90, sp10);
                var_s1 = 0;
                if (temp_v0_2 & 0xFF) {
                    temp_s0_2 = D_8005E558 + 0x18;
                    do {
                        var_v1 = var_s1 & 0xFF;
                        *(u16*)temp_s0_2 = (u16) sp10[var_v1];
                        temp_s0_2[-0xC] = (u8) sp90[var_v1];
                        temp_v1 = ((temp_s0_2[-0xC] + (temp_s0_2[-0x11] * 0x10)) << 5) + D_8005CFE4;
                        temp_s0_2[-0x9] = (u8) temp_v1[0];
                        temp_s0_2[-0xB] = (u8) temp_v1[2];
                        temp_s0_2[-0xA] = (u8) temp_v1[3];
                        temp_s0_2[-0x8] = (u8) temp_v1[4];
                        temp_s0_2[-0x7] = (u8) temp_v1[5];
                        temp_s0_2[-0x4] = (u8) temp_v1[1];
                        temp_s0_2[-0x6] = (u8) temp_v1[6];
                        temp_s0_2[-0x5] = (u8) temp_v1[7];
                        temp_v0_3 = func_8004E59C(0);
                        *(s16*)(temp_s0_2+2) = temp_v0_3;
                        if (temp_v0_3 < (s32) D_8005E340) {
                            *(u8*)(D_800572C7 + (temp_v0_3 * 0x34)) = 1;
                            *(s16*)(D_800572AE + (*(s16*)(temp_s0_2+2) * 0x34)) = 0;
                            *(s16*)(D_800572BA + (*(s16*)(temp_s0_2+2) * 0x34)) = arg0;
                            *(s16*)(D_800572C2 + (*(s16*)(temp_s0_2+2) * 0x34)) = (s16) temp_s0_2[-0x17];
                            *(s16*)(D_800572BC + (*(s16*)(temp_s0_2+2) * 0x34)) = (s16) temp_s0_2[-0x11];
                            *(s16*)(D_800572BE + (*(s16*)(temp_s0_2+2) * 0x34)) = arg2;
                            if (arg0 != 0x21) {
                                *(s16*)(D_800572B4 + (*(s16*)(temp_s0_2+2) * 0x34)) = arg4;
                            }
                            *(u8*)(D_800572B6 + (*(s16*)(temp_s0_2+2) * 0x34)) = (s8) arg5;
                            *(s16*)(D_800572C0 + (*(s16*)(temp_s0_2+2) * 0x34)) = (s16) temp_s0_2[-0xC];
                            *(s16*)(D_800572B8 + (*(s16*)(temp_s0_2+2) * 0x34)) = (s16) arg3;
                            *(s16*)(D_800572C4 + (*(s16*)(temp_s0_2+2) * 0x34)) = (s16) temp_s0_2[-0x9];
                            *(s16*)(D_800572AC + (*(s16*)(temp_s0_2+2) * 0x34)) = *(u16*)temp_s0_2;
                            func_8004E80C();
                            if ((s16) *(u16*)temp_s0_2 == 0xFF) {
                                func_8004EBDC(*(s16*)(temp_s0_2+2));
                            } else {
                                func_8004F1A4(temp_v0_2 & 0xFF, func_8004EA24() & 0xFFFF);
                            }
                            var_s2 |= 1 << D_8005E572;
                        } else {
                            var_s2 = -1;
                        }
                        var_s1 += 1;
                    } while ((u32) (var_s1 & 0xFF) < (u32) (temp_v0_2 & 0xFF));
                }
            }

        }
    }
    return var_s2;
}
