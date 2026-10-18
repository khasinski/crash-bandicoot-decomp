/* GCC_VERSION: 2.6.3 */
/* GNU_AS_G: 8 */
#include "common.h"

typedef struct Vec3 {
    s32 x;
    s32 y;
    s32 z;
} Vec3;

typedef struct GoolBound {
    Vec3 p1;
    Vec3 p2;
} GoolBound;

typedef struct GoolVectors {
    Vec3 trans;
    Vec3 rot;
    Vec3 scale;
} GoolVectors;

typedef struct GoolCodeHeader {
    s32 unk00;
    s32 unk04;
    s32 unk08;
    s32 unk0C;
    s32 unk10;
} GoolCodeHeader;

typedef struct GoolState {
    u32 status_c;
    u32 flags;
    u16 extern_idx;
    u16 pc_event;
    u16 pc_trans;
    u16 pc_code;
} GoolState;

typedef struct GoolExecutable {
    u8 pad00[0x10];
    GoolCodeHeader *header;
    u32 *code;
    u32 *data;
    void *unk1C;
    GoolState *states;
    u8 * const anims;
} GoolExecutable;

typedef struct GoolDefaults {
    u8 bytes[0x2A];
    u16 field2A, field2C, field2E;
} GoolDefaults;

typedef struct ZoneHeaderView {
    u8 pad00[0x210];
    s32 neighbor_count;
    u32 neighbors[8];
    u8 pad234[0xC8];
    u32 flags2FC;
} ZoneHeaderView;

typedef struct ResourceEntry {
    u32 word00;
    u32 id;
    s32 kind;
    s32 word0C;
    ZoneHeaderView *data;
} ResourceEntry;

typedef struct GoolAnimVertex {
    u8 x;
    u8 y;
    u8 z;
    u8 pad[3];
} GoolAnimVertex;

typedef struct GoolAnimFrame {
    u8 pad00[8];
    Vec3 offset;
    u8 pad14[0x24];
    GoolAnimVertex verts[1];
} GoolAnimFrame;

typedef struct GoolAnimModel {
    u8 pad00[4];
    Vec3 scale;
} GoolAnimModel;

typedef struct GoolAnimEntry {
    u8 pad00[0x10];
    void *items[1];
} GoolAnimEntry;

typedef struct GoolAnimSeq {
    u8 type;
    u8 pad01[3];
    u32 eid;
    u32 model_eid;
} GoolAnimSeq;

typedef struct GoolObj {
    s32 kind;
    s32 unk04;
    GoolBound bound;
    const GoolExecutable *exec;
    GoolExecutable *external;
    ResourceEntry *zone;
    s32 unk2C;
    u16 defaults[24];
    struct GoolObj *self;
    struct GoolObj *parent;
    struct GoolObj *next;
    struct GoolObj *children;
    struct GoolObj *creator;
    struct GoolObj *player;
    struct GoolObj *unk78;
    struct GoolObj *unk7C;
    Vec3 trans;
    Vec3 rot;
    Vec3 scale;
    Vec3 vel;
    Vec3 ang_vel;
    Vec3 target_rot;
    u32 status_a;
    u32 status_b;
    u32 status_c;
    s32 subtype;
    s32 pid_flags;
    s32 *sp;
    u32 *pc;
    s32 *fp;
    u32 *unkE8;
    u32 *unkEC;
    s32 unkF0;
    s32 unkF4;
    s32 unkF8;
    s32 unkFC;
    s32 unk100;
    s32 unk104;
    GoolAnimSeq *anim_seq;
    s32 anim_frame;
    void *entity;
    s32 path_progress;
    s32 path_length;
    s32 floor_y;
    u32 state_flags;
    s32 speed;
    s32 invincibility_state;
    s32 invincibility_time;
    s32 floor_time;
    s32 floor_vel_y;
    s32 cam_zoom;
    s32 event;
    s32 cam_rot_x;
    s32 ang_vel_x;
    s32 unk148;
    s32 voice_id;
    s32 unk150;
    s32 unk154;
    s32 node_id;
} GoolObj;

typedef struct GoolStateOut {
    s32 state;
    s32 flag;
} GoolStateOut;

typedef struct GoolQuery {
    s32 kind;
    GoolObj *obj;
    GoolObj *result;
    s32 best_dist;
    s32 max_dist;
} GoolQuery;

typedef struct ObjectRoot {
    s32 kind;
    GoolObj *word04;
} ObjectRoot;

typedef struct LevelStateView {
    u8 pad00[4];
    u16 level_id;
} LevelStateView;

typedef struct PadStateView {
    u8 pad00[0x84];
    u32 unk84;
} PadStateView;

extern GoolObj *D_800566B4;

extern s32 D_80056714[];
extern ResourceEntry *D_80057914[];
extern ResourceEntry *D_80057918[];
extern s32 D_80057960[];
extern u8 D_80057974[];
extern PadStateView *D_80058404[];
extern LevelStateView *D_8005C53C[];
extern u16 D_8005E348[];
extern u32 D_8005FF58[];
extern ObjectRoot D_80060DB8[];
extern GoolObj D_80060DD8;
extern u32 D_80060E04[];
extern s32 D_8006188C[];

typedef s32 (*Visitor)(GoolObj *, void *);

void func_80013798(u32);
s32 func_80015118(s32 *, s32, s32);
s32 func_80015458(s32 *, s32);
s32 func_800156D4(s32 *);
s32 func_8001579C(s32 *, s32);
GoolAnimEntry *func_80015A98(u32 *);
void func_8001AC9C(GoolObj *, s32, Vec3 *);
s32 func_8001B788(GoolObj *, Visitor, void *);
s32 func_8001B92C(ObjectRoot *, Visitor, void *);
s32 func_8001BA90(GoolObj *, void *);
s32 func_8001BAB0(GoolObj *, void *);
GoolObj *GOOL_CreateObject(GoolObj *, u32, u32, s32, s32 *, s32);
s32 func_8001D11C(GoolObj *, void *);
void func_8001D33C(GoolObj *, s32 *);
s32 GOOL_ChangeObjectState(GoolObj *, u32, s32 *, s32);
s32 *GOOL_TranslateGop(GoolObj *, u32);
s32 *func_8001FC4C(GoolObj *, u32, s32);
s32 func_8001FDC4(u32, s32);
void func_80024040(GoolObj *, GoolObj *, s32, s32, s32 *);
s32 func_800243A0(s32, s32, s32, s32);
s32 func_800245F0(s32, s32);
s32 func_80024628(s32, s32, s32);
void func_8002465C(Vec3 *, Vec3 *, Vec3 *, Vec3 *, Vec3 *);
void func_800248A0(Vec3 *, Vec3 *, s32);
void func_800249E0(Vec3 *, Vec3 *);
void func_80025134(GoolObj *, s32, u32, s32, s32 *);
void func_800251B8(GoolObj *, GoolObj *, s32, u32, s32, s32 *);
void func_80026200(s32);
void func_80026460(GoolObj *, void *, s32);
void func_80026650(void *);
s32 func_80026B80(s32 *, GoolBound *);
ResourceEntry *func_80026DD4(ResourceEntry *, s32 *);
s32 func_800277EC(Vec3 *, Vec3 *);
s32 func_80028644(GoolObj *, Vec3 *);
void func_800289B4(GoolObj *, Vec3 *);
void func_80028E3C(GoolObj *, Vec3 *, s32, s32);
void func_8002940C(GoolObj *);
s32 func_80029B90(Vec3 *, Vec3 *);
s32 func_80029C90(GoolObj *, Vec3 *, Vec3 *, s32, s32, s32);
s32 func_80029D30(Vec3 *, Vec3 *);
s32 func_80029DB0(Vec3 *, s32 *);
s32 func_80029E10(Vec3 *, Vec3 *);
s32 func_80029E48(Vec3 *, s32 *);
s32 func_8002F6B0(s32);
void func_8002FDD8(s32);
s32 func_800304C8(GoolObj *, s32 *, s32);
void func_80030840(s32, u32, s32 *, GoolObj *);
void func_800313B4(void);
void func_800313C4(s32);
s32 func_8003905C(s32);
s32 func_800390D0(s32);
s32 func_8003D4EC(s32, s32);
s32 func_8004301C(s32, s32);

