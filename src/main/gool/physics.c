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


typedef struct GoolColor {
    u16 r, g, b;
} GoolColor;

extern GoolObj * D_800566B4;
asm(".sdata\n.size D_800566B4,4\n.text");
extern u32 D_80060E04[];
extern s32 D_80057960[];
extern void func_80024040(GoolObj *, GoolObj *, s32, s32, s32 *);

static __inline__ void func_8001EA00(GoolObj *object, s32 mode) {
    ResourceEntry *entry;
    GoolDefaults *defaults;

    entry = object->zone;
    if (entry == NULL) {
        entry = D_80057914[0];
    }
    if (object == D_800566B4) {
        defaults = (GoolDefaults *)(entry->data + 0x348);
    } else {
        defaults = (GoolDefaults *)(entry->data + 0x318);
    }
    switch (mode) {
    case 0:
        object->defaults = *defaults;
        return;
    case 1:
        object->defaults.field2A = defaults->field2A;
        object->defaults.field2C = defaults->field2C;
        object->defaults.field2E = defaults->field2E;
        return;
    }
}

s32 func_8001EB28(GoolObj *obj) {
    s32 sp18;
    s32 rem;
    GoolDefaults *defaults = &obj->defaults;

    switch (obj->invincibility_state) {
    case 6:
        if (D_80060E04[0] - obj->invincibility_time >= 0x10U) {
            obj->invincibility_state = 0;
            obj->status_b |= 0x80;
        }
        break;
    case 7:
        if (D_80060E04[0] - obj->invincibility_time >= 0x10U || (obj->status_a & 1)) {
            obj->invincibility_state = 0;
            obj->status_b |= 0x80;
        }
        break;
    case 4:
        if (D_80060E04[0] - obj->invincibility_time >= 0x3DU) {
            obj->invincibility_state = 0;
            func_8001EA00(obj, 1);
        }
        /* fallthrough */
    case 3:
        if (obj->invincibility_state == 3 && D_80060E04[0] - obj->invincibility_time >= 0x1C4U) {
            obj->invincibility_state = 0;
            func_8001EA00(obj, 1);
        } else if (obj->invincibility_state == 4) {
            if (obj->unk78 != NULL && obj->unk78->exec->header->unk04 == 0x300) {
                sp18 = 0;
                func_80024040(obj, obj->unk78, 0xA00, 1, &sp18);
            }
        }
        /* fallthrough */
    case 5:
        if (obj->invincibility_state == 5 && D_80060E04[0] - obj->invincibility_time >= 0x25BU) {
            obj->invincibility_state = 0;
            func_8001EA00(obj, 1);
        }
        /* fallthrough */
    case 2:
        rem = (D_80057960[0] % 4) << 8;
        if (rem >= 0x100) {
            defaults->field2A = 0x47F - rem;
        } else {
            defaults->field2A = rem + 0x7F;
        }
        defaults->field2C = defaults->field2E = defaults->field2A;
        break;
    case 1:
        break;
    default:
        if (obj == D_800566B4 && (obj->status_b & 0x4000000)) {
            *(GoolColor *)&obj->defaults.field2A = *(GoolColor *)(obj->zone->data + 0x372);
        }
        break;
    }
    return -0xFF;
}

typedef struct GoolBound {
    s32 x1;
    s32 y1;
    s32 z1;
    s32 x2;
    s32 y2;
    s32 z2;
} GoolBound;

typedef struct GoolBoundEntry {
    GoolBound bound;
    GoolObj *obj;
} GoolBoundEntry;

typedef struct GoolBoundsGlobals {
    GoolBoundEntry bounds[96];
    s32 count;
} GoolBoundsGlobals;

extern GoolBoundsGlobals D_80060E08;
extern void func_8001D33C(GoolObj *, s32 *);
extern void func_8002465C(s32 *, s32 *, s32 *, s32 *, s32 *);
extern s32 func_80026CA8(GoolBound *, GoolBound *);
extern void func_80024AD4(GoolObj *, GoolBound *, GoolObj *, GoolBound *);

