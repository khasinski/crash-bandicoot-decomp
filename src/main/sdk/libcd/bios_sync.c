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
    g_cd_timeout_deadline = VSync(-1) + 0x1E0;
    g_cd_timeout_ticks = 0;
    g_cd_timeout_cmd_name[0] = name;
}

static inline s32 cd_check_timeout(void)
{
    if (VSync(-1) > g_cd_timeout_deadline || g_cd_timeout_ticks++ > 0x1E0000) {
        puts(g_str_bios_com_cd_timeout);
        BIOS_Printf(g_str_bios_com_s_s_sync_s, g_cd_timeout_cmd_name[0], g_cd_com_str_ptrs[g_cd_com_flags_tab[0]], g_cd_intr_str_ptrs[g_cd_status.sync], g_cd_intr_str_ptrs[g_cd_status.ready]);
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
        if ((event & 4) && g_cd_ready_cb != NULL) {
            g_cd_ready_cb(g_cd_status.ready, g_cd_ready_result_buf);
        }
        if ((event & 2) && g_cd_sync_cb != NULL) {
            g_cd_sync_cb(g_cd_status.sync, g_cd_sync_result_buf);
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
    cd_set_timeout(g_str_cd_com_sync);
    while (1) {
        if (cd_check_timeout() != 0) {
            return;
        }
        if (CheckCallback() != 0) {
            cd_poll_interrupts();
        }
        cd_publish_response(result, g_cd_ready_result_buf);
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
    cd_set_timeout(g_str_cd_com_ready);
    do {
        if (cd_check_timeout() != 0) {
            return -1;
        }
        if ((*g_spu_attr_zero_1 & 0x01000000) == 0) {
            ret = 0;
            goto done;
        }
    } while (mode == 0);
    ret = 1;
done:
    return ret;
}
