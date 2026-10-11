/* GCC_VERSION: 2.5.7 */
/* ASPSX_VERSION: 2.34 */
#include "common.h"
/* GCC_CPU: r4000 */
typedef struct {
    u8 gap0[4];
    u8 *cursor;
    u8 gap8[0x78];
    s32 accumulated;
    u8 tail[0x28];
} DeltaState;
extern DeltaState *D_80060418[];
s32 func_8004AEB8(s16 sequence, s16 channel) {
    s32 ticks;
    s32 scaled;
    u8 *cursor;
    u8 *next;
    u8 byte;
    s32 value;
    DeltaState *state;
    state = D_80060418[sequence] + channel;
    cursor = state->cursor;
    state->cursor = cursor + 1;
    value = *cursor;
    if (value == 0) return 0;
    if (value & 0x80) {
        value &= 0x7F;
        do {
            next = state->cursor;
            state->cursor = next + 1;
            byte = *next;
            value = (value << 7) + (byte & 0x7F);
        } while (byte & 0x80);
    }
    scaled = value * 4;
    ticks = (scaled + value) * 2;
    state->accumulated = ticks + state->accumulated;
    return ticks;
}
