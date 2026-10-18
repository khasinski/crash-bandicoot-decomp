#include "common.h"

/* GCC_VERSION: 2.6.3 */

typedef void (*Callback)(void);

typedef struct {
    u16 initialized;
    u16 in_interrupt;
    Callback callbacks[11];
    u16 mask;
    u16 saved_imask;
    s32 saved_dpcr;
    u32 context[12];
    u32 stack[0x3F0];
} IntrState;

extern IntrState D_80053934;

s32 func_8003D730(const char *, ...);
void func_8003E1F8(void);
void func_8003E4E0(s32);
void func_8003E6E4(s32, s32);
void func_8003EE24(void);
void func_8003EE34(void);

void func_8003E968(void)
{
    u16 pending;
    s32 i;

    if (D_80053934.initialized == 0) {
        func_8003D730(D_80011034, *D_800549C0);
        func_8003EE24();
    }
    D_80053934.in_interrupt = 1;
    pending = (D_80053934.mask & *D_800549C0) & *D_800549C4;
    while (pending != 0) {
        for (i = 0; pending != 0; i++, pending >>= 1) {
            if (i >= 11) {
                break;
            }
            if (pending & 1) {
                *D_800549C0 = ~(1 << i);
                if (D_80053934.callbacks[i] != NULL) {
                    D_80053934.callbacks[i]();
                }
            }
        }
        pending = (D_80053934.mask & *D_800549C0) & *D_800549C4;
    }
    if ((*D_800549C0 & *D_800549C4) != 0) {
        if (D_800549CC++ > 0x800) {
            func_8003D730(D_80011050, *D_800549C0, *D_800549C4);
            D_800549CC = 0;
            *D_800549C0 = 0;
        }
    } else {
        D_800549CC = 0;
    }
    D_80053934.in_interrupt = 0;
    func_8003EE24();
}

Callback func_8003EB50(s32 index, Callback callback)
{
    Callback previous = D_80053934.callbacks[index];
    s32 imask;

    if (callback != previous && D_80053934.initialized != 0) {
        imask = *D_800549C4;
        *D_800549C4 = 0;
        if (callback != NULL) {
            imask |= 1 << index;
            D_80053934.callbacks[index] = callback;
            D_80053934.mask |= 1 << index;
        } else {
            imask &= ~(1 << index);
            D_80053934.callbacks[index] = NULL;
            D_80053934.mask &= ~(1 << index);
        }
        if (index == 0) {
            func_8003E4E0(callback == NULL);
            func_8003E6E4(3, callback == NULL);
        }
        if (index == 4) {
            func_8003E6E4(0, callback == NULL);
        }
        if (index == 5) {
            func_8003E6E4(1, callback == NULL);
        }
        if (index == 6) {
            func_8003E6E4(2, callback == NULL);
        }
        *D_800549C4 = imask;
    }
    return previous;
}

void *func_8003ECA4(void)
{
    void *result;

    if (D_80053934.initialized != 0) {
        func_8003E1F8();
        D_80053934.saved_imask = *D_800549C4;
        D_80053934.saved_dpcr = *D_800549C8;
        *D_800549C0 = *D_800549C4 = 0;
        *D_800549C8 &= 0x77777777;
        func_8003EE34();
        D_80053934.initialized = 0;
        result = &D_80053934;
    } else {
        result = NULL;
    }
    return result;
}
