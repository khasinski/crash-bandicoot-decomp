#include "common.h"

/* GCC_VERSION: 2.6.3 */

/* Initialise resource state on first use; visit object roots and clear flags on release. */

#include "gool.h"
#include "zone.h"

ZoneEntry *func_80015A98(u32 *);
extern void func_8001D200(void *);
extern s32 D_80061A5C;
extern s32 D_80061A60;
extern s32 D_80061A64;

s32 func_80025628(ZoneEntry *zone)
{
    s32 i;

    for (i = 0; i < ((ZoneHeader *)zone->items[0])->path_count; i++) {
        ((ZonePath *)zone->items[i + ((ZoneHeader *)zone->items[0])->path_index])->zone = (ResourceEntry *)zone;
    }
    for (i = 0; i < ((ZoneHeader *)zone->items[0])->entity_count; i++) {
        *(ZoneEntry **)zone->items[i + ((ZoneHeader *)zone->items[0])->path_index + ((ZoneHeader *)zone->items[0])->path_count] = zone;
    }
    return -0xFF;
}

s32 func_800256DC(ZoneEntry *zone)
{
    s32 i;

    for (i = 0; i < ((ResourceMapMetadata *)zone->items[0])->count; i++) {
        *(ZoneEntry **)zone->items[i + 2] = zone;
    }
    return -0xFF;
}

s32 func_80025730(ZoneEntry *zone, ZoneEntry *neighbor)
{
    ZoneHeader *header = (ZoneHeader *)zone->items[0];
    s32 i;

    for (i = 0; i < header->neighbor_count; i++) {
        if (func_80015A98(&header->neighbors[i]) == neighbor) {
            return 1;
        }
    }
    return 0;
}

void func_800257B4(ObjectView *object)
{
    u8 *resource = object->resource;
    if (!(*(u32 *)(resource + CRASH_OFFSETOF(GoolResourceState, flags2DC)) & 1)) {
        D_80061A5C = 0;
        D_80061A64 = 0;
        D_80061A60 = 0x19000;
        *(u32 *)(resource + CRASH_OFFSETOF(GoolResourceState, flags2DC)) |= 3;
    }
}

void func_80025804(ObjectView *object)
{
    u8 *resource = object->resource;
    if (*(u32 *)(resource + CRASH_OFFSETOF(GoolResourceState, flags2DC)) & 1) {
        func_8001D200(object);
        *(u32 *)(resource + CRASH_OFFSETOF(GoolResourceState, flags2DC)) &= ~3;
    }
}
