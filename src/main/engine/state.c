#define CRASH_STATE_GLOBALS_OWNER
#include "common.h"
#include "engine_ticks.h"
#define CRASH_ENGINE_STATE_STORAGE
#include "engine_state.h"
#include "resource.h"
#include "gool.h"

/* GCC_VERSION: 2.6.3 */



/* Mode request and the eight-byte name/format records at 0x80056500. */
s32 gp_title_once = 1;
char gp_game_over_zone_name[8] = "0b_pZ";
char gp_main_menu_zone_name[8] = "0c_pZ";
char gp_naughty_dog_zone_name[8] = "0d_pZ";
char gp_load_menu_zone_name[8] = "0e_pZ";
char gp_options_menu_zone_name[8] = "0f_pZ";
char gp_island_1b_zone_name[8] = "1e_pZ";
char gp_island_1a_zone_name[8] = "1a_pZ";
char gp_island_2_zone_name[8] = "2b_pZ";
char gp_island_3_zone_name[8] = "3a_pZ";
char gp_scea_universal_zone_name[8] = "0a_pZ";
char gp_mdat_fmt_name[8] = "%cMapP";
char gp_mdat_default_name[8] = "0MapP";

/* Retail initial value at 0x80056564 is zero; preserve its .sdata placement. */
EngineState *gp_card = NULL;
/* Preserved render-state flag, initial retail value 1 at 0x80056568. */
s32 gp_card_new_device = 1;
/* Sentinel values make the first card flags/mode poll register a change. */
s32 gp_prev_card_flags = -1;
u32 gp_prev_card_state = 0xFFFFFFFF;


/* File cleanup requests and lifecycle entry points. */
typedef EngineFileRequest FileRequest;
s32 Card_TestRead(s32);
s32 Card_ClearFlags(s32);
s32 Card_SetState(s32);
s32 Card_BeginLoadIfIdle(void);
s32 Card_IncRetryCount(void);
s32 Card_ResetParts(s32);
s32 Card_SetFlags(s32);
void Card_Close(s32 *);
s32 VSync(s32);
s32 erase(char *);
s32 TestEvent(s32);
s32 Math_Randb(s32);

/* Traversal storage and lifecycle share the recovered engine globals. */
#include "object_links.h"

/* GCC_VERSION: 2.6.3 */
typedef EngineMode25State State;
/* Real zero-initialized storage at 0x80056678..0x800566C4.
 * Unidentified words retain address names; the two typed owners are shared
 * with object_defaults and update_request. */
asm(".globl gp_title_not_seen, D_8005667C, D_80056680, D_80056684, D_80056688, gp_save_id, gp_file_is_new, D_80056694, D_80056698, D_8005669C, D_800566A0, D_800566A4, gp_cur_pbak_header, D_800566AC, D_800566B0, gp_crash_obj, gp_level_entry, D_800566BC, gp_card_chan");
s32 gp_title_not_seen;
u32 D_8005667C;
u32 D_80056680;
u32 D_80056684;
u32 D_80056688;
u32 gp_save_id;
u32 gp_file_is_new;
u32 D_80056694;
u32 D_80056698;
u32 D_8005669C;
u32 D_800566A0;
u32 D_800566A4;
u32 gp_cur_pbak_header;
u32 D_800566AC;
u32 D_800566B0;
GoolDefaultsObject *gp_crash_obj;
u32 gp_level_entry, D_800566BC;
s32 gp_card_chan;

/* Real engine globals in retail address order, 0x800566C4..0x800566FC.
 * The state and grid pointers retain their recovered pointer types. */
asm(".globl gp_edesc_s_end_io, gp_edesc_s_error, gp_edesc_s_timeout, gp_edesc_s_newdev, D_800566D4, D_800566D8, D_800566DC, gp_title, D_800566E4, D_800566E8, gp_edesc_h_end_io, gp_edesc_h_error, gp_grid_rows, gp_edesc_h_timeout, gp_edesc_h_newdev");
s32 gp_edesc_s_end_io;
s32 gp_edesc_s_error;
s32 gp_edesc_s_timeout;
s32 gp_edesc_s_newdev;
s32 D_800566D4;
s32 D_800566D8;
s32 D_800566DC;
State *gp_title;
s32 D_800566E4;
s32 D_800566E8;
s32 gp_edesc_h_end_io;
s32 gp_edesc_h_error;
s32 *gp_grid_rows;
s32 gp_edesc_h_timeout;
s32 gp_edesc_h_newdev;

