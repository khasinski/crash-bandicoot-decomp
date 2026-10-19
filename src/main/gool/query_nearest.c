#include "common.h"

/* GCC_VERSION: 2.6.3 */

void SetRotMatrix(void *);
void SetLightMatrix(void *);
void RMemcpy(void *, u32, s32);
s32 *Gpu_GetCurPrimsTail(void);
void Gte_RTransformWorlds(u16 *, s32, s32, s32, s32 *, void *);
void Gte_RTransformWorldsFog(u16 *, s32, s32, s32, s32 *, void *);
void Gte_RTransformWorldsRipple(u16 *, s32, s32, s32, s32 *, void *);
void Gte_RTransformWorldsLightning(u16 *, s32, s32, s32, s32 *, void *);
void Gte_RTransformWorldsDark(u16 *, s32, s32, s32, s32 *, void *, u32, s32);
void Gte_RTransformWorldsDark2(u16 *, s32, s32, s32, s32 *, void *);
void *Ns_Lookup(void *);

extern struct {
    u8 pad[0x10];
    u8 *data;
} *g_pads;

extern struct {
    s32 unk0;
    s32 type;
} *g_ns_page_pool;

void *LIBC_Malloc(u32);

s32 Math_ApxDist(void *, void *);
void Gool_ObjectInterrupt(void *, s32, s32, s32 *);

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

s32 Gool_FindNearestObject(GoolObj *arg0, GoolQuery *arg1)
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
    dist = Math_ApxDist(arg0->trans, other->trans);
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
                        Gool_ObjectInterrupt(arg0, state, 1, &sp10);
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
