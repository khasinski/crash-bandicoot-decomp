/* GCC_VERSION: 2.6.3 */
#include "common.h"

typedef void (*Callback)(void);

extern char D_8001106C[];
extern char D_80011088[];
extern volatile u32 *D_800549F8;
extern Callback D_800549FC[];
extern volatile u32 *D_80054A1C;

s32 func_8003D730(const char *, ...);

void func_8003EFCC(void) {
    s32 i;
    u32 pending;

    pending = (*D_800549F8 >> 24) & 0x7F;
    while (pending != 0) {
        for (i = 0; pending != 0; i++, pending >>= 1) {
            if (i >= 7) {
                break;
            }
            if (pending & 1) {
                *D_800549F8 &= (1 << (i + 24)) | 0xFFFFFF;
                if (D_800549FC[i] != NULL) {
                    D_800549FC[i]();
                }
            }
        }
        pending = (*D_800549F8 >> 24) & 0x7F;
    }
    if ((*D_800549F8 & 0xFF000000) == 0x80000000 || (*D_800549F8 & 0x8000)) {
        func_8003D730(D_8001106C, *D_800549F8);
        for (i = 0; i < 7; i++) {
            func_8003D730(D_80011088, i, D_80054A1C[i * 4]);
        }
    }
}

Callback func_8003F150(s32 index, Callback callback) {
    Callback previous = D_800549FC[index];

    if (callback != previous) {
        if (callback != NULL) {
            D_800549FC[index] = callback;
            *D_800549F8 = ((*D_800549F8 & 0xFFFFFF) | 0x800000) | (1 << (index + 16));
        } else {
            D_800549FC[index] = NULL;
            *D_800549F8 = ((*D_800549F8 & 0xFFFFFF) | 0x800000) & ~(1 << (index + 16));
        }
    }
    return previous;
}

void func_8003F1F8(Callback *table, s32 count) {
    while (--count != -1) {
        *table++ = NULL;
    }
}
