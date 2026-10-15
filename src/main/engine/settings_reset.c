#include "common.h"

/* GCC_VERSION: 2.6.3 */
void func_80026200(s32);                                 /* extern */
void BIOS_MemSet(void *, s32, s32);                      /* extern */
void func_8003D1B4(void);                                /* extern */
extern u8 D_8005E348[];
extern s32 D_800618A0;
extern s32 D_800618D0;
extern s32 D_800618D4;
extern s32 D_800618D8;
extern s32 D_800618DC;
extern s32 D_800618E0;
extern s32 D_800618EC;
extern s32 D_800618F0;
extern s32 D_800618F4;
extern s32 D_800618F8;
extern s32 D_800618FC;
extern s32 D_80061900;
extern s32 D_80061908;
extern s32 D_8006190C;
extern s32 D_80061910;
extern s32 D_80061914;
extern s32 D_80061918;
extern s32 D_80061944;
extern s32 D_80061948;
extern s32 D_80061988;
extern s32 D_80061998;
extern s32 D_8006199C;
extern s32 D_800619A0;
extern s32 D_800619AC;
extern s32 D_80061A1C;
extern s32 D_80061A20;
extern s32 D_80061A3C;
extern s32 D_80061A40;
extern s32 D_80061A50;
extern s32 D_80061A58;

void func_80026140(void) {
    D_800618DC = 0x63;
    D_800618D8 = -1;
    D_800618D4 = 7;
    D_80061914 = 0xFF;
    D_80061918 = 0xFF;
    D_80061908 = 0x400;
    D_800618E0 = 0;
    D_8006190C = 0;
    D_80061910 = 0;
    D_80061944 = 1;
    D_8006199C = 0;
    D_80061A40 = 0;
    D_80061A58 = 0;
    D_800618D0 = 0;
    D_80061A1C = 0;
    D_80061A20 = 0;
    D_80061A50 = 1;
    func_80026200(1);
}

void func_80026200(s32 arg0) {
    if (arg0 != 0) {
        D_80061A3C = 0;
        D_800618A0 = 0;
        D_800618F0 = 0;
        D_800618F4 = 0;
        D_800618F8 = 0;
        D_800618FC = 0;
        D_80061900 = 0;
        D_80061948 = 1;
        D_80061988 = 0;
        D_800619A0 = -1;
        D_800619AC = 0;
        D_80061998 = 1;
        D_800618DC = 0x63;
        D_80061944 = 1;
        D_80061A1C = 0;
        D_80061A20 = 0;
        D_80061A50 = 1;
        D_800618EC = D_80061908;
        BIOS_MemSet(D_8005E348, 0, 0x200);
        func_8003D1B4();
    }
}

