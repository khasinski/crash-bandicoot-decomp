/* GCC_VERSION: 2.6.3 */
/* CC1_FLAGS: -O2 */
/* GNU_AS_G: 4 */
#include "common.h"
extern s32 g_draw_stamp;
#include "gpu.h"

/* =========================================================================
 * 1. Gpu_Update (asm/USA/main/text_765C.s)
 * ========================================================================= */

typedef struct RenderBufferFull {
    u32 word00;
    GpuDisplayEnv display;
    GpuDrawing drawing;
    s32 word74;
    s32 word78;
    u32 word7C;
    u32 word80;
    s32 word84;
    u32 ordering_table[0x800];
} RenderBufferFull;

typedef struct {
    u8 bytes[4];
} BufferToken;

extern BufferToken D_80057968[];
extern BufferToken D_8005796C;
extern struct { s32 v, pad; } gp_next_lid;
extern u32 g_cur_lid_ro;
extern u32 g_fade_counter;
extern s32 g_cam_rot_xz[];
extern s32 D_8005C54C[];
extern struct { RenderBufferFull *buf; } g_db_cur;
extern RenderBufferFull *g_db_prev;
extern RenderBufferFull *g_ot_cur;

s32 gp_rcnt_stopped = 0;
extern s32 *gp_cur_pbak_header;

typedef struct ZoneHeader8214 {
    u8 pad00[0x2E0];
    s32 word2E0;
    u8 pad2E4[0x18];
    u32 flags2FC;
    u8 pad300[0x10];
    u8 r310;
    u8 g311;
    u8 b312;
    u8 pad313;
    u8 r314;
    u8 g315;
    u8 b316;
} ZoneHeader8214;

typedef struct ZoneEntry8214 {
    u8 pad00[0x10];
    ZoneHeader8214 *header;
} ZoneEntry8214;

extern ZoneEntry8214 *g_pads[];

void Gpu_DrawOverlay(u32);
void Gpu_DrawRect(s32, s32, s32, s32, u8, u8, u8);
void Audio_Update(void);
void DrawSync(s32);
s32 VSync(s32);
void EnterCriticalSection(void);
void StopRCnt(u32);
void StartRCnt(u32);
void ExitCriticalSection(void);
void Card_Update(void);
s32 Gfx_TgeoGetTexinfoArray(s32);
void *PutDispEnv(GpuDisplayEnv *);
void *PutDrawEnv(GpuDrawing *);
void DrawOTag(u32 *);
void Gpu_RResetOT(void *, s32);

static __inline__ BufferToken *func_80016E28_inline(void)
{
    D_80057968[0] = D_8005796C;
    (void)frame_counter;
    return &D_80057968[0];
}

void Gpu_Update(void)
{
    BufferToken *token;
    RenderBufferFull *swap;

    token = func_80016E28_inline();
    if (gp_next_lid.v == 0 && (g_cur_lid_ro & 0x1000)) {
        g_draw_stamp++;
    }
    if (g_cam_rot_xz[0] != 0) {
        if (g_cam_rot_xz[0] > 0) {
            g_cam_rot_xz[0] -= D_80061A38;
            Gpu_DrawOverlay(g_cam_rot_xz[0]);
        } else if (g_cam_rot_xz[0] >= -2) {
            Gpu_DrawOverlay(0x100);
            g_cam_rot_xz[0] = -1;
        } else {
            g_cam_rot_xz[0] += D_80061A38;
            Gpu_DrawOverlay(g_cam_rot_xz[0] + 0x100);
            if (g_cam_rot_xz[0] == 0 && !(g_cur_lid_ro & 0x200000)) {
                g_cam_rot_xz[0] = -2;
            }
        }
    }
    if (!(g_cur_lid_ro & 0x80000)) {
        if (g_cur_lid_ro & 0x2000) {
            Gpu_DrawRect(0, 0, 0x200, g_pads[0]->header->word2E0, token->bytes[0], token->bytes[1], token->bytes[2]);
            Gpu_DrawRect(0, g_pads[0]->header->word2E0, 0x200, 0xD8 - g_pads[0]->header->word2E0, g_pads[0]->header->r310, g_pads[0]->header->g311, g_pads[0]->header->b312);
        } else {
            Gpu_DrawRect(0, 0, 0x200, 0xD8, 0, 0, 0);
        }
    }
    Audio_Update();
    g_db_prev->word80 = frame_counter;
    DrawSync(0);
    if (D_80061A30 == 0) {
        g_box_count = frame_counter - g_db_prev->word7C;
    } else {
        g_box_count = 0x11;
    }
    if (D_8005C54C[0] == 0) {
        swap = g_db_prev;
        g_db_cur.buf = swap;
        g_db_prev = g_ot_cur;
        g_ot_cur = swap;
    }
    VSync(0);
    if ((u32)(frame_counter - g_db_cur.buf->word7C) < 0x19) {
        VSync(0);
    }
    if (g_cur_lid_ro & 0x100000) {
        if (!gp_rcnt_stopped) {
            EnterCriticalSection();
            StopRCnt(0xF2000002);
            ExitCriticalSection();
        }
        gp_rcnt_stopped = 1;
        Card_Update();
        frame_counter += 0x22;
    } else {
        if (gp_rcnt_stopped) {
            EnterCriticalSection();
            StartRCnt(0xF2000002);
            ExitCriticalSection();
        }
        gp_rcnt_stopped = 0;
    }
    EnterCriticalSection();
    if (D_80061A30 == 2) {
        frame_counter = *gp_cur_pbak_header;
    }
    g_db_prev->word7C = frame_counter;
    ExitCriticalSection();
    g_db_cur.buf->word84 = Gfx_TgeoGetTexinfoArray(g_db_prev->word7C - g_db_cur.buf->word7C);
    PutDispEnv(&g_db_cur.buf->display);
    PutDrawEnv(&g_db_prev->drawing);
    if (D_8005C54C[0] > 0) {
        D_8005C54C[0]--;
    }
    if (D_8005C54C[0] == 0) {
        DrawOTag(g_db_prev->ordering_table);
    }
    g_ot_cur->word78 = g_ot_cur->word74;
    Gpu_RResetOT(g_ot_cur->ordering_table, 0x800);
    g_cur_lid_ro = g_fade_counter;
}