void Title_LoadEntries(s32, s32, s32);
void *LIBC_Calloc(int, int);
void BIOS_Abs(s32);
extern s32 gp_pbak_mode;
s32 Title_Init(void)
{
    State *state;
    if(gp_pbak_mode == 25) {
        state = LIBC_Calloc(1, sizeof(State));
        gp_title = state;
        if(state == NULL) BIOS_Abs(-1);
    }
    return 0;
}

extern volatile s32 D_800618D4;
s32 Title_LoadState(void);


/* Apply a pending mode request and initialise the recovered mode-state words. */
s32 Title_LoadNextState(void)
{
    extern s32 g_fade_counter[];
    s32 request;
    u32 value;
    EngineMode25State *reset_state, *requested_state;
    u32 selection;
    request = gp_title_once;
    gp_title_once = 0;
    gp_title_not_seen = request;
    if (gp_pbak_mode == 25) {
        g_fade_counter[0] = (g_fade_counter[0] & 0xFFFE3FF0) | 0x20000;
        if (request == 0) {
            value = D_800618D0;
            switch (value) {
            case 0: case 0x100: case 0x300: case 0x400:
                (gp_title)->word35D0 = (gp_title)->word35D4 = D_800618D4;
                selection = D_8006194C[0];
                (gp_title)->word3598 = 1;
                (gp_title)->word35A4 = selection;
                (gp_title)->word35A0 = selection;
                break;
            case 0x600:
                reset_state = gp_title;
                value = 5;
                goto set_value;
            case 0x200:
                reset_state = gp_title;
                value = 12;
set_value:
                D_800618D4 = value;
                reset_state->word35D4 = value;
                reset_state->word35D0 = value;
                value = 1;
                reset_state->word3598 = value;
                break;
            }
        } else {
            D_800618D4 = 10;
            requested_state = gp_title;
            requested_state->word35D4 = 10;
            requested_state->word35D0 = 10;
            requested_state->word3598 = 0;
        }
        Title_LoadState();
    }
    return 0;
}

s32 Ns_Open(s32 *, s32, s32);
s32 Ns_Close(s32 *, s32);
void Level_Update(ResourceItemListView *, u8 *, s32, s32);
extern s32 gp_next_lid;
extern s32 gp_use_cd;
extern ResourceSlotStateView g_slst_buf1[];

/* Change mode flags, recycle pending texture slots 8..14, and initialise
 * the item selected by the resource metadata before releasing the reference. */
void Title_LoadScreen(s32 *reference, s32 mode)
{
    extern s32 g_fade_counter[];
    s32 index;
    ResourceItemListView *resource;
    gp_next_lid = 0;
    gp_use_cd = -1;
    Gool_ForEachObjectHandle(Gool_ObjectHandleTraverseTreePostorder, Gool_ObjectTerminate, NULL);
    switch (mode) {
    case 0:
        g_fade_counter[0] = (g_fade_counter[0] & 0xFFFE3FF0) | 0x20000;
        gp_title->word359C = 1;
        break;
    case 1:
        g_fade_counter[0] = 0xFFFF;
        gp_title->word359C = 0;
        for (index = 8; index < 15; index++) {
            if (g_slst_buf1[index].state == 30)
                g_slst_buf1[index].state = 1;
        }
        break;
    case 3:
        g_fade_counter[0] = 0x2FFFC;
        gp_title->word359C = 1;
        break;
    }
    resource = (ResourceItemListView *)Ns_Open(reference, 1, 1);
    Level_Update(resource,
        resource->items[((ResourceItemSelection *)resource->items[0])->word204], 0, 2);
    Ns_Close(reference, 1);
}

