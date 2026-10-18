/* GCC_VERSION: 2.6.3 */
/* CC1_FLAGS: -O2 */
#include "common.h"
#include "gpu.h"

extern s32 D_80057868;

typedef struct WgeoHeader {
    s32 x;
    s32 y;
    s32 z;
    s32 unk0C;
    s32 unk10;
    s32 unk14;
    u32 tpage_count;
    s32 flags;
    u32 tpages[8];
} WgeoHeader;

typedef struct ZoneWorld {
    u32 eid;
    s32 trans[3];
    WgeoHeader *wgeo;
    void *item1;
    void *item2;
    void *polys;
    void *tpages[8];
} ZoneWorld;

typedef struct ZoneHeader9A2C {
    s32 world_count;
    ZoneWorld worlds[8];
} ZoneHeader9A2C;

void func_8001922C(ZoneHeader9A2C *arg0);

typedef struct ResourceItem {
    u8 pad00[0x10];
    void *item0;
    void *item1;
    void *item2;
} ResourceItem;

extern s32 D_80057864;
extern s16 D_80057804;

extern struct {
    s32 unk0;
    s32 level_id;
} *D_8005C53C;

extern s32 D_800618D4;

ResourceItem *func_80015A98(void *);
void func_8001A460(s32, s32);

void func_8001922C(ZoneHeader9A2C *arg0)
{
    s32 v[3];
    s32 i;
    u32 j;
    ResourceItem *entry;
    WgeoHeader *wgeo;
    s32 *trans;

    for (i = 0; i < arg0->world_count; i++) {
        entry = func_80015A98(&arg0->worlds[i].eid);
        wgeo = (WgeoHeader *)entry->item0;
        if (wgeo->flags == 1) {
            arg0->worlds[i].trans[0] = 0;
            arg0->worlds[i].trans[1] = 0;
            arg0->worlds[i].trans[2] = 0;
        } else {
            trans = (s32 *)(i * 64 + (s32)arg0);
            trans += 2;
            trans[0] = (D_80057804 * (v[0] = wgeo->x - (D_80057864 >> 8))
                      + D_80057806 * (v[1] = wgeo->y - (D_80057868 >> 8))
                      + D_80057808 * (v[2] = wgeo->z - (D_8005786C >> 8))) >> 12;
            trans[1] = (D_8005780A * v[0]
                      + D_8005780C * v[1]
                      + D_8005780E * v[2]) >> 12;
            trans[2] = (D_80057810 * v[0]
                      + D_80057812 * v[1]
                      + D_80057814 * v[2]) >> 12;
        }
        arg0->worlds[i].wgeo = wgeo;
        arg0->worlds[i].item1 = entry->item1;
        arg0->worlds[i].item2 = entry->item2;
        arg0->worlds[i].polys = wgeo + 1;
        for (j = 0; j < wgeo->tpage_count; j++) {
            arg0->worlds[i].tpages[j] = func_80015A98(&wgeo->tpages[j]);
        }
    }
    if (D_8005C53C->level_id == 0x19 && D_800618D4 == 0xF) {
        func_8001A460(D_800619B0, D_800619B8);
    }
}
