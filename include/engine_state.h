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
    u8 pad00[0x3598];
    s32 word3598, word359C;
    /* func_80031BF8 copies the word at D_8006194C into both fields.
     * The instructions establish word width, not pointer semantics. */
    u32 word35A0, word35A4;
    u8 pad35A8[0x28];
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
extern s32 D_80056500, D_80056678;
extern char D_80056504[8], D_8005650C[8], D_80056514[8], D_8005651C[8];
extern char D_80056524[8], D_8005652C[8], D_80056534[8], D_8005653C[8];
extern char D_80056544[8], D_8005654C[8], D_80056554[8], D_8005655C[8];
extern EngineState *D_80056564;
extern EngineMode25State *D_800566E0;
#endif
void func_8003AE08(EngineEventRequest *request);
void func_8003AED8(EngineEventRequest *request);
void func_80031D50(s32 *reference, s32 mode);
s32 func_80031BF8(void);

#endif
