/* GCC_VERSION: 2.6.3 */
/* GNU_AS_G: 8 */
#include "common.h"
#include "zone.h"

typedef struct ZqVec {
    s32 x, y, z;
} ZqVec;

typedef struct ZqBound {
    ZqVec p1;
    ZqVec p2;
} ZqBound;

typedef struct ZqRect {
    s32 x, y, z;
    s32 w, h, d;
} ZqRect;

typedef struct ZqZoneRect {
    s32 x, y, z;
    s32 w, h, d;
    u32 unk18;
    u16 root;
    s16 max_depth_x;
    s16 max_depth_y;
    s16 max_depth_z;
} ZqZoneRect;

typedef struct LevelStateView {
    u8 pad00[4];
    s32 level_id;
} LevelStateView;

typedef struct SubObj {
    u8 pad00[8];
    ZqBound bound;
    void *unk20;
    u8 pad24[4];
    ResourceEntry *entry;
    u8 pad2C[0x64 - 0x2C];
    struct SubObj *parent;
    u8 pad68[0x78 - 0x68];
    struct SubObj *unk78;
    u8 pad7C[4];
    ZqVec trans;
    u8 pad8C[0xA8 - 0x8C];
    s32 vel_y;
    u8 padAC[0xC8 - 0xAC];
    u32 status_a;
    u32 status_b;
    u32 status_c;
    u8 padD4[0xFC - 0xD4];
    u32 unkFC;
    u8 pad100[0x110 - 0x100];
    u16 *unk110;
    u8 pad114[0x120 - 0x114];
    u32 flags120;
    u8 pad124[4];
    s32 anim_state;
    u8 pad12C[4];
    u32 ground_time;
    s32 impact_vel_y;
    s32 offset138;
    s32 event;
    u8 pad140[0x148 - 0x140];
    s32 unk148;
    u8 pad14C[0x158 - 0x14C];
    s32 unk158;
} SubObj;

typedef struct SubWsNode {
    u16 flags;
    u16 x;
    u16 y;
    u16 z;
} SubWsNode;

typedef struct SubWorkspace {
    SubWsNode nodes[0x200];
    s32 initialized;
    s32 count;
    ZqBound bound1;
    ZqBound bound2;
    s32 unk1038;
    s32 unk103C;
    s32 unk1040;
    s32 unk1044;
    s32 unk1048;
    s32 unk104C;
} SubWorkspace;

extern LevelStateView *D_8005C53C[];
extern u32 D_80060E04[];
extern s32 D_800564BC;
extern s32 D_800565DC;
extern s32 *D_800566F4;

ZoneEntry *func_80015A98(u32 *);
s32 func_80024040(SubObj *, SubObj *, s32, s32, s32 *);
ZoneEntry *func_80026DD4(ZoneEntry *, ZqVec *);
void func_80027F50(void *, SubObj *, s32, s32);
s32 func_80037D50(ZqZoneRect *, ZqBound *, void *, s32);
void func_8003864C(SubWorkspace *, ZqBound *, s32, s32, s32, s32, s32, s32);
void func_8002D8B8(ZqVec *, SubObj *, SubWorkspace *, s32);
s32 func_8002CD9C(SubObj *, ZqVec *, SubWorkspace *);
s32 func_8002C8EC(SubObj *, ZqVec *, ZqVec *, SubWorkspace *, s32 *);
s32 func_8002E0A0(s32, s32, ZqVec *, SubObj *);
s32 func_8002E3F8(ZqVec *, s32, s32, s32 *, s32 *, SubObj *, s32);

typedef struct SubBox {
    ZqBound bound;
    SubObj *obj;
} SubBox;

typedef struct SubBoxList {
    SubBox boxes[96];
    s32 count;
} SubBoxList;

extern SubBoxList D_80060E08;
extern ZqVec D_800567F8;

void func_80024AD4(SubObj *, ZqBound *, SubObj *, ZqBound *);
void func_80038AC4(SubObj *, SubWorkspace *, ZqBound *, ZqBound *, s32, s32 *, s32, s32 (*)(SubObj *, u32));
s32 func_80038DF8(SubObj *, SubWorkspace *, ZqBound *, ZqBound *, s32, s32, s32);

