/* GCC_VERSION: 2.6.3 */
/* GNU_AS_G: 4 */
#include "common.h"
extern s32 g_draw_stamp;
extern s32 g_view_proj;
#include "zone.h"

typedef struct {
    s16 v[3][3];
    s16 b[3];
    s16 c[3][3];
    s16 a[3];
} LightMat;

typedef struct LevelHeader {
    s32 unk0;
    s32 level_id;
} LevelHeader;

extern LevelHeader *g_ns_page_pool[];

typedef struct SaveVec {
    s32 x, y, z;
} SaveVec;

typedef struct SaveTransform {
    SaveVec trans;
    SaveVec rot;
    SaveVec scale;
} SaveTransform;

typedef struct SaveObj {
    u8 pad00[0x28];
    ResourceEntry *entry;
    u8 pad2C[0x4C];
    struct SaveObj *unk78;
    u8 pad7C[4];
    SaveTransform transform;
    s32 unkA4;
    s32 unkA8;
    s32 unkAC;
    s32 unkB0;
    s32 unkB4;
    u8 padB8[0x10];
    u32 status_a;
    u32 status_b;
    u8 padD0[0x54];
    s32 unk124;
    u8 pad128[8];
    s32 unk130;
} SaveObj;

typedef struct LevelSave {
    SaveTransform transform;
    u32 zone_eid;
    s32 path_idx;
    s32 progress;
    s32 level_id;
    s32 flag34;
    u32 flags38[0x130];
    s32 unk4F8;
} LevelSave;

extern SaveObj *gp_crash_obj[2];
extern u32 D_800619A0[];
extern SaveVec D_80061A24;
s32 D_800564A0 = 0;
extern s32 gp_pbak_frame_idx;

extern s32 g_view_proj;
extern struct { s32 v, pad; } D_800566E8;
extern u32 g_fade_counter;
typedef struct { s32 v, pad; } WordView;
extern WordView D_800618A0;
extern WordView D_80061A3C;

void Gool_SendToColliders(void *, s32, s32, s32, s32);
ZoneEntry *Ns_Lookup(u32 *);
void Gool_ZoneObjectsTerminate(ZoneEntry *);
void Ns_ZoneUnload(ZoneLoadList *, s32);
void SetGeomScreen(s32);
ResourceEntry *Ns_Open(void *, s32, s32);
void Level_Update(ResourceEntry *, ZonePath *, s32, u32);
void Ns_Close(void *, s32);
SaveObj *GOOL_CreateObject(void *, s32, s32, s32, s32, s32);
void Level_InitMisc(s32);

void Level_SaveState(SaveObj *obj, LevelSave *save, s32 flag)
{
    ZoneHeader *header;
    s32 i;

    if (((ZoneHeader *)((ZoneEntry *)level_position.zone)->items[0])->flags & 0x2000) {
        return;
    }
    save->flag34 = flag;
    save->transform = (*(SaveObj **)&gp_crash_obj)->transform;
    if (!(obj->status_b & 0x200)) {
        save->transform.trans = obj->transform.trans;
    }
    if (D_800619A0[0] != -1 && D_800619A0[0] != 0) {
        save->transform.trans = D_80061A24;
    }
    save->transform.rot.x = 0;
    save->transform.rot.y = 0;
    save->transform.rot.z = 0;
    save->zone_eid = level_position.zone->id;
    save->progress = level_position.progress;
    save->level_id = g_ns_page_pool[0]->level_id;
    for (i = 0; i < ((ZoneHeader *)((ZoneEntry *)level_position.zone)->items[0])->path_count; i++) {
        header = (ZoneHeader *)((ZoneEntry *)level_position.zone)->items[0];
        if ((void *)level_position.path == ((ZoneEntry *)level_position.zone)->items[i + header->path_index]) {
            save->path_idx = i;
            break;
        }
    }
    save->unk4F8 = g_death_count[0];
    for (i = 0; i < sizeof(g_spawns) / sizeof(u32); i++) {
        save->flags38[i] = g_spawns[i];
    }
}

void Level_Restart(LevelSave *save)
{
    u32 zone_eid;
    ZoneHeader *header, *n_header;
    ZoneEntry *neighbor, *zone;
    SaveObj *player;
    s32 i;

    D_8006197C[0] = 0;
    if (save->level_id != g_ns_page_pool[0]->level_id) {
        gp_pbak_frame_idx = -2;
        D_800564A0 = 1;
        return;
    }
    Gool_SendToColliders(NULL, 0x1300, 0, 0, 0);
    if (level_position.zone != NULL) {
        header = (ZoneHeader *)((ZoneEntry *)level_position.zone)->items[0];
        level_position.object_zone = (ResourceEntry *)-1;
        for (i = 0; i < header->neighbor_count; i++) {
            neighbor = Ns_Lookup(&header->neighbors[i]);
            n_header = (ZoneHeader *)neighbor->items[0];
            if (n_header->display_flags & 1) {
                Gool_ZoneObjectsTerminate(neighbor);
                n_header->display_flags &= ~3;
            }
        }
        Ns_ZoneUnload(&header->load, 0);
    }
    level_position.zone = NULL;
    SetGeomScreen(g_view_proj);
    if (D_800564A0) {
        for (i = 0; i < sizeof(g_spawns) / sizeof(u32); i++) {
            g_spawns[i] = save->flags38[i];
        }
        if (D_800619A0[0] != -1) {
            g_spawns[D_800619A0[0] >> 8] &= ~2;
            g_spawns[D_800619A0[0] >> 8] |= 8;
        }
        for (i = 0; i < 0x130; i++) {
            g_spawns[i] &= ~1;
        }
    }
    zone_eid = save->zone_eid;
    zone = (ZoneEntry *)Ns_Open(&zone_eid, 1, 1);
    Level_Update((ResourceEntry *)zone, zone->items[save->path_idx + ((ZoneHeader *)zone->items[0])->path_index], save->progress, !D_800564A0);
    Ns_Close(&zone_eid, 1);
    if (gp_crash_obj[0] == NULL) {
        GOOL_CreateObject(D_80060DE8, 0, 0, 0, 0, 1);
    }
    gp_crash_obj[0]->transform = save->transform;
    player = gp_crash_obj[0];
    player->entry = level_position.zone;
    player->unk130 = 0;
    player->unkA4 = 0;
    player->unkA8 = 0;
    player->unkAC = 0;
    player->unk124 = 0;
    player->status_a = player->status_a;
    player->unkB4 = player->transform.rot.y;
    if (player->unk78 != NULL) {
        player->unk78->unk78 = NULL;
        player->unk78 = NULL;
    }
    g_draw_stamp = 0;
    D_80061894 = 0;
    D_800566E8.v = 0;
    g_fade_counter = 0xFFFF;
    if (!D_800564A0) {
        D_800618A0.v += 0x100;
        if (save->flag34) {
            D_80061A3C.v = 0;
        } else {
            D_80061A3C.v += 0x100;
        }
    }
    Level_InitMisc(0);
    if (D_800564A0) {
        g_death_count[0] = save->unk4F8;
        D_800564A0 = 0;
        if (D_800619A0[0] != -1) {
            g_death_count[0] -= 0x100;
        }
    }
}
