#ifndef CRASH_ZONE_H
#define CRASH_ZONE_H

#include "common.h"
#include "resource.h"

/* Link from a camera path to a path of the same or a neighbouring zone.
 * relation bit 0: the link leaves from the path start, bit 1: from its end.
 * goal bit 0: the link enters the other path at its start; bit 2 marks a
 * link that is only followed for 16 frames after a timed event. */
typedef struct ZoneNeighbor {
    u8 relation;
    u8 zone;
    u8 path;
    u8 goal;
} ZoneNeighbor;

/* Camera path item of a zone entry. Progress along it is length * 256.
 * A nonzero direction component tells which way the path runs. */
typedef struct ZonePath {
    u32 slst;
    ResourceEntry *zone;
    u32 neighbor_count;
    ZoneNeighbor neighbors[4];
    u8 entrance;
    u8 exit;
    u16 length;
    s16 cam_mode;
    s16 node_distance;
    s16 cam_zoom;
    u16 pad26[3];
    s16 direction_x;
    s16 direction_y;
    s16 direction_z;
} ZonePath;

/* First item of a zone entry. */
typedef struct ZoneHeader {
    u8 pad000[0x204];
    s32 path_index;
    u8 pad208[0xC];
    u32 neighbors[(0x2FC - 0x214) / 4];
    u32 flags;
} ZoneHeader;

typedef struct ZoneEntry {
    u8 pad00[0x10];
    void *items[1];
} ZoneEntry;

/* Current zone, a second zone pointer, the camera path and the progress
 * along that path. */
typedef struct LevelPosition {
    ResourceEntry *zone;
    ResourceEntry *object_zone;
    ZonePath *path;
    s32 progress;
} LevelPosition;

extern LevelPosition level_position __asm__("D_80057914");

#endif