static __inline__ s32 zone_rect_overlaps(ZqBound *b, ZqRect *r)
{
    if ((r->x << 8) < b->p2.x && (r->y << 8) < b->p2.y && (r->z << 8) < b->p2.z
        && ((r->x + r->w) << 8) >= b->p1.x && ((r->y + r->h) << 8) >= b->p1.y
        && ((r->z + r->d) << 8) >= b->p1.z) {
        return 1;
    }
    return 0;
}

static __inline__ s32 func_80026CA8(ZqBound *a, ZqBound *b)
{
    if (a->p1.y <= b->p2.y && a->p2.y > b->p1.y && a->p2.x > b->p1.x
        && a->p2.z > b->p1.z && a->p1.x <= b->p2.x && a->p1.z <= b->p2.z) {
        return 1;
    }
    return 0;
}

static __inline__ s32 func_80026D40(ZqBound *a, ZqBound *b)
{
    if (a->p1.x >= b->p1.x && a->p1.y >= b->p1.y && a->p1.z >= b->p1.z
        && a->p2.x < b->p2.x && a->p2.y < b->p2.y && a->p2.z < b->p2.z) {
        return 1;
    }
    return 0;
}

void func_8002D69C(s32, s32);
s32 func_80042B9C(s32);

static __inline__ void func_8002D7D4(s32 x1, s32 y1, s32 x2, s32 y2, s32 set)
{
    s32 *p;
    u32 mask;

    x2 += 16;
    mask = -1;
    if (x2 < 32) {
        if (x2 <= 0) {
            return;
        }
        mask = -1 << (32 - x2);
    }
    x1 += 15;
    if (x1 >= 32) {
        return;
    }
    if (x1 >= 0) {
        mask &= ~((s32)0x80000000 >> x1);
    }
    if (mask == 0) {
        return;
    }
    y1 += 16;
    y2 += 16;
    if (y1 < 0) {
        y1 = 0;
    }
    if (y2 > 32) {
        y2 = 32;
    }
    if (y1 >= 32) {
        return;
    }
    p = &D_800566F4[y1];
    if (set) {
        for (; y1 < y2; y1++, p++) {
            *p |= mask;
        }
    } else {
        mask = ~mask;
        for (; y1 < y2; y1++, p++) {
            *p &= mask;
        }
    }
}

#define ABS(x) ((x) >= 0 ? (x) : -(x))

s32 func_8002BE8C(SubObj *obj, ZqVec *in_vel, SubWorkspace *ws);
void func_8002C184(SubObj *obj, SubWorkspace *ws, s32 *pos, s32 *vel);
s32 func_8002C3B8(SubObj *obj, u32 node);
__inline__ void func_8002C51C(SubObj *obj, ZqVec *v1, ZqVec *v2, SubWorkspace *ws, s32 div_val, s32 *out);
s32 func_8002C660(SubObj *obj, ZqVec *v1, ZqVec *v2, SubWorkspace *ws);
s32 func_8002C8EC(SubObj *obj, ZqVec *v1, ZqVec *v2, SubWorkspace *ws, s32 *out_y);
s32 func_8002CD9C(SubObj *obj, ZqVec *v, SubWorkspace *ws);
__inline__ void func_8002D0B8(SubObj *obj, ZqVec *v1, ZqVec *v2, SubWorkspace *ws);
s32 func_8002D18C(SubObj *obj, ZqVec *v);
void func_8002D384(SubObj *obj, SubWorkspace *ws, s32 *pos, s32 *vel, s32 *out);