void func_8001EEA8(GoolObj *obj) {
    s32 trans[3];
    GoolBound player_bound;
    GoolBoundEntry *entry;
    void **res;
    s32 *model;
    s32 angle;

    entry = &D_80060E08.bounds[D_80060E08.count++];
    entry->obj = obj;
    if (obj->status_a & 0x8000) {
        func_8001D33C(obj, obj->vectors.scale);
        obj->status_a &= ~0x8000;
    }
    if (*(u8 *)obj->anim_seq != 1) {
        entry->bound.x1 = obj->vectors.trans[0] + obj->bound[0];
        entry->bound.y1 = obj->vectors.trans[1] + obj->bound[1];
        entry->bound.z1 = obj->vectors.trans[2] + obj->bound[2];
        entry->bound.x2 = obj->vectors.trans[0] + obj->bound[3];
        entry->bound.y2 = obj->vectors.trans[1] + obj->bound[4];
        entry->bound.z2 = obj->vectors.trans[2] + obj->bound[5];
    } else {
        res = (void **)func_80015A98((u8 *)obj->anim_seq + 4);
        model = (s32 *)res[((u32)obj->anim_frame >> 8) + 4];
        angle = obj->vectors.rot[1] & 0xFFF;
        if (angle == 0 && obj->vectors.scale[0] == 0x1000) {
            trans[0] = obj->vectors.trans[0] + model[11];
            trans[1] = obj->vectors.trans[1] + model[12];
            trans[2] = obj->vectors.trans[2] + model[13];
        } else {
            func_8002465C(model + 11, obj->vectors.trans, obj->vectors.rot, obj->vectors.scale, trans);
        }
        if (angle < 0x200 || angle > 0xE00) {
            entry->bound.x1 = trans[0] + obj->bound[0];
            entry->bound.y1 = trans[1] + obj->bound[1];
            entry->bound.z1 = trans[2] + obj->bound[2];
            entry->bound.x2 = trans[0] + obj->bound[3];
            entry->bound.y2 = trans[1] + obj->bound[4];
            entry->bound.z2 = trans[2] + obj->bound[5];
        } else if (angle < 0x600) {
            entry->bound.x1 = trans[0] + obj->bound[2];
            entry->bound.x2 = trans[0] + obj->bound[5];
            entry->bound.y1 = trans[1] + obj->bound[1];
            entry->bound.y2 = trans[1] + obj->bound[4];
            entry->bound.z1 = trans[2] - obj->bound[3];
            entry->bound.z2 = trans[2] - obj->bound[0];
        } else if (angle < 0xA00) {
            entry->bound.x1 = trans[0] + obj->bound[0];
            entry->bound.x2 = trans[0] + obj->bound[3];
            entry->bound.y1 = trans[1] + obj->bound[1];
            entry->bound.y2 = trans[1] + obj->bound[4];
            entry->bound.z1 = trans[2] - obj->bound[5];
            entry->bound.z2 = trans[2] - obj->bound[2];
        } else {
            entry->bound.x1 = trans[0] - obj->bound[5];
            entry->bound.x2 = trans[0] - obj->bound[2];
            entry->bound.y1 = trans[1] + obj->bound[1];
            entry->bound.y2 = trans[1] + obj->bound[4];
            entry->bound.z1 = trans[2] + obj->bound[0];
            entry->bound.z2 = trans[2] + obj->bound[3];
        }
    }
    if (D_800566B4->unkFC == obj->unkFC) {
        player_bound.x1 = D_800566B4->vectors.trans[0] + D_800566B4->bound[0];
        player_bound.y1 = D_800566B4->vectors.trans[1] + D_800566B4->bound[1];
        player_bound.z1 = D_800566B4->vectors.trans[2] + D_800566B4->bound[2];
        player_bound.x2 = D_800566B4->vectors.trans[0] + D_800566B4->bound[3];
        player_bound.y2 = D_800566B4->vectors.trans[1] + D_800566B4->bound[4];
        player_bound.z2 = D_800566B4->vectors.trans[2] + D_800566B4->bound[5];
        if (func_80026CA8(&player_bound, &entry->bound) != 0) {
            func_80024AD4(obj, &entry->bound, D_800566B4, &player_bound);
        } else {
            obj->unk78 = NULL;
        }
    }
}

