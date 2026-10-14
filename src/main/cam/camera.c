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

/* View of the global state object at D_80060DF0 (camera fields only). */
typedef struct CamGlobals {
    u8 pad000[0xAC0];
    u32 display_flags;      /* 0x800618B0 */
    s32 death_cam;          /* 0x800618B4 */
    u8 padAC8[0xAE0 - 0xAC8];
    s32 game_state;         /* 0x800618D0 */
    u8 padAE4[0xB9C - 0xAE4];
    s32 island_rot;         /* 0x8006198C */
    s32 wordBA0;            /* 0x80061990 */
    s32 island_state;       /* 0x80061994 */
} CamGlobals;

extern CamGlobals cam_globals __asm__("D_80060DF0");
/* Scalar names for the zone state also covered by level_position. CamFollow
 * reads it through the struct view, CamUpdate mostly through these. */
extern ZonePath *D_8005791C;
extern s32 D_80057920;
extern void *D_800566B4;    /* the player object */
extern s32 D_8005E71C;      /* pad buttons pressed this frame */
extern s32 D_80057974;
extern s32 D_80057874;
extern CamLevelView *D_8005C53C;
extern s32 D_8005E720;
extern u32 D_80060E04, D_80061990;

ZoneEntry *func_80015A98(u32 *);
s32 func_800245F0(s32, s32);
s32 func_80024628(s32, s32, s32);
void func_80025A60(ResourceEntry *, ZonePath *, s32, s32);
void func_80026460(void *, s32 *, s32);
void func_80029F6C(s32, CamCandidate *);
s32 func_8002A0C4(CamVec *, ZonePath *, CamCandidate *, u8, s32);
s32 func_8002A3EC(CamVec *, ZonePath *, CamCandidate *, u8, s32);
void func_8002BAB4(s32 *);

#define MIN(a, b) ((a) < (b) ? (a) : (b))
#define ABS(x) ((x) < 0 ? -(x) : (x))
#define SIGN(x) ((x) > 0 ? 1 : -((x) != 0))

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
void func_8002A82C(CamObject *obj, s32 flags)
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

/* Per-frame camera update, chosen by the current path's camera mode:
 * 0 fixed, 1/3 automatic (advance one step a frame, a pad press skips to the
 * next non-automatic path), 5/6 follow (func_8002A82C), 7 island map (step
 * along linked paths towards the stick angle), 8 step one way along the
 * path. The case 1/3 jump to `advance` keeps that update after the loop,
 * where retail has it. */