s32 func_8002BE8C(SubObj *obj, ZqVec *in_vel, SubWorkspace *ws)
{
    ZqVec pos;
    ZqVec vel;
    s32 arg;
    ZqVec *trans;
    s32 level;

    trans = &obj->trans;
    if (obj == NULL) {
        D_800565DC = 0;
        return 0;
    }
    level = D_8005C53C[0]->level_id;
    D_800564BC = (level == 0x11 || level == 0x1E) ? 0x27AC4 : 0xF424;
    pos.x = trans->x;
    pos.y = trans->y;
    pos.z = trans->z;
    vel.x = in_vel->x;
    vel.y = in_vel->y;
    vel.z = in_vel->z;
    if (D_800565DC) {
        if (ABS(D_800567F8.x - in_vel->x) < 10
            && ABS(D_800567F8.y - in_vel->y) < 10
            && ABS(D_800567F8.z - in_vel->z) < 10) {
            vel.x = 0;
            vel.y = in_vel->y;
            vel.z = 0;
        }
    }
    func_8002C184(obj, ws, (s32 *)&pos, (s32 *)&vel);
    if (!D_800565DC && (in_vel->x != 0 || in_vel->z != 0)
        && ((trans->x - pos.x) >= 0 ? (trans->x - pos.x) < 2 : (pos.x - trans->x) < 2)
        && ((trans->y - pos.y) >= 0 ? (trans->y - pos.y) < 2 : (pos.y - trans->y) < 2)
        && ((trans->z - pos.z) >= 0 ? (trans->z - pos.z) < 2 : (pos.z - trans->z) < 2)) {
        D_800567F8.x = in_vel->x;
        D_800567F8.y = in_vel->y;
        D_800567F8.z = in_vel->z;
        D_800565DC = 1;
    } else {
        D_800565DC = 0;
    }
    trans->x = pos.x;
    trans->y = pos.y;
    trans->z = pos.z;
    if (obj->status_a & 0x400) {
        arg = 0x6400;
        if (!(obj->status_a & 1) || obj->event != 0x900) {
            func_80024040(NULL, obj, obj->event, 1, &arg);
        }
    }
}

void func_8002C184(SubObj *obj, SubWorkspace *ws, s32 *pos, s32 *vel)
{
    s32 step[3];
    s32 out_pos[3];
    s32 nx, ny, nz, n, i;

    ws->unk104C = 0;
    nx = ABS(vel[0]) / 0x6400;
    ny = ABS(vel[1]) / 0x25800;
    nz = ABS(vel[2]) / 0x6400;
    if (nx > ny) {
        if (nx > nz) {
            n = nx;
        } else {
            n = nz;
        }
    } else {
        if (ny > nz) {
            n = ny;
        } else {
            n = nz;
        }
    }
    n++;
    for (i = 0; i < 3; i++) {
        step[i] = vel[i] / n;
    }
    while (vel[0] != 0 || vel[1] != 0 || vel[2] != 0) {
        for (i = 0; i < 3; i++) {
            if (ABS(step[i]) > ABS(vel[i])) {
                step[i] = vel[i];
            }
        }
        func_8002D384(obj, ws, pos, step, out_pos);
        for (i = 0; i < 3; i++) {
            pos[i] = out_pos[i];
            vel[i] -= step[i];
        }
    }
}


s32 func_8002C3B8(SubObj *obj, u32 node)
{
    s32 type, subtype, level;

    if (node != 0) {
        type = ((node & 0xE) >> 1) + 1;
    } else {
        type = 0;
    }
    subtype = (node & 0x3F0) >> 4;
    switch (subtype) {
    case 1:
        obj->status_a |= 0x400;
        obj->event = 0x700;
        break;
    case 2:
        obj->status_a |= 0x400;
        obj->event = 0xC00;
        break;
    case 5:
        obj->status_a |= 0x400;
        obj->event = 0x1E00;
        break;
    case 4:
        obj->status_a |= 0x400;
        obj->event = 0x1F00;
        break;
    case 3:
        obj->status_a |= 0x400;
        obj->event = 0x2100;
        break;
    case 12:
        obj->status_a |= 0x400;
        obj->event = 0x2300;
        break;
    case 6:
        obj->status_a |= 0x400;
        obj->event = 0xD00;
        break;
    case 11:
        obj->event = 0x900;
        obj->status_a |= 0x400;
        return 1;
    case 7:
    case 8:
    case 9:
    case 10:
        obj->status_a |= 0x2000;
        obj->event = 0x1200;
        break;
    }
    if (type == 4) {
        level = D_8005C53C[0]->level_id;
        if (level == 3 || level == 7) {
            obj->event = 0x2100;
            obj->status_a |= 0x400;
            return 0;
        } else {
            obj->event = 0x900;
            obj->status_a |= 0x400;
            return 1;
        }
    }
    if (type == 3 || type == 5) {
        return 1;
    }
    return 0;
}

