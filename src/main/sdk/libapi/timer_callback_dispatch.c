#include "common.h"

/* GCC_VERSION: 2.6.3 */
typedef void (*Callback)(void);
/* The interrupt tick counter can be read while callbacks are running. */
void trapIntrVSync(void) {
    s32 i = 0;
    Callback *slot = D_800549D0;
    D_800549F0++;
    do {
        Callback callback = *slot++;
        if (callback != NULL) callback();
        i++;
    } while (i < 8);
}
