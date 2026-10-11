#ifndef CRASH_AUDIO_CHANNELS_H
#define CRASH_AUDIO_CHANNELS_H

#include "common.h"

/* Channel records are 20 bytes; actions access the fields at 0, 4, 16, 18. */
typedef struct AudioChannel {
    s16 channel;
    u16 unknown02;
    s32 state;
    u8 unknown08[8];
    s16 left_volume;
    s16 right_volume;
} AudioChannel;

#endif