#include "ns.h"
#include "render.h"
extern s32 g_key_count[];
ResourceItemListView *Ns_Lookup(u32 *);
void BIOS_Abs(s32);
void Gfx_InitMatrices(void);
void Level_ResetGlobals(s32);
s32 Ns_AlphaNumChar(s32);
s32 sprintf(char *, char *, ...);
void Gool_ObjectSpawn(ResourceItemListView *, s32);
s32 Title_LoadState(void) {
    extern s32 g_fade_counter[];
    char buf[32];
    s32 ref;
    s32 mode;
    ResourceItemListView *list;
    s32 *header;
    s32 i;

    g_key_count[0] = 0;
    switch (gp_title->word35D0) {
    case 1:
    case 2:
    case 3:
    case 4:
        BIOS_Abs(0);
    case 6:
    case 15:
        g_ns_page_pool->word114 = 0x25;
        break;
    case 5:
    case 8:
    case 12:
    case 13:
    case 14:
        g_ns_page_pool->word114 = 0x37;
        break;
    default:
        g_ns_page_pool->word114 = 0x5A;
        break;
    }
    Gfx_InitMatrices();
    switch (gp_title->word35D0) {
    case 12:
        ref = Ns_StringToEID(gp_game_over_zone_name);
        mode = 1;
        break;
    case 5:
        Level_ResetGlobals(1);
        ref = Ns_StringToEID(gp_main_menu_zone_name);
        mode = 3;
        break;
    case 8:
        ref = Ns_StringToEID(gp_naughty_dog_zone_name);
        mode = 3;
        break;
    case 13:
    case 14:
        ref = Ns_StringToEID(gp_load_menu_zone_name);
        mode = 1;
        break;
    case 6:
        ref = Ns_StringToEID(gp_options_menu_zone_name);
        mode = 1;
        break;
    case 15:
        if (D_800618DC[0] == 99 || D_800618DC[0] < 10) {
            if (D_800618DC[0] == 9) {
                ref = Ns_StringToEID(gp_island_1b_zone_name);
            } else {
                ref = Ns_StringToEID(gp_island_1a_zone_name);
            }
        } else if (D_800618DC[0] < 18 || D_800618DC[0] >= 50) {
            ref = Ns_StringToEID(gp_island_2_zone_name);
        } else {
            ref = Ns_StringToEID(gp_island_3_zone_name);
        }
        mode = 1;
        break;
    default:
        ref = Ns_StringToEID(gp_scea_universal_zone_name);
        mode = 0;
        break;
    }
    if (mode == 0) {
        Title_LoadScreen(&ref, 0);
    }
    D_8006193C[0] = 0;
    g_item_pool1[0] = 0;
    switch (gp_title->word35D0) {
    case 1:
    case 2:
    case 3:
    case 4:
        D_800618B8[0] = ~gp_title->word35D0;
        break;
    case 5:
    case 6:
    case 8:
    case 12:
    case 13:
    case 14:
    case 15:
        Title_LoadScreen(&ref, mode);
        break;
    default:
        D_800618B8[0] = 0;
        gp_title->word359C = 1;
        break;
    }
    g_fade_counter[0] |= 0x200000;
    sprintf(buf, gp_mdat_fmt_name, (u8)Ns_AlphaNumChar(gp_title->word35D0));
    gp_title->word00 = Ns_StringToEID(buf);
    if ((g_fade_counter[0] & 0x20000) && gp_title->word359C != 0) {
        s32 h1;
        list = Ns_Lookup((s32 *)&gp_title->word00);
        header = (s32 *)list->items[0];
        Title_LoadEntries(gp_title->word35D0, 1, 1);
        gp_title->word0C = header[0];
        h1 = header[1];
        gp_title->word14 = 0;
        gp_title->word18 = 0;
        gp_title->word10 = h1;
        gp_title->word04 = gp_title->word0C << 4;
        gp_title->word08 = gp_title->word10 << 4;
        for (i = 0; i < header[3]; i++) {
            typedef struct { u8 pad00[0x18]; s16 max_level; } MapItemHeader;
            if ((u32)((MapItemHeader *)list->items[i + 2])->max_level <= D_80061948[0]) {
                Gool_ObjectSpawn(list, i);
            }
        }
    }
    return 0;
}

