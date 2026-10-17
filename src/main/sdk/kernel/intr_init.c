#include "common.h"
#include "gpu.h"

/* GCC_VERSION: 2.6.3 */


/* --- func_8003E88C --- */

typedef void (*Callback)(void);

typedef struct {
    u16 initialized;
    u16 in_interrupt;
    Callback callbacks[11];
    u16 mask;
    u16 saved_imask;
    s32 saved_dpcr;
    u32 context[12];
    u32 stack[0x400];
} IntrState;

extern IntrState D_80053934;
extern volatile u16 *D_800549C0;
extern volatile u16 *D_800549C4;
extern volatile s32 *D_800549C8;

typedef struct {
    u32 word00;
    s32 slot04;
    s32 slot08;
    s32 slot0C;
    s32 slot10;
    s32 slot14;
    s32 slot18;
} Dispatch;

extern Dispatch *D_800549BC;

void func_8003EDD8(void *, s32);
s32 setjmp(void *) __asm__("func_8003EE04");
void func_8003E968(void);
void func_8003EE44(void *);
s32 func_8003EE54(void);
s32 func_8003EF7C(void);
void func_8003EE14(void *);
void func_8003E208(void);

void *func_8003E88C(void) {
    void *result;

    if (D_80053934.initialized == 0) {
        *D_800549C0 = *D_800549C4 = 0;
        *D_800549C8 = 0x33333333;
        func_8003EDD8(&D_80053934, sizeof(IntrState) / 4);
        if (setjmp(D_80053934.context) != 0) {
            func_8003E968();
        }
        D_80053934.context[1] = (u32)&D_80053934.stack[0x3EC];
        func_8003EE44(D_80053934.context);
        D_80053934.initialized = 1;
        D_800549BC->slot14 = func_8003EE54();
        D_800549BC->slot04 = func_8003EF7C();
        func_8003EE14(D_800549BC);
        func_8003E208();
        result = &D_80053934;
    } else {
        result = NULL;
    }
    return result;
}

