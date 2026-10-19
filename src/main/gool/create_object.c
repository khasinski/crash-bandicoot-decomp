/* GCC_VERSION: 2.6.3 */
/* GNU_AS_G: 8 */
#include "common.h"

typedef struct GoolVectors {
    s32 trans[3];
    s32 rot[3];
    s32 scale[3];
} GoolVectors;

typedef struct GoolCodeHeader {
    s32 unk00;
    s32 unk04;
    s32 unk08;
    s32 unk0C;
    s32 unk10;
} GoolCodeHeader;

typedef struct GoolExecutable {
    u8 pad00[0x10];
    GoolCodeHeader *header;
    u8 *code;
    u8 *data;
    u16 *states;
    void *unk20;
    u32 *anims;
} GoolExecutable;

typedef struct GoolDefaults {
    u8 bytes[0x2A];
    u16 field2A, field2C, field2E;
} GoolDefaults;

typedef struct ResourceEntry {
    u8 pad00[0x10];
    u8 *data;
} ResourceEntry;

typedef struct GoolObj {
    s32 kind;
    s32 unk04;
    u8 pad08[0x18];
    GoolExecutable *exec;
    s32 unk24;
    ResourceEntry *zone;
    s32 unk2C;
    GoolDefaults defaults;
    struct GoolObj *self;
    struct GoolObj *parent;
    struct GoolObj *next;
    struct GoolObj *children;
    s32 unk70;
    void *player;
    s32 unk78;
    s32 unk7C;
    GoolVectors vectors;
    s32 unkA4;
    s32 unkA8;
    s32 unkAC;
    s32 unkB0;
    s32 unkB4;
    s32 unkB8;
    s32 unkBC;
    s32 unkC0;
    s32 unkC4;
    u32 status_a;
    u32 status_b;
    u32 status_c;
    s32 subtype;
    s32 pid_flags;
    u32 *sp;
    u32 *pc;
    u32 *fp;
    u32 *unkE8;
    u32 *unkEC;
    s32 unkF0;
    s32 unkF4;
    s32 unkF8;
    s32 unkFC;
    s32 unk100;
    s32 unk104;
    void *anim_seq;
    s32 anim_frame;
    void *entity;
    s32 path_progress;
    s32 path_length;
    s32 floor_y;
    u32 state_flags;
    s32 speed;
    s32 invincibility_state;
    s32 invincibility_time;
    s32 floor_time;
    s32 floor_vel_y;
    s32 cam_zoom;
    s32 event;
    s32 cam_rot_x;
    s32 ang_vel_x;
    s32 unk148;
    s32 voice_id;
    s32 unk150;
    s32 unk154;
    s32 node_id;
} GoolObj;

typedef struct NsdTable {
    u8 pad00[0x14];
    s32 items[1];
} NsdTable;

extern NsdTable *g_ns_page_pool[];
extern GoolObj *g_player[];
extern ResourceEntry *g_pads[];
extern GoolObj g_gool_obj_list_3;
GoolExecutable *Ns_Open(s32 *, s32, s32);
s32 GOOL_ChangeObjectState(GoolObj *, u32, s32 *, s32);

extern GoolObj *gp_crash_obj;

extern GoolObj g_gool_obj_list_7;
void Gool_ExecStateCode(GoolObj *, GoolObj *, s32, s32, void *);
void Audio_VoiceFree(GoolObj *);

#define NODE_CHILDREN(n) ((n)->kind == 2 ? (GoolObj *)(n)->unk04 : (n)->children)
#define NODE_CHILDREN_PTR(n) ((n)->kind == 2 ? (GoolObj **)&(n)->unk04 : &(n)->children)

static __inline__ s32 Gool_RemoveLevelSpawn(GoolObj *node, GoolObj *new_parent)
{
    GoolObj *parent = node->parent;
    GoolObj *prev;

    if (parent != NULL) {
        prev = NODE_CHILDREN(parent);
        if (prev == node) {
            *NODE_CHILDREN_PTR(parent) = node->next;
        } else if (prev != NULL) {
            while (prev->next != node) {
                if (prev == NULL) {
                    return -0x18;
                }
                prev = prev->next;
                if (prev == NULL) {
                    return -0x18;
                }
            }
            prev->next = node->next;
        } else {
            return -0x18;
        }
    }
    node->parent = new_parent;
    node->next = NODE_CHILDREN(new_parent);
    *NODE_CHILDREN_PTR(new_parent) = node;
}

typedef s32 (*Visitor)(GoolObj *, void *);
GoolObj *GOOL_TestObjectStateFlags(GoolObj *, u32);
s32 Gool_ObjectTerminate(GoolObj *, void *);

