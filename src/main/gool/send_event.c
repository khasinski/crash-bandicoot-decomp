/* GCC_VERSION: 2.6.3 */
/* GNU_AS_G: 8 */
#include "common.h"

static __inline__ s32 func_8001FB20(s32 value, s32 bits)
{
    s32 shift = 0x20 - bits;
    return (s32)((u32)value << shift) >> shift;
}

void printf(char *, ...);

typedef struct GoolExecView {
    u8 pad00[0x10];
    struct {
        s32 unk00;
        s32 unk04;
        s32 unk08;
        s32 unk0C;
        s32 unk10;
    } *header;
    u8 *code;
    s32 *data;
    u16 *states;
    u8 *unk20;
} GoolExecView;

typedef struct GoolObjView {
    u8 pad00[0x20];
    GoolExecView *exec;
    GoolExecView *external;
    u8 pad28[0x38];
    struct GoolObjView *links[8];
    u8 pad80[0x48];
    u32 status_a;
    u32 status_b;
    u32 status_c;
    u8 padD4[0x8];
    s32 *sp;
    u32 *pc;
    s32 *fp;
    u32 *unkE8;
    u32 *unkEC;
    s32 unkF0;
    s32 unkF4;
    u8 padF8[0x30];
    s32 anim_type;
    u8 pad12C[0x10];
    s32 event;
} GoolObjView;

typedef struct GoolTimeState {
    u8 pad00[0x84];
    u32 unk84;
} GoolTimeState;

extern GoolTimeState *D_80058404[];

#define ABS(x) ((x) < 0 ? -(x) : (x))
#define SCALE_DT(x) (((s32)((x) * (D_80058404[0]->unk84 < 0x67U ? D_80058404[0]->unk84 : 0x66))) / 1024)

extern GoolObjView *D_800566B4;
s32 GOOL_InterpretObject(GoolObjView *, s32, void *);
s32 GOOL_ChangeObjectState(GoolObjView *, s32, s32, s32 *);

static __inline__ s32 GOOL_CreateObjectStackFrame(GoolObjView *object, s32 arg_words, s32 flags)
{
    u32 *sp;
    u32 *old_fp;
    u32 *new_sp;
    u32 *new_fp;

    sp = (u32 *)object->sp;
    old_fp = (u32 *)object->fp;
    object->fp = (s32 *)sp;
    *object->sp++ = flags;
    *object->sp++ = (s32)object->pc;
    *object->sp++ = ((u32)(new_sp = sp - arg_words - 24) - (u32)object) | (((u32)(new_fp = old_fp - 24) - (u32)object) << 16);
    return -0xFF;
}