void Title_KillObjectsAndEntries(void)
{
    Gool_ForEachObjectHandle(Gool_ObjectHandleTraverseTreePostorder, Gool_ObjectTerminate, NULL);
    if(gp_title->word359C != 0)
        Title_LoadEntries(gp_title->word35D0, 0, -1);
}

void LIBC_Free(void *);
extern s32 gp_pbak_mode;
s32 Title_Kill(void)
{
    if(gp_title != NULL) LIBC_Free(gp_title);
    gp_pbak_mode = 0;
    return 0;
}


#include "ns.h"
#include "render.h"

void *LIBC_Malloc(u32);
void DrawSync(s32);
void Gpu_FillDisplay(void);
extern RenderBuffer *g_db_prev;
extern s32 D_8005C54C;

typedef struct EngineGpuRect {
    s16 x, y, w, h;
} EngineGpuRect;

ResourceItemListView *Ns_Lookup(u32 *);
void LoadImage(EngineGpuRect *, void *);

s32 Title_Loading(s32 level, u8 *image, NsDirectory *dir)
{
    EngineGpuRect rect;
    u16 *buf;
    u16 *clut;
    s32 pass;
    u8 *src;
    s32 strip;
    s32 dx;
    s32 x;
    s32 y;
    u16 *dst;
    s32 row;
    s32 col;

    if (dir->word40C && dir->word410 && dir->word414
        && D_800618D0 != 0x600 && D_800618D0 != 0x200 && D_800618D0 != 0x500
        && (D_800618D0 != 0 || level != 25)) {
        buf = LIBC_Malloc(0x4000);
        DrawSync(0);
        clut = (u16 *)image;
        for (pass = 0; pass < 2; pass++) {
            src = image + 0x200;
            Gpu_FillDisplay();
            strip = 0;
            dx = dir->word410 / 2 - 0x100;
            x = g_db_prev->drawing.env.clip.x - dx;
            y = g_db_prev->drawing.env.clip.y - dir->word414 / 2 + 0x6C;
            for (; strip < dir->word414 / 8; strip++) {
                dst = buf;
                for (row = 0; row < 8; row++) {
                    for (col = 0; col < dir->word410; col++) {
                        *dst++ = clut[*src++];
                    }
                }
                rect.x = x;
                rect.y = y;
                y += 8;
                rect.w = dir->word410;
                rect.h = 8;
                LoadImage(&rect, buf);
                DrawSync(0);
            }
            Gpu_SwapBuffers();
        }
        D_8005C54C = 2;
        LIBC_Free(buf);
    }
    return -255;
}

/* Upload one 8x16 background tile cell and update its packed CLUT id. */
void Title_LoadSingleTile(EngineTileCell *cell)
{
    EngineGpuRect rect;

    if (cell->tile_x >= 0 && cell->tile_x < gp_title->word0C
        && cell->tile_y >= 0 && cell->tile_y < gp_title->word10) {
        cell->clut = *(u32 *)Ns_Lookup(
            &((u32 *)Ns_Lookup(&gp_title->word00)->items[0])[cell->tile_x + 0x6C]
        )->items[cell->tile_y];
        rect.x = 0x100 + (cell->page << 7) + (cell->x << 3);
        rect.y = (cell->y << 4) + 0x100;
        rect.w = 8;
        rect.h = 16;
        LoadImage(&rect, Ns_Lookup(
            &((u32 *)Ns_Lookup(&gp_title->word00)->items[0])[cell->tile_x + 0x6C]
        )->items[cell->tile_y] + 4);
    }
}

extern s32 D_800618BC[];
extern s32 g_cam_rot_xz;
void Gool_ExecStateCode(s32, s32, s32, s32, s32 *);

/* Finish the pending object request before selecting the next mode. */
__inline__ void Title_RequestState(s32 mode)
{
    s32 zero;

    if (gp_next_lid && D_800618BC[0]) {
        zero = 0;
        Gool_ExecStateCode(0, D_800618BC[0], 0xC00, 1, &zero);
        gp_use_cd = -1;
        gp_next_lid = 0;
    }
    g_cam_rot_xz = -256;
    D_800618D4 = mode;
    gp_title->word35D4 = mode;
    gp_title->word3598 = 5;
}
typedef struct EngineSprt16 {
    GpuPacketHeader header;
    s16 x, y;
    u8 u, v;
    u16 clut;
} EngineSprt16;

