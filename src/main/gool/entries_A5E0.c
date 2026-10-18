/* GCC_VERSION: 2.6.3 */
/* GNU_AS_G: 8 */
#include "common.h"

void func_80042E9C(void *);
void func_80042ECC(void *);
void func_80033FBC(void *, u32, s32);
s32 *func_80016E18(void);
void func_80035E10(u16 *, s32, s32, s32, s32 *, void *);
void func_80036340(u16 *, s32, s32, s32, s32 *, void *);

extern u16 *D_800566B8[];
extern u8 D_800577E4[];
extern struct {
    u8 pad[0x10];
    u8 *data;
} *D_80057914[];
extern s32 D_800578D0[];
extern s32 D_80057960[];
extern u8 D_80051774[];

extern s32 D_80056440;
extern s32 D_80056444;
extern s32 D_80056448;
extern s32 D_8005644C;
extern s32 D_80056450;
extern s32 D_80056454;
extern s32 D_80056458;
extern s32 D_8005645C;
extern s32 D_80056400[];
extern s32 D_80056474;
extern s32 D_80056478;
extern s32 D_800567B8[];

void func_80019DE0(s32 arg0)
{
    s32 i;
    s32 val;

    if (arg0 == 0) {
        for (i = 0; i < 16; i++) {
            D_800567B8[i] = ((D_80056478 + 1) / 8) * i - D_80056478;
        }
        return;
    }
    if (*D_800566B8[0] != 0) {
        if (D_80056400[0] == 0) {
            for (i = 0; i < 16; i++) {
                val = D_800567B8[i] + D_80056474;
                D_800567B8[i] = val;
                if (val > D_80056478) {
                    val = -D_80056478 + 1;
                    D_800567B8[i] = val;
                }
            }
        }
        for (i = 0; i < 16; i++) {
            val = D_800567B8[i];
            ((s32 *)0x1F800048)[i] = val >= 0 ? val : -val;
        }
        func_80042E9C(D_800577E4);
        func_80042ECC(D_800577E4 + 0x110);
        func_80033FBC(D_80057914[0]->data + 4, 0x1F800100, 0x100);
        func_80035E10(D_800566B8[0], arg0, 0x800 - (D_800578D0[0] / 2), D_80057960[0], func_80016E18(), D_80051774);
    }
}

void func_80019F90(s32 arg0)
{
    if (*D_800566B8[0] != 0) {
        func_80042E9C(D_800577E4);
        func_80042ECC(D_800577E4 + 0x110);
        func_80033FBC(D_80057914[0]->data + 4, 0x1F800100, 0x100);
        *(s32 *)0x1F800048 = D_80056440 << 4;
        *(s32 *)0x1F80004C = D_80056444 << 4;
        *(s32 *)0x1F800050 = D_80056448 << 4;
        *(s32 *)0x1F800054 = D_8005644C;
        *(s32 *)0x1F800058 = D_80056450 << 4;
        *(s32 *)0x1F80005C = D_80056454 << 4;
        *(s32 *)0x1F800060 = D_80056458 << 4;
        *(s32 *)0x1F800064 = D_8005645C;
        func_80036340(D_800566B8[0], arg0, 0x800 - (D_800578D0[0] / 2), D_80057960[0], func_80016E18(), D_80051774);
    }
}

