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

extern GpuState D_80054A6C;


/* --- func_80042000 & func_800422E4 --- */

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

extern volatile u32 *D_80054B40;
extern volatile u32 *D_80054B4C;
extern volatile GpuActiveEntry D_80054B60;
extern volatile s32 D_80054B70;
extern volatile s32 D_80054B74;
extern s32 D_80054B78[];
extern s32 D_80054B7C[];
extern volatile GpuQueueEntry D_8005E74C[64];

s32 func_8003E754(s32, void *);
s32 func_8003E870(s32);
s32 func_800422E4(void);
void func_80042864(void);
s32 func_80042898(void);

s32 func_80042000(void (*func)(void *, s32), u32 *buf, s32 size, s32 arg)
{
    s32 i;
    u32 *src;

    func_80042864();
    while (((D_80054B70 + 1) & 0x3F) == D_80054B74) {
        if (func_80042898() != 0) {
            return -1;
        }
        func_800422E4();
    }

    D_80054B78[0] = func_8003E870(0);
    D_80054A6C.active = 1;
    if (D_80054A6C.mode == 0 ||
        (D_80054B70 == D_80054B74 && !(*D_80054B4C & 0x01000000) && D_80054A6C.callback == 0)) {
        while (!(*D_80054B40 & 0x04000000)) {
        }
        func(buf, arg);
        D_80054B60.func = func;
        D_80054B60.buf = buf;
        D_80054B60.arg = arg;
        func_8003E870(D_80054B78[0]);
        return 0;
    }

    func_8003E754(2, func_800422E4);
    if (size != 0) {
        for (i = 0; i < size / 4; i++) {
            D_8005E74C[D_80054B70].data[i] = buf[i];
        }
        D_8005E74C[D_80054B70].buf = (void *)D_8005E74C[D_80054B70].data;
    } else {
        D_8005E74C[D_80054B70].buf = buf;
    }
    D_8005E74C[D_80054B70].arg = arg;
    D_8005E74C[D_80054B70].func = func;
    D_80054B70 = (D_80054B70 + 1) & 0x3F;
    func_8003E870(D_80054B78[0]);
    func_800422E4();
    return (D_80054B70 - D_80054B74) & 0x3F;
}

s32 func_800422E4(void)
{
    if (*D_80054B4C & 0x01000000) {
        return 1;
    }
    D_80054B7C[0] = func_8003E870(0);
    while (D_80054B70 != D_80054B74 && !(*D_80054B4C & 0x01000000)) {
        if (((D_80054B74 + 1) & 0x3F) == D_80054B70 && D_80054A6C.callback == 0) {
            func_8003E754(2, 0);
        }
        while (!(*D_80054B40 & 0x04000000)) {
        }
        D_8005E74C[D_80054B74].func(D_8005E74C[D_80054B74].buf, D_8005E74C[D_80054B74].arg);
        D_80054B60.func = D_8005E74C[D_80054B74].func;
        D_80054B60.buf = D_8005E74C[D_80054B74].buf;
        D_80054B60.arg = D_8005E74C[D_80054B74].arg;
        D_80054B74 = (D_80054B74 + 1) & 0x3F;
    }
    func_8003E870(D_80054B7C[0]);
    if (D_80054B70 == D_80054B74 && !(*D_80054B4C & 0x01000000) && D_80054A6C.active && D_80054A6C.callback) {
        D_80054A6C.active = 0;
        D_80054A6C.callback();
    }
    return (D_80054B70 - D_80054B74) & 0x3F;
}