extern u32 g_cur_lid_ro;
void SetSprt16(GpuPacketHeader *);
void AddPrim(GpuPacketTag *, GpuPacketTag *);
void Gpu_DrawOverlay(s32);
void Title_CalcTiles(EngineMode25State *, s32, s32);
void Title_LoadImages(EngineMode25State *, s32, s32);


s32 Title_Update(GpuPacketTag *ot)
{
    char pad[32];
    s32 row;
    s32 col;
    EngineTileCell *cell;
    EngineSprt16 *sprt;
    EngineDrawModePacket *mode_pkt;

    switch ((u32)gp_title->word3598) {
    case 0:
        gp_title->word35A4 = 0;
        gp_title->word35A0 = 0;
    case 1: {
        extern s32 g_fade_counter[];
        g_cam_rot_xz = 0x120;
        g_fade_counter[0] |= 0xC;
        gp_title->word3598 = 6;
        if (g_fade_counter[0] & 0x20000) {
            Title_CalcTiles(gp_title, gp_title->word14, gp_title->word18);
            Title_LoadImages(gp_title, gp_title->word14, gp_title->word18);
        }
    }
        g_cam_rot_xz = 0x120;
        break;
    case 2:
        gp_title->word3598 = 6;
        g_cam_rot_xz = 0x120;
        break;
    }
    if ((g_cur_lid_ro & 0x20000) && gp_title->word359C) {
        row = 0;
        cell = gp_title->cells;
        do {
            col = 0;
            do {
                sprt = (EngineSprt16 *)g_ot_cur->word78;
                g_ot_cur->word78 = (s32)(sprt + 1);
                SetSprt16(&sprt->header);
                sprt->x = (cell->tile_x << 4) - gp_title->word14 - 0x100;
                sprt->y = (cell->tile_y << 4) - gp_title->word18 - 0x78;
                sprt->u = cell->x << 4;
                sprt->v = cell->y << 4;
                sprt->header.color[0] = 0x80;
                sprt->header.color[1] = 0x80;
                sprt->header.color[2] = 0x80;
                sprt->clut = gp_title->cluts[cell->clut];
                AddPrim(ot, (GpuPacketTag *)sprt);
                col++;
                mode_pkt = (EngineDrawModePacket *)g_ot_cur->word78;
                g_ot_cur->word78 = (s32)(mode_pkt + 1);
                *mode_pkt = gp_title->draw_modes[cell->page];
                cell++;
                AddPrim(ot, (GpuPacketTag *)mode_pkt);
            } while (col < 33);
            row++;
        } while (row < 16);
    }
    switch ((u32)gp_title->word3598) {
    case 3:
        break;
    case 5:
        if (g_cam_rot_xz == 0) {
            gp_title->word3598 = 7;
            {
                extern s32 g_fade_counter[1];
                g_fade_counter[0] &= ~0xC;
            }
            Gpu_DrawOverlay(0xFF);
        }
        break;
    case 6:
        if (g_cam_rot_xz == 0) {
            gp_title->word3598 = 3;
        }
        break;
    case 7:
        Gool_ForEachObjectHandle(Gool_ObjectHandleTraverseTreePostorder, Gool_ObjectTerminate, NULL);
        if (gp_title->word359C != 0) {
            Title_LoadEntries(gp_title->word35D0, 0, -1);
        }
        gp_title->word3598 = 1;
        gp_title->word35D0 = gp_title->word35D4;
        Gpu_DrawOverlay(0xFF);
        Title_LoadState();
        return 0;
    }
    if (D_800618D4 != gp_title->word35D4) {
        Title_RequestState(D_800618D4);
    }
    return 0;
}
/* Fill 16 rows by 33 columns of three-word coordinate/page entries. */
void Title_CalcUvs(u32 base_address)
{
    s32 simple_row;
    s32 right_half;
    s32 column;
    s32 y;
    s32 row;
    s32 page;
    s32 index;
    s32 x;
    s32 byte_offset;
    EngineTileCoords *entry;

    row = 0;
    do {
        column = 0;
        simple_row = row < 15;
        index = row;
next_column:
        if (simple_row) {
            if (column < 0x1E) {
                right_half = column >= 0xF;
                x = column + right_half;
                y = row;
                page = right_half;
            } else {
                x = row + 0x20;
                y = column - 0x1E;
                page = 2;
            }
        } else {
            page = 3;
            x = (column % 15) + 0x30;
            y = column / 15;
        }
        byte_offset = index * 3;
        column += 1;
        byte_offset = byte_offset << 2;
        entry = (EngineTileCoords *)(byte_offset + base_address);
        entry->x = x;
        entry->y = y;
        entry->page = page;
        index += 0x10;
        if (column < 0x21) {
            goto next_column;
        }
        row += 1;
    } while (row < 0x10);
}

