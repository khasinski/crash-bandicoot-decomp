/* GCC_VERSION: 2.6.3 */
/* ASPSX_VERSION: 2.21 */
/* GNU_AS_G: 0 */
#include "common.h"

typedef void (*CdCallback)(s32, u8 *);

typedef struct {
    u8 sync;
    u8 ready;
    u8 data;
    u8 pad[13];
} CdStatus;

typedef struct {
    s32 ack_clear[32];
    s32 unused[32];
    s32 param_count[32];
} CdCmdTable;



extern CdCmdTable D_800556E4;
extern volatile u8 *g_cd_reg0;
extern volatile u8 *D_80055868;
extern volatile u8 *D_8005586C;
extern volatile CdStatus g_cd_status;

s32 VSync(s32);
s32 BIOS_Printf(const char *, ...);
s32 puts(const char *, ...);
s32 CheckCallback(void);
s32 getintr(void);
void CD_initvol(void);

static inline void cd_set_timeout(const char *name)
{
    D_800571B0 = VSync(-1) + 0x1E0;
    D_800571B4 = 0;
    D_800571B8[0] = name;
}

static inline s32 cd_check_timeout(void)
{
    if (VSync(-1) > D_800571B0 || D_800571B4++ > 0x1E0000) {
        puts(D_800114F8);
        BIOS_Printf(D_80011508, D_800571B8[0], D_800555C4[D_800555C1[0]], D_80055644[g_cd_status.sync], D_80055644[g_cd_status.ready]);
        CD_initvol();
        return -1;
    }
    return 0;
}

static inline void cd_poll_interrupts(void)
{
    s32 event;
    u8 bank = *g_cd_reg0 & 3;
    while ((event = getintr()) != 0) {
        if ((event & 4) && D_800555A4 != NULL) {
            D_800555A4(g_cd_status.ready, D_800571A0);
        }
        if ((event & 2) && g_cd_sync_cb != NULL) {
            g_cd_sync_cb(g_cd_status.sync, D_80057198);
        }
    }
    *g_cd_reg0 = bank;
}

static inline void cd_publish_response(u8 *dst, u8 *src)
{
    s32 count;
    if (dst != NULL) {
        s32 end;
        count = 7;
        end = -1;
        do {
            u8 val = *src++;
            count--;
            *dst++ = val;
        } while (count != end);
    }
}

s32 CD_sync(s32 mode, u8 *result)
{
    s32 status;
    cd_set_timeout(D_80011580);
    do {
        if (cd_check_timeout() != 0) {
            return -1;
        }
        if (CheckCallback() != 0) {
            cd_poll_interrupts();
        }
        status = g_cd_status.sync;
        if (status == 2 || status == 5) {
            g_cd_status.sync = 2;
            cd_publish_response(result, D_80057198);
            return status;
        }
    } while (mode == 0);
    return 0;
}

s32 CD_ready(s32 mode, u8 *result)
{
    s32 status;
    cd_set_timeout(D_80011588);
    do {
        if (cd_check_timeout() != 0) {
            return -1;
        }
        if (CheckCallback() != 0) {
            cd_poll_interrupts();
        }
        status = g_cd_status.data;
        if (status != 0) {
            g_cd_status.data = 0;
            cd_publish_response(result, D_800571A8);
            return status;
        }
        status = g_cd_status.ready;
        if (status != 0) {
            g_cd_status.ready = 0;
            cd_publish_response(result, D_800571A0);
            return status;
        }
    } while (mode == 0);
    return 0;
}

s32 CD_cw(u8 com, u8 *param, u8 *result, s32 arg3)
{
    s32 i;
    if (D_800555AC >= 2) {
        BIOS_Printf(D_80011594, D_800555C4[com]);
    }
    if (D_800556E4.param_count[com] != 0 && param == NULL) {
        if (D_800555AC > 0) {
            BIOS_Printf(D_8001159C, D_800555C4[com]);
        }
        return -2;
    }
    CD_sync(0, NULL);
    if (com == 2) {
        for (i = 0; i < 4; i++) {
            D_800555BC[i] = param[i];
        }
    }
    g_cd_status.sync = 0;
    if (D_800556E4.ack_clear[com] != 0) {
        g_cd_status.ready = 0;
    }
    *g_cd_reg0 = 0;
    for (i = 0; i < D_800556E4.param_count[com]; i++) {
        *D_8005586C = param[i];
    }
    D_800555C1[0] = com;
    *D_80055868 = com;
    if (arg3 != 0) {
        return 0;
    }
    cd_set_timeout(D_800115AC);
    while (g_cd_status.sync == 0) {
        if (cd_check_timeout() != 0) {
            return -1;
        }
        if (CheckCallback() != 0) {
            cd_poll_interrupts();
        }
    }
    if (g_cd_status.sync == 2 && com == 0x0E) {
        D_800555C0 = *param;
    }
    cd_publish_response(result, D_80057198);
    return -(g_cd_status.sync == 5);
}
