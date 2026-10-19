#include "common.h"

/* GCC_VERSION: 2.6.3 */

/* Initialise resource state on first use; visit object roots and clear flags on release. */

#include "gool.h"
#include "zone.h"

ZoneEntry *Ns_Lookup(u32 *);
void Gool_ZoneObjectsTerminate(void *);
extern s32 g_doctor_cortex_obj;
extern s32 D_80061A64;

s32 Level_ZdatOnLoad(ZoneEntry *zone)
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

s32 Level_MdatOnLoad(ZoneEntry *zone)
{
    s32 i;

    for (i = 0; i < ((ResourceMapMetadata *)zone->items[0])->count; i++) {
        *(ZoneEntry **)zone->items[i + 2] = zone;
    }
    return -0xFF;
}

s32 Level_ZdatOnLoad2(ZoneEntry *zone, ZoneEntry *neighbor)
{
    ZoneHeader *header = (ZoneHeader *)zone->items[0];
    s32 i;

    for (i = 0; i < header->neighbor_count; i++) {
        if (Ns_Lookup(&header->neighbors[i]) == neighbor) {
            return 1;
        }
    }
    return 0;
}

void Level_MdatOnLoad2(ObjectView *object)
{
    u8 *resource = object->resource;
    if (!(*(u32 *)(resource + CRASH_OFFSETOF(GoolResourceState, flags2DC)) & 1)) {
        g_doctor_cortex_obj = 0;
        D_80061A64 = 0;
        D_80061A60[0] = 0x19000;
        *(u32 *)(resource + CRASH_OFFSETOF(GoolResourceState, flags2DC)) |= 3;
    }
}

void Zone_TerminateObjects(ObjectView *object)
{
    u8 *resource = object->resource;
    if (*(u32 *)(resource + CRASH_OFFSETOF(GoolResourceState, flags2DC)) & 1) {
        Gool_ZoneObjectsTerminate(object);
        *(u32 *)(resource + CRASH_OFFSETOF(GoolResourceState, flags2DC)) &= ~3;
    }
}
