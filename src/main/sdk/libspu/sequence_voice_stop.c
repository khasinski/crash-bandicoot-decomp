/* GCC_VERSION: 2.5.7 */
/* GCC_CPU: r4000 */
#include "common.h"
extern u8 D_8005E340;
extern s16 D_800572BA[][26];
extern s16 D_8005E572;
void func_8004F0D4(s32);
void func_80050060(s16 selector) {
    u8 voice=0;
    if (D_8005E340!=0) {
        do {
            if (D_800572BA[voice&0xFF][0]==selector) {
                D_8005E572=voice&0xFF;
                func_8004F0D4(0);
            }
            voice++;
        } while ((u32)(voice&0xFF)<D_8005E340);
    }
}
