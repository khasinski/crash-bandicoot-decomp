#include "common.h"
extern s32 D_80061910;
extern s32 g_levels_unlocked;
extern s32 g_cur_map_level;

/* GCC_VERSION: 2.6.3 */
void Level_ResetGlobals(s32);                                 /* extern */
void BIOS_MemSet(void *, s32, s32);                      /* extern */
void Card_InvalidateFilename(void);                                /* extern */
extern s32 D_800618A0;
extern s32 D_800618D4;



extern s32 D_800619A0;

extern s32 D_80061A3C;

void Level_InitGlobals(void) {
    D_800618DC[0] = 0x63;
    g_pbak_state = -1;
    D_800618D4 = 7;
    g_cur_map_level = 0xFF;
    g_levels_unlocked = 0xFF;
    g_new_gem_flag[0] = 0x400;
    g_life_count = 0;
    D_8006190C[0] = 0;
    D_80061910 = 0;
    g_item_pool2[0] = 1;
    D_8006199C = 0;
    D_80061A40 = 0;
    D_80061A58 = 0;
    D_800618D0 = 0;
    D_80061A1C = 0;
    D_80061A20 = 0;
    D_80061A50 = 1;
    Level_ResetGlobals(1);
}

void Level_ResetGlobals(s32 arg0) {
    if (arg0 != 0) {
        D_80061A3C = 0;
        D_800618A0 = 0;
        g_brio_count = 0;
        g_tawna_count = 0;
        g_checkpoint_id = 0;
        D_800618FC = 0;
        g_mono = 0;
        D_80061948[0] = 1;
        D_80061988[0] = 0;
        D_800619A0 = -1;
        D_800619AC[0] = 0;
        D_80061998[0] = 1;
        D_800618DC[0] = 0x63;
        g_item_pool2[0] = 1;
        D_80061A1C = 0;
        D_80061A20 = 0;
        D_80061A50 = 1;
        g_cortex_count = g_new_gem_flag[0];
        BIOS_MemSet(g_level_spawns, 0, 0x200);
        Card_InvalidateFilename();
    }
}