s32 GetTPage(s32, s32, s32, s32);
void SetDrawMode(EngineDrawModePacket *, s32, s32, s32, EngineGpuRect *);

void Title_CalcTiles(EngineMode25State *state, s32 x, s32 y)
{
    EngineGpuRect rect;
    s32 row;
    s32 col;
    EngineTileCell *cell;
    s32 tx;
    s32 ty;

    Title_CalcUvs((u32)state->coords);
    state->word3560 = GetTPage(1, 1, 0x100, 0x100);
    state->word3562 = GetTPage(1, 1, 0x180, 0x100);
    state->word3564 = GetTPage(1, 1, 0x200, 0x100);
    state->word3566 = GetTPage(1, 1, 0x280, 0x100);
    rect.x = 0x100;
    rect.y = 0x100;
    rect.w = 0x100;
    rect.h = 0x100;
    SetDrawMode(&state->draw_modes[0], 1, 1, state->word3560, &rect);
    rect.x = 0x180;
    rect.y = 0x100;
    rect.w = 0x100;
    rect.h = 0x100;
    SetDrawMode(&state->draw_modes[1], 1, 1, state->word3562, &rect);
    rect.x = 0x200;
    rect.y = 0x100;
    rect.w = 0x100;
    rect.h = 0x100;
    SetDrawMode(&state->draw_modes[2], 1, 1, state->word3564, &rect);
    rect.x = 0x280;
    rect.y = 0x100;
    rect.w = 0x100;
    rect.h = 0x100;
    SetDrawMode(&state->draw_modes[3], 1, 1, state->word3566, &rect);
    tx = x >> 4;
    ty = y >> 4;
    for (row = 0; row < 16; row++) {
        for (col = 0; col < 33; col++) {
            cell = &state->cells[(col << 4) + row];
            cell->tile_x = tx + col;
            cell->tile_y = ty + row;
            cell->x = state->coords[(col << 4) + row].x;
            cell->y = state->coords[(col << 4) + row].y;
            cell->page = state->coords[(col << 4) + row].page;
        }
    }
}

void Title_LoadImages(EngineMode25State *state, s32 x, s32 y)
{
    EngineGpuRect rect;
    s32 row;
    s32 col;
    EngineTileCell *cell;
    s32 coord_x;
    s32 coord_y;

    DrawSync(0);
    for (row = 0; row < 16; row++) {
        for (col = 0; col < 33; col++) {
            if ((x >> 4) + col < gp_title->word0C
                && (y >> 4) + row < gp_title->word10) {
                cell = &state->cells[(col << 4) + row];
                cell->off_x = x + (col << 4);
                cell->off_y = y + (row << 4);
                cell->clut = *(u32 *)Ns_Lookup(
                    &((u32 *)Ns_Lookup(&gp_title->word00)->items[0])[(x >> 4) + col + 0x6C]
                )->items[(y >> 4) + row];
                coord_x = state->coords[(col << 4) + row].x;
                coord_y = state->coords[(col << 4) + row].y;
                rect.w = 8;
                rect.h = 16;
                rect.x = (coord_x << 3) + 0x100;
                rect.y = (coord_y << 4) + 0x100;
                LoadImage(&rect, Ns_Lookup(
                    &((u32 *)Ns_Lookup(&gp_title->word00)->items[0])[(x >> 4) + col + 0x6C]
                )->items[(y >> 4) + row] + 4);
            }
        }
    }
}

