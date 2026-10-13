/* GCC_VERSION: 2.6.3 */
#include "common.h"
#include "zone.h"

/* One viewpoint considered by func_8002A82C: a path, the progress the camera
 * would take on it and how far that is from the current progress. */
typedef struct CamCandidate {
    ZonePath *path;
    s32 word04;
    s32 progress;
    s32 exit;
    s32 entrance;
    s32 delta;
    s32 distance;
    s32 flags;
    s32 relation;
    s32 pan_x;
    s32 zoom;
    s32 pan_y;
    s32 found;
} CamCandidate;

typedef struct CamVec {
    s32 x, y, z;
} CamVec;

typedef struct CamObject {
    u8 pad00[0x80];
    CamVec trans;
    u8 pad8C[0x140 - 0x8C];
    s32 cam_zoom;
} CamObject;

typedef struct CamLevelView {
    u8 pad00[4];
    s32 level_id;
} CamLevelView;

/* Camera offsets (z, zoom, x pan, y pan) and their seek directions; only this
 * unit addresses them through $gp. */
s32 D_800564A4 = -0x12C00;
s32 D_800564A8 = 0x6A400;
s32 D_800564AC = 0;
s32 D_800564B0 = 0;
s32 D_800564B4 = 0x3E800;
s32 D_800564B8 = 0;

/* .sbss owned by this unit: camera speed along the path. */
asm(".globl D_800565C0");
s32 D_800565C0;

extern CamLevelView *D_8005C53C;
extern s32 D_8005E720;
extern u32 D_80060E04, D_80061990;

ZoneEntry *func_80015A98(u32 *);
s32 func_80024628(s32, s32, s32);
void func_80025A60(ResourceEntry *, ZonePath *, s32, s32);
void func_80029F6C(s32, CamCandidate *);
s32 func_8002A0C4(CamVec *, ZonePath *, CamCandidate *, u8, s32);
s32 func_8002A3EC(CamVec *, ZonePath *, CamCandidate *, u8, s32);

#define MIN(a, b) ((a) < (b) ? (a) : (b))
#define ABS(x) ((x) < 0 ? -(x) : (x))

INCLUDE_ASM("asm/USA/main/nonmatchings/cam/camera", func_80029F6C);

INCLUDE_ASM("asm/USA/main/nonmatchings/cam/camera", func_8002A0C4);

INCLUDE_ASM("asm/USA/main/nonmatchings/cam/camera", func_8002A3EC);

/* Path reached through neighbour link i of the current path. */
static __inline__ ZonePath *cam_neighbor_path(s32 i)
{
    ZoneEntry *zone;

    zone = func_80015A98(&((ZoneHeader *)level_position.zone->data)
                              ->neighbors[level_position.path->neighbors[i].zone]);
    return zone->items[level_position.path->neighbors[i].path
                       + ((ZoneHeader *)zone->items[0])->path_index];
}

/* Steer the camera: update the offsets from the pad and the zone flags, then
 * find the progress on the current or a linked path that best follows obj
 * and move towards it. */