s32 Gool_ObjectSearchTree(GoolObj *, Visitor, void *);
static __inline__ s32 Gool_FindObject_inline(GoolObj *root, Visitor visitor, void *context)
{
    GoolObj *child;
    GoolObj *next;
    s32 result = 0;

    if (root == NULL) {
        return 0;
    }
    if (root->kind != 2) {
        result = visitor(root, context);
        if (result != 0) {
            return result;
        }
    }
    if (root->kind == 2) {
        child = (GoolObj *)root->unk04;
    } else {
        child = root->children;
    }
    while (child != NULL && result == 0) {
        next = child->next;
        result = Gool_ObjectSearchTree(child, visitor, context);
        child = next;
    }
    return result;
}

typedef struct ZoneEntity {
    u8 pad00[4];
    u16 flags;
    u8 group;
    u8 pad07;
    u16 id;
    u16 path_length;
    s16 rot_x;
    s16 rot_y;
    s16 rot_z;
    u8 type;
    u8 subtype;
    s16 x;
    s16 y;
    s16 z;
} ZoneEntity;

typedef struct ObjectRoot {
    s32 kind;
    GoolObj *word04;
} ObjectRoot;

typedef struct ZoneHeaderView {
    u8 pad00[0x204];
    s32 path_index;
    s32 path_count;
    u8 pad20C[0xD0];
    u32 flags2DC;
    u8 pad2E0[0x38];
    GoolDefaults obj_defaults;
    GoolDefaults player_defaults;
} ZoneHeaderView;

typedef struct ZoneEntryView {
    u32 word00;
    u32 id;
    s32 kind;
    s32 word0C;
    void *items[1];
} ZoneEntryView;

extern GoolObj *g_doctor_cortex_obj[];
extern ZoneEntity *g_mdat_title_str_ptr[];
extern GoolObj g_gool_obj_list_4;
extern s32 gp_pbak_frame_idx[];
s32 Math_Absdiff(s32, s32);
void Gool_ObjectOrientOnPath(GoolObj *, s32, s32 *);
void Level_SaveState(GoolObj *, void *, s32);

#define IS_PLAYER_ENTITY(e) \
    ((e)->group == 3 && \
     ((e)->type == 0 || ((e)->id != 0 && (e)->id < 5) || \
      (((e)->type == 0x2C || (e)->type == 0x30) && (e)->subtype == 0)))

GoolObj *GOOL_CreateObject(GoolObj *parent, s32 exec_id, s32 subtype, s32 arg_count, s32 *args, s32 flag);
s32 GOOL_InitObject(GoolObj *obj, s32 exec_id, s32 subtype, s32 arg_count, s32 *args);
s32 Gool_ObjectKill(GoolObj *obj, s32 flag);