typedef struct EngineClutSpan {
    s32 x;
    s32 y;
    s32 count;
} EngineClutSpan;

typedef struct EngineMapHeader {
    s32 count00;
    s32 word04;
    s32 clut_count;
    s32 word0C;
    s32 word10;
    s32 count14;
    EngineClutSpan spans[8];
    s32 pages[46][1];
    s32 words130[32];
    s32 words1B0[32];
} EngineMapHeader;

static __inline__ s32 engine_resource_adjust(s32 *resource, s32 argument, s32 count)
{
    if (*resource != 0x6396347F) {
        if (count > 0) {
            return Ns_Open(resource, argument, count);
        } else {
            Ns_Close(resource, -count);
        }
    }
    return 0;
}

static __inline__ void engine_update_slot_state(s32 slot, s32 active)
{
    if (active) {
        Ns_TexturePageFree(slot);
        g_slst_buf1[slot].state = 30;
    } else if (g_slst_buf1[slot].state == 30) {
        g_slst_buf1[slot].state = 1;
    }
}

s32 Ns_AlphaNumChar(s32);
u16 LoadClut(void *, s32, s32);
void Gfx_TgeoOnLoad(void *);

void Title_LoadEntries(s32 mode, s32 arg1, s32 count)
{
    char name[16];
    s32 ref;
    ResourceItemListView *list;
    EngineMapHeader *header;
    EngineClutSpan *span;
    s32 span_offset;
    s32 clut_count;
    s32 i;
    s32 end;
    s32 page_idx;
    u8 *clut_data;
    EngineState *entry;

    *(EngineByteRecord *)name = *(EngineByteRecord *)gp_mdat_default_name;
    name[0] = Ns_AlphaNumChar(mode);
    ref = Ns_StringToEID((u8 *)name);
    engine_resource_adjust(&ref, arg1, count);
    list = Ns_Lookup((u32 *)&ref);
    header = (EngineMapHeader *)list->items[0];
    if (count > 0) {
        span = header->spans;
        span_offset = 0;
        clut_count = header->clut_count;
        for (i = 0; i < clut_count;) {
            ref = header->pages[i / 120][0];
            engine_resource_adjust(&ref, arg1, count);
            if (clut_count - i < 120) {
                end = clut_count;
            } else {
                end = i + 120;
            }
            for (; i < end; i++, span_offset++) {
                page_idx = i / 120;
                clut_data = Ns_Lookup((u32 *)&((EngineMapHeader *)list->items[0])->pages[page_idx][0])->items[i % 120];
                if (span_offset >= span->count) {
                    span++;
                    span_offset = 0;
                }
                gp_title->cluts[i] = LoadClut(clut_data, span->x, span_offset + span->y);
            }
            engine_resource_adjust(&ref, arg1, -count);
        }
        Ns_TexturePageFree(9);
        g_slst_buf1[9].state = 30;
        Ns_TexturePageFree(10);
        g_slst_buf1[10].state = 30;
        Ns_TexturePageFree(13);
        g_slst_buf1[13].state = 30;
        engine_update_slot_state(8, clut_count > 160);
        engine_update_slot_state(12, clut_count > 288);
        engine_update_slot_state(14, clut_count > 416);
    }
    for (i = 0; i < header->count00; i++) {
        engine_resource_adjust(&header->words1B0[i], arg1, count);
    }
    for (i = 0; i < header->count14; i++) {
        entry = (EngineState *)engine_resource_adjust(&header->words130[i], arg1, count);
        if (arg1 != 0 && count > 0 && entry->word08 == 2) {
            Gfx_TgeoOnLoad(entry);
        }
    }
}
void Slst_Noop1(void)
{
}
#include "engine/Slst_NoopWrapper.c"
void Slst_Noop2(void *a, void *b, void *c, u32 color)
{
}
void Slst_Noop3(void)
{
}

