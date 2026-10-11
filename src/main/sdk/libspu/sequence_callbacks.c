#include "common.h"

extern void (*D_80056260)(void);
extern void (*D_80056264)(void);

void func_8004B828(void) {
    if (D_80056264 != 0) {
        D_80056264();
    }
    D_80056260();
}
