#include "common.h"

/* GCC_VERSION: 2.6.3 */
typedef void (*Callback)(void);
extern Callback D_800549D0[8];
/* The interrupt tick counter can be read while callbacks are running. */
extern volatile s32 D_800549F0;
void func_8003EEAC(void) {
    s32 i = 0;
    Callback *slot = D_800549D0;
    D_800549F0++;
    do {
        Callback callback = *slot++;
        if (callback != NULL) callback();
        i++;
    } while (i < 8);
}