#define ABS(x) ((x) < 0 ? -(x) : (x))
#define SCALE_DT(x) (((s32)((x) * (D_80058404[0]->unk84 < 0x67U ? D_80058404[0]->unk84 : 0x66))) / 1024)

#define NODE_CHILDREN(n) ((n)->kind == 2 ? (GoolObj *)(n)->unk04 : (n)->children)
#define NODE_CHILDREN_PTR(n) ((n)->kind == 2 ? (GoolObj **)&(n)->unk04 : &(n)->children)

static __inline__ s32 *TRANS_GOP_IN(GoolObj *obj, s32 gop)
{
    u32 offset;
    if ((gop & 0xE00) == 0xE00) {
        if (gop == 0xE1F) {
            return --obj->sp;
        }
        offset = ((gop & 0x1FF) << 2) + 0x60;
        return (s32 *)((u32)obj + offset);
    }
    return GOOL_TranslateGop(obj, gop);
}

static __inline__ s32 *TRANS_GOP_OUT(GoolObj *obj, s32 gop)
{
    u32 offset;
    if ((gop & 0xE00) == 0xE00) {
        if (gop == 0xE1F) {
            return obj->sp++;
        }
        offset = ((gop & 0x1FF) << 2) + 0x60;
        return (s32 *)((u32)obj + offset);
    }
    return GOOL_TranslateGop(obj, gop);
}

static __inline__ s32 *TRANS_REG_IN(GoolObj *obj, s32 reg)
{
    u32 offset;
    if (reg == 0x1F) {
        return --obj->sp;
    }
    offset = (reg << 2) + 0x60;
    return (s32 *)((u32)obj + offset);
}

static __inline__ s32 *TRANS_REG_OUT(GoolObj *obj, s32 reg)
{
    u32 offset;
    if (reg == 0x1F) {
        return obj->sp++;
    }
    offset = (reg << 2) + 0x60;
    return (s32 *)((u32)obj + offset);
}

static __inline__ s32 GOOL_CreateObjectStackFrame(GoolObj *object, s32 arg_words, s32 flags)
{
    s32 *sp;
    s32 *old_fp;
    s32 *new_sp;
    s32 *new_fp;

    sp = object->sp;
    old_fp = object->fp;
    object->fp = sp;
    *object->sp++ = flags;
    *object->sp++ = (s32)object->pc;
    *object->sp++ = ((u32)(new_sp = sp - arg_words - 24) - (u32)object) | (((u32)(new_fp = old_fp - 24) - (u32)object) << 16);
    return -0xFF;
}

static __inline__ s32 func_8001D97C(GoolObj *object, s32 *flags, u32 cur_flags)
{
    u32 packed;
    u32 frame_offset;
    u32 stack_offset;
    u32 restored_frame;
    s32 *frame;
    s32 *stack;

    frame = object->fp;
    object->sp = frame + 2;
    packed = frame[2];
    frame_offset = packed >> 16;
    if (frame_offset == 0) {
        return -0x19;
    }
    object->sp = frame + 1;
    object->pc = (u32 *)frame[1];
    if (flags != NULL) {
        stack = object->sp - 1;
        object->sp = stack;
        ((struct { s32 v; } *)flags)->v = (cur_flags & 0xFFFF0000) | *(u16 *)stack;
    }
    stack_offset = (packed & 0xFFFF) + 0x60;
    object->sp = (s32 *)(stack_offset + (u32)object);
    restored_frame = frame_offset + 0x60;
    object->fp = (s32 *)(restored_frame + (u32)object);
    return -0xFF;
}

static __inline__ s32 inline_8001B788(GoolObj *root, Visitor visitor, void *context)
{
    GoolObj *child;
    GoolObj *next;
    s32 result = 0;

    if (root == NULL) {
        return 0;
    }
    if (root->kind != 2) {
        result = visitor(root, context);
        if (result != 0) {
            return result;
        }
    }
    if (root->kind == 2) {
        child = (GoolObj *)root->unk04;
    } else {
        child = root->children;
    }
    while (child != NULL && result == 0) {
        next = child->next;
        result = func_8001B788(child, visitor, context);
        child = next;
    }
    return result;
}

static __inline__ s32 func_8001B56C(GoolObj *object, GoolObj *new_parent)
{
    GoolObj *parent;
    GoolObj *prev;

    parent = object->parent;
    if (parent != NULL) {
        prev = NODE_CHILDREN(parent);
        if (prev == object) {
            *NODE_CHILDREN_PTR(parent) = object->next;
        } else if (prev != NULL) {
            while (prev->next != object) {
                if (prev == NULL) {
                    return -0x18;
                }
                prev = prev->next;
                if (prev == NULL) {
                    return -0x18;
                }
            }
            prev->next = object->next;
        } else {
            return -0x18;
        }
    }
    object->parent = new_parent;
    object->next = NODE_CHILDREN(new_parent);
    *NODE_CHILDREN_PTR(new_parent) = object;
    return -0xFF;
}

static __inline__ void func_8001D200(void *object)
{
    s32 index;

    for (index = 0; index < 8; index++) {
        func_8001B92C(&D_80060DB8[index], func_8001D11C, object);
    }
}

static __inline__ void func_8001D264(void)
{
    ZoneHeaderView *zone;
    s32 i;
    void *entry;

    if (D_80057914[0] != NULL) {
        zone = D_80057914[0]->data;
        for (i = 0; i < zone->neighbor_count; i++) {
            entry = func_80015A98(&zone->neighbors[i]);
            func_8001D200(entry);
        }
    }
}

