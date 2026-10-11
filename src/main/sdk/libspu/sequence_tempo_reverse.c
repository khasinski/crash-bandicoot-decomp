/* GCC_VERSION: 2.5.7 */
/* GCC_CPU: r4000 */
#include "common.h"
extern u8 *D_80060418[];
void func_8004CFB0(s32,s16,s16,u32);
void func_80049538(s16 sequence,s16 channel,s16 value,u32 duration) {
    u8 **entry;
    s32 offset;
    u32 table;
    u8 *state;
    u8 *updated;
    func_8004CFB0(sequence,channel,value,duration);
    table=(u32)D_80060418;
    entry=(u8 **)(sequence*4+table);
    offset=channel*0xAC;
    state=*entry+offset;
    *(s32 *)(state+0x90)|=0x20;
    updated=*entry+offset;
    *(s32 *)(updated+0x90)&=~0x10;
}
