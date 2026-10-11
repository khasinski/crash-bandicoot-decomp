/* GCC_VERSION: 2.5.7 */
/* GCC_CPU: r4000 */
#include "common.h"
extern u8 *D_80060418[];
s16 func_8004F998();
void func_8004B6D8(s16 sequence,s16 channel,u8 mode,s16 repeat) {
    u8 **entry;
    s32 offset;
    u8 *state;
    u8 *updated;
    u8 *playing;
    u8 *paused;
    s32 sequence_index=sequence;
    u8 **base_table=D_80060418;
    entry=base_table+sequence_index;
    offset=channel*0xAC;
    state=offset+*entry;
    *(s32 *)(state+0x90)&=~0x200;
    updated=offset+*entry;
    *(s32 *)(updated+0x90)&=~4;
    *(s16 *)(state+0x46)=repeat;
    if (mode==1) {
        playing=offset+*entry;
        *(s32 *)(playing+0x90)|=1;
        *(s16 *)(state+0x48)=0;
        state[0x2B]=1;
        func_8004F998((channel<<8)|sequence,*(u16 *)(state+0x74),*(u16 *)(state+0x76),0);
    } else if (mode==0) {
        paused=channel*0xAC+*entry;
        *(s32 *)(paused+0x90)|=2;
    }
}