s32 func_8002B2BC(void)
{
    u8 unused[0x48];        /* frame space with no remaining use */
    ZoneEntry *zone, *neighbor;
    ZonePath *path, *next_path;
    ZonePath *target;
    s32 target_progress, side, j;
    s32 progress, next_progress, angle, state, skip, index, i;

    if (D_800566B4 == NULL) {
        return 0;
    }
    if (cam_globals.display_flags & 0x10000) {
        func_8002BAB4(&cam_globals.death_cam);
        return 0;
    }
    if (!(cam_globals.display_flags & 2)) {
        return 0;
    }
    switch (D_8005791C->cam_mode) {
    case 5:
    case 6:
        cam_globals.game_state = 0x100;
        func_8002A82C((CamObject *)D_800566B4, 0);
        return 1;
    case 0:
        cam_globals.game_state = 0x100;
        return 1;
    case 1:
    case 3:
        skip = 0;
        if ((D_8005E71C & 0xF0) && !(((ZoneHeader *)D_80057914->data)->flags & 0x81000)) {
            skip = 1;
        }
        do {
            if (!(((ZoneHeader *)level_position.zone->data)->flags & 0x1000)) {
                cam_globals.game_state = 0;
            }
            if ((D_80057920 >> 8) + 1 < D_8005791C->length && !skip) {
                goto advance;
            }
            if (D_8005791C->neighbor_count == 0) {
                return 1;
            }
            zone = func_80015A98(&((ZoneHeader *)D_80057914->data)
                                      ->neighbors[D_8005791C->neighbors[0].zone]);
            target = zone->items[D_8005791C->neighbors[0].path
                               + ((ZoneHeader *)zone->items[0])->path_index];
            if (D_8005791C->neighbors[0].goal & 1) {
                target_progress = 0;
            } else {
                target_progress = (target->length - 1) << 8;
            }
            func_80025A60((ResourceEntry *)zone, target, target_progress, 0);
            if (!(((ZoneHeader *)D_80057914->data)->flags & 0x1000)) {
                func_80026460(D_800566B4, &D_80057974, 1);
            }
            if (!skip) {
                return 1;
            }
        } while (D_8005791C->cam_mode == 1 || D_8005791C->cam_mode == 3);
        return 1;
    advance:
        func_80025A60(D_80057914, D_8005791C, D_80057920 + 0x100, 0);
        return 1;
    case 8:
        side = cam_globals.island_state & 3;
        index = -1;
        for (j = 0; j < D_8005791C->neighbor_count; j++) {
            if ((D_8005791C->neighbors[j].relation & 3) == (side ^ 3)) {
                index = j;
                break;
            }
        }
        if (side & 1) {
            if ((D_80057920 >> 8) + 1 >= D_8005791C->length) {
                if (index != -1) {
                    zone = func_80015A98(&((ZoneHeader *)D_80057914->data)
                                              ->neighbors[D_8005791C->neighbors[index].zone]);
                    target = zone->items[D_8005791C->neighbors[index].path
                                         + ((ZoneHeader *)zone->items[0])->path_index];
                    if (D_8005791C->neighbors[index].goal & 1) {
                        target_progress = 0;
                    } else {
                        target_progress = (target->length - 1) << 8;
                    }
                    func_80025A60((ResourceEntry *)zone, target, target_progress, 0);
                }
            } else {
                func_80025A60(D_80057914, D_8005791C, D_80057920 + 0x100, 0);
            }
        } else {
            if ((D_80057920 >> 8) - 1 < 0) {
                if (index != -1) {
                    zone = func_80015A98(&((ZoneHeader *)D_80057914->data)
                                              ->neighbors[D_8005791C->neighbors[index].zone]);
                    target = zone->items[D_8005791C->neighbors[index].path
                                         + ((ZoneHeader *)zone->items[0])->path_index];
                    if (D_8005791C->neighbors[index].goal & 1) {
                        target_progress = 0;
                    } else {
                        target_progress = (target->length - 1) << 8;
                    }
                    func_80025A60((ResourceEntry *)zone, target, target_progress, 0);
                }
            } else {
                func_80025A60(D_80057914, D_8005791C, D_80057920 - 0x100, 0);
            }
        }
        if (D_8005791C->cam_mode != 8) {
            cam_globals.island_state = 1;
        }
        return 1;
    case 7:
        path = NULL;
        state = cam_globals.island_state;
        switch (state) {
        case 0:
            return 0;
        case 5:
        case 6:
            angle = 0x22;
            break;
        case -1:
            state = 1;
            angle = -(cam_globals.island_rot & 0xFFF);
            break;
        default:
            angle = func_800245F0(D_80057874, cam_globals.island_rot);
            if (ABS(angle) >= 0x17) {
                angle = SIGN(angle);
            } else {
                angle = 0;
            }
            break;
        }
        next_path = D_8005791C;
        next_progress = D_80057920;
        do {
            ZoneHeader *header;
            s32 goal;

            if (angle == 0) {
                break;
            }
            path = next_path;
            progress = next_progress;
            if (cam_globals.island_state == -1) {
                s32 diff = func_800245F0(path->points[progress >> 8].rot_y, ABS(angle));

                if (diff < 0) {
                    diff = -diff;
                }
                if (diff < 0x17) {
                    break;
                }
            }
            next_progress = progress + 0x100;
            if (state & 4) {
                next_progress = progress + 0x400;
            }
            index = -1;
            if (next_progress >= path->length << 8) {
                for (i = 0; i < path->neighbor_count; i++) {
                    if (path->neighbors[i].goal == state) {
                        index = i;
                    } else if (index == -1) {
                        if (next_path->neighbor_count == 1 || (state & 3) == (path->neighbors[i].goal & 3)) {
                            index = i;
                        }
                    }
                }
                if (index == -1) {
                    for (i = 0; i < next_path->neighbor_count; i++) {
                        if (!(next_path->neighbors[i].goal & 4)) {
                            index = i;
                            break;
                        }
                    }
                }
                header = (ZoneHeader *)next_path->zone->data;
                neighbor = func_80015A98(&header->neighbors[next_path->neighbors[index].zone]);
                goal = next_path->neighbors[index].goal;
                next_path = neighbor->items[next_path->neighbors[index].path + ((ZoneHeader *)neighbor->items[0])->path_index];
                if (!(goal & 1)) {
                    next_progress = (next_path->length - 1) << 8;
                } else {
                    next_progress = 0;
                }
                if (state & 4) {
                    path = next_path;
                    progress = next_progress;
                    break;
                }
            } else if (state & 4) {
                progress = next_progress;
                break;
            }
            if (angle > 0) {
                path = next_path;
                progress = next_progress;
                break;
            }
        } while (next_path != D_8005791C || (next_progress >> 8) != (D_80057920 >> 8));
        if (cam_globals.island_state == -1) {
            cam_globals.island_state = state;
        }
        if (path != NULL && (path != D_8005791C || progress != D_80057920)) {
            func_80025A60(path->zone, path, progress, 0);
        }
        return 1;
    default:
        return 1;
    }
}

INCLUDE_ASM("asm/USA/main/nonmatchings/cam/camera", func_8002BAB4);
