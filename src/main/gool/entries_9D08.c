#include "common.h"

/* GCC_VERSION: 2.6.3 */

extern void func_80042E9C(void *);
extern void func_80042ECC(void *);
extern void func_80033FBC(void *, u32, s32);
extern s32 *func_80016E18(void);
extern void func_80035438(u16 *, s32, s32, s32, s32 *, void *);
extern void func_80035898(u16 *, s32, s32, s32, s32 *, void *);
extern void func_80035E10(u16 *, s32, s32, s32, s32 *, void *);
extern void func_80036340(u16 *, s32, s32, s32, s32 *, void *);
extern void func_80036BF4(u16 *, s32, s32, s32, s32 *, void *, u32, s32);
extern void func_800375EC(u16 *, s32, s32, s32, s32 *, void *);
extern void *func_80015A98(void *);

extern u16 *D_800566B8;
extern u8 D_800577E4[];
extern struct {
    u8 pad[0x10];
    u8 *data;
} *D_80057914;
extern s32 D_800578D0;
extern s32 D_80057960;
extern u8 D_80051774[];

extern struct {
    s32 unk0;
    s32 type;
} *D_8005C53C;
extern struct {
    u8 pad000[0xAA8];
    s32 wordAA8;
    u8 padAAC[0xAC8 - 0xAAC];
    s32 wordAC8;
} D_80060DF0;

extern s32 D_80056440;
asm(".sdata\n.size D_80056440,4\n.text");
extern s32 D_80056444;
asm(".sdata\n.size D_80056444,4\n.text");
extern s32 D_80056448;
asm(".sdata\n.size D_80056448,4\n.text");
extern s32 D_8005644C;
asm(".sdata\n.size D_8005644C,4\n.text");
extern s32 D_80056450;
asm(".sdata\n.size D_80056450,4\n.text");
extern s32 D_80056454;
asm(".sdata\n.size D_80056454,4\n.text");
extern s32 D_80056458;
asm(".sdata\n.size D_80056458,4\n.text");
extern s32 D_8005645C;
asm(".sdata\n.size D_8005645C,4\n.text");
extern s32 D_80056460;
asm(".sdata\n.size D_80056460,4\n.text");
extern s32 D_80056464;
asm(".sdata\n.size D_80056464,4\n.text");
extern s32 D_80056468;
asm(".sdata\n.size D_80056468,4\n.text");
extern s32 D_8005646C;
asm(".sdata\n.size D_8005646C,4\n.text");
extern s32 D_800566D4;
asm(".sdata\n.size D_800566D4,4\n.text");
extern s32 D_800566D8;
asm(".sdata\n.size D_800566D8,4\n.text");
extern s32 D_800566DC;
asm(".sdata\n.size D_800566DC,4\n.text");
extern s32 D_80056400;
extern s32 D_80056474;
asm(".sdata\n.size D_80056474,4\n.text");
extern s32 D_80056478;
asm(".sdata\n.size D_80056478,4\n.text");
extern s32 D_800567B8[];
extern void * D_800566B4;
asm(".sdata\n.size D_800566B4,4\n.text");


void func_80019508(s32 arg0)
{
    if (*D_800566B8 != 0) {
        func_80042E9C(D_800577E4);
        func_80042ECC(D_800577E4 + 0x110);
        func_80033FBC(D_80057914->data + 4, 0x1F800100, 0x100);
        func_80035438(D_800566B8, arg0, 0x800 - (D_800578D0 / 2), D_80057960, func_80016E18(), D_80051774);
    }
}

