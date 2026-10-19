/* GCC_VERSION: 2.6.3 */
#include "common.h"
#include "ns.h"

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

typedef struct GoolAnimSeq {
    u8 type;
    u8 pad01[3];
    u32 eid;
    s32 count;
    u8 data[1];
} GoolAnimSeq;

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

extern RenderProjectionState g_view_proj;


#define ABS(x) ((x) < 0 ? -(x) : (x))

void Gool_TextObjectTransform(GoolObj *obj, GoolAnimSeq *anim_seq, u32 anim_frame, u32 *ot, u32 center_flag)
{
    u8 buf[80];
    s32 shift;
    GoolAnimSeq *anim4;
    u8 *str;
    s32 i;
    u32 font_offset;
    GoolFont *font;
    void *tex;
    u8 *p;
    s32 width;

    shift = ABS(obj->vectors.scale[0]) / 27279;
    if (Gte_RCalcSpriteRotMatrix(
            &obj->vectors,
            &(*(CamTransformState *)g_m_view).vec888,
            obj->status_b & 0x200,
            shift,
            &(*(CamTransformState *)g_m_view).mat844,
            g_view_proj.distance,
            0x3C00,
            ((obj->status_b >> 18) ^ 1) & 1)) {
        anim4 = anim_seq;
        str = anim4->data;
        i = 0;
        while (i < (s32)anim_frame) {
            if (*str++ == '\0') {
                i++;
            }
        }
        font_offset = (u32)obj->invincibility_state >> 8;
        font = (GoolFont *)(obj->exec->anims + (font_offset ? font_offset : anim4->count));
        tex = Ns_Lookup(&font->eid);
        sprintf(buf, str, *(obj->sp - 2), *(obj->sp - 3), *(obj->sp - 4), *(obj->sp - 5));
        str = buf;
        p = str;
        while (*p != '\0') {
            p++;
        }
        if (p != str) {
            p--;
            while (p != str) {
                if (*p != ' ') {
                    break;
                }
                p--;
            }
            p[1] = '\0';
        }
        width = 0;
        if (center_flag) {
            width = Gool_TextStringTransform(obj, str, 0, font, tex, shift, NULL);
        }
        Gool_TextStringTransform(obj, str, -width / 2, font, tex, shift, ot);
    }
}
