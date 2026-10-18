#include "common.h"

/* GCC_VERSION: 2.6.3 */

/* Acknowledge controller interrupts and reset CD status. */

extern volatile s8 D_800555C0;
extern volatile s8 *D_80055864;
extern volatile s8 *D_8005586C;
extern volatile u8 *D_80055870;

extern volatile s8 D_8005587C;
extern volatile u8 D_8005587D[];

void func_80044C40(void) {
    u32 acknowledge = 7;
    u8 status;
    *D_80055864 = 1;
    if (*D_80055870 & 7) {
        do {
            *D_80055864 = 1;
            *D_80055870 = acknowledge;
            *D_8005586C = acknowledge;
        } while (*D_80055870 & 7);
    }
    D_8005587E = 0;
    status = D_8005587E;
    D_800555C0 = 0;
    *D_8005587D = status;
    D_8005587C = 2;
    *D_80055864 = 0;
    *D_80055870 = 0;
    *D_80055874 = 0x1325;
}
