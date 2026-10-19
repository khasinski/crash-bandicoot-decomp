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

typedef struct SVec3 {
    s16 x, y, z;
} SVec3;

typedef struct ZoneEntryView {
    u32 word00;
    u32 id;
    s32 kind;
    s32 word0C;
    void *items[2];
} ZoneEntryView;

typedef struct ZoneEntity {
    ZoneEntryView *zone;
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
    SVec3 points[1];
} ZoneEntity;

typedef struct Unk4Bytes {
    u8 bytes[4];
} Unk4Bytes;

extern GoolVec3 D_80051768;
extern Unk4Bytes D_8005647C;
s32 SquareRoot0(s32);
s32 ratan2(s32, s32);

#define ABS(x) ((x) < 0 ? -(x) : (x))

s32 Gool_ObjectOrientOnPath(GoolObj *obj, s32 progress, s32 *trans_arr) {
    GoolVec3 *trans = (GoolVec3 *)trans_arr;
    GoolVec3 next_pt;
    GoolVec3 diff;
    GoolVec3 proj;
    ZoneEntity *entity;
    GoolVec3 *origin;
    s32 shift;
    s32 idx;
    s32 frac;
    SVec3 *pt;
    s32 dist;
    s32 dot;
    u32 old_status_a;

    entity = (ZoneEntity *)obj->entity;
    if (obj == NULL || entity == NULL) {
        return -0xE;
    }
    switch (entity->zone->kind) {
    case 7:
        origin = (GoolVec3 *)entity->zone->items[1];
        shift = 2;
        break;
    case 17:
        origin = &D_80051768;
        shift = 0;
        break;
    }
    if ((idx = ABS(progress) >> 8) == entity->path_length - 1 && idx != 0) {
        frac = (progress & 0xFF) + 0x100;
        idx = entity->path_length - 2;
    } else {
        frac = progress & 0xFF;
    }
    pt = &entity->points[idx];
    trans->x = ((pt->x << shift) + origin->x) << 8;
    trans->y = ((pt->y << shift) + origin->y) << 8;
    trans->z = ((pt->z << shift) + origin->z) << 8;
    if (entity->path_length == 1) {
        return 1;
    }
    pt++;
    next_pt.x = ((pt->x << shift) + origin->x) << 8;
    next_pt.y = ((pt->y << shift) + origin->y) << 8;
    next_pt.z = ((pt->z << shift) + origin->z) << 8;
    diff.x = next_pt.x - trans->x;
    diff.y = next_pt.y - trans->y;
    diff.z = next_pt.z - trans->z;
    if (obj->status_b & 0x8000) {
        dot = (next_pt.z - trans->z) >> 8;
        dist = SquareRoot0(
            ((next_pt.x - trans->x) >> 8) * ((next_pt.x - trans->x) >> 8) +
            dot * dot);
        if (dist != 0) {
            Unk4Bytes sp40 = D_8005647C;
            s32 abs_dx;
            s32 abs_dz;
            s32 temp;

            temp = ((obj->vectors.trans[0] - trans->x) >> 4) * ((next_pt.x - trans->x) >> 4) +
                   (temp = ((obj->vectors.trans[2] - trans->z) >> 4) * ((next_pt.z - trans->z) >> 4));
            dot = temp / dist;
            frac = dot / dist;
            if (frac >= 0x100 && (progress >> 8) < entity->path_length - 1) {
                return Gool_ObjectOrientOnPath(obj, (idx + 1) << 8, (s32 *)trans);
            }
            proj.x = (((dot >> 4) * ((next_pt.x - trans->x) >> 4)) / dist) + trans->x;
            proj.z = (((dot >> 4) * ((next_pt.z - trans->z) >> 4)) / dist) + trans->z;
            abs_dx = ABS(proj.x - obj->vectors.trans[0]);
            abs_dz = ABS(proj.z - obj->vectors.trans[2]);
            if (abs_dz < abs_dx) {
                obj->unkC0 = abs_dx + abs_dz / 2;
            } else {
                obj->unkC0 = abs_dz + abs_dx / 2;
            }
            obj->unkC0 = obj->unkC0;
            if (obj->unkC0 > obj->unk154 || (frac < 0 && idx == 0) || frac >= 0x100) {
                obj->status_a |= 0x200;
            }
            if ((next_pt.z - trans->z) * (obj->vectors.trans[0] >> 8) -
                (next_pt.x - trans->x) * (obj->vectors.trans[2] >> 8) -
                (trans->x >> 8) * next_pt.z +
                (trans->z >> 8) * next_pt.x < 0) {
                obj->unkC0 = -obj->unkC0;
            }
        } else {
            return -0xE;
        }
    }
    old_status_a = obj->status_a;
    if (obj->path_progress < 0 || (progress >> 8) >= entity->path_length - 1) {
        obj->status_a = old_status_a | 4;
    } else {
        obj->status_a = old_status_a & ~4;
    }
    if ((obj->status_a & 4) != (old_status_a & 4) && !(obj->status_a & 0x10)) {
        obj->status_a |= 0x10;
    } else {
        obj->status_a &= ~0x10;
    }
    if (obj->status_b & 4) {
        if ((obj->status_b & 2) && (obj->status_a & 4)) {
            obj->unkB4 = ratan2(-diff.x, -diff.z);
        } else {
            obj->unkB4 = ratan2(diff.x, diff.z);
        }
        if (obj->status_b & 0x800) {
            s32 abs_dx = ABS(diff.x);
            s32 abs_dz = ABS(diff.z);
            obj->vectors.rot[2] = ratan2(diff.x, diff.z);
            obj->unkB8 = -ratan2(diff.y, abs_dz < abs_dx ? abs_dx + abs_dz / 2 : abs_dz + abs_dx / 2);
        }
    } else if (obj->status_b & 0x800) {
        s32 abs_dx = ABS(diff.x);
        s32 abs_dz = ABS(diff.z);
        obj->unkB8 = ratan2(diff.y, abs_dz < abs_dx ? abs_dx + abs_dz / 2 : abs_dz + abs_dx / 2);
        obj->vectors.rot[2] = ratan2(-diff.x, -diff.z);
    }
    next_pt.x = ((next_pt.x - trans->x) * frac) >> 8;
    next_pt.y = ((next_pt.y - trans->y) * frac) >> 8;
    next_pt.z = ((next_pt.z - trans->z) * frac) >> 8;
    trans->x += next_pt.x;
    trans->y += next_pt.y;
    trans->z += next_pt.z;
    return entity->path_length;
}