s32 func_80024040(GoolObjView *sender, GoolObjView *recipient, s32 event, s32 argc, s32 *argv)
{
    s32 sp10[2];
    s32 res;
    u32 state;
    s32 idx;
    s32 i;
    u32 status_c;
    u32 target_flags;
    s32 anim_type;
    u32 test;

    res = -0x1A;
    if (recipient != NULL) {
        if (sender != NULL) {
            sender->unkF4 = 1;
        }
        recipient->links[7] = sender;
        if (recipient->unkEC != NULL) {
            *recipient->sp++ = event;
            *recipient->sp++ = (s32)argv;
            GOOL_CreateObjectStackFrame(recipient, 2, 0xFFFF);
            recipient->pc = recipient->unkEC;
            res = GOOL_InterpretObject(recipient, 8, sp10);
            if (res != -0x1A) {
                if (res >= -0xFE) {
                    return res;
                }
                state = sp10[0];
            }
            if (sender != NULL) {
                sender->unkF4 = sp10[1];
            }
        }
        if (res >= -0xFE) {
            idx = event >> 8;
            if (idx < recipient->exec->header->unk10) {
                state = recipient->exec->states[idx];
            } else {
                state = 0xFF;
            }
            if (sender != NULL) {
                sender->unkF4 = (state != 0xFF);
            }
            if (state & 0x8000) {
                recipient->event = event;
                for (i = 0; i < argc; i++) {
                    *recipient->sp++ = argv[i];
                }
                GOOL_CreateObjectStackFrame(recipient, argc, 0xFFFF);
                recipient->pc = (u32 *)recipient->exec->code + (state & 0x7FFF);
                return GOOL_InterpretObject(recipient, 3, 0);
            }
        }
        if (state != 0xFF) {
            i = recipient->status_c;
            if (event == 0x1800 || event == 0x1900 || event == 0x2500) {
                i &= ~2;
            }
            target_flags = *(u32 *)((state << 4) + (u32)recipient->exec->unk20);
            if (recipient == D_800566B4) {
                anim_type = recipient->anim_type;
                if ((u32)(anim_type - 3) < 2 || anim_type == 2) {
                    test = (i | 0x1002) & target_flags;
                } else {
                    test = i & target_flags;
                }
            } else {
                test = i & target_flags;
            }
            if (test == 0) {
                recipient->event = event;
                if (event == 0x1800 || event == 0x1900) {
                    recipient->status_a |= 0x10000;
                }
                GOOL_ChangeObjectState(recipient, state, argc, argv);
            } else if (state != 0xFF && sender != NULL) {
                sender->unkF4 = 0;
            }
        }
    } else if (sender != NULL) {
        sender->unkF4 = 0;
    }
    return -0xFF;
}

s32 func_800243A0(s32 cur_ang, s32 tgt_ang, s32 speed, GoolObjView *obj)
{
    s32 diff;
    s32 wrapped_diff;

    speed = SCALE_DT(speed);
    cur_ang &= 0xFFF;
    tgt_ang &= 0xFFF;
    diff = tgt_ang - cur_ang;
    if (ABS(diff) >= 0x801) {
        if (diff > 0) {
            wrapped_diff = diff - 0x1000;
        } else {
            wrapped_diff = diff + 0x1000;
        }
    } else {
        wrapped_diff = diff;
    }
    diff = ABS(wrapped_diff);
    if (obj != NULL && (obj->status_b & 0x20000000) && diff < (speed << 2)) {
        if (diff < (speed << 1)) {
            if (diff < speed) {
                speed /= 8;
            } else {
                speed /= 4;
            }
        } else if (diff < speed * 3) {
            speed /= 2;
        } else {
            speed = (speed * 3) / 4;
        }
    }
    if (diff < speed) {
        cur_ang = tgt_ang;
        if (obj != NULL) {
            obj->status_a |= 0x800;
        }
    } else {
        if (ABS(diff) == 0x800 && tgt_ang >= 0x800) {
            wrapped_diff = -wrapped_diff;
        }
        if (wrapped_diff < 0) {
            cur_ang = (cur_ang - speed) & 0xFFF;
            if (obj != NULL) {
                obj->status_a |= 8;
            }
        } else {
            cur_ang = (cur_ang + speed) & 0xFFF;
            if (obj != NULL) {
                obj->status_a &= ~8;
            }
        }
    }
    return cur_ang;
}

s32 func_80024528(s32 cur_ang, s32 tgt_ang, s32 speed, GoolObjView *obj)
{
    s32 step;
    s32 diff;

    step = SCALE_DT(speed);
    cur_ang &= 0xFFF;
    tgt_ang &= 0xFFF;
    diff = tgt_ang - cur_ang;
    if (ABS(diff) >= 0x801) {
        if (diff > 0) {
            speed = diff - 0x1000;
        } else {
            speed = diff + 0x1000;
        }
    } else {
        speed = diff;
    }
    if (speed == 0 || ((diff = ABS(speed)) < ABS(step) && (step ^ speed) >= 0)) {
        cur_ang = tgt_ang;
        if (obj != NULL) {
            obj->status_a |= 0x800;
        }
    } else {
        cur_ang = (cur_ang + step) & 0xFFF;
    }
    return cur_ang;
}
