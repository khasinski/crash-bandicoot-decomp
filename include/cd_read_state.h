#ifndef CRASH_CD_READ_STATE_H
#define CRASH_CD_READ_STATE_H
#include "common.h"

/* Ten words shared by the CD read setup and interrupt callback. */
typedef struct CdReadState {
    s32 state;
    s32 buffer;
    s32 count;
    volatile s32 cursor;
    volatile s32 mode;
    s32 size;
    volatile s32 remaining;
    s32 time;
    s32 word20;
    s32 word24;
} CdReadState;
extern CdReadState g_cd_read_state;
#endif
