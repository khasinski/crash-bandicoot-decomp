/* GCC_VERSION: 2.5.7 */
/* ASPSX_VERSION: 2.34 */
#include "common.h"
/* GCC_CPU: r4000 */
extern u8 *D_80060418[];
void func_8004AF70(s16 sequence, s16 channel) {
    u32 table_base;
    s32 sequence_shift;
    u8 **table;
    s32 offset;
    u8 *state;
    u8 *first;
    u8 *second;
    u8 *third;
    u8 *fourth;
    u8 *fifth;
    u8 *last;
    sequence_shift = (s32)sequence << 16;
    table_base = (u32)D_80060418;
    table = (u8 **)((sequence_shift >> 14) + table_base);
    offset = channel * 0xAC;
    state = offset + *table;
    *(s16 *)(state + 0x46) = 1;
    *(s16 *)(state + 0x48) = 0;
    first = offset + *table;
    *(s32 *)(first + 0x90) &= ~0x100;
    second = offset + *table;
    *(s32 *)(second + 0x90) &= ~8;
    third = offset + *table;
    *(s32 *)(third + 0x90) &= ~2;
    fourth = offset + *table;
    *(s32 *)(fourth + 0x90) &= ~4;
    fifth = offset + *table;
    *(s32 *)(fifth + 0x90) &= ~0x200;
    state[0x2B] = 1;
    *(u8 **)(state + 4) = *(u8 **)(state + 8);
    last = offset + *table;
    *(s32 *)(last + 0x90) |= 1;
}
