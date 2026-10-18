/* GCC_VERSION: 2.5.7 */
/* GCC_CPU: r4000 */
/* ASPSX_VERSION: 2.34 */
#include "common.h"


typedef struct {
    u16 unk0;
    u16 unk2;
    u8 pad4[2];
    u16 unk6;
    u8 pad8[16];
    s16 unk18;
    u8 pad1A;
    u8 unk1B;
    u8 pad1C[24];
} VoiceStruct;

typedef struct { u16 value; u8 pad[50]; } VoiceU16;
typedef struct { s16 value; u8 pad[50]; } VoiceS16;
typedef struct { u8 value; u8 pad[51]; } VoiceU8;

typedef struct {
    u8 unk0[7];
    u8 unk7;
    u8 unk8[4];
    u8 unkC;
    u8 unkD[2];
    u8 unkF;
    u8 unk10[8];
    s16 unk18;
    s16 unk1A;
    s16 unk1C;
    s16 unk1E;
} SvmCur;

extern SvmCur D_8005E558;
extern VoiceU16 D_800572B2[];
extern u32 D_80060D70[];
extern u8 *D_8005CFCC;
extern u32 D_8005CFE4;
extern u16 D_8005E58E[];
extern u16 D_8005E590[];
extern u16 D_8005E592[];
extern u8 D_800577A4[];
extern u16 D_80057EF0;
void func_8004DA78(s32, s32);


void func_8004E80C(void) {
    s32 var_t0;
    s32 pad[2];

    D_8005E558.unk1C = D_8005E558.unk1A * 8;
    D_8005E558.unk1E = (D_8005E558.unk7 << 4) + D_8005E558.unkC;
    D_800572B2[D_8005E558.unk1A].value = 0x7FFF;
    for (var_t0 = 0; var_t0 < 0x10; var_t0++) {
        D_80060D70[var_t0] &= ~(1 << D_8005E558.unk1A);
    }
    if ((D_8005E558.unk18 & 1) > 0) {
        D_8005E58E[D_8005E558.unk1C] = *(u16 *)(D_8005CFCC + ((((s16) D_8005E558.unk18 - 1) / 2) * 0x10) + 0xC);
        D_800577A4[D_8005E558.unk1A] |= 8;
    } else {
        D_8005E58E[D_8005E558.unk1C] = *(u16 *)(D_8005CFCC + ((((s16) D_8005E558.unk18 - 1) / 2) * 0x10) + 0xE);
        D_800577A4[D_8005E558.unk1A] |= 8;
    }
    D_8005E590[D_8005E558.unk1C] = *(u16 *)(((((D_8005E558.unk7 << 4) + D_8005E558.unkC) << 5) + D_8005CFE4) + 0x10);
    D_8005E592[D_8005E558.unk1C] = *(u16 *)(((((D_8005E558.unk7 << 4) + D_8005E558.unkC) << 5) + D_8005CFE4) + 0x12) + D_80057EF0;
    D_800577A4[D_8005E558.unk1A] |= 0x30;
}
