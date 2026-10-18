/* GCC_VERSION: 2.6.3 */
/* GNU_AS_G: 8 */
#include "common.h"

typedef struct GoolVectors {
    s32 trans[3];
    s32 rot[3];
    s32 scale[3];
} GoolVectors;

typedef struct GoolCodeHeader {
    s32 unk00;
    s32 unk04;
    s32 unk08;
    s32 unk0C;
    s32 unk10;
} GoolCodeHeader;

typedef struct GoolExecutable {
    u8 pad00[0x10];
    GoolCodeHeader *header;
    u8 *code;
    u8 *data;
    u16 *states;
    void *unk20;
    u32 *anims;
} GoolExecutable;

typedef struct GoolDefaults {
    u8 bytes[0x2A];
    u16 field2A, field2C, field2E;
} GoolDefaults;

typedef struct ResourceEntry {
    u8 pad00[0x10];
    u8 *data;
} ResourceEntry;

typedef struct GoolObj {
    s32 kind;
    s32 unk04;
    u8 pad08[0x18];
    GoolExecutable *exec;
    s32 unk24;
    ResourceEntry *zone;
    s32 unk2C;
    GoolDefaults defaults;
    struct GoolObj *self;
    struct GoolObj *parent;
    struct GoolObj *next;
    struct GoolObj *children;
    s32 unk70;
    void *player;
    s32 unk78;
    s32 unk7C;
    GoolVectors vectors;
    s32 unkA4;
    s32 unkA8;
    s32 unkAC;
    s32 unkB0;
    s32 unkB4;
    s32 unkB8;
    s32 unkBC;
    s32 unkC0;
    s32 unkC4;
    u32 status_a;
    u32 status_b;
    u32 status_c;
    s32 subtype;
    s32 pid_flags;
    u32 *sp;
    u32 *pc;
    u32 *fp;
    u32 *unkE8;
    u32 *unkEC;
    s32 unkF0;
    s32 unkF4;
    s32 unkF8;
    s32 unkFC;
    s32 unk100;
    s32 unk104;
    void *anim_seq;
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

typedef struct NsdTable {
    u8 pad00[0x14];
    s32 items[1];
} NsdTable;

extern ResourceEntry *D_80057914[];
GoolExecutable *func_80015118(s32 *, s32, s32);
s32 GOOL_ChangeObjectState(GoolObj *, u32, s32 *, s32);


extern GoolObj *D_800566B4;

void func_80024040(GoolObj *, GoolObj *, s32, s32, void *);
void func_80030260(GoolObj *);

#define NODE_CHILDREN(n) ((n)->kind == 2 ? (GoolObj *)(n)->unk04 : (n)->children)
#define NODE_CHILDREN_PTR(n) ((n)->kind == 2 ? (GoolObj **)&(n)->unk04 : &(n)->children)

typedef struct ZoneEntity {
    u8 pad00[4];
    u16 flags;
    u8 group;
    u8 pad07;
    u16 id;
    u16 path_length;
    s16 rot_x;
    s16 rot_y;
    s16 rot_z;
    u8 type;
    u8 subtype;
    s16 x;
    s16 y;
    s16 z;
} ZoneEntity;

typedef struct ObjectRoot {
    s32 kind;
    GoolObj *word04;
} ObjectRoot;

typedef struct ZoneHeaderView {
    u8 pad00[0x204];
    s32 path_index;
    s32 path_count;
    u8 pad20C[0xD0];
    u32 flags2DC;
} ZoneHeaderView;

typedef struct ZoneEntryView {
    u32 word00;
    u32 id;
    s32 kind;
    s32 word0C;
    void *items[1];
} ZoneEntryView;

s32 func_8002F840(s32, s32);
void func_8001AC9C(GoolObj *, s32, s32 *);
void func_80026460(GoolObj *, void *, s32);

extern GoolObj *D_80060E00[];
extern u32 D_80060E04[];
extern u32 D_800618B0[];
void func_800167A4(void);
void func_8001EEA8(GoolObj *);
s32 GOOL_InterpretObject(GoolObj *, s32, s32);
void func_8001EB28(GoolObj *, s32);
void func_8001F30C(GoolObj *, s32);
void func_8001DE78(GoolObj *);

static __inline__ s32 GOOL_CreateObjectStackFrame(GoolObj *object, s32 arg_words, s32 flags)
{
    u32 *sp;
    u32 *old_fp;
    u32 *new_sp;
    u32 *new_fp;

    sp = object->sp;
    old_fp = object->fp;
    object->fp = sp;
    *object->sp++ = flags;
    *object->sp++ = (u32)object->pc;
    *object->sp++ = ((u32)(new_sp = sp - arg_words - 24) - (u32)object) | (((u32)(new_fp = old_fp - 24) - (u32)object) << 16);
    return -0xFF;
}

s32 GOOL_UpdateObject(GoolObj *obj, s32 flag) {
    u32 update_flag;
    GoolCodeHeader *header;
    s32 res;
    u32 *sp;
    u32 wait_entry;

    if (obj->unk04 != 3) {
        return -0xFF;
    }
    if (obj == D_800566B4) {
        func_800167A4();
    }
    D_80060E00[0] = obj;
    update_flag = D_800618B0[0] & 8;
    if (update_flag != 0) {
        if (((obj->status_b & 0x2000000) || (obj->state_flags & 0x20000)) && (D_800618B0[0] & 0x8000)) {
            update_flag = 1;
        } else {
            header = obj->exec->header;
            switch (header->unk04) {
            case 0x100:
                update_flag = D_800618B0[0] & 0x20;
                break;
            case 0x300:
            case 0x500:
            case 0x600:
                update_flag = D_800618B0[0] & 0x80;
                break;
            case 0x200:
                update_flag = D_800618B0[0] & 0x100;
                if (header->unk00 == 4 && (obj->subtype == 4 || obj->subtype == 7)) {
                    flag = 1;
                }
                break;
            case 0x400:
                update_flag = D_800618B0[0] & 0x400;
                break;
            }
        }
    }
    if (flag != 0 && update_flag != 0) {
        if ((obj->status_b & 0x10000000) && obj->unk104 != 0) {
            obj->unk104--;
            if (obj->unk104 == 0) {
                obj->status_b &= ~0x10000000;
            }
        } else {
            obj->unkFC = D_80060E04[0];
            if ((obj->status_b & 0x10) && D_800566B4->unkFC == obj->unkFC) {
                func_8001EEA8(obj);
            }
            if (obj->unkE8 != NULL) {
                GOOL_CreateObjectStackFrame(obj, 0, 0xFFFF);
                obj->pc = obj->unkE8;
                res = GOOL_InterpretObject(obj, 3, 0);
                if (res >= -0xFE) {
                    return res;
                }
            }
            sp = obj->sp;
            wait_entry = sp[-1];
            if (D_80060E04[0] - (wait_entry & 0xFFFFFF) >= (wait_entry >> 24)) {
                obj->sp = sp - 1;
                res = GOOL_InterpretObject(obj, 4, 0);
                if (res >= -0xFE) {
                    return res;
                }
            }
            func_8001EB28(obj, flag);
            func_8001F30C(obj, flag);
            obj->status_a &= ~0x20;
        }
    }
    if (obj->anim_seq != NULL && !(obj->status_b & 0x100) && (D_800618B0[0] & 4)) {
        if (((obj->status_b & 0x2000000) || (obj->state_flags & 0x20000)) && (D_800618B0[0] & 0x4000)) {
            update_flag = 1;
        } else {
            update_flag = 0;
            switch (obj->exec->header->unk04) {
            case 0x100:
                update_flag = D_800618B0[0] & 0x10;
                break;
            case 0x300:
            case 0x500:
            case 0x600:
                update_flag = D_800618B0[0] & 0x40;
                break;
            case 0x200:
                update_flag = D_800618B0[0] & 0x200;
                break;
            case 0x400:
                update_flag = D_800618B0[0] & 0x800;
                break;
            }
        }
        if (update_flag != 0) {
            func_8001DE78(obj);
        }
    }
    D_80060E00[0] = NULL;
    return -0xFF;
}

typedef struct GoolAnimSeq {
    u8 type;
    u8 pad01[3];
    u32 eid;
    s32 count;
    u8 data[1];
} GoolAnimSeq;

typedef struct GoolFrag {
    u8 tex[8];
    s16 x1;
    s16 y1;
    s16 x2;
    s16 y2;
} GoolFrag;

typedef struct GoolBound {
    s32 x1;
    s32 y1;
    s32 z1;
    s32 x2;
    s32 y2;
    s32 z2;
} GoolBound;

typedef struct RenderBufferView {
    u8 pad00[0x88];
    u32 ordering_table[0x800];
} RenderBufferView;

typedef struct CamTransformState {
    u8 mat7E4[0x60];
    u8 mat844[0x20];
    u8 vec864[0x24];
    u8 vec888[0x48];
} CamTransformState;

typedef struct RenderProjectionState {
    s32 distance;
    s16 matrix[9];
} RenderProjectionState;

extern CamTransformState D_800577E4;
extern RenderProjectionState D_800578D0;
extern RenderBufferView *D_8005840C[];
extern u8 D_80051774[];

ZoneEntryView *func_80015A98(u32 *);
s32 *func_80016E18(void);
s32 func_8003A144(GoolVectors *, void *, u32, s32, void *, s32, s32, u32);
void func_8003A76C(u32 *, void *, void *, s32, s32, s32 *, void *);
void func_80018B98(void *, s32, void *, GoolBound *, u32 *);
void func_80018A40(void *, u32 *, GoolObj *);
void func_80018964(void *, u32 *, GoolObj *);
void func_8001E7D8(GoolObj *, GoolAnimSeq *, u32, u32 *, u32);

#define ABS(x) ((x) < 0 ? -(x) : (x))

void func_8001DE78(GoolObj *obj) {
    GoolAnimSeq *anim_seq;
    u32 anim_frame;
    GoolBound bound;
    ResourceEntry *zone;

    anim_seq = (GoolAnimSeq *)obj->anim_seq;
    anim_frame = (u32)obj->anim_frame >> 8;
    switch (anim_seq->type) {
    case 2:
        {
            GoolAnimSeq *anim2 = anim_seq;
            s32 shift = ABS(obj->vectors.scale[0]) / 27279;
            if (func_8003A144(
                    &obj->vectors,
                    (obj->status_b & 0x200000) ? &D_800577E4.vec864 : &D_800577E4.vec888,
                    obj->status_b & 0x200,
                    shift,
                    (obj->status_b & 0x200000) ? &D_800577E4.mat7E4 : &D_800577E4.mat844,
                    D_800578D0.distance,
                    *(s32 *)(D_80057914[0]->data + 0x2E8) >> 8,
                    ((obj->status_b >> 18) ^ 1) & 1)) {
                void *tex = func_80015A98(&anim2->eid);
                func_8003A76C(
                    D_8005840C[0]->ordering_table,
                    (u8 *)anim2 + (anim_frame * 8 + 8),
                    tex,
                    200 << shift,
                    obj->cam_zoom + (0x800 - D_800578D0.distance / 2),
                    func_80016E18(),
                    D_80051774);
            }
        }
        break;
    case 5:
        {
            s32 shift = ABS(obj->vectors.scale[0]) / 27279;
            if (func_8003A144(
                    &obj->vectors,
                    &D_800577E4.vec888,
                    obj->status_b & 0x200,
                    shift,
                    &D_800577E4.mat844,
                    D_800578D0.distance,
                    *(s32 *)(D_80057914[0]->data + 0x2E8) >> 8,
                    ((obj->status_b >> 18) ^ 1) & 1)) {
                GoolAnimSeq *anim5 = anim_seq;
                s32 i = 0;
                GoolFrag *frag = (GoolFrag *)((u8 *)anim5 + (anim_frame * anim5->count * 16 + 12));
                void *tex = func_80015A98(&anim5->eid);
                for (; i < anim5->count; frag++, i++) {
                    bound.x1 = frag->x1 << shift;
                    bound.y1 = frag->y1 << shift;
                    bound.x2 = frag->x2 << shift;
                    bound.y2 = frag->y2 << shift;
                    func_80018B98(frag, obj->cam_zoom, tex, &bound, D_8005840C[0]->ordering_table);
                }
            }
        }
        break;
    case 4:
        func_8001E7D8(obj, anim_seq, anim_frame, D_8005840C[0]->ordering_table, obj->status_b & 0x400);
        break;
    case 1:
        if (func_80015A98(&anim_seq->eid)->kind == 20) {
            func_80018A40(
                func_80015A98(&((GoolAnimSeq *)obj->anim_seq)->eid)->items[(u32)obj->anim_frame >> 8],
                D_8005840C[0]->ordering_table,
                obj);
        } else {
            func_80018964(
                func_80015A98(&((GoolAnimSeq *)obj->anim_seq)->eid)->items[(u32)obj->anim_frame >> 8],
                D_8005840C[0]->ordering_table,
                obj);
        }
        if (obj->status_b & 0x100000) {
            if (obj == D_800566B4) {
                obj->defaults = *(GoolDefaults *)(obj->zone->data + 0x348);
            } else {
                zone = obj->zone ? obj->zone : D_80057914[0];
                obj->defaults = *(GoolDefaults *)(zone->data + 0x318);
            }
        }
        break;
    }
}

typedef struct GoolGlyph {
    u32 word00;
    u32 word04;
    s16 width;
    s16 height;
} GoolGlyph;

typedef struct GoolFont {
    u32 unk00;
    u32 eid;
    GoolGlyph glyphs[63];
    GoolGlyph backdrop;
} GoolFont;

s32 BIOS_AToI(u8 *);
void func_80018DBC(GoolObj *, GoolGlyph *, s32, void *, GoolBound *, u32 *, s32);
void func_8003D740(u8 *, u8 *, u32, u32, u32, u32);

s32 func_8001E3D4(GoolObj *obj, u8 *str, s32 start_x, GoolFont *font, void *tex, s32 shift, u32 *ot) {
    GoolBound glyph_bound;
    GoolBound bg_bound;
    u8 num_buf[8];
    s32 max_x;
    s32 has_bg;
    s32 color_flag;
    s32 cur_y;
    s32 scale_x;
    s32 scale_y;
    s32 len;
    u8 axis;
    u8 ch;
    GoolGlyph *glyph;
    s32 x2;
    s32 y2;
    s32 y1;

    color_flag = 1;
    cur_y = 0;
    max_x = 0;
    has_bg = 0;
    if (ot != NULL) {
        has_bg = obj->status_b & 0x4000000;
        if (has_bg) {
            bg_bound.x1 = 999999;
            bg_bound.y1 = 999999;
            bg_bound.x2 = -999999;
            bg_bound.y2 = -999999;
        }
    }
    glyph_bound.x1 = start_x;
    while (*str != '\0') {
        scale_x = 400;
        scale_y = 400;
        if (*str == '~') {
        tilde_loop:
            str++;
            switch (*str++) {
            case 'c':
                color_flag = (*str++ == '1');
                if (*str == '~') {
                    goto tilde_loop;
                }
                break;
            case 'p':
                if (*(u32 *)((u8 *)obj->sp - ((*str++ - 0x2E) << 2)) == 1) {
                    str++;
                }
                if (*str == '\0') {
                    goto done;
                }
                if (*str == '~') {
                    goto tilde_loop;
                }
                break;
            case 's':
                len = 0;
                axis = *str++;
                while ((ch = *str++) != '~') {
                    num_buf[len++] = ch;
                }
                num_buf[len] = '\0';
                if (axis == 'x') {
                    scale_x = BIOS_AToI(num_buf);
                } else {
                    scale_y = BIOS_AToI(num_buf);
                }
                if (*str == '~') {
                    goto tilde_loop;
                }
                break;
            case 'n':
            case '%':
                cur_y -= font->glyphs[0].height << shift;
                glyph_bound.x1 = start_x;
                goto next_char;
            }
        }
        x2 = (scale_x << shift) + glyph_bound.x1;
        glyph = &font->glyphs[*str - ' '];
        glyph_bound.x2 = x2;
        glyph_bound.y2 = cur_y + (glyph->height << shift);
        glyph_bound.y1 = glyph_bound.y2 - (scale_y << shift);
        if (glyph_bound.x2 > max_x) {
            max_x = glyph_bound.x2;
        }
        if (ot != NULL && glyph->word00 != 0) {
            if (has_bg) {
                bg_bound.x1 = bg_bound.x1 < glyph_bound.x1 ? bg_bound.x1 : glyph_bound.x1;
                bg_bound.y1 = bg_bound.y1 < glyph_bound.y1 ? bg_bound.y1 : glyph_bound.y1;
                bg_bound.x2 = bg_bound.x2 < glyph_bound.x2 ? glyph_bound.x2 : bg_bound.x2;
                bg_bound.y2 = bg_bound.y2 < glyph_bound.y2 ? glyph_bound.y2 : bg_bound.y2;
            }
            func_80018DBC(obj, glyph, obj->cam_zoom, tex, &glyph_bound, ot, color_flag);
        }
        glyph_bound.x1 += glyph->width << shift;
    next_char:
        str++;
    }
done:
    if (has_bg && ot != NULL) {
        GoolGlyph *backdrop = &font->backdrop;
        GoolBound *bg_ptr = &bg_bound;
        if (backdrop->word00 != 0) {
            bg_bound.x1 -= 100;
            bg_bound.y1 -= 0;
            bg_bound.x2 += 100;
            bg_bound.y2 += 0;
            func_80018B98(backdrop, obj->cam_zoom - 10, tex, bg_ptr, ot);
        }
    }
    return max_x;
}