s32 GOOL_InterpretObject(GoolObj *obj, u32 flags, GoolStateOut *out_state)
{
    u32 ins;
    u32 opcode;

    GoolObj *recipient;
    s32 tmp_swap;
    s32 cond1;
    s32 cond2;

next_ins:
    while (1) {
        ins = *obj->pc++;
        opcode = ins >> 24;
        switch (opcode) {
        case 0x80:
        case 0x81:
        {
            s32 *s_ptr; s32 *d_ptr; s32 s_val; s32 d_val;
            break;

        }
        case 0x11:
        {
            s32 *s_ptr; s32 *d_ptr; s32 s_val; s32 d_val;
            s_val = *TRANS_GOP_IN(obj, (ins >> 12) & 0xFFF);
            d_ptr = TRANS_GOP_OUT(obj, ins & 0xFFF);
            if (d_ptr != NULL) {
                *d_ptr = s_val;
            }
            break;

        }
        case 0x16:
        case 0x26:
        {
            s32 *s_ptr; s32 *d_ptr; s32 s_val; s32 d_val;
            s_ptr = TRANS_GOP_IN(obj, (ins >> 12) & 0xFFF);
            d_ptr = TRANS_GOP_IN(obj, ins & 0xFFF);
            if ((ins >> 24) == 0x26) {
                if (d_ptr != NULL) {
                    *obj->sp++ = (s32)d_ptr;
                    if (s_ptr != NULL) {
                        *obj->sp++ = (s32)s_ptr;
                    }
                }
            } else {
                if (d_ptr != NULL) {
                    if (s_ptr != NULL) {
                        tmp_swap = *s_ptr;
                    }
                    *obj->sp++ = *d_ptr;
                    if (s_ptr != NULL) {
                        *obj->sp++ = tmp_swap;
                    }
                }
            }
            break;

        }
        case 0x14:
        {
            s32 *s_ptr; s32 *d_ptr; s32 s_val; s32 d_val;
            s_val = (s32)TRANS_GOP_IN(obj, (ins >> 12) & 0xFFF);
            d_ptr = TRANS_GOP_OUT(obj, ins & 0xFFF);
            if (d_ptr != NULL) {
                *d_ptr = s_val;
            }
            break;

        }
        case 0x27:
        {
            s32 *s_ptr; s32 *d_ptr; s32 s_val; s32 d_val;
            s_ptr = TRANS_GOP_IN(obj, (ins >> 12) & 0xFFF);
            d_ptr = TRANS_GOP_OUT(obj, ins & 0xFFF);
            if (d_ptr != NULL) {
                *d_ptr = (s32)&obj->exec->anims[((u32)*s_ptr >> 8) << 2];
            }
            break;

        }
        case 0x19:
        {
            s32 *s_ptr; s32 *d_ptr; s32 s_val; s32 d_val;
            s_val = *TRANS_GOP_IN(obj, (ins >> 12) & 0xFFF);
            d_ptr = TRANS_GOP_OUT(obj, ins & 0xFFF);
            if (d_ptr != NULL) {
                *d_ptr = ABS(s_val);
            }
            break;

        }
        case 0x18:
        {
            s32 *s_ptr; s32 *d_ptr; s32 s_val; s32 d_val;
            {
                u32 offset;
                d_ptr = TRANS_REG_OUT(obj, (ins >> 14) & 0x3F);
                offset = ins & 0x3FFF;
                if (offset != 0x3FFF) {
                    *d_ptr = (s32)&obj->exec->code[offset];
                } else {
                    *d_ptr = 0;
                }
            }
            break;

        }
        case 0x12:
        {
            s32 *s_ptr; s32 *d_ptr; s32 s_val; s32 d_val;
            s_val = *TRANS_GOP_IN(obj, (ins >> 12) & 0xFFF);
            d_ptr = TRANS_GOP_OUT(obj, ins & 0xFFF);
            if (d_ptr != NULL) {
                *d_ptr = (s_val == 0);
            }
            break;

        }
        case 0x17:
        {
            s32 *s_ptr; s32 *d_ptr; s32 s_val; s32 d_val;
            s_val = *TRANS_GOP_IN(obj, (ins >> 12) & 0xFFF);
            d_ptr = TRANS_GOP_OUT(obj, ins & 0xFFF);
            if (d_ptr != NULL) {
                *d_ptr = ~s_val;
            }
            break;

        }
        case 0x13:
        {
            s32 *s_ptr; s32 *d_ptr; s32 s_val; s32 d_val;
            {
                s32 rate;
                s32 limit;
                s32 val;

                if (((ins >> 12) & 0xFFF) == 0xBF0) {
                    s32 *sp = obj->sp;
                    obj->sp = sp - 1;
                    rate = *(sp - 1);
                    obj->sp = sp - 2;
                    limit = *(sp - 2);
                } else {
                    rate = 0x100;
                    limit = *TRANS_GOP_IN(obj, (ins >> 12) & 0xFFF);
                }
                s_ptr = TRANS_GOP_IN(obj, ins & 0xFFF);
                if (s_ptr != NULL) {
                    val = *s_ptr;
                    if (limit >= 0) {
                        val += rate;
                        if (val >= limit) {
                            val = (rate << 1) - limit;
                        }
                        limit = ABS(val);
                    } else {
                        val -= rate;
                        if (val <= limit) {
                            val = -limit - (rate << 1);
                        }
                        limit = -ABS(val);
                    }
                    d_ptr = TRANS_GOP_OUT(obj, ins & 0xFFF);
                    *d_ptr = val;
                    *obj->sp++ = limit;
                }
            }
            break;

        }
        case 0x22:
        case 0x25:
        {
            s32 *s_ptr; s32 *d_ptr; s32 s_val; s32 d_val;
            {
                s32 rate;
                s32 target;

                if (((ins >> 12) & 0xFFF) == 0xBF0) {
                    s32 *sp = obj->sp;
                    obj->sp = sp - 1;
                    rate = *(sp - 1);
                    obj->sp = sp - 2;
                    target = *(sp - 2);
                } else {
                    rate = 0x100;
                    target = *TRANS_GOP_IN(obj, (ins >> 12) & 0xFFF);
                }
                s_ptr = TRANS_GOP_IN(obj, ins & 0xFFF);
                if (s_ptr != NULL) {
                    s_val = *s_ptr;
                    if ((ins >> 24) == 0x22) {
                        if (rate < 0) {
                            rate = -rate;
                        }
                        *obj->sp++ = func_80024628(s_val, target, rate);
                    } else {
                        *obj->sp++ = func_800243A0(s_val, target, rate, 0);
                    }
                } else {
                    *obj->sp++ = 0;
                }
            }
            break;

        }
        case 0x00:
        {
            s32 *s_ptr; s32 *d_ptr; s32 s_val; s32 d_val;
            s_ptr = TRANS_GOP_IN(obj, (ins >> 12) & 0xFFF);
            d_ptr = TRANS_GOP_IN(obj, ins & 0xFFF);
            *obj->sp++ = *s_ptr + *d_ptr;
            break;

        }
        case 0x01:
        {
            s32 *s_ptr; s32 *d_ptr; s32 s_val; s32 d_val;
            s_ptr = TRANS_GOP_IN(obj, (ins >> 12) & 0xFFF);
            d_ptr = TRANS_GOP_IN(obj, ins & 0xFFF);
            *obj->sp++ = ({ s32 v = *s_ptr; *d_ptr - v; });
            break;

        }
        case 0x21:
        {
            s32 *s_ptr; s32 *d_ptr; s32 s_val; s32 d_val;
            s_val = *TRANS_GOP_IN(obj, (ins >> 12) & 0xFFF);
            d_ptr = TRANS_GOP_IN(obj, ins & 0xFFF);
            *obj->sp++ = func_800245F0(*d_ptr, s_val);
            break;

        }
        case 0x02:
        {
            s32 *s_ptr; s32 *d_ptr; s32 s_val; s32 d_val;
            s_ptr = TRANS_GOP_IN(obj, (ins >> 12) & 0xFFF);
            d_ptr = TRANS_GOP_IN(obj, ins & 0xFFF);
            *obj->sp++ = *s_ptr * *d_ptr;
            break;

        }
        case 0x03:
        {
            s32 *s_ptr; s32 *d_ptr; s32 s_val; s32 d_val;
            s_ptr = TRANS_GOP_IN(obj, (ins >> 12) & 0xFFF);
            d_ptr = TRANS_GOP_IN(obj, ins & 0xFFF);
            *obj->sp++ = *d_ptr / *s_ptr;
            break;

        }
        case 0x0D:
        {
            s32 *s_ptr; s32 *d_ptr; s32 s_val; s32 d_val;
            s_val = *TRANS_GOP_IN(obj, (ins >> 12) & 0xFFF);
            d_ptr = TRANS_GOP_IN(obj, ins & 0xFFF);
            *obj->sp++ = *d_ptr % s_val;
            break;

        }
        case 0x10:
        {
            s32 *s_ptr; s32 *d_ptr; s32 s_val; s32 d_val;
            s_val = *TRANS_GOP_IN(obj, (ins >> 12) & 0xFFF);
            d_val = *TRANS_GOP_IN(obj, ins & 0xFFF);
            *obj->sp++ = func_8002F6B0(s_val - d_val) + d_val;
            break;

        }
        case 0x15:
        {
            s32 *s_ptr; s32 *d_ptr; s32 s_val; long d_val;
            s_val = *TRANS_GOP_IN(obj, (ins >> 12) & 0xFFF);
            d_val = *TRANS_GOP_IN(obj, ins & 0xFFF);
            *obj->sp++ = s_val < 0 ? d_val >> -s_val : d_val << s_val;
            break;

        }
        case 0x07:
        {
            s32 *s_ptr; s32 *d_ptr; s32 s_val; s32 d_val;
            s_ptr = TRANS_GOP_IN(obj, (ins >> 12) & 0xFFF);
            d_ptr = TRANS_GOP_IN(obj, ins & 0xFFF);
            *obj->sp++ = *s_ptr & *d_ptr;
            break;

        }
        case 0x08:
        {
            s32 *s_ptr; s32 *d_ptr; s32 s_val; s32 d_val;
            s_ptr = TRANS_GOP_IN(obj, (ins >> 12) & 0xFFF);
            d_ptr = TRANS_GOP_IN(obj, ins & 0xFFF);
            *obj->sp++ = *s_ptr | *d_ptr;
            break;

        }
        case 0x0E:
        {
            s32 *s_ptr; s32 *d_ptr; s32 s_val; s32 d_val;
            s_ptr = TRANS_GOP_IN(obj, (ins >> 12) & 0xFFF);
            d_ptr = TRANS_GOP_IN(obj, ins & 0xFFF);
            *obj->sp++ = *s_ptr ^ *d_ptr;
            break;

        }
        case 0x0F:
        {
            s32 *s_ptr; s32 *d_ptr; s32 s_val; s32 d_val;
            s_val = *TRANS_GOP_IN(obj, (ins >> 12) & 0xFFF);
            d_ptr = TRANS_GOP_IN(obj, ins & 0xFFF);
            *obj->sp++ = !((s_val & *d_ptr) ^ s_val);
            break;

        }
        case 0x04:
        {
            s32 *s_ptr; s32 *d_ptr; s32 s_val; s32 d_val;
            s_ptr = TRANS_GOP_IN(obj, (ins >> 12) & 0xFFF);
            d_ptr = TRANS_GOP_IN(obj, ins & 0xFFF);
            *obj->sp++ = (*s_ptr == *d_ptr);
            break;

        }
        case 0x09:
        {
            s32 *s_ptr; s32 *d_ptr; s32 s_val; s32 d_val;
            s_ptr = TRANS_GOP_IN(obj, (ins >> 12) & 0xFFF);
            d_ptr = TRANS_GOP_IN(obj, ins & 0xFFF);
            *obj->sp++ = (*s_ptr > *d_ptr);
            break;

        }
        case 0x0A:
        {
            s32 *s_ptr; s32 *d_ptr; s32 s_val; s32 d_val;
            s_ptr = TRANS_GOP_IN(obj, (ins >> 12) & 0xFFF);
            d_ptr = TRANS_GOP_IN(obj, ins & 0xFFF);
            *obj->sp++ = (*s_ptr >= *d_ptr);
            break;

        }
        case 0x0B:
        {
            s32 *s_ptr; s32 *d_ptr; s32 s_val; s32 d_val;
            s_ptr = TRANS_GOP_IN(obj, (ins >> 12) & 0xFFF);
            d_ptr = TRANS_GOP_IN(obj, ins & 0xFFF);
            *obj->sp++ = (*s_ptr < *d_ptr);
            break;

        }
        case 0x0C:
        {
            s32 *s_ptr; s32 *d_ptr; s32 s_val; s32 d_val;
            s_ptr = TRANS_GOP_IN(obj, (ins >> 12) & 0xFFF);
            d_ptr = TRANS_GOP_IN(obj, ins & 0xFFF);
            *obj->sp++ = (*s_ptr <= *d_ptr);
            break;

        }
        case 0x05:
        {
            s32 *s_ptr; s32 *d_ptr; s32 s_val; s32 d_val;
            s_ptr = TRANS_GOP_IN(obj, (ins >> 12) & 0xFFF);
            d_ptr = TRANS_GOP_IN(obj, ins & 0xFFF);
            *obj->sp++ = (*d_ptr && *s_ptr);
            break;

        }
        case 0x06:
        {
            s32 *s_ptr; s32 *d_ptr; s32 s_val; s32 d_val;
            s_ptr = TRANS_GOP_IN(obj, (ins >> 12) & 0xFFF);
            d_ptr = TRANS_GOP_IN(obj, ins & 0xFFF);
            *obj->sp++ = (*d_ptr || *s_ptr);
            break;

        }
        case 0x1A:
        {
            s32 *s_ptr; s32 *d_ptr; s32 s_val; s32 d_val;
            *obj->sp++ = func_8001FDC4(ins & 0x1FFFFF, 0);
            break;

        }
        case 0x1B:
        {
            s32 *s_ptr; s32 *d_ptr; s32 s_val; s32 d_val;
            s_val = *TRANS_GOP_IN(obj, (ins >> 12) & 0xFFF);
            d_val = *TRANS_GOP_IN(obj, ins & 0xFFF);
            *obj->sp++ = d_val + SCALE_DT(s_val);
            break;

        }
        case 0x1D:
        {
            s32 *s_ptr; s32 *d_ptr; s32 s_val; s32 d_val;
            {
                s32 period;
                s32 phase;
                s32 shift;
                s32 sin_val;

                period = *TRANS_GOP_IN(obj, (ins >> 12) & 0xFFF);
                d_ptr = TRANS_GOP_IN(obj, ins & 0xFFF);
                phase = (*d_ptr << 11) / period;
                shift = (period > 0xFFFF) << 1;
                sin_val = (func_8003905C(phase - 0x400) + 0x1000) >> shift;
                *obj->sp++ = (sin_val * period) >> (0xD - shift);
            }
            break;

        }
        case 0x1E:
        {
            s32 *s_ptr; s32 *d_ptr; s32 s_val; s32 d_val;
            s_val = *TRANS_GOP_IN(obj, (ins >> 12) & 0xFFF);
            d_val = *TRANS_GOP_IN(obj, ins & 0xFFF);
            *obj->sp++ = (s_val + D_80057960[0]) % d_val;
            break;

        }
        case 0x1F:
        {
            s32 *s_ptr; s32 *d_ptr; s32 s_val; s32 d_val;
            d_ptr = TRANS_GOP_IN(obj, ins & 0xFFF);
            *obj->sp++ = D_8006188C[*d_ptr >> 8];
            break;

        }
        case 0x20:
        {
            s32 *s_ptr; s32 *d_ptr; s32 s_val; s32 d_val;
            s_ptr = TRANS_GOP_IN(obj, (ins >> 12) & 0xFFF);
            d_ptr = TRANS_GOP_IN(obj, ins & 0xFFF);
            D_8006188C[*d_ptr >> 8] = *s_ptr;
            break;

        }
        case 0x23:
        {
            s32 *s_ptr; s32 *d_ptr; s32 s_val; s32 d_val;
            {
                GoolObj *link = (&obj->self)[(ins >> 12) & 7];
                *obj->sp++ = link->defaults[(ins >> 15) & 0x3F];
            }
            break;

        }
        case 0x24:
        {
            s32 *s_ptr; s32 *d_ptr; s32 s_val; s32 d_val;
            {
                GoolObj *link = (&obj->self)[(ins >> 12) & 7];
                u32 idx = (ins >> 15) & 0x3F;
                d_ptr = TRANS_GOP_IN(obj, ins & 0xFFF);
                link->defaults[idx] = *(u16 *)d_ptr;
            }
            break;

        }
        case 0x1C:
        {
            s32 *s_ptr; s32 *d_ptr; s32 s_val; s32 d_val;
            {
                s32 subarg;

                s_ptr = TRANS_GOP_IN(obj, ins & 0xFFF);
                subarg = (s32)(ins << 12) >> 27;
                switch ((ins >> 20) & 0xF) {
                case 0:
                    if (s_ptr != NULL) {
                        if (*s_ptr != 0) {
                            *obj->sp++ = ((s32 *)*s_ptr)[subarg];
                        } else {
                            goto push_zero;
                        }
                    }
                    break;

                case 1:
                case 6:
                    {
                        Vec3 v1;
                        Vec3 v2;
                        Vec3 *vec_a;
                        Vec3 *vec_b;
                        GoolObj *link;

                        if (((ins >> 20) & 0xF) == 6) {
                            vec_a = (Vec3 *)s_ptr;
                        } else {
                            vec_a = &obj->trans;
                        }
                        link = (&obj->self)[(ins >> 12) & 7];
                        vec_b = &link->trans;
                        if (subarg & 2) {
                            v1.x = vec_a->x;
                            v1.y = 0;
                            v1.z = vec_a->z;
                            v2.x = link->trans.x;
                            v2.y = 0;
                            v2.z = link->trans.z;
                            vec_a = &v1;
                            vec_b = &v2;
                        }
                        if (subarg & 1) {
                            *obj->sp++ = func_80029D30(vec_a, vec_b);
                        } else {
                            *obj->sp++ = func_80029B90(vec_a, vec_b);
                        }
                    }
                    break;

                case 5:
                    {
                        GoolObj *link = (&obj->self)[(ins >> 12) & 7];
                        s32 diff = func_80029E10(&obj->trans, &link->trans) - (obj->rot.y & 0xFFF);
                        if (ABS(diff) >= 0x800) {
                            diff = (-diff) & 0xFFF;
                        }
                        *obj->sp++ = diff;
                    }
                    break;

                case 2:
                    if (!(obj->status_b & 0x200200)) {
                        *obj->sp++ = func_80029E10(&(&obj->self)[(ins >> 12) & 7]->trans, (Vec3 *)s_ptr);
                    } else {
                        *obj->sp++ = func_80029E48(&(&obj->self)[(ins >> 12) & 7]->trans, s_ptr);
                    }
                    break;

                case 3:
                    *obj->sp++ = ((s32 *)&(&obj->self)[(ins >> 12) & 7]->self)[(u32)*s_ptr >> 8];
                    break;

                case 4:
                    {
                        GoolObj *link = (&obj->self)[(ins >> 12) & 7];
                        ((s32 *)&link->self)[(u32)*s_ptr >> 8] = *--obj->sp;
                    }
                    break;

                case 7:
                    if (s_ptr != NULL) {
                        if (*s_ptr != 0 && (D_8005FF58[(u32)*s_ptr >> 8] & 1)) {
                            s32 i = 3;
                            s32 found = 0;
                            do {
                                ObjectRoot *root = &D_80060DB8[i++];
                                found = inline_8001B788((GoolObj *)root, func_8001BA90, (void *)*s_ptr);
                            } while (found == 0 && i < 5);
                            *obj->sp++ = found;
                        } else {
                            goto push_zero;
                        }
                    }
                    break;

                case 8:
                    if (s_ptr != NULL) {
                        if (subarg != 0) {
                            D_8005FF58[(u32)*s_ptr >> 8] &= ~2;
                        } else {
                            D_8005FF58[(u32)*s_ptr >> 8] |= 2;
                        }
                    }
                    break;

                case 10:
                    if (s_ptr != NULL) {
                        switch (subarg) {
                        case 0:
                            D_8005FF58[(u32)*s_ptr >> 8] &= ~4;
                            break;
                        case 1:
                            D_8005FF58[(u32)*s_ptr >> 8] |= 4;
                            break;
                        case 4:
                            {
                                u16 *p = D_8005E348;
                                u16 tag = (*s_ptr >> 8) | (D_8005C53C[0]->level_id << 9);
                                while (*p != 0) {
                                    if (*p == tag) {
                                        if (p[1] != 0) {
                                            *p = 1;
                                        } else {
                                            *p = 0;
                                        }
                                        break;
                                    }
                                    p++;
                                }
                            }
                        case 2:
                            D_8005FF58[(u32)*s_ptr >> 8] &= ~8;
                            break;
                        case 5:
                            {
                                u16 *p = D_8005E348;
                                u16 *free_slot = NULL;
                                s32 tag = (*s_ptr >> 8) | (D_8005C53C[0]->level_id << 9);
                                if (!(D_80057914[0]->data->flags2FC & 0x2000)) {
                                    while (*p != 0) {
                                        if (*p == (u16)tag) {
                                            goto set_bit_3;
                                        }
                                        if (*p == 1) {
                                            free_slot = p;
                                        }
                                        p++;
                                    }
                                    if (free_slot == NULL) {
                                        free_slot = p;
                                    }
                                    *free_slot = tag;
                                }
                            }
                        case 3:
                        set_bit_3:
                            D_8005FF58[(u32)*s_ptr >> 8] |= 8;
                            break;
                        case 9:
                            D_8005FF58[(u32)*s_ptr >> 8] |= 1;
                            break;
                        case 8:
                            D_8005FF58[(u32)*s_ptr >> 8] &= ~1;
                            break;
                        }
                    }
                    break;

                case 11:
                    switch (subarg) {
                    case 1:
                        *obj->sp++ = s_ptr ? (((D_8005FF58[(u32)*s_ptr >> 8] >> 1) ^ 1) & 1) : 0;
                        break;
                    case 2:
                        *obj->sp++ = s_ptr ? (D_8005FF58[(u32)*s_ptr >> 8] & 4) : 0;
                        break;
                    case 3:
                        *obj->sp++ = s_ptr ? (D_8005FF58[(u32)*s_ptr >> 8] & 8) : 0;
                        break;
                    }
                    break;

                case 9:
                    {
                        ResourceEntry *zone;
                        if (s_ptr == NULL) {
                            zone = D_80057914[0];
                        } else {
                            zone = func_80026DD4(D_80057914[0], s_ptr);
                        }
                        if ((s32)zone < -0xFE) {
                            (&obj->self)[(ins >> 12) & 7]->zone = zone;
                        }
                    }
                    break;

                case 12:
                    switch (subarg) {
                    case 0:
                        func_80026460(obj, D_80057974, 0);
                        break;
                    case 1:
                        func_80026650(D_80057974);
                        break;
                    case 2:
                        {
                            GoolObj *new_parent = (GoolObj *)&D_80060DB8[(u32)*s_ptr >> 8];
                            GoolObj *parent = obj->parent;
                            GoolObj *prev;

                            if (parent != NULL) {
                                prev = NODE_CHILDREN(parent);
                                if (prev == obj) {
                                    *NODE_CHILDREN_PTR(parent) = obj->next;
                                } else if (prev != NULL) {
                                    while (prev->next != obj) {
                                        if (prev == NULL) {
                                            goto end_case_2;
                                        }
                                        prev = prev->next;
                                        if (prev == NULL) {
                                            goto next_ins;
                                        }
                                    }
                                    prev->next = obj->next;
                                } else {
                                    goto next_ins;
                                }
                            }
                            obj->parent = new_parent;
                            obj->next = NODE_CHILDREN(new_parent);
                            *NODE_CHILDREN_PTR(new_parent) = obj;
                        end_case_2:;
                        }
                        break;
                    case 3:
                        func_8002FDD8(*s_ptr);
                        break;
                    case 4:
                        ((GoolObj *)*s_ptr)->zone = D_80057918[0];
                        break;
                    case 5:
                        func_800313B4();
                        break;
                    case 6:
                        func_800313C4(*s_ptr);
                        break;
                    case 7:
                        func_8001D264();
                        break;
                    case 8:
                        {
                            GoolObj *link = (&obj->self)[(ins >> 12) & 7];
                            s32 dist = func_80029DB0(&link->trans, s_ptr);
                            *obj->sp++ = func_8004301C(link->trans.y - s_ptr[1], dist);
                        }
                        break;
                    case 9:
                        D_80056714[0] = (u32)*s_ptr >> 8;
                        break;
                    case 10:
                        func_80013798((u32)*s_ptr >> 8);
                        break;
                    case 11:
                        func_80026200(1);
                        break;
                    }
                    break;

                case 13:
                    {
                        GoolQuery query;
                        query.kind = (ins >> 15) & 0x1F;
                        query.obj = (&obj->self)[(ins >> 12) & 7];
                        query.result = NULL;
                        query.best_dist = 0x7FFFFFFF;
                        query.max_dist = *s_ptr;
                        inline_8001B788(&D_80060DD8, func_8001BAB0, &query);
                        if (query.result != NULL) {
                            *obj->sp++ = (s32)query.result;
                        } else {
                        push_zero:
                            *obj->sp++ = 0;
                        }
                    }
                    break;

                case 14:
                    {
                        GoolBound bound;
                        GoolObj *link = (&obj->self)[(ins >> 12) & 7];
                        bound.p1.x = link->trans.x + link->bound.p1.x;
                        bound.p1.y = link->trans.y + link->bound.p1.y;
                        bound.p1.z = link->trans.z + link->bound.p1.z;
                        bound.p2.x = link->trans.x + link->bound.p2.x;
                        bound.p2.y = link->trans.y + link->bound.p2.y;
                        bound.p2.z = link->trans.z + link->bound.p2.z;
                        *obj->sp++ = func_80026B80(s_ptr, &bound);
                    }
                    break;

                case 15:
                    obj->unkF4 = func_8003D4EC(subarg, *s_ptr);
                    break;
                }
            }
            break;

        }
        case 0x88:
        case 0x89:
        {
            s32 *s_ptr; s32 *d_ptr; s32 s_val; s32 d_val;
            {
                u32 mode = (ins >> 22) & 3;
                u32 cond_type = (ins >> 20) & 3;
                s32 res;

                if (!(flags & 8)) {
                    return -0xE;
                }
                switch (cond_type) {
                case 0:
                    cond1 = 1;
                    break;
                case 1:
                    cond1 = *TRANS_REG_IN(obj, (ins >> 14) & 0x3F);
                    break;
                case 2:
                    cond1 = (*TRANS_REG_IN(obj, (ins >> 14) & 0x3F) == 0);
                    break;
                }
                if (cond1) {
                    flags |= 0x20;
                    out_state->flag = (opcode != 0x88);
                    switch (mode) {
                    case 2:
                        res = func_8001D97C(obj, NULL, 0);
                        if (res >= -0xFE) {
                            return res;
                        }
                        out_state->state = 0xFF;
                        return -0xFF;
                    case 1:
                        res = func_8001D97C(obj, NULL, 0);
                        if (res >= -0xFE) {
                            return res;
                        }
                        out_state->state = ins & 0x3FFF;
                        return -0xFF;
                    }
                } else if (mode == 0) {
                    obj->pc += (s32)(ins << 22) >> 22;
                    obj->sp = (s32 *)((u8 *)obj->sp - ((ins >> 8) & 0x3C));
                }
            }
            break;

        }
        case 0x82:
        {
            s32 *s_ptr; s32 *d_ptr; s32 s_val; s32 d_val;
            {
                u32 mode = (ins >> 22) & 3;
                u32 cond_type = (ins >> 20) & 3;
                s32 res;

                switch (cond_type) {
                case 0:
                    cond2 = 1;
                    break;
                case 1:
                    cond2 = *TRANS_REG_IN(obj, (ins >> 14) & 0x3F);
                    break;
                case 2:
                    cond2 = (*TRANS_REG_IN(obj, (ins >> 14) & 0x3F) == 0);
                    break;
                }
                if (cond2) {
                    switch (mode) {
                    case 2:
                        {
                            s32 saved_flags;
                            ((struct { s32 v; } *)&saved_flags)->v = flags;
                            res = func_8001D97C(obj, &saved_flags, flags);
                            if (flags & 8) {
                                if (flags & 0x20) {
                                    out_state->state = 0xFF;
                                    return -0xFF;
                                }
                                return -0x1A;
                            }
                            if ((flags & 1) || res >= -0xFE) {
                                if (flags & 0x10) {
                                    if (res < -0xFE) {
                                        *obj->sp++ = 0;
                                    }
                                }
                                return res;
                            }
                            if ((saved_flags & 0xFFFF) != 0xFFFF) {
                                flags = saved_flags;
                            }
                        }
                        break;
                    case 0:
                        obj->pc += (s32)(ins << 22) >> 22;
                        obj->sp = (s32 *)((u8 *)obj->sp - ((ins >> 8) & 0x3C));
                        break;
                    case 1:
                        {
                            u32 status_c = obj->status_c;
                            u32 state_status_c = obj->exec->states[ins & 0x3FFF].status_c;
                            s32 inv_state = obj->invincibility_state;
                            u32 mask;

                            if ((u32)(inv_state - 3) < 2 || inv_state == 2) {
                                mask = (status_c | 0x1002) & state_status_c;
                            } else {
                                mask = status_c & state_status_c;
                            }
                            if (mask == 0) {
                                res = GOOL_ChangeObjectState(obj, ins & 0x3FFF, NULL, 0);
                                if (res < -0xFE && (flags & 2)) {
                                    return res;
                                }
                                obj->sp--;
                            }
                        }
                        break;
                    }
                }
            }
            break;

        }
        case 0x86:
        {
            s32 *s_ptr; s32 *d_ptr; s32 s_val; s32 d_val;
            {
                u32 offset;
                GOOL_CreateObjectStackFrame(obj, (ins >> 20) & 0xF, flags);
                offset = ins & 0x3FFF;
                if (offset != 0x3FFF) {
                    obj->pc = &obj->exec->code[offset];
                } else {
                    obj->pc = NULL;
                }
                flags &= ~9;
            }
            break;

        }
        case 0x83:
        {
            s32 *s_ptr; s32 *d_ptr; s32 s_val; s32 d_val;
            obj->anim_seq = (GoolAnimSeq *)((u32)obj->exec->anims + ((ins >> 5) & 0x7FC));
            obj->anim_frame = (ins & 0x7F) << 8;
            *obj->sp++ = (((ins >> 16) & 0x3F) << 24) | D_80060E04[0];
            switch ((ins >> 22) & 3) {
            case 0:
                if (obj->scale.x < 0) {
                    obj->scale.x = -obj->scale.x;
                }
                break;
            case 1:
                if (obj->scale.x > 0) {
                    obj->scale.x = -obj->scale.x;
                }
                break;
            case 2:
                obj->scale.x = -obj->scale.x;
                break;
            }
            if (obj->status_b & 0x18) {
                if (!func_80029C90(obj, &obj->trans, &D_800566B4->trans, 0x7D000, 0xAF000, 0x7D000) || (s32)obj->status_b < 0) {
                    func_8001D33C(obj, &obj->scale.x);
                }
            }
            if (flags & 4) {
                return -0xFF;
            }
            break;

        }
        case 0x84:
        {
            s32 *s_ptr; s32 *d_ptr; s32 s_val; s32 d_val;
            d_ptr = TRANS_GOP_IN(obj, ins & 0xFFF);
            obj->anim_frame = *d_ptr;
            *obj->sp++ = (((ins >> 16) & 0x3F) << 24) | D_80060E04[0];
            switch ((ins >> 22) & 3) {
            case 0:
                if (obj->scale.x < 0) {
                    obj->scale.x = -obj->scale.x;
                }
                break;
            case 1:
                if (obj->scale.x > 0) {
                    obj->scale.x = -obj->scale.x;
                }
                break;
            case 2:
                obj->scale.x = -obj->scale.x;
                break;
            }
            func_8001D33C(obj, &obj->scale.x);
            if (flags & 4) {
                return -0xFF;
            }
            break;

        }
        case 0x8B:
        {
            s32 *s_ptr; s32 *d_ptr; s32 s_val; s32 d_val;
            s_val = *func_8001FC4C(obj, (ins >> 12) & 0xFFF, 0);
            s_ptr = func_8001FC4C(obj, ins & 0xFFF, 0);
            switch (s_val) {
            case 1:
                obj->unkF4 = func_80015118(s_ptr, 0, 1);
                break;
            case 6:
                obj->unkF4 = func_80015118(s_ptr, 1, 1);
                break;
            case 2:
                obj->unkF4 = func_80015458(s_ptr, 1);
                break;
            case 3:
                *obj->sp++ = func_80015458(s_ptr, 0);
                break;
            case 4:
                *obj->sp++ = func_800156D4(s_ptr);
                break;
            case 5:
                {
                    s32 n = *s_ptr;
                    d_val = func_8001579C(&obj->sp[-n], n);
                    obj->sp -= n;
                    *obj->sp++ = d_val;
                }
                break;
            }
            break;

        }
        case 0x85:
        {
            s32 *s_ptr; s32 *d_ptr; s32 s_val; s32 d_val;
            {
                Vec3 *vec_dst;

                vec_dst = &(&obj->trans)[(ins >> 12) & 7];
                s_ptr = TRANS_GOP_IN(obj, ins & 0xFFF);
                switch ((ins >> 18) & 7) {
                case 0:
                    if (s_ptr != NULL && obj->entity != NULL) {
                        Vec3 v2;
                        v2 = *vec_dst;
                        func_8001AC9C(obj, *s_ptr, &v2);
                        *vec_dst = v2;
                        obj->floor_y = vec_dst->y;
                    }
                    break;

                case 2:
                    vec_dst->x = ((func_8003905C(obj->ang_vel.y & 0xFFF) >> 4) * *s_ptr) >> 8;
                    if (!(obj->status_b & 0x200200)) {
                        vec_dst->z = ((func_800390D0(obj->ang_vel.y & 0xFFF) >> 4) * *s_ptr) >> 8;
                    } else {
                        vec_dst->y = ((func_800390D0(obj->ang_vel.y & 0xFFF) >> 4) * *s_ptr) >> 8;
                    }
                    obj->speed = *s_ptr;
                    break;

                case 4:
                case 5:
                    {
                        Vec3 v1;
                        Vec3 *vec_src;
                        Vec3 *rot_ptr;
                        Vec3 *scale_ptr = NULL;

                        v1.z = *s_ptr;
                        v1.y = *--obj->sp;
                        v1.x = *--obj->sp;
                        vec_src = &(&obj->trans)[(ins >> 15) & 7];
                        if (((ins >> 18) & 7) == 4) {
                            rot_ptr = &obj->rot;
                            scale_ptr = &obj->scale;
                        } else {
                            rot_ptr = &obj->ang_vel;
                        }
                        func_8002465C(&v1, vec_dst, rot_ptr, scale_ptr, vec_src);
                    }
                    break;

                case 6:
                    {
                        Vec3 v3;
                        Vec3 v4;
                        GoolObj *link = (&obj->self)[(ins >> 21) & 7];
                        GoolAnimSeq *anim_seq = link->anim_seq;
                        if (anim_seq != NULL && anim_seq->type == 1) {
                            GoolAnimFrame *frame = (GoolAnimFrame *)func_80015A98(&anim_seq->eid)->items[(u32)link->anim_frame >> 8];
                            GoolAnimEntry *model_group = (GoolAnimEntry *)func_80015A98(&link->anim_seq->eid)->items[(u32)link->anim_frame >> 8];
                            GoolAnimModel *model;
                            GoolAnimVertex *vert;

                            model_group = func_80015A98((u32 *)model_group + 1);
                            model = (GoolAnimModel *)model_group->items[0];
                            vert = &frame->verts[(u32)*s_ptr >> 8];
                            v3.x = ((frame->offset.x - 0x80) + vert->x) << 10;
                            v3.y = ((frame->offset.y - 0x80) + vert->y) << 10;
                            v3.z = ((frame->offset.z - 0x80) + vert->z) << 10;
                            v4.x = (link->scale.x * model->scale.x) >> 12;
                            v4.y = (link->scale.y * model->scale.y) >> 12;
                            v4.z = (link->scale.z * model->scale.z) >> 12;
                            func_8002465C(&v3, &link->trans, &link->rot, &v4, vec_dst);
                        }
                    }
                    break;

                case 1:
                    {
                        Vec3 *vec_src = &(&obj->trans)[(ins >> 15) & 7];
                        func_800249E0(vec_dst, vec_src);
                        if (s_ptr[0] != 0) {
                            s32 z_scaled = vec_src->z >> 8;
                            if (z_scaled != 0) {
                                s_ptr[0] = (s_ptr[0] * 280) / z_scaled;
                                s_ptr[1] = (s_ptr[1] * 280) / z_scaled;
                                s_ptr[2] = (s_ptr[2] * 280) / z_scaled;
                            }
                        }
                    }
                    break;

                case 7:
                    func_800248A0(vec_dst, &(&obj->trans)[(ins >> 15) & 7], 0);
                    break;
                }
            }
            break;

        }
        case 0x8E:
        {
            s32 *s_ptr; s32 *d_ptr; s32 s_val; s32 d_val;
            {
                Vec3 *vec_src;

                vec_src = &(&obj->trans)[(ins >> 12) & 7];
                func_8001FC4C(obj, ins & 0xFFF, 0);
                switch ((ins >> 18) & 7) {
                case 0:
                    {
                        Vec3 va;
                        Vec3 vb;

                        va = obj->trans;
                        vb = *vec_src;
                        va.y += obj->bound.p2.y / 2;
                        obj->unkF4 = func_800277EC(&va, &vb);
                        if ((ins & 0xFFF) != 0xBE0) {
                            *(Vec3 *)TRANS_GOP_OUT(obj, ins & 0xFFF) = vb;
                        }
                        (&obj->trans)[(ins >> 15) & 7] = va;
                    }
                    break;

                case 1:
                    {
                        Vec3 v_tmp;
                        Vec3 va;
                        Vec3 vb;

                        v_tmp = obj->trans;
                        va = obj->trans;
                        if (obj == D_800566B4 || obj->parent == D_800566B4) {
                            func_800289B4(obj, &v_tmp);
                        }
                        obj->unkF4 = func_80028644(obj, &va);
                        if ((ins & 0xFFF) != 0xBE0) {
                            *(Vec3 *)TRANS_GOP_OUT(obj, ins & 0xFFF) = vb;
                        }
                        (&obj->trans)[(ins >> 15) & 7] = va;
                    }
                    break;

                case 2:
                case 3:
                case 4:
                case 5:
                    {
                        Vec3 va;
                        Vec3 vb;
                        u32 subop = (ins >> 18) & 7;
                        s32 arg3 = (u32)(subop - 4) < 2;
                        s32 is_odd = (subop == 5 || subop == 3);
                        ResourceEntry *zone;
                        s32 mode_flags;
                        Vec3 *va_ptr;

                        va = obj->trans;
                        va_ptr = &va;
                        zone = obj->zone ? obj->zone : D_80057914[0];
                        if (zone->data->flags2FC & 1) {
                            mode_flags = is_odd ? 6 : 2;
                        } else {
                            mode_flags = is_odd ? 5 : 1;
                        }
                        func_80028E3C(obj, va_ptr, mode_flags, !arg3);
                        if ((ins & 0xFFF) != 0xBE0) {
                            *(Vec3 *)TRANS_GOP_OUT(obj, ins & 0xFFF) = vb;
                        }
                        (&obj->trans)[(ins >> 15) & 7] = va;
                    }
                    break;

                case 6:
                    func_8002940C(obj);
                    break;
                }
            }
            break;

        }
        case 0x87:
        case 0x90:
        {
            s32 *s_ptr; s32 *d_ptr; s32 s_val; s32 d_val;
            recipient = (&obj->self)[(ins >> 21) & 7];
        case 0x8F:
            {
                s32 args[16];
                s32 *event_ptr;
                s32 cond;
                s32 count;
                s32 i;

                event_ptr = TRANS_GOP_IN(obj, ins & 0xFFF);
                obj->status_a &= ~0x20000;
                cond = *TRANS_REG_IN(obj, (ins >> 12) & 0x3F);
                if (cond != 0 && (opcode == 0x8F || recipient != NULL) && event_ptr != NULL) {
                    count = (ins >> 18) & 7;
                    for (i = 0; i < count; i++) {
                        args[i] = obj->sp[i - count];
                    }
                    switch (opcode) {
                    case 0x87:
                        func_80024040(obj, recipient, *event_ptr, count, args);
                        break;
                    case 0x90:
                        func_800251B8(obj, recipient, *event_ptr, (ins >> 21) & 7, count, args);
                        break;
                    case 0x8F:
                        func_80025134(obj, *event_ptr, (ins >> 21) & 7, count, args);
                        break;
                    }
                } else {
                    obj->unkF4 = 0;
                }
                if (!(obj->status_a & 0x20000)) {
                    obj->sp = (s32 *)((u8 *)obj->sp - ((ins >> 16) & 0x1C));
                } else {
                    if (flags & 2) {
                        return -0xFF;
                    }
                    obj->sp--;
                }
            }
            break;

        }
        case 0x8A:
        case 0x91:
        {
            s32 *s_ptr; s32 *d_ptr; s32 s_val; s32 d_val;
            {
                s32 count = ins & 0x3F;
                s32 arg_count = (ins >> 20) & 0xF;
                s32 i;

                if (count == 0) {
                    d_val = arg_count + 1;
                    count = *(obj->sp - d_val);
                    arg_count = d_val;
                }
                for (i = 0; i < count; i++) {
                    GoolObj *child = GOOL_CreateObject(
                        obj,
                        (ins >> 12) & 0xFF,
                        (ins >> 6) & 0x3F,
                        (ins >> 20) & 0xF,
                        &obj->sp[-((ins >> 20) & 0xF)],
                        opcode == 0x91);
                    if ((s32)child < -0xFE) {
                        child->creator = obj;
                        obj->unkF4 = (s32)child;
                    } else {
                        obj->unkF4 = 0;
                    }
                }
                obj->sp -= arg_count;
            }
            break;

        }
        case 0x8C:
        {
            s32 *s_ptr; s32 *d_ptr; s32 s_val; s32 d_val;
            s_ptr = TRANS_GOP_IN(obj, (ins >> 12) & 0xFFF);
            d_ptr = TRANS_GOP_IN(obj, ins & 0xFFF);
            obj->voice_id = func_800304C8(obj, d_ptr, *(s16 *)s_ptr);
            break;

        }
        case 0x8D:
        {
            s32 *s_ptr; s32 *d_ptr; s32 s_val; s32 d_val;
            {
                u32 mode;
                u32 reg;
                s32 val;

                d_ptr = TRANS_GOP_IN(obj, ins & 0xFFF);
                mode = (ins >> 20) & 0xF;
                reg = (ins >> 12) & 0x3F;
                if (reg == 0) {
                    val = 0;
                } else {
                    val = *TRANS_REG_IN(obj, reg);
                }
                if (mode == 0xF) {
                    mode = 0x80000000;
                }
                if (ins & 0x40000) {
                    mode |= 0x40000000;
                }
                if (ins & 0x80000) {
                    mode |= 0x20000000;
                }
                func_80030840(val, mode, d_ptr, obj);
            }
            break;

        }
        default:
        {
            s32 *s_ptr; s32 *d_ptr; s32 s_val; s32 d_val;
            return -0xE;
        }
        }
    }
}
