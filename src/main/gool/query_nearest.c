#include "common.h"

/* GCC_VERSION: 2.6.3 */

void func_80042E9C(void *);
void func_80042ECC(void *);
void func_80033FBC(void *, u32, s32);
s32 *func_80016E18(void);
void func_80035438(u16 *, s32, s32, s32, s32 *, void *);
void func_80035898(u16 *, s32, s32, s32, s32 *, void *);
void func_80035E10(u16 *, s32, s32, s32, s32 *, void *);
void func_80036340(u16 *, s32, s32, s32, s32 *, void *);
void func_80036BF4(u16 *, s32, s32, s32, s32 *, void *, u32, s32);
void func_800375EC(u16 *, s32, s32, s32, s32 *, void *);
void *func_80015A98(void *);

extern struct {
    u8 pad[0x10];
    u8 *data;
} *D_80057914;

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

void *LIBC_Malloc(u32);

s32 func_80029B90(void *, void *);
void func_800252C0(void *, s32, s32, s32 *);

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
