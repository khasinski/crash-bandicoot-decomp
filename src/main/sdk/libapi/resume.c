#include "common.h"

/* GCC_VERSION: 2.6.3 */

/* Restore the saved interrupt context and hardware masks if callbacks are paused.
 * The partial state view begins at its flag and includes context bytes at 0x38.
 */
s32 ExitCriticalSection(void);
s32 HookEntryInt(void *);
extern u16 g_event_handlers[];

u16 *restartIntr(void)
{
    u16 *result;

    if (*g_event_handlers == 0) {
        HookEntryInt(&g_event_handlers[0x1C]);
        *g_event_handlers = 1;
        *D_800549C4 = D_80053966;
        *D_800549C8 = D_80053968;
        ExitCriticalSection();
        result = g_event_handlers;
    } else {
        result = NULL;
    }
    return result;
}

void intr_memclr(s32 *table, s32 count)
{
    while (--count != -1) {
        *table++ = 0;
    }
}

