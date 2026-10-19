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

extern IntrState g_event_handlers;

s32 BIOS_Printf(const char *, ...);
void EnterCriticalSection(void);
void ChangeClearPAD(s32);
void ChangeClearRCnt(s32, s32);
void ReturnFromException(void);
void ResetEntryInt(void);

void trapIntr(void)
{
    u16 pending;
    s32 i;

    if (g_event_handlers.initialized == 0) {
        BIOS_Printf(D_80011034, *D_800549C0);
        ReturnFromException();
    }
    g_event_handlers.in_interrupt = 1;
    pending = (g_event_handlers.mask & *D_800549C0) & *D_800549C4;
    while (pending != 0) {
        for (i = 0; pending != 0; i++, pending >>= 1) {
            if (i >= 11) {
                break;
            }
            if (pending & 1) {
                *D_800549C0 = ~(1 << i);
                if (g_event_handlers.callbacks[i] != NULL) {
                    g_event_handlers.callbacks[i]();
                }
            }
        }
        pending = (g_event_handlers.mask & *D_800549C0) & *D_800549C4;
    }
    if ((*D_800549C0 & *D_800549C4) != 0) {
        if (D_800549CC++ > 0x800) {
            BIOS_Printf(D_80011050, *D_800549C0, *D_800549C4);
            D_800549CC = 0;
            *D_800549C0 = 0;
        }
    } else {
        D_800549CC = 0;
    }
    g_event_handlers.in_interrupt = 0;
    ReturnFromException();
}

Callback setIntr(s32 index, Callback callback)
{
    Callback previous = g_event_handlers.callbacks[index];
    s32 imask;

    if (callback != previous && g_event_handlers.initialized != 0) {
        imask = *D_800549C4;
        *D_800549C4 = 0;
        if (callback != NULL) {
            imask |= 1 << index;
            g_event_handlers.callbacks[index] = callback;
            g_event_handlers.mask |= 1 << index;
        } else {
            imask &= ~(1 << index);
            g_event_handlers.callbacks[index] = NULL;
            g_event_handlers.mask &= ~(1 << index);
        }
        if (index == 0) {
            ChangeClearPAD(callback == NULL);
            ChangeClearRCnt(3, callback == NULL);
        }
        if (index == 4) {
            ChangeClearRCnt(0, callback == NULL);
        }
        if (index == 5) {
            ChangeClearRCnt(1, callback == NULL);
        }
        if (index == 6) {
            ChangeClearRCnt(2, callback == NULL);
        }
        *D_800549C4 = imask;
    }
    return previous;
}

void *stopIntr(void)
{
    void *result;

    if (g_event_handlers.initialized != 0) {
        EnterCriticalSection();
        g_event_handlers.saved_imask = *D_800549C4;
        g_event_handlers.saved_dpcr = *D_800549C8;
        *D_800549C0 = *D_800549C4 = 0;
        *D_800549C8 &= 0x77777777;
        ResetEntryInt();
        g_event_handlers.initialized = 0;
        result = &g_event_handlers;
    } else {
        result = NULL;
    }
    return result;
}
