/* GCC_VERSION: 2.5.7 */
/* GCC_CPU: r4000 */
/* ASPSX_VERSION: 2.34 */
#include "common.h"

typedef struct {
    u16 unk0;
    u16 unk2;
    u16 unk4;
    volatile u16 unk6;
    u8 pad8[19];
    u8 unk1B;
    s16 unk1C;
    u8 pad1E[10];
    s16 unk28;
    u8 pad2A[10];
} VoiceStruct;

extern s32 D_8005E744;
extern u32 D_80060D70[];
extern u8 D_8005E340;
extern VoiceStruct D_800572AC[];
extern u16 *D_80056270;
extern u8 D_8005E710;
extern u16 D_80061A68;
extern u16 D_80061A70;
extern u16 D_8005724C;
extern u16 D_80057254;
extern u16 D_8005725C;
extern u16 D_80057264;
extern void (*D_8005E708)(s32);
extern void (*D_8005E550)(s32);
extern u8 D_800577A4[];
extern u16 D_8005E588[];
extern u32 D_80056274;

void func_8004DA78(s32, s32);

void func_8004D680(void) {
    s32 i = 0;
    u32 Mask2;
    u32 mask = 0;

    D_8005E744 = (D_8005E744 + 1) & 0xF;
    D_80060D70[D_8005E744] = 0;
    for (i = 0; i < D_8005E340; i++) {
        D_800572AC[i].unk6 = D_80056270[i * 8 + 6];
        if (D_800572AC[i].unk6 == 0) {
            D_80060D70[D_8005E744] |= (1 << i);
        }
    }
    if (D_8005E710 == 0) {
        Mask2 = 0xFFFFFFFF;
        for (i = 0; i < 15; i++) {
            Mask2 &= D_80060D70[i];
        }
        for (i = 0; i < D_8005E340; i++) {
            if (Mask2 & (1 << i)) {
                if (D_800572AC[i].unk1B == 2) {
                    func_8004DA78(0, 0xFFFFFF);
                }
                D_800572AC[i].unk1B = 0;
            }
        }
    }
    i = 0;
    D_8005724C &= ~D_80061A68;
    D_80057254 &= ~D_80061A70;
    for (i = 0; i < 24; i++) {
        if (D_800572AC[i].unk1C != 0) {
            D_8005E708(i);
        }
        if (D_800572AC[i].unk28 != 0) {
            D_8005E550(i);
        }
    }
    for (i = 0; i < 24; i++) {
        if (D_800577A4[i] & 1) {
            D_80056270[i * 8 + 0] = D_8005E588[i * 8 + 0];
            D_80056270[i * 8 + 1] = D_8005E588[i * 8 + 1];
        }
        if (D_800577A4[i] & 4) {
            D_80056270[i * 8 + 2] = D_8005E588[i * 8 + 2];
        }
        if (D_800577A4[i] & 8) {
            D_80056270[i * 8 + 3] = D_8005E588[i * 8 + 3];
        }
        if (D_800577A4[i] & 0x10) {
            D_80056270[i * 8 + 4] = D_8005E588[i * 8 + 4];
            D_80056270[i * 8 + 5] = D_8005E588[i * 8 + 5];
        }
        D_800577A4[i] = 0;
    }
    D_80056270[0xC6] = D_80061A68;
    D_80056270[0xC7] = D_80061A70;
    D_80056270[0xC4] = D_8005724C;
    D_80056270[0xC5] = D_80057254;
    if (D_8005E340 < 24) {
        mask = (D_80056270[0xCD] << 16) | D_80056270[0xCC];
        mask &= D_80056274;
    }
    D_80061A68 = 0;
    D_80061A70 = 0;
    D_8005724C = 0;
    D_80057254 = 0;
    D_80056270[0xCC] = D_8005725C | mask;
    D_80056270[0xCD] = D_80057264 | (mask >> 16);
}