typedef struct GoolMoveParams {
    s32 accel;
    s32 max_speed;
    s32 unk8;
    s32 decel;
} GoolMoveParams;

typedef struct GoolDirEntry {
    s32 dir;
    s32 angle;
    s32 speed_scale;
} GoolDirEntry;

typedef struct GoolTimeState {
    u8 pad00[0x84];
    u32 unk84;
} GoolTimeState;

extern s32 D_800618D0[];
extern GoolMoveParams D_80052C24[];
extern u32 D_8005E720[];
extern GoolDirEntry D_80052B64[];
extern s32 D_80057930[];
extern GoolTimeState *D_80058404[];
extern u8 D_8005CFEC[];

extern s32 func_8003905C(s32);
extern s32 func_800390D0(s32);
extern s32 func_800243A0(s32, s32, s32, GoolObj *);
extern s32 func_80024528(s32, s32, s32, GoolObj *);
extern void func_8002BE8C(GoolObj *, s32 *, void *);
extern s32 func_8001AC9C(GoolObj *, s32, s32 *);
extern s32 func_80029C90(GoolObj *, s32 *, s32 *, s32, s32, s32);

#define ABS(x) ((x) < 0 ? -(x) : (x))
#define SCALE_DT(x) (((s32)((D_80058404[0]->unk84 < 0x67U ? D_80058404[0]->unk84 : 0x66) * (x))) / 1024)
#define CLAMP(x, min, max) ((x) >= (max) ? (max) : ((x) < (min) ? (min) : (x)))

