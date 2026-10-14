/* GCC_VERSION: 2.6.3 */
#include "common.h"

typedef struct ZqVec {
    s32 x, y, z;
} ZqVec;

typedef struct ZqRect {
    s32 x, y, z;
    s32 w, h, d;
} ZqRect;

/* Zone dimensions item: bounds, then the octree header. */
typedef struct ZqZoneRect {
    u8 pad00[0x1E];
    s16 max_depth_x;
    s16 max_depth_y;
    s16 max_depth_z;
} ZqZoneRect;


INCLUDE_ASM("asm/USA/main/nonmatchings/level/zone_query", func_80026B80);

INCLUDE_ASM("asm/USA/main/nonmatchings/level/zone_query", func_80026C04);

INCLUDE_ASM("asm/USA/main/nonmatchings/level/zone_query", func_80026CA8);

INCLUDE_ASM("asm/USA/main/nonmatchings/level/zone_query", func_80026D40);

INCLUDE_ASM("asm/USA/main/nonmatchings/level/zone_query", func_80026DD4);

/* ZoneFindNode: follow the ray va + t*vb through the zone octree below node,
 * which covers rect. A leaf returns its node and moves va onto the nearest
 * face it crossed (reversing that component of vb); an empty node advances
 * va just past its far side. Recurses into the children that contain va. */
s32 func_80026FF0(ZqZoneRect *zone, u16 node, ZqRect *rect, ZqVec *va, ZqVec *vb, s32 level)
{
    u16 *children;
    s32 t, tn, axis, i, j, k, idx, res;

    /* Non-leaf nodes are offsets of their child arrays in the zone item;
     * leaves (odd) and empty nodes (0) are returned as they are. */
    if (!(node & 1) && node) {
        children = (u16 *)((u8 *)zone + node);
    } else {
        children = (u16 *)(u32)node;
    }
    if ((node & 1) || !node) {
        ZqVec corner;

        t = 0x7FFFFFFF;
        if (!children) {
            if (vb->x > 0) {
                corner.x = rect->x + rect->w;
            } else {
                corner.x = rect->x;
            }
            if (vb->y > 0) {
                corner.y = rect->y + rect->h;
            } else {
                corner.y = rect->y;
            }
            if (vb->z > 0) {
                corner.z = rect->z + rect->d;
            } else {
                corner.z = rect->z;
            }
            if (vb->x) {
                tn = ((corner.x - va->x) << 8) / vb->x;
                if (tn < t) {
                    t = tn;
                }
            }
            if (vb->y) {
                tn = ((corner.y - va->y) << 8) / vb->y;
                if (tn < t) {
                    t = tn;
                }
            }
            if (vb->z) {
                tn = ((corner.z - va->z) << 8) / vb->z;
                if (tn < t) {
                    t = tn;
                }
            }
            t += 0x100;
            va->x += (t * vb->x) >> 8;
            va->y += (t * vb->y) >> 8;
            va->z += (t * vb->z) >> 8;
        } else {
            if (vb->x < 0) {
                corner.x = rect->x + rect->w;
            } else {
                corner.x = rect->x;
            }
            if (vb->y < 0) {
                corner.y = rect->y + rect->h;
            } else {
                corner.y = rect->y;
            }
            if (vb->z < 0) {
                corner.z = rect->z + rect->d;
            } else {
                corner.z = rect->z;
            }
            t = 0x80000000;
            if (vb->x) {
                tn = ((corner.x - (va->x - vb->x)) << 8) / vb->x;
                if (tn > t) {
                    t = tn;
                    axis = 0;
                }
            }
            if (vb->z) {
                tn = ((corner.z - (va->z - vb->z)) << 8) / vb->z;
                if (tn > t || __builtin_abs(vb->x) < __builtin_abs(vb->z)) {
                    t = tn;
                    axis = 2;
                }
            }
            if (vb->y) {
                tn = ((corner.y - (va->y - vb->y)) << 8) / vb->y;
                if (tn > t || (axis == 0 && __builtin_abs(vb->x) < __builtin_abs(vb->y))
                    || (axis == 2 && __builtin_abs(vb->z) < __builtin_abs(vb->y))) {
                    t = tn;
                    axis = 1;
                }
            }
            switch (axis) {
            case 0:
                vb->x = -vb->x;
                va->x = corner.x;
                break;
            case 1:
                vb->y = -vb->y;
                va->y = corner.y;
                break;
            case 2:
                vb->z = -vb->z;
                va->z = corner.z;
                break;
            }
        }
        return (s32)children;
    } else {
        s32 split[3];
        ZqRect child;

        split[0] = level < zone->max_depth_x;
        if (split[0]) {
            child.w = rect->w / 2;
        } else {
            child.w = rect->w;
        }
        split[1] = level < zone->max_depth_y;
        if (split[1]) {
            child.h = rect->h / 2;
        } else {
            child.h = rect->h;
        }
        split[2] = level < zone->max_depth_z;
        if (split[2]) {
            child.d = rect->d / 2;
        } else {
            child.d = rect->d;
        }
        idx = 0;
        for (i = 0; i < (split[0] ? 2 : 1); i++) {
            for (j = 0; j < (split[1] ? 2 : 1); j++) {
                for (k = 0; k < (split[2] ? 2 : 1);) {
                    child.x = rect->x + (i ? child.w : 0);
                    child.y = rect->y + (j ? child.h : 0);
                    child.z = rect->z + (k ? child.d : 0);
                    k++;
                    if (child.x < va->x && child.y < va->y && child.z < va->z
                        && child.x + child.w >= va->x && child.y + child.h >= va->y
                        && child.z + child.d >= va->z) {
                        res = func_80026FF0(zone, children[idx], &child, va, vb, level + 1);
                        if (res) {
                            return res;
                        }
                    }
                    idx++;
                }
            }
        }
        /* No return here: retail leaves whatever is in v0 (0 on every
         * path that gets here). */
    }
}

INCLUDE_ASM("asm/USA/main/nonmatchings/level/zone_query", func_800277EC);
