/* GCC_VERSION: 2.5.7 */
/* ASPSX_VERSION: 2.34 */
#include "common.h"
/* GCC_CPU: r4000 */
s16 func_8004FF54(s16, u16 *, u16 *);
extern u8 *D_80060418[];
void func_8004B44C(s16 sequence, s16 channel) {
    s32 sequence_index;
    u8 **base_table;
    u8 **table;
    s32 offset;
    u8 *state;
    u8 *first;
    u8 *second;
    u8 *last;
    sequence_index = sequence;
    base_table = D_80060418;
    table = base_table + sequence_index;
    offset = channel * 0xAC;
    state = offset + *table;
    func_8004FF54((channel << 8) | sequence, (u16 *)(state + 0x78), (u16 *)(state + 0x7A));
    first = offset + *table;
    *(s32 *)(first + 0x90) &= ~1;
    second = offset + *table;
    *(s32 *)(second + 0x90) &= ~8;
    last = offset + *table;
    *(s32 *)(last + 0x90) |= 2;
}