void func_8001F30C(GoolObj *obj) {
    GoolVec3 vel;
    GoolVec3 saved_trans;
    GoolVec3 path_trans;
    GoolMoveParams *params;
    u32 state_flags;
    u32 dir_idx;
    s32 speed_scale;
    s32 target_rot;
    s32 diff;
    s32 cos_val;

    if ((obj->status_b & 0x80) && D_800618D0[0] == 0x100) {
        params = &D_80052C24[0];
        if (obj->state_flags & 4) {
            params = &D_80052C24[1];
            if (obj->status_a & 0x2000) {
                params += 4;
            }
        }
        if (obj->invincibility_state == 5) {
            params = &D_80052C24[4];
        }
        if (obj->state_flags & 8) {
            params = &D_80052C24[2];
            if (obj->status_a & 0x2000) {
                params += 4;
            }
        }
        state_flags = obj->state_flags;
        if (state_flags & 0x10) {
            params = &D_80052C24[3];
        }
        dir_idx = (D_8005E720[0] & 0xF000) >> 12;
        speed_scale = D_80052B64[dir_idx].speed_scale;
        if (D_80052B64[dir_idx].dir != 8) {
            target_rot = (D_80052B64[dir_idx].angle + D_80057930[0]) & 0xFFF;
            diff = ABS(target_rot - obj->unkB4);
            if (diff > 0x800) {
                diff = 0x1000 - diff;
            }
            if (state_flags & 8) {
                cos_val = func_800390D0(diff);
                obj->speed += (SCALE_DT(params->accel) * (cos_val >> 6)) >> 6;
                if (obj->speed <= 0x100) {
                    obj->unkB4 = target_rot;
                } else if (diff < 0x7C8) {
                    obj->unkB4 = func_800243A0(obj->unkB4, target_rot, 0xF00, NULL);
                } else {
                    obj->speed -= SCALE_DT(params->decel);
                    if (obj->speed < 0) {
                        obj->speed = 0;
                    }
                }
            } else if (obj->speed <= 0x100 || diff <= 0x400) {
                obj->unkB4 = target_rot;
                obj->speed += SCALE_DT(params->accel);
            } else {
                obj->speed = 0;
            }
            if (obj->speed > params->max_speed) {
                obj->speed = params->max_speed;
            }
        } else {
            obj->speed -= SCALE_DT(params->decel);
            if (obj->speed < 0) {
                obj->speed = 0;
            }
        }
        speed_scale = (speed_scale * obj->speed) >> 8;
        obj->unkA4 = ((func_8003905C(obj->unkB4) >> 4) * speed_scale) >> 8;
        obj->unkAC = ((func_800390D0(obj->unkB4) >> 4) * speed_scale) >> 8;
    }
    if ((obj->status_a & 1) && obj->event != 0x1200) {
        obj->status_a &= ~0x2000;
    }
    obj->status_a &= 0xFFCAA07E;
    if (obj->status_b & 1) {
        obj->vectors.rot[1] = func_800243A0(obj->vectors.rot[1], obj->unkB4, obj->unkB0, obj);
    }
    if (obj->status_b & 0x80000) {
        obj->vectors.rot[1] = func_80024528(obj->vectors.rot[1], obj->unkB4, obj->unkB0, obj);
    }
    if (obj->status_b & 0x2000) {
        obj->vectors.rot[0] = func_800243A0(obj->vectors.rot[0], obj->unkB8, obj->ang_vel_x, NULL);
    }
    if (obj->exec->header->unk00 != 5) {
        obj->unk78 = NULL;
    }
    if (obj->status_b & 0x40) {
        vel.x = SCALE_DT(obj->unkA4);
        vel.y = SCALE_DT(obj->unkA8);
        vel.z = SCALE_DT(obj->unkAC);
        saved_trans = *(GoolVec3 *)obj->vectors.trans;
        if (obj->status_b & 8) {
            obj->event = 0xFF;
            func_8002BE8C(obj, (s32 *)&vel, D_8005CFEC);
        } else {
            obj->vectors.trans[0] += vel.x;
            obj->vectors.trans[1] += vel.y;
            obj->vectors.trans[2] += vel.z;
        }
        if (obj->status_b & 0x8000) {
            func_8001AC9C(obj, 0, (s32 *)&path_trans);
            obj->floor_y = path_trans.y;
            if (obj->status_a & 0x200) {
                *(GoolVec3 *)obj->vectors.trans = saved_trans;
            }
        }
        if (obj->status_b & 0x1000) {
            obj->unkA4 = CLAMP(obj->unkA4, -obj->unkB8, obj->unkB8);
            obj->unkA8 = CLAMP(obj->unkA8, -obj->unkB8, obj->unkB8);
            obj->unkAC = CLAMP(obj->unkAC, -obj->unkB8, obj->unkB8);
        }
        if (obj->status_b & 0x4000) {
            if (obj->vectors.trans[1] <= obj->floor_y) {
                obj->vectors.trans[1] = obj->floor_y;
                obj->status_a |= 1;
                obj->floor_time = D_80060E04[0];
                if (obj->unkA8 < 0) {
                    obj->floor_vel_y = obj->unkA8;
                    obj->unkA8 = 0;
                }
            }
        }
    }
    if (obj->status_b & 0x20) {
        obj->unkA8 -= (D_80058404[0]->unk84 < 0x67U ? D_80058404[0]->unk84 : 0x66) * 4000;
        if (obj->unkA8 < -0x2EE000) {
            obj->unkA8 = -0x2EE000;
        }
    }
    if ((obj->status_b & 0x10) && D_800566B4->unkFC != obj->unkFC &&
        func_80029C90(obj, obj->vectors.trans, D_800566B4->vectors.trans, 0x7D000, 0xAF000, 0x7D000) == 0) {
        func_8001EEA8(obj);
    }
}

typedef struct SVec3 {
    s16 x, y, z;
} SVec3;

