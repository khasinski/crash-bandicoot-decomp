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
extern volatile CdStatus g_cd_status;

s32 VSync(s32);
s32 BIOS_Printf(const char *, ...);
s32 puts(const char *, ...);
s32 CheckCallback(void);
s32 getintr(void);
void CD_initvol(void);
s32 CD_read(void);
s32 CD_datasync(s32);

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

s32 CD_readsync(s32 mode, u8 *result)
{
    cd_set_timeout(D_8001164C);
    while (1) {
        if (cd_check_timeout() != 0) {
            return;
        }
        if (CheckCallback() != 0) {
            cd_poll_interrupts();
        }
        cd_publish_response(result, D_800571A0);
        if (VSync(-1) > g_cd_read_state.time + 0x3C) {
            CD_read();
        }
        if (g_cd_read_state.remaining == 0) {
            CD_datasync(0);
        }
        if (mode == 0 && g_cd_read_state.remaining > 0) {
            continue;
        }
        return g_cd_read_state.remaining;
    }
}

s32 CD_datasync(s32 mode)
{
    s32 ret;
    cd_set_timeout(D_80011654);
    do {
        if (cd_check_timeout() != 0) {
            return -1;
        }
        if ((*D_800558D8 & 0x01000000) == 0) {
            ret = 0;
            goto done;
        }
    } while (mode == 0);
    ret = 1;
done:
    return ret;
}
