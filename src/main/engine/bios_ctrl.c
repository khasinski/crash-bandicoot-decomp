/* GCC_VERSION: 2.6.3 */
#include "common.h"

#include "engine_state.h"

extern EngineState *D_80056564;
asm(".sdata\n.size D_80056564,4\n.text");
extern s32 engine_flag_shadow[] __asm__("D_80061978");
extern EngineByteRecord D_80056590, D_8005703C;

void func_8003CD60(s32);
s32 func_8003D094(void);
s32 func_8003D1F0(void);
s32 func_8003D308(void);
s32 func_8003D444(void);

static __inline__ s32 func_8003D008_inline(void)
{
    D_80056564->word04 &= ~0x20;
    return 0;
}

static __inline__ s32 func_8003D028_inline(s32 value)
{
    EngineState *state = D_80056564;
    s32 result = 0;

    if (state->word04 & 13) {
        engine_flag_shadow[0] = state->word04 |= 2;
        result = 1;
    } else {
        state->word00 = 6;
        engine_flag_shadow[0] = state->word04 |= 1;
        state->word14 = 0;
        state->word10 = 32;
        state->word0C = value;
    }
    return result;
}

static __inline__ s32 func_8003D3D8_inline(s32 value)
{
    EngineState *state = D_80056564;
    s32 result = 0;

    if (state->word04 & 13) {
        engine_flag_shadow[0] = state->word04 |= 2;
        result = 1;
    } else {
        state->word00 = 2;
        engine_flag_shadow[0] = state->word04 |= 1;
        state->word14 = 0;
        state->word10 = 32;
        state->word0C = value;
    }
    return result;
}

static __inline__ s32 func_8003D1B4_inline(void)
{
    D_8005703C = D_80056590;
    return 0;
}

static __inline__ s32 func_8003D4AC_inline(void)
{
    s32 result;
    if (D_80056564) {
        func_8003CD60((D_80056564->word04 & 0x10) | 4);
        result = 0;
    } else {
        result = 1;
    }
    return result;
}

s32 func_8003D4EC(s32 op, s32 value)
{
    switch (op) {
    case 0:
    case 1:
        return 1;
    case 2:
        return func_8003D008_inline();
    case 3:
        return func_8003D028_inline(value);
    case 4:
        return func_8003D3D8_inline(value);
    case 5:
        return func_8003D444();
    case 6:
        return func_8003D094();
    case 7:
        return func_8003D1F0();
    case 8:
        return func_8003D308();
    case 9:
        return func_8003D1B4_inline();
    case 10:
        return func_8003D4AC_inline();
    default:
        return 1;
    }
}
