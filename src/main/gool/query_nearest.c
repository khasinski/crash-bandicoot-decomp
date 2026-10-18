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

typedef struct GoolCodeHeader {
    s32 unk00;
    s32 category;
} GoolCodeHeader;

typedef struct GoolExecutable {
    u8 pad00[0x10];
    GoolCodeHeader *header;
    void *code;
    void *data;
    u16 *states;
    s32 states_base;
} GoolExecutable;

typedef struct GoolObj {
    u8 pad00[0x20];
    GoolExecutable *exec;
    u8 pad24[0x58];
    struct GoolObj *interrupter;
    s32 trans[3];
    u8 pad8C[0x44];
    u32 status_c;
    u8 padD4[0x24];
    s32 unkF8;
    u8 padFC[0x24];
    u32 state_flags;
    u8 pad124[4];
    s32 anim_type;
} GoolObj;

typedef struct {
    u32 mask;
    GoolObj *other;
    GoolObj *best;
    s32 max_dist;
    s32 event;
} GoolQuery;

s32 func_8001BAB0(GoolObj *arg0, GoolQuery *arg1)
{
    GoolObj *other;
    s32 dist;
    s32 event;
    GoolExecutable *hdr;
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
    if (!((1 << (arg0->exec->header->category >> 8)) & arg1->mask)) {
        return 0;
    }
    dist = func_80029B90(arg0->trans, other->trans);
    if (dist < arg1->max_dist) {
        event = arg1->event;
        if (event != 0xFF) {
            hdr = arg0->exec;
            state = hdr->states[event >> 8];
            if (state == 0xFF) {
                if ((event == 0x300 && (event = arg0->anim_type, state_flags1 = arg0->status_c, (u32)(event - 3) >= 2 && event != 2 && !(state_flags1 & 2)))
                    || (arg1->event == 0xA00 && !(arg0->state_flags & 0x800))
                    || arg1->event == 0x1D00) {
                    state = 0xFE;
                } else {
                    return 0;
                }
            } else {
                if (!(state & 0x8000)) {
                    state_flags2 = arg0->status_c;
                    anim_type2 = arg0->anim_type;
                    target_flags = *(u32 *)((state << 4) + hdr->states_base);
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
                        arg0->interrupter = arg1->other;
                        func_800252C0(arg0, state, 1, &sp10);
                        if (arg1->other->unkF8 == 0) {
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
