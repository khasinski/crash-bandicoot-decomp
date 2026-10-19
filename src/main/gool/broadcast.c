/* GCC_VERSION: 2.6.3 */
/* GNU_AS_G: 4 */
#include "common.h"
#include "object_links.h"
#include "gool.h"
#include "zone.h"
#include "ns.h"

s32 GOOL_TraverseObjectTreePostorder(Node *, Visitor, void *);
s32 Gool_ObjectKill(Node *, s32);
s32 Gool_SendIfColliding(Node *, void *);

s32 Gool_SendToColliders2(Node *arg0, Node *arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5)
{
    struct { Node *sender; s32 word04, word08, word0C, word10, word14; } message;
    void *context = &message;
    Node *node, *next, *child, *next_child;

    message.sender = arg0;
    message.word04 = arg2;
    message.word0C = arg3;
    message.word10 = 0;
    message.word08 = arg4;
    message.word14 = arg5;
    if (arg1->kind == 2) {
        node = arg1->word04;
    } else {
        node = arg1->children;
    }
    if (node != NULL) {
        do {
            child = node->children;
            next = node->next;
            if (child != NULL) {
                do {
                    next_child = child->next;
                    if (GOOL_TraverseObjectTreePostorder(child, Gool_SendIfColliding, context) == -25) {
                        Gool_ObjectKill(node, 0);
                    }
                    child = next_child;
                } while (child != NULL);
            }
            if (Gool_SendIfColliding(node, context) == -25) {
                Gool_ObjectKill(arg1, 0);
            }
            node = next;
        } while (node != NULL);
    }
    return -0xFF;
}

typedef struct GoolScriptHeader {
    u8 pad00[0x14];
    u8 *code;
} GoolScriptHeader;

typedef struct GoolStackObj {
    u8 pad00[0x20];
    GoolScriptHeader *script;
    u8 pad24[0xDC - 0x24];
    u32 *sp;
    u8 *pc;
    u32 *fp;
} GoolStackObj;

s32 GOOL_InterpretObject(GoolStackObj *, s32, s32);

s32 Gool_ObjectInterrupt(GoolStackObj *obj, u32 arg1, s32 argc, u32 *argv)
{
    s32 i;
    u32 *sp;
    u32 *old_fp;
    u32 *new_sp;
    u32 *new_fp;

    for (i = 0; i < argc; i++) {
        *obj->sp++ = *argv++;
    }
    sp = obj->sp;
    old_fp = obj->fp;
    obj->fp = sp;
    *obj->sp++ = 0xFFFF;
    *obj->sp++ = (u32)obj->pc;
    *obj->sp++ = ((u32)(new_sp = sp - argc - 24) - (u32)obj) | (((u32)(new_fp = old_fp - 24) - (u32)obj) << 16);
    obj->pc = ((arg1 & 0x7FFF) << 2) + obj->script->code;
    return GOOL_InterpretObject(obj, 3, 0);
}

void BIOS_MemSet(void *, s32, s32);
void GOOL_InitLevelSpawns(s32);
void Gfx_InitMatrices(void);
ResourceEntry *Ns_Open(void *, s32, s32);
void Ns_Close(void *, s32);
void Pbak_Choose(u32 *);
void Level_Update(ZoneEntry *, void *, s32, s32);
void Shader_ParamsUpdate(s32);
void Shader_ParamsUpdateRipple(s32);

typedef struct LevelDesc {
    s32 unk0;
    s32 unk4;
    u32 eid;
    s32 path_idx;
} LevelDesc;


extern LevelDesc *g_ns_page_pool[];

s32 gp_cur_zone = 0;
s32 gp_cur_path = 1;

extern s32 D_800566E8[];
extern s32 g_fade_counter[];
extern s32 g_cur_lid_ro[];

extern u32 D_800566B0[2];
extern u8 D_80057968[];
extern u32 D_80057970[];
extern u32 engine_counter[];
extern s32 gp_next_lid[];

s32 Level_LdatInit(void)
{
    s32 progress;
    s32 mode;
    ZoneEntry *zone;

    D_80061A30 = 0;
    if (*D_8005C538[0] != 0x6396347F) {
        D_800566E4 = 0;
        D_800566E8[0] = 0;
        g_fade_counter[0] = 0xFFFF;
        g_cur_lid_ro[0] = 0xFFFF;
        BIOS_MemSet(g_spawns, 0, 0x4C0);
        progress = 0;
        GOOL_InitLevelSpawns(g_ns_page_pool[0]->unk4);
        mode = (D_8005C52C[0] == 0x11 || D_8005C52C[0] == 0x1E) ? 2 : 1;
        Gfx_InitMatrices();
        if (D_8005C52C[0] == 0x19 && D_800618D0 == 0x200 && gp_cur_path == 0) {
            g_ns_page_pool[0]->eid = Ns_StringToEID(gp_cur_progress);
        }
        if (gp_cur_zone == 1) {
            g_ns_page_pool[0]->eid = D_80057998[0];
            gp_cur_zone = 0;
            g_ns_page_pool[0]->path_idx = D_8005799C[0];
            progress = D_800579A0[0];
        }
        zone = (ZoneEntry *)Ns_Open(&g_ns_page_pool[0]->eid, 1, mode);
        D_800566B0[0] = 0x6396347F;
        level_position.zone = NULL;
        level_position.path = NULL;
        level_position.progress = 0;
        D_80057968[0] = 0;
        D_80057969[0] = 0;
        D_8005796A[0] = 0;
        D_8005796B[0] = 0;
        D_80057970[0] = engine_counter[0];
        if (D_800618D0 == 0x600) {
            Pbak_Choose(D_800566B0);
        }
        Level_Update(zone, zone->items[g_ns_page_pool[0]->path_idx + ((ZoneHeader *)zone->items[0])->path_index], progress, 0);
        Ns_Close(&g_ns_page_pool[0]->eid, 1);
    } else {
        g_ns_page_pool[0]->unk0 = 0;
    }
    if (gp_next_lid[0] == 0) {
        Shader_ParamsUpdate(1);
        Shader_ParamsUpdateRipple(1);
    }
    gp_cur_path = 0;
    return -0xFF;
}
