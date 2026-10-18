/* GCC_VERSION: 2.5.7 */
/* GCC_CPU: r4000 */
/* ASPSX_VERSION: 2.34 */
#include "common.h"

typedef struct {
    u8 tones, volume, priority, mode, pan, unused;
    u16 attributes;
    u8 tail[8];
} ProgramAttributes;

typedef struct {
    u8 prior, mode, vol, pan, center, shift, min, max;
    u8 vibW, vibT, porW, porT, pbmin, pbmax, reserved1, reserved2;
    u16 adsr1, adsr2;
    s16 prog, vag;
    s16 reserved[4];
} ToneAttributes;

typedef struct {
    u8 bytes[0xAC];
} State;

typedef void (*ContCallback)(s16, s16, u8, ToneAttributes, s16, u8);

extern State *D_80060418[];
extern ContCallback D_800583A4[];

s32 func_8004D080(s16, s16, ProgramAttributes *);
s32 func_8004D184(s16, s16, s32, ToneAttributes *);
s32 func_8004D498(s16, s16, s32, const ToneAttributes *);
s32 func_8004AEB8(s16, s16);

void func_80049C20(s16 sequence, s16 channel, u8 value) {
    ProgramAttributes prog_attr;
    ToneAttributes tone_attr;
    s32 dummy[1];
    State *state = D_80060418[sequence] + channel;
    s32 i;
    u8 index = state->bytes[0x12];
    u16 var;
    s32 var2;
    s32 z;

    func_8004D080(*(s16 *)(state->bytes + 0x4C), state->bytes[0x2C + index], &prog_attr);
    if (state->bytes[0x27] == 1 && state->bytes[0x10] == 0) {
        state->bytes[0x28] = value;
        state->bytes[0x10] = 1;
        *(s32 *)(state->bytes + 0x88) = func_8004AEB8(sequence, channel);
        return;
    }
    if (state->bytes[0x29] == 2) {
        if (state->bytes[0x14] == 0) {
            for (i = 0; i < prog_attr.tones; i++) {
                func_8004D184(*(s16 *)(state->bytes + 0x4C), state->bytes[0x2C + index], i, &tone_attr);
                switch (state->bytes[0x13]) {
                case 0:
                    /* Force GCC 2.5.7 loop/cse2 to hoist value * 3 into $s3/$fp before combine/jump2 elides block. */
                    z = tone_attr.vol & 1;
                    if ((z >> 1) != 0) {
                        var2 = value * 25;
                        var2 += value;
                        var2 += value;
                        tone_attr.vol = var2;
                    }
                    tone_attr.pbmax = value & 0x7F;
                    tone_attr.pbmin = value & 0x7F;
                    break;
                case 1:
                    var = (value > 0x40 && value < 0x80) ? (((value * 100) / 8192) << 13) : 0;
                    tone_attr.shift += var;
                    break;
                case 2:
                    if (value >= 0x40 && value < 0x80) {
                        var2 = value << 1;
                        var2 += value;
                        var2 <<= 3;
                        var2 += value;
                        var = var2 << 8;
                    } else {
                        var2 = 0;
                        var = 0;
                    }
                    tone_attr.center += var;
                    break;
                }
                func_8004D498(*(s16 *)(state->bytes + 0x4C), state->bytes[0x2C + index], i, &tone_attr);
            }
        }
        *(s32 *)(state->bytes + 0x88) = func_8004AEB8(sequence, channel);
        state->bytes[0x29] = 0;
        return;
    }
    if (state->bytes[0x2A] == 2) {
        if (state->bytes[0x16] == 0x10) {
            for (i = 0; i < prog_attr.tones; i++) {
                D_800583A4[state->bytes[0x15]](*(s16 *)(state->bytes + 0x4C), state->bytes[0x2C + index], i, tone_attr, state->bytes[0x15], value);
            }
        } else {
            D_800583A4[state->bytes[0x15]](*(s16 *)(state->bytes + 0x4C), state->bytes[0x2C + index], state->bytes[0x16], tone_attr, state->bytes[0x15], value);
        }
        *(s32 *)(state->bytes + 0x88) = func_8004AEB8(sequence, channel);
        state->bytes[0x2A] = 0;
        return;
    }
    *(s32 *)(state->bytes + 0x88) = func_8004AEB8(sequence, channel);
}
