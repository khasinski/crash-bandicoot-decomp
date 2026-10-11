#ifndef CRASH_ENGINE_STATE_H
#define CRASH_ENGINE_STATE_H

#include "common.h"

/* Partial prefix of the 0x6F4-byte allocation in func_8003CE20.
 * The allocation size is not evidence for the unknown trailing fields. */
typedef struct EngineState {
    s32 word00, word04, word08, word0C, word10, word14, word18;
} EngineState;

/* Separate allocation in func_80031BAC; last observed word is at 0x35D4. */
typedef struct EngineMode25State {
    u8 pad00[0x359C];
    s32 word359C;
    u8 pad35A0[0x30];
    s32 word35D0, word35D4;
} EngineMode25State;

/* BIOS event lifecycle, used by func_8003AE08 and func_8003AED8. */
typedef struct EngineEventRequest {
    s32 *resource;
    s32 *pending;
    s32 event;
} EngineEventRequest;

typedef struct EngineByteRecord {
    u8 data[6];
} EngineByteRecord;

/* GCC 2.6.3 emits tentative storage in declaration order. The owner defines
 * these globals in retail order instead of declaring them ahead of that list. */
#ifndef CRASH_ENGINE_STATE_STORAGE
extern EngineState *D_80056564;
extern EngineMode25State *D_800566E0;
#endif
void func_8003AE08(EngineEventRequest *request);
void func_8003AED8(EngineEventRequest *request);
void func_80031D50(s32 *reference, s32 mode);

#endif
