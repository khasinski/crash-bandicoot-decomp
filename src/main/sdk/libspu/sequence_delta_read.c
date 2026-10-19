/* GCC_VERSION: 2.5.7 */
/* ASPSX_VERSION: 2.34 */
#include "common.h"
/* GCC_CPU: r4000 */
s32 _SsReadDeltaValue(s16 sequence, s16 channel) {
    s32 ticks;
    s32 scaled;
    u8 *cursor;
    u8 *next;
    u8 byte;
    s32 value;
    SequenceState *state;
    state = g_ss_score_table[sequence] + channel;
    cursor = state->field_4;
    state->field_4 = cursor + 1;
    value = *cursor;
    if (value == 0) return 0;
    if (value & 0x80) {
        value &= 0x7F;
        do {
            next = state->field_4;
            state->field_4 = next + 1;
            byte = *next;
            value = (value << 7) + (byte & 0x7F);
        } while (byte & 0x80);
    }
    scaled = value * 4;
    ticks = (scaled + value) * 2;
    state->field_80 = ticks + state->field_80;
    return ticks;
}
