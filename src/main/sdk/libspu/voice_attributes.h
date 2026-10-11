#ifndef CRASH_SDK_LIBSPU_VOICE_ATTRIBUTES_H
#define CRASH_SDK_LIBSPU_VOICE_ATTRIBUTES_H

#include "common.h"

/* Layout recovered from SPU attribute readback and update code. */
typedef struct {
    s32 field_0;
    s32 field_4;
    u16 field_8;
    u16 field_A;
    s16 field_C;
    s16 field_E;
    u16 field_10;
    u16 field_12;
    u16 field_14;
    u16 field_16;
    u16 field_18;
    u16 field_1A;
    s32 field_1C;
    s32 field_20;
    s32 field_24;
    s32 field_28;
    s32 field_2C;
    u16 field_30;
    u16 field_32;
    u16 field_34;
    u16 field_36;
    u16 field_38;
    u16 field_3A;
    u16 field_3C;
} VoiceAttributes;

#endif
