#include "common.h"
typedef struct {s16 state;u8 pad02[0xE];s32 id;u8 pad14[8];s32 *id_pointer;u8 pad20[0xC];} Slot;
extern Slot D_800580A4[];
extern s32 *D_8005CFBC;
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
