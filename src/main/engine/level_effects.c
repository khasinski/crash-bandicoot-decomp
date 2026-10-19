/* GCC_VERSION: 2.6.3 */
#include "common.h"
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

extern SaveObj *gp_crash_obj;

extern s32 gp_next_lid;
extern SaveObj *D_800618CC;


s32 D_800564C8 = -1;
s32 gp_octree_root = 0;

static s32 D_800565EC;
static s32 D_800565F0;
static s32 D_800565F4;
static s32 D_800565F8;
static s32 D_800565FC;
static s32 D_80056600;
static s32 D_80056604;
static s32 D_80056608;
static s32 D_8005660C;
static s32 D_80056610;
static s32 D_80056614;
static s32 D_80056618;
static s32 D_8005661C;
static s32 D_80056620;
static s32 D_80056624;
static s32 D_80056628;
static s32 D_8005662C;
static s32 D_80056630;
static s32 D_80056634[2];

void Gfx_TransformWorldsRipple(s32);
s32 Math_Randb(s32);
void Audio_Control(s32, s32, s32 *, s32);
void Audio_VoiceCreate(s32, s32 *, s32);

void Shader_ParamsUpdateRipple(s32 arg0)
{
    switch (g_ns_page_pool[0]->level_id) {
    case 0xF:
    case 0x18:
        D_80056474 = 0xA;
        D_80056478 = 0x7F;
        break;
    case 0x17:
        D_80056474 = 0xA;
        D_80056478 = 0x7F;
        break;
    case 0x24:
    case 0x33:
        D_80056474 = 4;
        D_80056478 = 0x7F;
        break;
    default:
        D_80056474 = 1;
        D_80056478 = 0x17;
        break;
    }
    if (arg0 != 0) {
        Gfx_TransformWorldsRipple(0);
    }
}