__inline__ void func_8002C51C(SubObj *obj, ZqVec *v1, ZqVec *v2, SubWorkspace *ws, s32 div_val, s32 *out)
{
    ZqBound unused;
    s32 max_y, dy;
    ZqBound *bound;

    max_y = v2->y + D_800564BC;
    dy = v1->y - v2->y;
    bound = &ws->bound2;
    if (dy > 0) {
        max_y += dy;
    }
    ws->bound2.p1.x = v2->x + (-0x9600 / div_val) + 0xC80;
    ws->bound2.p2.x = v2->x + (0x9600 / div_val) - 0xC80;
    ws->bound2.p1.y = v2->y;
    ws->bound2.p2.y = v2->y + 0x29900;
    ws->bound2.p1.z = v2->z + (-0x9600 / div_val) + 0xC80;
    ws->bound2.p2.z = v2->z + (0x9600 / div_val) - 0xC80;
    func_80038AC4(obj, ws, &ws->bound1, bound, max_y, out, -0x3B9AC9FF, func_8002C3B8);
}


s32 func_8002C660(SubObj *obj, ZqVec *v1, ZqVec *v2, SubWorkspace *ws)
{
    s32 res;
    SubObj *hit_obj;
    ZqBound *bound;
    s32 max_y, dy, i, cand_y;
    SubBox *box, *hit_box;
    SubObj *cand_obj;

    res = -0x3B9AC9FF;
    hit_obj = NULL;
    bound = &ws->bound2;
    max_y = v2->y + 0xF424;
    dy = v1->y - v2->y;
    if (D_80060E08.count == 0) {
        return -0x3B9AC9FF;
    }
    if (dy > 0) {
        max_y += dy;
    }
    ws->bound2.p1.x = v2->x - 0x4B00;
    ws->bound2.p2.x = v2->x + 0x4B00;
    ws->bound2.p1.y = v2->y;
    ws->bound2.p2.y = v2->y + 0x29900;
    ws->bound2.p1.z = v2->z - 0x4B00;
    ws->bound2.p2.z = v2->z + 0x4B00;
    ws->unk104C += 0x10;
    for (i = 0, box = D_80060E08.boxes; i < D_80060E08.count; i++, box++) {
        cand_y = box->bound.p2.y;
        cand_obj = box->obj;
        if ((cand_y <= max_y || (cand_obj->status_b & 0x400000))
            && cand_y > res
            && func_80026CA8(bound, &box->bound)) {
            hit_box = box;
            if (cand_obj->status_b & 0x20000) {
                if (!(((obj->flags120 & 0x10) || obj->anim_state == 5)
                      && *(s32 *)(*(s32 *)((u8 *)cand_obj->unk20 + 0x10) + 4) == 0x300
                      && (!(cand_obj->status_c & 0x1012) || (cand_obj->flags120 & 0x10020)))) {
                    res = hit_box->bound.p2.y + 1;
                }
            }
            hit_obj = cand_obj;
            ws->unk104C += 0x1000;
        }
    }
    if (hit_obj != NULL) {
        func_80024AD4(obj, bound, hit_obj, &hit_box->bound);
    }
    return res;
}


