/* GCC_VERSION: 2.6.3 */
#include "common.h"

typedef struct GoolVec3 {
    s32 x, y, z;
} GoolVec3;

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
    void *unk14;
} ResourceEntry;

typedef struct GoolObj {
    s32 kind;
    s32 unk04;
    s32 bound[6];
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
    struct GoolObj *unk78;
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

typedef struct CamTransformState {
    u8 mat7E4[0x60];
    u8 mat844[0x20];
    u8 vec864[0x24];
    u8 vec888[0x48];
} CamTransformState;

extern CamTransformState D_800577E4;
extern s32 D_800578D0[];
extern ResourceEntry *D_80057914[];
extern u8 D_80051774[];

extern ResourceEntry *func_80015A98(void *);
extern s32 *func_80016E18(void);
extern s32 func_800180CC(u8 *, void *, GoolObj *, s32, s32 *);
extern void func_8003460C(u8 *, u32 *, void *, void *, s32, s32, s32 *, void *, s32);
extern void func_80034B08(u8 *, u32 *, void *, void *, s32, s32, s32 *, void *, s32);
extern s32 func_8003A144(GoolVectors *, void *, u32, s32, void *, s32, s32, u32);

void func_80018964(u8 *arg0, u32 *arg1, GoolObj *arg2) {
    ResourceEntry *res;
    void *data;

    res = func_80015A98(arg0 + 4);
    data = res->data;
    if (func_800180CC(arg0, data, arg2, 1, NULL) != 0) {
        func_8003460C(
            arg0,
            arg1,
            res->unk14,
            data,
            arg2->vectors.scale[0],
            arg2->cam_zoom + (0x800 - D_800578D0[0] / 2),
            func_80016E18(),
            D_80051774,
            0);
    }
}

void func_80018A40(u8 *arg0, u32 *arg1, GoolObj *arg2) {
    ResourceEntry *res;
    s32 sp28;
    void *data;
    s32 visible;

    res = func_80015A98(arg0 + 4);
    sp28 = 0;
    data = res->data;
    if (arg2->status_b & 0x200) {
        visible = func_8003A144(
            &arg2->vectors,
            &D_800577E4.vec888,
            1,
            0,
            &D_800577E4.mat844,
            D_800578D0[0],
            *(s32 *)(D_80057914[0]->data + 0x2E8) >> 8,
            ((arg2->status_b >> 18) ^ 1) & 1);
    } else {
        visible = func_800180CC(arg0, data, arg2, 0, &sp28);
    }
    if (visible != 0) {
        func_80034B08(
            arg0,
            arg1,
            res->unk14,
            data,
            arg2->vectors.scale[0],
            arg2->cam_zoom + (0x800 - D_800578D0[0] / 2),
            func_80016E18(),
            D_80051774,
            sp28);
    }
}
