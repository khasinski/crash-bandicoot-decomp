/* GCC_VERSION: 2.6.3 */
/* GNU_AS_G: 8 */
#include "common.h"
#include "zone.h"
#include "ns.h"

typedef struct LvlVec {
    s32 x, y, z;
} LvlVec;

/* Camera vectors at 0x80057864: position, rotation, and copies of the
 * rotation from before and after the latest path update. */
typedef struct LvlCamera {
    LvlVec trans;
    LvlVec rot;
    u8 pad18[0xD0 - 0x18];
    LvlVec rot_after;
    LvlVec rot_before;
} LvlCamera;

typedef struct LvlColorState {
    ZoneColor prev;
    ZoneColor cur;
    ZoneColor target;
    u32 start_tick;
} LvlColorState;

extern LvlCamera lvl_camera __asm__("D_80057864");
extern LvlColorState lvl_color __asm__("D_80057964");
extern u32 engine_counter[] __asm__("func_80034520");
extern u32 D_8005FF58[], D_80061904[];
extern s32 D_800618D0[], D_80061998[], D_80061A5C[], D_80061A60[], D_80061A64[];

/* SLST polygon id lists: current, and the two buffers swapped per step. */
extern void *D_800566B8;
extern void *D_800566BC;
extern void *D_80056700;

ResourceEntry *func_80015118(void *, s32, s32);
void func_80015458(void *, s32);
ZoneEntry *func_80015A98(u32 *);
void func_8001495C(ZoneLoadList *, s32);
void func_80014D00(u32, s32, s32, u32);
void func_80013748(void);
void func_8001BCC8(ZoneEntry *, s32);
void func_8001D200(ZoneEntry *);
void *func_80029B0C(void *, void *, void *, s32);
void func_800260AC(void *, u32);
void func_800296A8(ZonePath *, s32, LvlVec *);
void func_800317DC(void *);

/* Whether one of the header's neighbour links resolves to entry. */
static __inline__ s32 zone_has_neighbor(ZoneHeader *header, ZoneEntry *entry)
{
    s32 i;

    for (i = 0; i < header->neighbor_count; i++) {
        if (func_80015A98(&header->neighbors[i]) == entry) {
            return 1;
        }
    }
    return 0;
}

/* Spawn type-3 entities of zone when its pending-spawn display flag is set. */
__inline__ void func_80025858(ZoneEntry *zone)
{
    ZoneHeader *header, *cur;
    u8 *entity;
    s32 i;

    header = (ZoneHeader *)zone->items[0];
    if (header->display_flags & 2) {
        for (i = 0; i < header->entity_count; i++) {
            cur = (ZoneHeader *)zone->items[0];
            entity = (u8 *)zone->items[i + cur->path_index + cur->path_count];
            if (entity[6] == 3) {
                func_8001BCC8(zone, i);
            }
        }
        header->display_flags &= ~2;
    }
}

/* Spawn pending type-3 entities across all neighbours of the current zone. */
void func_80025928(void)
{
    ZoneHeader *header;
    ZoneEntry *neighbor;
    s32 i;

    if (level_position.zone == NULL) {
        return;
    }
    header = (ZoneHeader *)((ZoneEntry *)level_position.zone)->items[0];
    for (i = 0; i < header->neighbor_count; i++) {
        neighbor = func_80015A98(&header->neighbors[i]);
        func_80025858(neighbor);
    }
}


/* LevelUpdate: move the camera to progress along path in zone. Updates the
 * visible polygon lists (SLST) point by point, and on a zone change unloads
 * the old zone's neighbours, loads the new zone's entries and pages and
 * marks its neighbours. Clears the NS update-pending word at the end. */
