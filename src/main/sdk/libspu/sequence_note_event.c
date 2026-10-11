/* GCC_VERSION: 2.5.7 */
/* GCC_CPU: r4000 */
#include "common.h"
typedef struct {
    u8 bytes[0xAC];
} State;
extern State *D_80060418[];
s32 func_8004DDE4();
s32 func_8004E330();
void func_8004AD64(s16 sequence,s16 channel,u8 note,u8 velocity) {
    State *state=D_80060418[sequence]+channel;
    s32 index=state->bytes[0x12];
    u8 *slot=state->bytes+index;
    u8 parameter=slot[0x17];
    u16 volume=velocity;
    if (!((*(s16 *)(state->bytes+0xAA)>>index)&1)) {
        if (*(u16 *)(state->bytes+0x74)!=0) {
            if(velocity!=0) {
                func_8004DDE4((channel<<8)|sequence,*(s16 *)(state->bytes+0x4C),slot[0x2C],note,volume,parameter);
                *(s16 *)(state->bytes+0xA8)=volume;
            } else {
                func_8004E330((channel<<8)|sequence,*(s16 *)(state->bytes+0x4C),slot[0x2C],note);
            }
        }
    }
}