void func_8002A82C(CamObject *obj)
{
    CamCandidate cams[4];
    CamVec trans;
    CamCandidate *nearest;
    ZonePath *path, *neighbor;
    s32 nearest_distance, y, flags, count;
    s32 new_pan, new_zoom, snap_pan, snap_zoom, total_zoom, distance;
    s32 found, not_same, exit;
    s32 direction;
    u32 header_flags;
    s32 i;

    count = 0;
    nearest_distance = 0x7FFFFFFF;
    flags = 0;
    y = obj->trans.y;
    /* Bit 0: in the first half (or first 50 units) of the path; bit 1: in
     * the second half (or last 50 units). */
    if ((level_position.progress >> 8) < level_position.path->length / 2
        || (level_position.progress >> 8) < 50) {
        flags = 1;
    }
    if ((level_position.progress >> 8) >= level_position.path->length / 2
        || level_position.path->length - (level_position.progress >> 8) < 50) {
        flags |= 2;
    }
    new_zoom = 0;
    new_pan = 0;
    snap_zoom = 1;
    snap_pan = 1;

    header_flags = ((ZoneHeader *)level_position.zone->data)->flags;
    if ((header_flags & 0x80) || D_800564A8 < 0x32000) {
        if (header_flags & 0x8000) {
            D_800564AC = 1;
        } else {
            D_800564AC = 0;
        }
    } else if (D_8005E720 & 0x1000) {
        D_800564AC = 0;
    } else if (D_8005E720 & 0x4000) {
        D_800564AC = 1;
    }
    if (D_8005E720 & 0x8000) {
        D_800564B0 = 0;
    } else if (D_8005E720 & 0x2000) {
        D_800564B0 = 1;
    }
    if (D_800564AC) {
        if (D_8005C53C->level_id == 3) {
            D_800564A4 += 0x3200;
            if (D_800564A4 > 0x4B000) {
                D_800564A4 = 0x4B000;
            }
        } else {
            D_800564A4 += 0x3200;
            if (D_800564A4 > 0x12C00) {
                D_800564A4 = 0x12C00;
            }
        }
    } else {
        D_800564A4 -= 0x3200;
        if (D_800564A4 < -0x12C00) {
            D_800564A4 = -0x12C00;
        }
    }
    if (((ZoneHeader *)level_position.zone->data)->flags & 0x4000) {
        if (level_position.path->direction_x) {
            if (D_800564B0) {
                D_800564B8 = (D_800564B8 + 0x6400
                              > (level_position.path->direction_x > 0 ? 0x4B000 : 0))
                    ? (level_position.path->direction_x > 0 ? 0x4B000 : 0)
                    : D_800564B8 + 0x6400;
            } else {
                D_800564B8 = (D_800564B8 - 0x6400
                              < (level_position.path->direction_x < 0 ? -0x4B000 : 0))
                    ? (level_position.path->direction_x < 0 ? -0x4B000 : 0)
                    : D_800564B8 - 0x6400;
            }
        }
    } else {
        D_800564B8 = 0;
    }

    /* A linked path running up/down sets the pan, one running in depth the
     * zoom; the current path overrides both and is approached gradually. */
    for (i = 0; i < level_position.path->neighbor_count; i++) {
        if (level_position.path->neighbors[i].relation & flags) {
            neighbor = cam_neighbor_path(i);
            if (neighbor->direction_y) {
                new_pan = neighbor->cam_zoom << 8;
            }
            if (neighbor->direction_z) {
                new_zoom = neighbor->cam_zoom << 8;
            }
        }
    }
    if (level_position.path->direction_y) {
        snap_pan = 0;
        new_pan = level_position.path->cam_zoom << 8;
    }
    if (level_position.path->direction_z) {
        snap_zoom = 0;
        new_zoom = level_position.path->cam_zoom << 8;
    }
    if (new_zoom && (level_position.progress >> 8) >= 11
        && (level_position.progress >> 8) < level_position.path->length - 10) {
        if (snap_zoom) {
            D_800564A8 = new_zoom;
        } else {
            D_800564A8 = func_80024628(D_800564A8, new_zoom, 0x1900);
        }
    }
    total_zoom = D_800564A8 + D_800564A4 + obj->cam_zoom;
    if (new_pan) {
        if (snap_pan) {
            D_800564B4 = new_pan;
        } else {
            D_800564B4 = func_80024628(D_800564B4, new_pan, 0x6400);
        }
    }

    /* Candidate on the current path. */
    direction = level_position.path->direction_z;
    cams[count].pan_x = D_800564B8;
    cams[count].pan_y = D_800564B4;
    cams[count].zoom = total_zoom;
    if (direction) {
        trans.x = obj->trans.x;
        trans.y = obj->trans.y;
        trans.z = obj->trans.z;
        found = func_8002A3EC(&trans, level_position.path, &cams[count], 0, 0);
    } else {
        trans.x = obj->trans.x + D_800564B8;
        trans.y = obj->trans.y + D_800564B4;
        trans.z = total_zoom + obj->trans.z;
        found = func_8002A0C4(&trans, level_position.path, &cams[count], 0, 0);
    }
    if (found) {
        cams[count].delta = ABS(level_position.progress - cams[count].progress);
        if (level_position.progress > cams[count].progress) {
            cams[count].flags = 1;
        } else {
            cams[count].flags = 2;
        }
        count++;
    }

    /* Candidates on the linked paths, measured through the shared end. */
    for (i = 0; i < level_position.path->neighbor_count; i++) {
        if ((level_position.path->neighbors[i].goal & 4) && D_80060E04 - D_80061990 > 15) {
            continue;
        }
        if (!(level_position.path->neighbors[i].relation & flags)) {
            continue;
        }
        path = cam_neighbor_path(i);
        if (ABS(path->direction_x) == ABS(level_position.path->direction_x)
            && ABS(path->direction_y) == ABS(level_position.path->direction_y)
            && ABS(path->direction_z) == ABS(level_position.path->direction_z)) {
            not_same = 0;
        } else {
            not_same = 1;
        }
        cams[count].pan_x = D_800564B8;
        cams[count].pan_y = D_800564B4;
        cams[count].zoom = total_zoom;
        direction = path->direction_z;
        if (direction) {
            trans.x = obj->trans.x;
            trans.y = y;
            trans.z = obj->trans.z;
            found = func_8002A3EC(&trans, path, &cams[count],
                                  level_position.path->neighbors[i].goal, not_same);
        } else {
            trans.x = obj->trans.x + D_800564B8;
            trans.y = y + D_800564B4;
            trans.z = total_zoom + obj->trans.z;
            found = func_8002A0C4(&trans, path, &cams[count],
                                  level_position.path->neighbors[i].goal, not_same);
        }
        if (found) {
            if (level_position.path->neighbors[i].relation & 1) {
                exit = 0;
                distance = level_position.progress;
            } else {
                exit = (level_position.path->length << 8) - 1;
                distance = exit - level_position.progress;
            }
            cams[count].exit = exit;
            if (level_position.path->neighbors[i].goal & 1) {
                cams[count].entrance = 0;
                cams[count].delta = distance + 0x100 + cams[count].progress;
                cams[count].relation = 2;
            } else {
                cams[count].entrance = (path->length << 8) - 1;
                cams[count].delta = distance + (((path->length << 8) - 1) - cams[count].progress) + 0x100;
                cams[count].relation = 1;
            }
            cams[count].flags = level_position.path->neighbors[i].relation;
            count++;
        }
    }

    if (count == 0) {
        return;
    }
    /* A path with camera mode 1 wins; otherwise prefer found positions,
     * then the nearest. */
    nearest = &cams[0];
    for (i = 0; i < count; i++) {
        if (cams[i].path->cam_mode == 1) {
            nearest = &cams[i];
            break;
        }
        if (cams[i].found > nearest->found
            || (cams[i].distance < nearest_distance && cams[i].found >= nearest->found)) {
            nearest = &cams[i];
            nearest_distance = cams[i].distance;
        }
    }
    if (nearest->delta == 0) {
        return;
    }
    if (nearest->delta * level_position.path->node_distance <= 30000) {
        /* Close enough: jump there. */
        func_80025A60(nearest->path->zone, nearest->path, nearest->progress, 0);
        D_800565C0 = nearest->delta;
    } else {
        if (nearest->delta <= 0x200) {
            D_800565C0 = nearest->delta / 2;
        } else if (nearest->delta >= 0x500) {
            D_800565C0 = MIN(nearest->delta / 2 + 0x100, D_800565C0 + 0x100);
        } else {
            D_800565C0 = 0x200;
        }
        func_80029F6C(D_800565C0, nearest);
    }
}

INCLUDE_ASM("asm/USA/main/nonmatchings/cam/camera", func_8002B2BC);

INCLUDE_ASM("asm/USA/main/nonmatchings/cam/camera", func_8002BAB4);
