#include "common.h"
#include "gpu.h"

/* GCC_VERSION: 2.6.3 */

typedef struct {
    u8 version;
    volatile u8 mode;
    u8 debug;
    u8 reverse;
    s16 w;
    s16 h;
    volatile s32 active;
    void (* volatile callback)(void);
} GpuState;

extern GpuState g_gpu_mode;

/* --- _addque2 & _exeque --- */

typedef struct {
    void (*func)(void *, s32);
    void *buf;
    s32 arg;
    u32 data[21];
} GpuQueueEntry;

typedef struct {
    void (*func)(void *, s32);
    void *buf;
    s32 arg;
} GpuActiveEntry;

extern volatile GpuActiveEntry D_80054B60;

extern volatile GpuQueueEntry D_8005E74C[64];

s32 DMACallback(s32, void *);
s32 SetIntrMask(s32);
s32 _exeque(void);
void set_alarm(void);
s32 get_alarm(void);

s32 _addque2(void (*func)(void *, s32), u32 *buf, s32 size, s32 arg)
{
    s32 i;
    u32 *src;

    set_alarm();
    while (((g_gpu_q_write + 1) & 0x3F) == g_gpu_q_read) {
        if (get_alarm() != 0) {
            return -1;
        }
        _exeque();
    }

    D_80054B78[0] = SetIntrMask(0);
    g_gpu_mode.active = 1;
    if (g_gpu_mode.mode == 0 ||
        (g_gpu_q_write == g_gpu_q_read && !(*D_80054B4C & 0x01000000) && g_gpu_mode.callback == 0)) {
        while (!(*g_gpu_stat_reg & 0x04000000)) {
        }
        func(buf, arg);
        D_80054B60.func = func;
        D_80054B60.buf = buf;
        D_80054B60.arg = arg;
        SetIntrMask(D_80054B78[0]);
        return 0;
    }

    DMACallback(2, _exeque);
    if (size != 0) {
        for (i = 0; i < size / 4; i++) {
            D_8005E74C[g_gpu_q_write].data[i] = buf[i];
        }
        D_8005E74C[g_gpu_q_write].buf = (void *)D_8005E74C[g_gpu_q_write].data;
    } else {
        D_8005E74C[g_gpu_q_write].buf = buf;
    }
    D_8005E74C[g_gpu_q_write].arg = arg;
    D_8005E74C[g_gpu_q_write].func = func;
    g_gpu_q_write = (g_gpu_q_write + 1) & 0x3F;
    SetIntrMask(D_80054B78[0]);
    _exeque();
    return (g_gpu_q_write - g_gpu_q_read) & 0x3F;
}

s32 _exeque(void)
{
    if (*D_80054B4C & 0x01000000) {
        return 1;
    }
    D_80054B7C[0] = SetIntrMask(0);
    while (g_gpu_q_write != g_gpu_q_read && !(*D_80054B4C & 0x01000000)) {
        if (((g_gpu_q_read + 1) & 0x3F) == g_gpu_q_write && g_gpu_mode.callback == 0) {
            DMACallback(2, 0);
        }
        while (!(*g_gpu_stat_reg & 0x04000000)) {
        }
        D_8005E74C[g_gpu_q_read].func(D_8005E74C[g_gpu_q_read].buf, D_8005E74C[g_gpu_q_read].arg);
        D_80054B60.func = D_8005E74C[g_gpu_q_read].func;
        D_80054B60.buf = D_8005E74C[g_gpu_q_read].buf;
        D_80054B60.arg = D_8005E74C[g_gpu_q_read].arg;
        g_gpu_q_read = (g_gpu_q_read + 1) & 0x3F;
    }
    SetIntrMask(D_80054B7C[0]);
    if (g_gpu_q_write == g_gpu_q_read && !(*D_80054B4C & 0x01000000) && g_gpu_mode.active && g_gpu_mode.callback) {
        g_gpu_mode.active = 0;
        g_gpu_mode.callback();
    }
    return (g_gpu_q_write - g_gpu_q_read) & 0x3F;
}