GoolObj *Gool_ObjectSpawn(ZoneEntryView *zone, s32 idx) {
    GoolObj *prev_box;
    ZoneEntity *entity;
    GoolObj *obj;
    GoolObj *victim;
    s32 res;
    s32 tmp;

    if (zone != NULL) {
        prev_box = NULL;
        switch (zone->kind) {
        case 7:
            {
                ZoneHeaderView *header = (ZoneHeaderView *)zone->items[0];
                entity = (ZoneEntity *)zone->items[idx + header->path_index + header->path_count];
            }
            break;
        case 17:
            entity = (ZoneEntity *)zone->items[idx + 2];
            break;
        }
        if (IS_PLAYER_ENTITY(entity) && gp_crash_obj != NULL) {
            return (GoolObj *)-0xE;
        }
        if (entity->type == 0x22) {
            if (g_mdat_title_str_ptr[0] != NULL &&
                Math_Absdiff(entity->x, g_mdat_title_str_ptr[0]->x) < 10 &&
                Math_Absdiff(entity->z, g_mdat_title_str_ptr[0]->z) < 10 &&
                Math_Absdiff(entity->y, g_mdat_title_str_ptr[0]->y + 100) < 10) {
                prev_box = g_doctor_cortex_obj[0];
            } else {
                g_spu_reverb_addr[0] = 0x19000;
                prev_box = NULL;
                g_doctor_cortex_obj[0] = NULL;
            }
            g_mdat_title_str_ptr[0] = entity;
        }
        if ((g_spawns[entity->id] & 1) || (g_spawns[entity->id] & 2)) {
            if (entity->type == 0x22) {
                g_spu_reverb_addr[0] += 0x19000;
            }
            return (GoolObj *)-0xE;
        }
        if (IS_PLAYER_ENTITY(entity)) {
            obj = g_player[0];
            gp_crash_obj = obj;
            idx = 6;
        } else {
        retry:
            obj = NODE_CHILDREN(&g_gool_obj_list_7);
            idx = 3;
            if (obj == NULL) {
                victim = (GoolObj *)Gool_FindObject_inline(&g_gool_obj_list_3, (Visitor)GOOL_TestObjectStateFlags, (void *)0x80000);
                if (victim != NULL) {
                    Gool_ObjectTerminate(victim, NULL);
                    goto retry;
                }
                return (GoolObj *)-0x16;
            }
        }
        Gool_RemoveLevelSpawn(obj, (GoolObj *)&((ObjectRoot *)g_free_objects)[idx]);
        obj->unk04 = entity->group;
        res = GOOL_InitObject(obj, entity->type, entity->subtype, 0, NULL);
        if (res >= -0xFE) {
            Gool_RemoveLevelSpawn(obj, &g_gool_obj_list_7);
            return (GoolObj *)res;
        }
        g_spawns[entity->id] |= 1;
        obj->pid_flags = entity->id << 8;
        if (zone != NULL && zone->kind == 17) {
            zone = (ZoneEntryView *)g_pads[0];
        }
        obj->zone = (ResourceEntry *)zone;
        if (IS_PLAYER_ENTITY(entity)) {
            obj->defaults = ((ZoneHeaderView *)zone->items[0])->player_defaults;
        } else {
            obj->defaults = ((ZoneHeaderView *)zone->items[0])->obj_defaults;
        }
        obj->entity = entity;
        obj->path_length = entity->path_length << 8;
        if (!(entity->flags & 1)) {
            obj->vectors.rot[0] = entity->rot_x;
            obj->vectors.rot[1] = entity->rot_y;
            obj->vectors.rot[2] = entity->rot_z;
        }
        obj->unkBC = entity->rot_x << 8;
        obj->unkC0 = entity->rot_y << 8;
        obj->unkC4 = entity->rot_z << 8;
        Gool_ObjectOrientOnPath(obj, 0, obj->vectors.trans);
        if (obj == gp_crash_obj && gp_pbak_frame_idx[0] == -1) {
            Level_SaveState(obj, g_checkpoint_save_state, 1);
        }
        if (obj->exec->header->unk04 == 0x300) {
            Gool_RemoveLevelSpawn(obj, &g_gool_obj_list_4);
        }
        if (obj->exec->header->unk00 == 0x22) {
            if (prev_box != NULL) {
                obj->unkA4 = (s32)prev_box;
                obj->unkA8 = 0;
                prev_box->unkA8 = (s32)obj;
            } else {
                obj->unkA4 = 0;
                obj->unkA8 = 0;
            }
            obj->vectors.trans[1] += 0x19000 - g_spu_reverb_addr[0];
            g_doctor_cortex_obj[0] = obj;
            if (!(((ZoneHeaderView *)zone->items[0])->flags2DC & 4)) {
                tmp = ((obj->vectors.trans[2] >> 4) ^ obj->vectors.trans[0]) & 7;
                obj->unk104 = tmp;
                if (tmp != 0) {
                    obj->status_b |= 0x10000000;
                }
            }
        }
        return obj;
    }
    return (GoolObj *)-0xE;
}

GoolObj *GOOL_CreateObject(GoolObj *parent, s32 exec_id, s32 subtype, s32 arg_count, s32 *args, s32 flag) {
    GoolObj *obj;
    GoolObj *victim;
    s32 res;

    if (!exec_id && !subtype) {
        obj = g_player[0];
        gp_crash_obj = obj;
    } else {
    retry:
        obj = NODE_CHILDREN(&g_gool_obj_list_7);
        if (obj == NULL && flag != 0) {
            victim = (GoolObj *)Gool_FindObject_inline(&g_gool_obj_list_3, (Visitor)GOOL_TestObjectStateFlags, (void *)0x80000);
            if (victim != NULL) {
                Gool_ObjectTerminate(victim, NULL);
                goto retry;
            }
        }
    }
    if (obj == NULL) {
        return (GoolObj *)-0x16;
    }
    Gool_RemoveLevelSpawn(obj, parent);
    obj->unk04 = 3;
    res = GOOL_InitObject(obj, exec_id, subtype, arg_count, args);
    if (obj->zone != NULL) {
        obj->defaults = ((ZoneHeaderView *)obj->zone->data)->obj_defaults;
    } else if (obj == gp_crash_obj) {
        obj->defaults = ((ZoneHeaderView *)g_pads[0]->data)->player_defaults;
    } else {
        obj->defaults = ((ZoneHeaderView *)g_pads[0]->data)->obj_defaults;
    }
    if (res >= -0xFE) {
        return (GoolObj *)res;
    }
    return obj;
}

