/* GCC_VERSION: 2.5.7 */
/* GCC_CPU: r4000 */
#include "common.h"
extern u8 *D_80060418[];
void func_8004C764(s16 sequence,s16 channel) {
    s32 index=sequence;
    u8 **base_table=D_80060418;
    u8 **entry=base_table+index;
    s32 offset=channel*0xAC;
    u8 *state=offset+*entry;
    u8 *updated;
    state[0x2B]=1;
    updated=offset+*entry;
    *(s32 *)(updated+0x90)&=~8;
}
