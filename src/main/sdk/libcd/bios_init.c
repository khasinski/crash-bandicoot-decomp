/* GCC_VERSION: 2.6.3 */
/* ASPSX_VERSION: 2.21 */
/* GNU_AS_G: 0 */
#include "common.h"

typedef void (*CdCallback)(s32, u8 *);

typedef struct CdReadState {
    volatile s32 state;
    s32 buffer;
    s32 count;
    volatile s32 cursor;
    volatile s32 mode;
    s32 size;
    volatile s32 remaining;
    s32 time;
    CdCallback word20;
    CdCallback word24;
} CdReadState;
extern CdReadState g_cd_read_state;

typedef struct {
    u8 sync;
    u8 ready;
    u8 data;
    u8 pad[13];
} CdStatus;


extern volatile u8 *g_cd_reg0;
extern volatile u8 *D_8005586C;
extern volatile u8 *D_80055870;

extern volatile CdStatus g_cd_status;


s32 VSync(s32);
s32 BIOS_Printf(const char *, ...);
s32 puts(const char *, ...);
s32 ResetCallback(void);
s32 InterruptCallback(s32, void (*)(void));
s32 CD_sync(s32, u8 *);
s32 CD_cw(u8, u8 *, u8 *, s32);
void cd_callback(void);
void cb_read(s32, u8 *);

static inline void cd_sync_disc(void)
{
    CdCallback saved_callback;
    s32 poll_count = 0;

    if (D_800558A8 < D_800555B8) {
        saved_callback = g_cd_sync_cb;
        g_cd_sync_cb = NULL;
        while (D_800555B0 & 0x10) {
            if ((poll_count++ & 0xFF) == 0) {
                puts(D_800115B4);
            }
            CD_cw(1, NULL, NULL, 0);
        }
        while (CD_cw(0x16, D_800558AC, NULL, 0) != 0) {
            CD_cw(1, NULL, NULL, 0);
            puts(D_800115C4);
        }
        g_cd_sync_cb = saved_callback;
        D_800558A8 = D_800555B8;
    }
}

static inline void cd_reset_hw(void)
{
    *g_cd_reg0 = 1;
    while (*D_80055870 & 7) {
        *g_cd_reg0 = 1;
        *D_80055870 = 7;
        *D_8005586C = 7;
    }
    D_800555C0 = 0;
    g_cd_status.ready = (g_cd_status.data = 0);
    g_cd_status.sync = 2;
    *g_cd_reg0 = 0;
    *D_80055870 = 0;
    *D_80055874 = 0x1325;
}

static inline void cd_init_callbacks(void)
{
    s32 *ptr = (s32 *)&g_cd_read_state;
    s32 count = 9;
    D_800555A4 = NULL;
    g_cd_sync_cb = NULL;
    D_800555B4 = 0;
    D_800555B0 = 0;
    do {
        *ptr = 0;
        count--;
        ptr++;
    } while (count != -1);
    ResetCallback();
    InterruptCallback(2, &cd_callback);
}

s32 CD_reset(void)
{
    puts(D_80011608);
    BIOS_Printf(D_80011614, D_800558B0);
    D_800555C1[0] = 0;
    D_800555C0 = 0;
    cd_init_callbacks();
    cd_reset_hw();
    CD_cw(1, NULL, NULL, 0);
    if (D_800555B0 & 0x10) {
        CD_cw(1, NULL, NULL, 0);
    }
    cd_sync_disc();
    if (CD_cw(0x0A, NULL, NULL, 0) != 0) {
        return -1;
    }
    if (CD_cw(0x0C, NULL, NULL, 0) != 0) {
        return -1;
    }
    return -(CD_sync(0, NULL) != 2);
}

s32 CD_read(void)
{
    u8 mode;
    D_800555A4 = NULL;
    g_cd_sync_cb = NULL;
    while (g_cd_read_state.state-- > 0) {
        if (g_cd_read_state.state < 7) {
            puts(D_80011620);
            BIOS_Printf(D_80011630, g_cd_read_state.state, D_800555BC[0], D_800555BC[1], D_800555BC[2]);
            cd_sync_disc();
            if (CD_cw(9, NULL, NULL, 0) != 0) {
                continue;
            }
            if (CD_cw(2, D_800555BC, NULL, 0) != 0) {
                continue;
            }
        }
        cd_reset_hw();
        if ((mode = g_cd_read_state.mode) != D_800555C0) {
            if (CD_cw(0x0E, &mode, NULL, 0) != 0) {
                continue;
            }
        }
        D_800555A4 = cb_read;
        g_cd_read_state.cursor = g_cd_read_state.count;
        CD_cw(6, NULL, NULL, 1);
        g_cd_read_state.remaining = g_cd_read_state.buffer;
        g_cd_read_state.time = VSync(-1) + 0x1E0;
        return g_cd_read_state.remaining;
    }
    return g_cd_read_state.remaining = -1;
}
