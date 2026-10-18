/* GCC_VERSION: 2.5.7 */
/* GCC_CPU: r4000 */
#include "common.h"
typedef struct {
    u8 gap00[0x90];
    s32 field_90;
    u8 gap94[0xAC - 0x94];
} SequenceState;
extern SequenceState *D_80060418[];
void func_8004CFB0(s32,s16,s16,u32);
void func_80049538(s16 sequence,s16 channel,s16 value,u32 duration) {
    func_8004CFB0(sequence,channel,value,duration);
    D_80060418[sequence][channel].field_90 |= 0x20;
    D_80060418[sequence][channel].field_90 &= ~0x10;
}