void Shader_ParamsUpdate(s32 arg0)
{
    u8 name[8];
    s32 sp18;
    s32 sp1C;
    s32 v1, v2, v3;

    if (arg0 != 0) {
        gp_ripple_amp = 0x800;
        gp_ripple_freq = 0xFF;
        D_80056454 = 0xFF;
        D_80056458 = 0xFF;
        gp_lightning_state = 0x800;
        gp_fade_step = 0;
        D_80056444 = 0;
        D_80056448 = 0;
        gp_octree_root = 0;
        D_800564C8 = -1;
        switch (g_ns_page_pool[0]->level_id) {
        case 0x21:
            gp_ripple_amp = 0;
            gp_ripple_freq = 0xC8;
            D_80056454 = 0x50;
            D_80056458 = 0;
            break;
        case 0x20:
        case 0x23:
            gp_ripple_amp = 0;
            gp_lightning_state = 0x640;
            D_80056600 = 0xA5;
            D_80056604 = 0x5A;
            D_80056608 = 0x64;
            D_8005660C = 0xFF;
            D_80056610 = 0x4B;
            D_80056614 = 0;
            D_800565F4 = 0xA5;
            D_800565F8 = 0x5A;
            D_800565FC = 0x64;
            break;
        case 5:
            gp_ripple_amp = 0;
            gp_ripple_freq = 0xEE;
            D_80056454 = 0xEE;
            D_80056458 = 0x3C;
            break;
        case 0x13:
            gp_ripple_amp = 0;
            gp_ripple_freq = 0;
            D_80056454 = 0xF0;
            D_80056458 = 0xFF;
            break;
        case 0xA:
        case 0x1C:
        case 0x1D:
            gp_ripple_amp = 0;
            gp_ripple_freq = 0xFF;
            D_80056454 = 0x64;
            D_80056458 = 0;
            break;
        case 3:
        case 6:
        case 7:
        case 0x37:
            gp_ripple_amp = 0;
            gp_ripple_freq = 0xFF;
            D_80056454 = 0x2B;
            D_80056458 = 0xB;
            break;
        case 0x28:
        case 0x2A:
            D_80056618 = 0;
            gp_dark_cone_rot = 0;
            D_80056464 = 0xA;
            D_80056624 = 0xFFF;
            D_80056630 = 0x7D0;
            D_8005646C = -0x36B0;
            break;
        }
    } else {
        switch (g_ns_page_pool[0]->level_id) {
        case 0x28:
        case 0x2A:
            if ((v1 = (s32)D_800618CC) != 0) {
                D_800566D4 = ((SaveObj *)v1)->transform.trans.x;
                D_800566D8 = ((SaveObj *)v1)->transform.trans.y;
                D_800566DC = ((SaveObj *)v1)->transform.trans.z;
            } else {
                D_800566D4 = gp_crash_obj->transform.trans.x;
                D_800566D8 = gp_crash_obj->transform.trans.y;
                D_800566DC = gp_crash_obj->transform.trans.z;
            }
            v1 = g_pause_obj;
            if (v1 != 0) {
                if (v1 != D_80056618) {
                    D_8005661C = -0x1F40;
                    D_80056620 = -0x1F4;
                    D_80056628 = 0x4B;
                    D_8005662C = -0x4B;
                }
            } else {
                if (D_80056618 != 0) {
                    D_8005661C = 0xFFF;
                    D_80056620 = 0x64;
                    D_80056628 = 0x7D0;
                    D_8005662C = 0x14;
                }
            }
            D_80056618 = v1;
            if (D_80056624 != D_8005661C) {
                if ((D_80056624 < D_8005661C && D_80056624 + D_80056620 >= D_8005661C) ||
                    (D_80056624 > D_8005661C && D_80056624 + D_80056620 <= D_8005661C)) {
                    D_80056620 = 0;
                    D_80056624 = D_8005661C;
                } else {
                    D_80056624 += D_80056620;
                }
            }
            if (D_80056630 != D_80056628) {
                if ((D_80056630 < D_80056628 && D_80056630 + D_8005662C >= D_80056628) ||
                    (D_80056630 > D_80056628 && D_80056630 + D_8005662C <= D_80056628)) {
                    D_8005662C = 0;
                    D_80056630 = D_80056628;
                } else {
                    D_80056630 += D_8005662C;
                }
            }
            D_80056468 = D_80056624;
            D_80056470 = D_80056630;
            break;
        case 0x21:
            switch (gp_octree_root) {
            case 0:
                D_800565EC = Math_Randb(1000);
                D_800565F0 = (D_800565EC - gp_lightning_state) / 4;
                gp_lightning_state += D_800565F0;
                break;
            case 1:
            case 2:
            case 3:
                gp_lightning_state += D_800565F0;
                break;
            }
            gp_octree_root = ++gp_octree_root % 4;
            break;
        case 5:
        case 0xA:
        case 0x1C:
        case 0x1D:
            switch (gp_octree_root) {
            case 0:
                D_800565EC = Math_Randb(0x5DC);
                gp_lightning_state += (D_800565EC - gp_lightning_state) / 2;
                break;
            case 1:
                gp_lightning_state = D_800565EC;
                break;
            }
            gp_octree_root = (gp_octree_root + 1) % 2;
            break;
        case 0x20:
        case 0x23:
            switch (gp_octree_root) {
            case 0:
                D_800565EC = Math_Randb(100);
                D_800565F4 = D_80056600 + (D_8005660C - D_80056600) * D_800565EC / 100;
                D_800565F8 = D_80056604 + (D_80056610 - D_80056604) * D_800565EC / 100;
                D_800565FC = D_80056608 + (D_80056614 - D_80056608) * D_800565EC / 100;
                gp_ripple_freq += (D_800565F4 - gp_ripple_freq) / 2;
                D_80056454 += (D_800565F8 - D_80056454) / 2;
                D_80056458 += (D_800565FC - D_80056458) / 2;
                break;
            case 1:
                gp_ripple_freq = D_800565F4;
                D_80056454 = D_800565F8;
                D_80056458 = D_800565FC;
                break;
            }
            gp_octree_root = (gp_octree_root + 1) % 2;
            break;
        case 3:
        case 6:
        case 7:
        case 0x37:
            if (D_80052D74[gp_octree_root] == -1) {
                gp_octree_root = 0;
            }
            gp_lightning_state = D_80052D74[gp_octree_root++];
            break;
        case 0x13:
            if (D_80052D74[gp_octree_root] == -1) {
                gp_octree_root = 0;
            }
            gp_lightning_state = D_80052D74[gp_octree_root++] >> 1;
            break;
        case 0x1B:
        case 0x22:
        case 0x2E:
            if (D_800564C8 != -1) {
                v2 = D_80053054[D_800564C8][gp_octree_root];
                if (v2 == -1) {
                    *(volatile s32 *)&gp_ripple_amp = 0;
                    gp_lightning_state = 0;
                    D_800564C8 = -1;
                } else {
                    gp_ripple_amp = v2;
                    gp_lightning_state = D_80053054[D_800564C8][gp_octree_root++];
                }
            } else {
                gp_ripple_amp = 0;
                gp_lightning_state = 0;
                if (Math_Randb(1000) < 0x19) {
                    if (g_ns_page_pool[0]->level_id == 0x22 || g_ns_page_pool[0]->level_id == 0x2E) {
                        switch (Math_Randb(3)) {
                        case 0:
                            D_800564C8 = 5;
                            break;
                        case 1:
                            D_800564C8 = 4;
                            break;
                        case 2:
                            D_800564C8 = Math_Randb(4);
                            break;
                        }
                    } else {
                        D_800564C8 = Math_Randb(6);
                    }
                    gp_octree_root = 0;
                    if (gp_next_lid == 0 &&
                        (g_ns_page_pool[0]->level_id == 0x1B || g_ns_page_pool[0]->level_id == 0x22 || g_ns_page_pool[0]->level_id == 0x2E) &&
                        (v3 = frame_counter) - D_80056634[1] > 0x1800) {
                        __builtin_memcpy(name, D_800564D0, 6);
                        for (sp18 = 0; sp18 < 1; sp18++) {
                            D_80056634[sp18 + 1] = D_80056634[sp18];
                        }
                        D_80056634[0] = v3;
                        name[2] += Math_Randb(3);
                        sp1C = Ns_StringToEID(name);
                        sp18 = (Math_Randb(0x4CC) + 0xD99) >> 3;
                        Audio_Control(0, 1, &sp18, 0);
                        sp18 = Math_Randb(0xF) + 1;
                        Audio_Control(0, 7, &sp18, 0);
                        sp18 = Math_Randb(0x14) + 0x14;
                        if (Math_Randb(100) >= 0x15) {
                            sp18 += Math_Randb(0x32);
                        }
                        Audio_VoiceCreate(0, &sp1C, sp18 * 0x3FFF / 100);
                    }
                }
            }
            break;
        }
    }
}