s32 GOOL_InitObject(GoolObj *obj, s32 exec_id, s32 subtype, s32 arg_count, s32 *args) {
    GoolObj *parent;
    s32 *entry_ptr;
    GoolExecutable *exec;
    u16 state;

    obj->pid_flags = 0;
    obj->entity = NULL;
    obj->path_progress = 0;
    obj->path_length = 0;
    obj->kind = 1;
    obj->unkA4 = 0;
    obj->unkA8 = 0;
    obj->unkAC = 0;
    obj->unkB0 = 0;
    obj->unkB4 = 0;
    obj->unkB8 = 0;
    obj->unkBC = 0;
    obj->unkC0 = 0;
    obj->unkC4 = 0;
    obj->speed = 0;
    obj->anim_frame = 0;
    obj->unkF8 = 0;
    obj->unkB4 = 0;
    obj->status_a = 0;
    obj->status_c = 0;
    obj->status_b = 0;
    obj->invincibility_state = 0;
    obj->cam_zoom = 0;
    obj->floor_time = 0;
    obj->unk148 = 0;
    obj->node_id = 0xFFFF;
    obj->voice_id = -2;
    parent = obj->parent;
    if (parent->kind == 1) {
        obj->zone = parent->zone;
        obj->vectors = obj->parent->vectors;
    } else {
        obj->zone = NULL;
        obj->vectors.rot[0] = 0;
        obj->vectors.rot[1] = 0;
        obj->vectors.rot[2] = 0;
        obj->vectors.scale[0] = 0x1000;
        obj->vectors.scale[1] = 0x1000;
        obj->vectors.scale[2] = 0x1000;
    }
    switch (exec_id) {
    case 4:
    case 5:
    case 29:
        obj->zone = NULL;
        break;
    case 0:
        obj->cam_rot_x = 0;
        break;
    }
    if (obj->unk04 != 3) {
        return -0xE;
    }
    entry_ptr = &g_ns_page_pool[0]->items[exec_id];
    if (*entry_ptr != 0x6396347F && exec_id < 0x40) {
        obj->exec = Ns_Open(entry_ptr, 1, 0);
        if ((s32)obj->exec >= -0xFE) {
            return -0xE;
        }
        obj->self = obj;
        obj->unk78 = 0;
        obj->unk70 = 0;
        obj->unk7C = 0;
        obj->player = g_player[0];
        obj->subtype = subtype;
        obj->anim_seq = NULL;
        obj->unkF0 = 0;
        exec = obj->exec;
        state = exec->states[exec->header->unk10 + obj->subtype];
        if (state == 0xFF) {
            return -0x1B;
        }
        if (GOOL_ChangeObjectState(obj, state, (s32 *)arg_count, (s32)args) < -0xFE) {
            return -0xFF;
        }
    }
    return -0xE;
}

s32 Gool_ObjectKill(GoolObj *obj, s32 flag) {
    GoolObj *child;
    GoolObj *next;
    GoolObj *head;

    if (obj == NULL) {
        return -0xFF;
    }
    if (obj == gp_crash_obj && ((GoolCodeHeader *)g_ns_page_pool[0])->unk04 != 0x19) {
        return -0xFF;
    }
    if (flag != 0) {
        Gool_ExecStateCode(NULL, obj, 0x1A00, 0, NULL);
    }
    child = obj->children;
    if (child != NULL) {
        do {
            next = child->next;
            Gool_ObjectKill(child, flag);
            child = next;
        } while (child != NULL);
    }
    Audio_VoiceFree(obj);
    g_spawns[obj->pid_flags >> 8] &= ~1;
    obj->kind = 0;
    if (obj == gp_crash_obj) {
        head = NODE_CHILDREN(&g_gool_obj_list_7);
        Gool_RemoveLevelSpawn(obj, &g_gool_obj_list_7);
        *NODE_CHILDREN_PTR(&g_gool_obj_list_7) = head;
        g_player[0]->parent = NULL;
        g_player[0]->children = NULL;
        g_player[0]->next = NULL;
        ((struct { GoolObj *x; } *)&gp_crash_obj)->x = NULL;
    } else {
        Gool_RemoveLevelSpawn(obj, &g_gool_obj_list_7);
    }
    return -0xFF;
}