void func_80025A60(ResourceEntry *zone, ZonePath *path, s32 progress, u32 flags)
{
    u8 unused[0x18];        /* frame space with no remaining use */
    ZoneHeader *header, *cur_header, *n_header, *neighbor_header;
    ZoneEntry *slst, *neighbor;
    void *tmp;
    s32 last, pt, next, steps, i, flag;

    if (path == NULL || zone == NULL) {
        goto done;
    }
    last = (path->length << 8) - 1;
    if (progress < last) {
        last = progress;
        if (last < 0) {
            last = 0;
        }
    }
    progress = last;
    if (((ZoneHeader *)((ZoneEntry *)zone)->items[0])->world_count) {
        if (level_position.zone != zone || path != level_position.path
            || (level_position.progress >> 8) != (progress >> 8)) {
            slst = (ZoneEntry *)func_80015118(path, 1, 1);
            pt = progress >> 8;
            steps = (progress - level_position.progress) >> 8;
            /* pt + 1 goes through a variable: written inline, fold turns
             * it into (length - 1) - pt, which retail does not have. */
            if (path != level_position.path || __builtin_abs(steps) > pt
                || __builtin_abs(steps) > path->length - (next = pt + 1)) {
                tmp = D_800566BC;
                D_800566BC = D_80056700;
                D_80056700 = tmp;
                if (pt < path->length / 2) {
                    D_800566B8 = func_80029B0C(slst->items[0], D_800566B8, D_80056700, 1);
                    pt = 0;
                } else {
                    D_800566B8 = func_80029B0C(slst->items[path->length], D_800566B8, D_80056700, 0);
                    pt = path->length - 1;
                }
            } else {
                pt = level_position.progress >> 8;
            }
            steps = (progress >> 8) - pt;
            while (steps != 0) {
                tmp = D_800566BC;
                D_800566BC = D_80056700;
                D_80056700 = tmp;
                if (steps > 0) {
                    steps--;
                    D_800566B8 = func_80029B0C(slst->items[++pt], D_800566B8, D_80056700, 1);
                } else {
                    D_800566B8 = func_80029B0C(slst->items[pt--], D_800566B8, D_80056700, 0);
                    steps++;
                }
            }
            func_80015458(path, 1);
        } else {
            if (level_position.progress == progress) {
                goto done;
            }
            level_position.progress = progress;
            goto camera;
        }
    }
    if (level_position.zone != zone) {
        flag = 1;
        cur_header = NULL;
        header = (ZoneHeader *)((ZoneEntry *)zone)->items[0];
        D_80061998[0] = 0;
        if (D_800618D0[0] == 0x600) {
            if (flags & 2) {
                flag = 1;
            } else {
                flag = 0;
            }
        }
        if (level_position.zone != NULL) {
            cur_header = (ZoneHeader *)((ZoneEntry *)level_position.zone)->items[0];
            flag = flags & 2;
            level_position.object_zone = zone;
            for (i = 0; i < cur_header->neighbor_count; i++) {
                neighbor = func_80015A98(&cur_header->neighbors[i]);
                if (zone_has_neighbor((ZoneHeader *)((ZoneEntry *)zone)->items[0], neighbor)) {
                    continue;
                }
                n_header = (ZoneHeader *)neighbor->items[0];
                if (n_header->display_flags & 1) {
                    func_8001D200(neighbor);
                    n_header->display_flags &= ~3;
                }
            }
        }
        if (flags & 1) {
            for (i = 0; i < 0x130; i++) {
                D_8005FF58[i] &= ~2;
                D_8005FF58[i] &= ~4;
            }
        }
        level_position.zone = zone;
        level_position.path = path;
        level_position.progress = progress;
        func_8001495C(cur_header != NULL ? &cur_header->load : NULL, 0);
        for (i = 0; i < header->load.entry_count; i++) {
            func_80015118(&header->load.entries[i], 0, 1);
        }
        for (i = 0; i < header->load.page_count; i++) {
            func_80014D00(header->load.pages[i], 0, 1, 0x6396347F);
        }
        if (flag) {
            func_80013748();
        }
        for (i = 0; i < header->neighbor_count; i++) {
            neighbor = func_80015A98(&header->neighbors[i]);
            neighbor_header = (ZoneHeader *)neighbor->items[0];
            if (!(neighbor_header->display_flags & 1)) {
                D_80061A5C[0] = 0;
                D_80061A64[0] = 0;
                D_80061A60[0] = 0x19000;
                neighbor_header->display_flags |= 3;
            }
            if (flag) {
                ((ZoneHeader *)neighbor->items[0])->display_flags |= 4;
            } else {
                ((ZoneHeader *)neighbor->items[0])->display_flags &= ~4;
            }
        }
        func_800260AC(header->gfx, flags);
    } else {
        level_position.zone = zone;
        level_position.path = path;
        level_position.progress = progress;
    }
camera:
    lvl_camera.rot_before = lvl_camera.rot;
    func_800296A8(level_position.path, -level_position.progress, &lvl_camera.trans);
    lvl_camera.rot_after = lvl_camera.rot;
done:
    D_8005C528.wordA98 = 0;
}

/* Update the zone colour transition state and graphics parameters. */
void func_800260AC(void *arg0, u32 flags)
{
    ZoneGfx *gfx = (ZoneGfx *)arg0;

    lvl_color.start_tick = engine_counter[0];
    lvl_color.prev = lvl_color.cur;
    lvl_color.target = gfx->color;
    D_80061904[0] = gfx->flags;
    if (!(flags & 4)) {
        func_800317DC(gfx->unk24);
    }
}
