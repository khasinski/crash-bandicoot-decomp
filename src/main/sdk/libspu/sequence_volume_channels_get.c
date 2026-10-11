/* GCC_VERSION: 2.5.7 */
/* GCC_CPU: r4000 */
#include "common.h"
extern u8 *D_80060418[];
extern s16 D_8005E56E;
s32 func_8004FFC0(s32 selector) {
    s32 channel=(selector&0xFF00)>>8;
    u8 *state=D_80060418[selector&0xFF]+channel*0xAC;
    D_8005E56E=selector;
    return *(s16 *)(state+0x74);
}
s32 func_80050010(s32 selector) {
    s32 channel=(selector&0xFF00)>>8;
    u8 *state=D_80060418[selector&0xFF]+channel*0xAC;
    D_8005E56E=selector;
    return *(s16 *)(state+0x76);
}