s32 func_8002C8EC(SubObj *obj, ZqVec *v1, ZqVec *v2, SubWorkspace *ws, s32 *out_y)
{
    s32 out[3];
    ZqBound unused;
    s32 offset_y, flags, y2, y1, y3, res;
    ZqBound *bound;

    offset_y = 0;
    ws->bound2.p1.x = v2->x - 0x9600;
    ws->bound2.p2.x = v2->x + 0x9600;
    ws->bound2.p1.y = v2->y;
    ws->bound2.p2.y = v2->y + 0x29900;
    ws->bound2.p1.z = v2->z - 0x9600;
    ws->bound2.p2.z = v2->z + 0x9600;
    flags = 0x40001;
    bound = &ws->bound2;
    if (!ws->initialized || !func_80026D40(bound, &ws->bound1)) {
        func_800294B0(v2, obj, ws);
    }
    func_8002C51C(obj, v1, v2, ws, 8, out);
    y2 = out[2];
    y1 = out[1];
    if (y2 == -0x3B9AC9FF) {
        ws->unk1040 = 0;
    } else {
        ws->unk1040 = y2;
    }
    if (y1 == -0x3B9AC9FF) {
        ws->unk1044 = 0;
    } else {
        ws->unk1044 = y1;
    }
    y3 = func_8002C660(obj, v1, v2, ws);
    if (y3 == -0x3B9AC9FF) {
        ws->unk1048 = 0;
    } else {
        y2 = y3;
        ws->unk1048 = y2;
        flags &= ~0x40000;
        if (obj->unk78 != NULL) {
            if (obj->unk78->status_b & 0x400000) {
                offset_y = 0x19000;
            }
            if ((u32)(obj->unkFC - obj->ground_time) >= 4) {
                flags = 0x4001;
            }
        }
        flags |= 0x200000;
    }
    if ((y2 == -0x3B9AC9FF && y1 == y2) || obj->vel_y > 0) {
        if (obj->vel_y > 0) {
            obj->status_a &= ~0x244001;
        }
        ws->unk1038 = 0;
        res = -0x3B9AC9FF;
    } else {
        s32 tmp;
        if (y2 != -0x3B9AC9FF) {
            tmp = y2;
        } else {
            tmp = y1;
            flags = 1;
        }
        ws->unk1038 = tmp;
        res = tmp + 1;
        if (y2 == -0x3B9AC9FF) {
            tmp = obj->trans.y;
        } else {
            tmp = obj->trans.y + D_800564BC + offset_y;
        }
        *out_y = tmp;
        if (tmp < res) {
            res = obj->trans.y;
        }
        bound->p1.y = res;
        bound->p2.y = res + 0x29900;
        v2->y = res;
        if (!ws->initialized || !func_80026D40(bound, &ws->bound1)) {
            func_800294B0(v2, obj, ws);
        }
        if (obj->vel_y < 0 && (flags & 1)) {
            obj->impact_vel_y = obj->vel_y;
            obj->vel_y = 0;
        }
        obj->status_a |= flags;
        obj->ground_time = D_80060E04[0];
    }
    return res;
}

s32 func_8002CD9C(SubObj *obj, ZqVec *v, SubWorkspace *ws)
{
    ZqVec vec;
    s32 arg;
    s32 i, res1, res2;
    SubObj *hit_obj, *cand_obj;
    ZqBound *bound;
    SubBox *box;

    res1 = -0x3B9AC9FF;
    ws->bound2.p1.x = v->x - 0x4B00;
    ws->bound2.p2.x = v->x + 0x4B00;
    ws->bound2.p1.y = v->y + 0x1F2C0;
    ws->bound2.p2.y = v->y + 0x29900;
    ws->bound2.p1.z = v->z - 0x4B00;
    ws->bound2.p2.z = v->z + 0x4B00;
    hit_obj = NULL;
    bound = &ws->bound2;
    for (i = 0, box = D_80060E08.boxes; i < D_80060E08.count; i++, box++) {
        cand_obj = box->obj;
        if ((cand_obj->status_b & 0x8000000)
            && func_80026CA8(bound, &box->bound)) {
            hit_obj = cand_obj;
            if (res1 == -0x3B9AC9FF) {
                res1 = box->bound.p1.y;
            } else {
                res1 = (box->bound.p1.y < res1) ? box->bound.p1.y : res1;
            }
        }
    }
    bound->p1.x = v->x - 0x2580;
    bound->p2.x = v->x + 0x2580;
    bound->p1.z = v->z - 0x2580;
    bound->p2.z = v->z + 0x2580;
    res2 = func_80038DF8(obj, ws, &ws->bound1, bound, 2, 1, -0x3B9AC9FF);
    if (((ZoneHeader *)((ZoneEntry *)obj->entry)->items[0])->flags & 0x20000) {
        vec.x = v->x;
        vec.y = bound->p2.y;
        vec.z = v->z;
        if ((s32)func_80026DD4((ZoneEntry *)level_position.zone, &vec) >= -0xFE) {
            if ((((ZqZoneRect *)((ZoneEntry *)obj->entry)->items[1])->y << 8) < vec.y) {
                res2 = ((ZqZoneRect *)((ZoneEntry *)obj->entry)->items[1])->y << 8;
            }
        }
    }
    if (res1 != -0x3B9AC9FF && (res2 == -0x3B9AC9FF || res1 < res2)) {
        hit_obj->status_a |= 0x80;
        arg = 0x6400;
        func_80024040(obj, hit_obj, 0x1700, 1, &arg);
        return res1;
    }
    return res2;
}


