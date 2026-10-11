#ifndef CD_AUDIO_H
#define CD_AUDIO_H

#include "common.h"
extern volatile u8 *D_80055864;
extern volatile u8 *D_80055868;
extern volatile u8 *D_8005586C;
extern volatile u8 *D_80055870;

static inline s32 CD_WriteVolumeRegisters(u8 *arg0) {
    *D_80055864 = 2;
    *D_8005586C = arg0[0];
    *D_80055870 = arg0[1];
    *D_80055864 = 3;
    *D_80055868 = arg0[2];
    *D_8005586C = arg0[3];
    *D_80055870 = 0x20;
    return 0;
}

#endif
