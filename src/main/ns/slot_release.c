/* GCC_VERSION: 2.6.3 */
#include "resource.h"
typedef ResourceSlotStateView Slot;
extern ResourceSlot D_80057F40[8];
extern Slot D_800580A4[];

s32 func_80014514(s32 arg0) {
    s16 temp_v1;

    temp_v1 = D_800580A4[arg0].state;
    switch (temp_v1) {                              /* irregular */
    case 20:
        *D_800580A4[arg0].id_pointer = D_800580A4[arg0].id;
        D_8005CFBC[D_800580A4[arg0].id >> 1] = -0x12;
        /* fallthrough */
    case 21:
        D_800580A4[arg0].state = 1;
        break;
    }
    return -0xE;
}

s32 func_800145C8(s32 arg0, s32 arg1) {
    s32 i;
    ResourceSlot *slot;

    for (i = 7; i >= 0; i--) {
        slot = &D_80057F40[i];
        if ((s16)slot->state == 1 && D_80057F40[i].word06 == arg0) {
            if (arg1 == -1 || arg1 == D_80057F40[i].word08) {
                return i;
            }
        }
    }
    return -12;
}
