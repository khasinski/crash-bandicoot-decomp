#include "common.h"
#include "render.h"
#include "resource.h"

/* GCC_VERSION: 2.6.3 */

/* Initialise the runtime, run the game loop for initial level 0x19, then shut down. */

void __main(void);
void Core_Init(void);
void CORE_Loop(s32);
void Core_Kill(void);
extern s32 gp_pause_B_pressed;

s32 CORE_Main(void)
{
    __main();
    gp_pause_B_pressed = 1;
    Core_Init();
    CORE_Loop(0x19);
    Core_Kill();
    return 0;
}

typedef struct ZoneHeaderView {
    s32 word00;
    u8 pad04[0x2F8];
    u32 flags;
} ZoneHeaderView;

typedef struct LevelDataView {
    u8 pad00[4];
    s32 level_id;
    u8 pad08[0xC];
    s32 eid14;
    u8 pad18[8];
    s32 eid20;
    s32 eid24;
    s32 eid28;
    u8 pad2C[0x5C];
    s32 eid88;
    u8 pad8C[0x10];
    s32 eid9C;
    u8 padA0[0x44];
    s32 eidE4;
} LevelDataView;

typedef struct NsState {
    u8 pad00[0x14];
    LevelDataView *level;
    u8 pad18[0xC];
    s32 draw_skip;
} NsState;

/* Object storage from the pause object's parent at 0x80060DF0 through the
 * playback mode at 0x80061A30. The loop addresses all three through one base. */

typedef struct DrawStampView {
    u8 pad00[0x7C];
    u32 stamp;
} DrawStampView;

extern NsState g_ns;
extern s32 gp_pbak_mode;
extern s32 D_800618BC;

void Pad_Update(void);
void Ns_Open(void *, s32, s32);
void Level_InitMisc(s32);
s32 GOOL_CreateObject(void *parent, s32 exec, s32 subtype, s32 argc, s32 *argv, s32 flag);

/* Spawn default HUD objects and load the level's initial resource entries. */
void Core_ObjectsCreate(void)
{
    Pad_Update();
    D_800618BC = 0;
    switch (gp_pbak_mode) {
    case 0x38:
    case 0x39:
        break;
    case 0x19:
        Ns_Open(&g_ns.level->eid24, 0, 1);
        Ns_Open(&g_ns.level->eidE4, 0, 1);
        break;
    case 0x2D:
        Ns_Open(&g_ns.level->eid88, 0, 1);
        Ns_Open(&g_ns.level->eid9C, 0, 1);
        Ns_Open(&g_ns.level->eid20, 0, 1);
        break;
    default:
        D_800618A8 = GOOL_CreateObject(&g_handles, 4, 0, 0, 0, 0);
        D_800618A4 = GOOL_CreateObject(&g_handles, 4, 1, 0, 0, 0);
        D_800618C4 = GOOL_CreateObject(&g_handles, 4, 5, 0, 0, 0);
        Ns_Open(&g_ns.level->eid14, 0, 1);
        Ns_Open(&g_ns.level->eid28, 0, 1);
        Ns_Open(&g_ns.level->eid88, 0, 1);
        if (gp_pbak_mode != 0x2C) {
            Ns_Open(&g_ns.level->eid9C, 0, 1);
        }
        Ns_Open(&g_ns.level->eid20, 0, 1);
        Ns_Open(&g_ns.level->eid24, 0, 1);
        break;
    }
    Level_InitMisc(1);
}
extern s32 g_gool_pads;
extern s32 g_key_count;
extern DrawStampView *g_db_prev;
extern u32 D_800566B0;
extern void *gp_crash_obj;
extern s32 gp_pbak_frame_idx;

extern s32 D_800618A0;
extern s32 D_80061A3C;
extern s32 D_800619A0;
extern s32 g_cur_lid_ro;

/* .sdata owned by this unit (gp-addressed only here). */
s32 gp_cur_lid = 0;
s32 gp_next_lid = 0;
s32 gp_paused = 0x1000;
s32 D_80056408 = 0x200000;
s32 gp_use_cd = 0;

/* .sbss owned by this unit. */
asm(".globl gp_rcnt_event, D_800565BC");
u32 gp_rcnt_event;
u32 D_800565BC;

void Level_InitGlobals(void);
void Ns_Init(NsState *ns, s32 level);
void Core_ObjectsCreate(void);
s32 GOOL_CreateObject(void *parent, s32 exec, s32 subtype, s32 argc, s32 *argv, s32 flag);
void Gool_ExecStateCode(s32 sender, s32 object, s32 event, s32 argc, s32 *argv);
void Pbak_Play(u32 *eid);
void Gool_SendToColliders(s32, s32, s32, s32, s32);
void Ns_Kill(NsState *ns);
void Level_SpawnObjects2(void);
void Level_Restart(s32 *state);
void Ns_Update(s32);
void Shader_ParamsUpdate(s32);
void Shader_ParamsUpdateRipple(s32);
void Cam_Update(void);
void Gfx_UpdateMatrices(void);
void Gfx_TransformWorldsDark2(u32 *);
void Gfx_TransformWorldsDark(u32 *);
void Gfx_TransformWorldsFog(u32 *);
void Gfx_TransformWorldsRipple(u32 *);
void Gfx_TransformWorldsLightning(u32 *);
void Gfx_TransformWorlds(u32 *);
void Gool_UpdateObjects(s32);
void Title_Update(u32 *);
void Gpu_Update(void);

