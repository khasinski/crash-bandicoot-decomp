#include "common.h"

extern void (*D_80056260)(void);
extern s32 D_8005626C;

/* Call the registered callback on alternate invocations. */
void func_8004B868(void) {
    if (D_8005626C == 0) {
        D_8005626C = 1;
        return;
    }
    D_8005626C = 0;
    D_80056260();
}