__inline__ void func_8002D0B8(SubObj *obj, ZqVec *v1, ZqVec *v2, SubWorkspace *ws)
{
    s32 res;

    res = func_8002CD9C(obj, v2, ws);
    if (res == -0x3B9AC9FF) {
        ws->unk103C = 0;
    } else {
        ws->unk103C = res;
    }
    if (res != -0x3B9AC9FF && (v2->y + 0x29900) > (res - 1)) {
        if (v1->y < (res - 1) - 0x29900) {
            v2->y = (res - 1) - 0x29900;
        }
        obj->status_a |= 0x80;
        if (obj->vel_y > 0) {
            obj->vel_y = 0;
        }
    }
}


s32 func_8002D18C(SubObj *obj, ZqVec *v)
{
    s32 arg1, arg2, arg3;
    ZoneEntry *zone;
    ZqZoneRect *rect;
    s32 *header;
    s32 flag, level;

    zone = func_80026DD4((ZoneEntry *)level_position.zone, v);
    if ((s32)zone >= -0xFE) {
        rect = (ZqZoneRect *)((ZoneEntry *)obj->entry)->items[1];
        if (v->y < ((rect->y << 8) - obj->bound.p1.y)) {
            flag = 1;
            if (D_8005C53C[0]->level_id == 0x17) {
                arg1 = 0;
                func_80024040(NULL, obj, 0x2100, 1, &arg1);
            }
            if ((((ZoneHeader *)((ZoneEntry *)obj->entry)->items[0])->flags & 2)
                && obj->anim_state != 2) {
                arg2 = 0x6400;
                func_80024040(NULL, obj, 0x900, 1, &arg2);
                flag = 0;
            }
            if (flag) {
                v->y = (rect->y << 8) - obj->bound.p1.y;
                obj->impact_vel_y = obj->vel_y;
                obj->vel_y = 0;
                obj->status_a |= 1;
                obj->ground_time = D_80060E04[0];
            }
        }
    } else {
        obj->entry = (ResourceEntry *)zone;
    }
    if (obj->entry != NULL) {
        header = (s32 *)((ZoneEntry *)obj->entry)->items[0];
        if ((header[0xBF] & 4) && obj->trans.y < header[0xC0]
            && ((level = D_8005C53C[0]->level_id) == 0xF || level == 0x18)) {
            arg3 = 0x27100;
            func_80024040(NULL, obj, 0x2100, 1, &arg3);
        }
    }
    return -0xFF;
}


void func_8002D384(SubObj *obj, SubWorkspace *ws, s32 *pos, s32 *vel, s32 *out)
{
    s32 next_pos[3];
    s32 delta[3];
    s32 sp40;
    s32 sp44;
    s32 sp48;
    s32 i, gx, gz;

    for (i = 0; i < 3; i++) {
        delta[i] = vel[i];
    }
    for (i = 0; i < 3; i++) {
        next_pos[i] = pos[i] + delta[i];
    }
    func_8002C8EC(obj, (ZqVec *)pos, (ZqVec *)next_pos, ws, &sp40);
    func_8002DF50((ZqVec *)pos, obj, ws);
    gx = (((next_pos[0] - pos[0]) << 2) / 0x2000) + 0x10;
    gz = (((next_pos[2] - pos[2]) << 2) / 0x2000) + 0x10;
    if (func_8002E3F8((ZqVec *)pos, gx, gz, &sp44, &sp48, obj, 0)) {
        next_pos[0] = (((sp44 - 0x10) << 13) >> 2) + pos[0];
        next_pos[2] = (((sp48 - 0x10) << 13) >> 2) + pos[2];
    } else {
        next_pos[0] = pos[0];
        next_pos[2] = pos[2];
    }
    ws->unk104C++;
    if ((gx != 0x10 || gz != 0x10) && gx == sp44 && gz == sp48) {
        obj->status_a |= 0x100;
    }
    func_8002D0B8(obj, (ZqVec *)pos, (ZqVec *)next_pos, ws);
    func_8002D18C(obj, (ZqVec *)next_pos);
    for (i = 0; i < 3; i++) {
        out[i] = next_pos[i];
    }
}