/* Run levels until the exit flag is set: pause toggling, demo playback,
 * level transitions, per-frame update and zone-specific drawing. */
void CORE_Loop(s32 level)
{
    char debug_text[0xA8]; /* reserved in the retail frame, never accessed */
    s32 arg;
    s32 restore;
    s32 id;
    u32 flags;
    ZoneHeaderView *zone;

    Level_InitGlobals();
    Ns_Init(&g_ns, level);
    Core_ObjectsCreate();
    do {
        /* Start toggles pause outside the title, map and intro levels. */
        if ((g_gool_pads & 0x800) && g_pause_state.playback_mode == 0
            && (((id = g_ns.level->level_id) != 0x19 && id != 0x2D && id != 0x38
                 && g_pause_state.pause_override != -1) || g_key_count > 0)) {
            if ((gp_next_lid = 1 - gp_next_lid) != 0) {
                if (g_pause_state.pause_object == 0) {
                    g_pause_state.pause_object = GOOL_CreateObject(&g_pause_state, 4, 4, 0, 0, 0);
                    if (g_pause_state.pause_object >= -0xFE) {
                        gp_next_lid = 0;
                        g_pause_state.pause_object = 0;
                        goto not_paused;
                    }
                    gp_use_cd = 1;
                    gp_rcnt_event = engine_counter[0];
                    D_800565BC = g_db_prev->stamp;
                }
            } else if (g_pause_state.pause_object != 0) {
                arg = 0;
                Gool_ExecStateCode(0, g_pause_state.pause_object, 0xC00, 1, &arg);
                g_pause_state.pause_object = 0;
                gp_use_cd = -1;
                engine_counter[0] = gp_rcnt_event;
                g_db_prev->stamp = D_800565BC;
            }
        } else {
not_paused:
            gp_use_cd = 0;
        }

        /* 0x6396347F is the null resource ID. */
        if (gp_crash_obj != 0 && D_800566B0 != 0x6396347F) {
            Pbak_Play(&D_800566B0);
        }

        /* Game over and continue states return to the map (level 0x19). */
        if (gp_pbak_frame_idx == -1 && g_ns.level->level_id != 0x19
            && (D_800618D0 == 0x200 || D_800618D0 == 0x300 || D_800618D0 == 0x400)) {
            gp_pbak_frame_idx = 0x19;
        }
        /* Level change; -2 restores the saved level after a bonus round. */
        if (gp_pbak_frame_idx != -1) {
            restore = 0;
            level = gp_pbak_frame_idx;
            Gool_SendToColliders(0, 0x2900, 0, 0, 0);
            if (gp_pbak_frame_idx == -2) {
                level = D_800579A4;
                restore = 1;
                gp_cur_zone = 1;
            } else {
                gp_cur_zone = 0;
            }
            g_ns.draw_skip = 2;
            Ns_Kill(&g_ns);
            gp_next_lid = 0;
            if (level == 0x19) {
                D_800618A0 = 0;
                D_80061A3C = 0;
                g_checkpoint_id = 0;
                D_800618FC = 0;
                g_mono = 0;
                D_800619A0 = -1;
            }
            Ns_Init(&g_ns, level);
            Core_ObjectsCreate();
            if (restore) {
                gp_pbak_frame_idx = -2;
                Level_SpawnObjects2();
                gp_pbak_frame_idx = -1;
                Level_Restart(D_80057974);
            }
            gp_cur_zone = 0;
        }

        Ns_Update(-1);
        Level_SpawnObjects2();
        if (gp_next_lid == 0) {
            if (((ZoneHeaderView *)g_pads->data)->flags & 0x600) {
                Shader_ParamsUpdate(0);
            }
            if (gp_next_lid == 0) {
                if (((ZoneHeaderView *)g_pads->data)->flags & 0x100) {
                    Shader_ParamsUpdateRipple(0);
                }
                if (gp_next_lid == 0) {
                    Cam_Update();
                }
            }
        }
        Gfx_UpdateMatrices();

        if (g_cur_lid_ro & 1) {
            zone = (ZoneHeaderView *)g_pads->data;
            if (zone->word00 != 0 && gp_cur_lid == 0) {
                flags = zone->flags;
                if (flags & 0x400) {
                    Gfx_TransformWorldsDark2(g_ot_cur->ordering_table);
                } else if ((flags & 0x210) == 0x210) {
                    Gfx_TransformWorldsDark(g_ot_cur->ordering_table);
                } else if (flags & 0x10) {
                    Gfx_TransformWorldsFog(g_ot_cur->ordering_table);
                } else if (flags & 0x100) {
                    Gfx_TransformWorldsRipple(g_ot_cur->ordering_table);
                } else if (flags & 0x200) {
                    Gfx_TransformWorldsLightning(g_ot_cur->ordering_table);
                } else {
                    Gfx_TransformWorlds(g_ot_cur->ordering_table);
                }
            }
        }
        Gool_UpdateObjects(gp_next_lid == 0);
        if (g_ns.level->level_id == 0x19) {
            Title_Update(g_ot_cur->ordering_table);
        }
        Gpu_Update();
    } while (gp_bonus_return == 0);

    g_cur_lid_ro = 0;
    Gpu_Update();
    Gpu_Update();
    Ns_Kill(&g_ns);
}
