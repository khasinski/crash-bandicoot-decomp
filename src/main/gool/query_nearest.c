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


extern void *LIBC_Malloc(u32);

typedef struct GoolAllocGlobals {
    u8 *db0;
    u8 *db4;
    s32 db8[16];
    s32 df8;
    u8 *dfc;
    void *e00;
    s32 e04;
} GoolAllocGlobals;

extern GoolAllocGlobals gool_alloc __asm__("D_80060DB0");
extern u8 * volatile D_80060DB0;
extern u8 *D_80060DB4;
extern s32 D_80060DB8[];
extern s32 D_80060DF8;
extern void *D_80060E00;
extern s32 D_80060E04;

extern s32 func_80029B90(void *, void *);
extern void func_800252C0(void *, s32, s32, s32 *);

typedef struct {
    u32 mask;
    u8 *other;
    u8 *best;
    s32 max_dist;
    s32 event;
} GoolQuery;

s32 func_8001BAB0(u8 *arg0, GoolQuery *arg1)
{
    u8 *other;
    s32 dist;
    s32 event;
    u8 *hdr;
    u32 state;
    u32 state_flags1;
    u32 state_flags2;
    s32 anim_type2;
    u32 target_flags;
    u32 test;
    s32 sp10;

    other = arg1->other;
    if (arg0 == other) {
        return 0;
    }
    if (!((1 << (*(s32 *)(*(u8 **)(*(u8 **)(arg0 + 0x20) + 0x10) + 4) >> 8)) & arg1->mask)) {
        return 0;
    }
    dist = func_80029B90(arg0 + 0x80, other + 0x80);
    if (dist < arg1->max_dist) {
        event = arg1->event;
        if (event != 0xFF) {
            hdr = *(u8 **)(arg0 + 0x20);
            state = ((u16 *)*(u8 **)(hdr + 0x1C))[event >> 8];
            if (state == 0xFF) {
                if ((event == 0x300 && (event = *(s32 *)(arg0 + 0x128), state_flags1 = *(u32 *)(arg0 + 0xD0), (u32)(event - 3) >= 2 && event != 2 && !(state_flags1 & 2)))
                    || (arg1->event == 0xA00 && !(*(u32 *)(arg0 + 0x120) & 0x800))
                    || arg1->event == 0x1D00) {
                    state = 0xFE;
                } else {
                    return 0;
                }
            } else {
                if (!(state & 0x8000)) {
                    state_flags2 = *(u32 *)(arg0 + 0xD0);
                    anim_type2 = *(s32 *)(arg0 + 0x128);
                    target_flags = *(u32 *)((state << 4) + *(s32 *)(hdr + 0x20));
                    if ((u32)(anim_type2 - 3) < 2 || anim_type2 == 2) {
                        test = (state_flags2 | 0x1002) & target_flags;
                    } else {
                        test = state_flags2 & target_flags;
                    }
                    if (test != 0) {
                        return 0;
                    }
                }
                if (state & 0x8000) {
                    if (arg1->event == 0xF00) {
                        sp10 = 0x100;
                        *(u8 **)(arg0 + 0x7C) = arg1->other;
                        func_800252C0(arg0, state, 1, &sp10);
                        if (*(s32 *)(arg1->other + 0xF8) == 0) {
                            return 0;
                        }
                    }
                }
            }
        } else {
            state = 0xFE;
        }
        if (state != 0xFF) {
            arg1->best = arg0;
            arg1->max_dist = dist;
        }
    }
    return 0;
}
