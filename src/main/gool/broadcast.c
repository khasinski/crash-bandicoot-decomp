/* GCC_VERSION: 2.6.3 */
/* GNU_AS_G: 4 */
#include "common.h"
#include "object_links.h"
#include "gool.h"
#include "zone.h"
#include "ns.h"

s32 GOOL_TraverseObjectTreePostorder(Node *, Visitor, void *);
s32 func_8001CDD0(Node *, s32);
s32 func_80024CC8(Node *, void *);

s32 func_800251B8(Node *arg0, Node *arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5)
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
                    if (GOOL_TraverseObjectTreePostorder(child, func_80024CC8, context) == -25) {
                        func_8001CDD0(node, 0);
                    }
                    child = next_child;
                } while (child != NULL);
            }
            if (func_80024CC8(node, context) == -25) {
                func_8001CDD0(arg1, 0);
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

s32 func_800252C0(GoolStackObj *obj, u32 arg1, s32 argc, u32 *argv)
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
void func_80017790(void);
ResourceEntry *func_80015118(void *, s32, s32);
void func_80015458(void *, s32);
void func_8002EABC(u32 *);
void func_80025A60(ZoneEntry *, void *, s32, s32);
void func_8002EC68(s32);
void func_8002EBB4(s32);

typedef struct LevelDesc {
    s32 unk0;
    s32 unk4;
    u32 eid;
    s32 path_idx;
} LevelDesc;

extern s32 D_80061A30[];

extern LevelDesc *D_8005C53C[];

s32 D_80056490 = 0;
s32 D_80056494 = 1;

extern s32 D_800566E8[];
extern s32 D_8006189C[];
extern s32 D_800618B0[];
extern u32 D_8005FF58[];
extern s32 D_800618D0[];

extern u32 D_800566B0[2];
extern u8 D_80057968[];
extern u32 D_80057970[];
extern u32 func_80034520[];
extern s32 D_80056400[];

s32 func_800253A0(void)
{
    s32 progress;
    s32 mode;
    ZoneEntry *zone;

    D_80061A30[0] = 0;
    if (*D_8005C538[0] != 0x6396347F) {
        D_800566E4 = 0;
        D_800566E8[0] = 0;
        D_8006189C[0] = 0xFFFF;
        D_800618B0[0] = 0xFFFF;
        BIOS_MemSet(D_8005FF58, 0, 0x4C0);
        progress = 0;
        GOOL_InitLevelSpawns(D_8005C53C[0]->unk4);
        mode = (D_8005C52C[0] == 0x11 || D_8005C52C[0] == 0x1E) ? 2 : 1;
        func_80017790();
        if (D_8005C52C[0] == 0x19 && D_800618D0[0] == 0x200 && D_80056494 == 0) {
            D_8005C53C[0]->eid = func_80012660(D_80056498);
        }
        if (D_80056490 == 1) {
            D_8005C53C[0]->eid = D_80057998[0];
            D_80056490 = 0;
            D_8005C53C[0]->path_idx = D_8005799C[0];
            progress = D_800579A0[0];
        }
        zone = (ZoneEntry *)func_80015118(&D_8005C53C[0]->eid, 1, mode);
        D_800566B0[0] = 0x6396347F;
        level_position.zone = NULL;
        level_position.path = NULL;
        level_position.progress = 0;
        D_80057968[0] = 0;
        D_80057969[0] = 0;
        D_8005796A[0] = 0;
        D_8005796B[0] = 0;
        D_80057970[0] = func_80034520[0];
        if (D_800618D0[0] == 0x600) {
            func_8002EABC(D_800566B0);
        }
        func_80025A60(zone, zone->items[D_8005C53C[0]->path_idx + ((ZoneHeader *)zone->items[0])->path_index], progress, 0);
        func_80015458(&D_8005C53C[0]->eid, 1);
    } else {
        D_8005C53C[0]->unk0 = 0;
    }
    if (D_80056400[0] == 0) {
        func_8002EC68(1);
        func_8002EBB4(1);
    }
    D_80056494 = 0;
    return -0xFF;
}
