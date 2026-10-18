/* GCC_VERSION: 2.5.7 */
/* GCC_CPU: r4000 */
/* ASPSX_VERSION: 2.34 */
#include "common.h"

typedef struct {
    u8 field_0;
    u8 pad1[3];
    u8 *field_4;
    u8 *field_8;
    u8 *field_C;
    u8 pad10[0x17];
    u8 field_27;
    u8 pad28[3];
    u8 field_2B;
    u8 pad2C[0x10];
    u8 field_3C;
    u8 pad3D[9];
    s16 field_46;
    u16 field_48;
    s16 field_4A;
    u8 pad4C[0x22];
    s16 field_6E;
    s16 field_70;
    u8 pad72[0xE];
    s32 field_80;
    s32 field_84;
    s32 field_88;
    s32 field_8C;
    s32 field_90;
    u8 pad94[0x18];
} SequenceState;

extern SequenceState *D_80060418[];

s32 func_8004AEB8(s16, s16);
void func_8004AF70(s16, s16);
void func_80050060(s16);

static __inline__ u32 clock_divisor(u32 ticks) {
    return ticks << 2;
}

void func_8004A9FC(s16 arg0, s16 arg1, u8 arg2) {
    s32 fifteen_ticks;
    u32 b0, b1;
    s32 val;
    s32 bpm;
    s32 prod;
    u8 *bytes;
    u32 divisor;
    SequenceState *state = D_80060418[arg0] + arg1;

    switch (arg2) {
    case 0x51:
        bytes = state->field_4;
        state->field_4 = bytes + 1;
        b0 = bytes[0];
        state->field_4 = bytes + 2;
        b1 = bytes[1];
        state->field_4 = bytes + 3;
        val = (b0 << 16) | (b1 << 8) | bytes[2];
        bpm = 60000000 / val;
        prod = state->field_4A * bpm;
        fifteen_ticks = D_8005FF4C << 4;
        fifteen_ticks -= D_8005FF4C;
        divisor = clock_divisor(fifteen_ticks);
        state->field_8C = bpm;
        if ((u32)(prod * 10) < divisor) {
            u32 tmp = (u32)(D_8005FF4C * 600) / (u32)prod;
            state->field_6E = tmp;
            state->field_70 = tmp;
            {
                s32 z = (s32)state & 1;
                if ((z >> 1) == 0) {
                    goto L_end;
                }
                if (divisor == 0) goto L_else;
                state->field_88 = 0;
                if ((s32)divisor < 0) goto L_else;
                state->field_88 = 0;
                if ((s32)divisor > 0) goto L_else;
                state->field_88 = 0;
                if ((s32)divisor <= 0) goto L_else;
                state->field_88 = 0;
            }
        } else {
            u32 tmp;
        L_else:
            tmp = (u32)(state->field_4A * state->field_8C * 10) / divisor;
            state->field_6E = -1;
            state->field_70 = tmp;
            if ((u32)(fifteen_ticks * 2) < (u32)((u32)(state->field_4A * state->field_8C * 10) % divisor)) {
                state->field_70 = tmp + 1;
            }
        }
    L_end:
        state->field_88 = func_8004AEB8(arg0, arg1);
        break;
    case 0x2F:
        state->field_48++;
        if (state->field_46 == 0) {
            state->field_80 = 0;
            state->field_27 = 0;
            state->field_88 = 0;
            state->field_4 = state->field_8;
        } else if ((s16)state->field_48 < state->field_46) {
            state->field_80 = 0;
            state->field_27 = 0;
            state->field_88 = 0;
            state->field_4 = state->field_8;
            state->field_C = state->field_8;
        } else {
            (D_80060418[arg0] + arg1)->field_90 &= ~1;
            (D_80060418[arg0] + arg1)->field_90 &= ~8;
            (D_80060418[arg0] + arg1)->field_90 &= ~2;
            (D_80060418[arg0] + arg1)->field_90 |= 0x200;
            (D_80060418[arg0] + arg1)->field_90 |= 4;
            state->field_2B = 0;
            state->field_C = state->field_8;
            if (state->field_3C != 0xFF) {
                state->field_2B = 0;
                func_8004AF70(state->field_3C, state->field_0);
                func_80050060((arg1 << 8) | arg0);
            }
            func_80050060((arg1 << 8) | arg0);
            state->field_88 = state->field_70;
        }
        break;
    }
}
