/* GCC_VERSION: 2.5.7 */
/* GCC_CPU: r4000 */
#include "common.h"
extern u8 *D_80060418[];
/* The packed selector is passed as a word by this SDK caller. */
void func_80050060();
void func_8004C300(s16 sequence,s16 channel)
{
    s32 sequence_index=sequence;
    u32 table=(u32)D_80060418;
    u8 **entry=(u8 **)(table+sequence_index*4);
    s32 offset=channel*0xAC;
    u8 *state=*entry+offset;
    u8 *updated;
    s32 shifted=channel<<8;
    func_80050060(shifted|sequence);
    state[0x2B]=0;
    updated=*entry+offset;
    *(s32 *)(updated+0x90)&=~2;
}
