/* GCC_VERSION: 2.5.7 */
/* GCC_CPU: r4000 */
#include "common.h"

extern s16 D_800572BA[][26];
void SpuVmKeyOffNow(s32);
void SpuVmSeqKeyOff(s16 selector) {
    u8 voice=0;
    if (gp_spawn_count!=0) {
        do {
            if (D_800572BA[voice&0xFF][0]==selector) {
                D_8005E572[0]=voice&0xFF;
                SpuVmKeyOffNow(0);
            }
            voice++;
        } while ((u32)(voice&0xFF)<gp_spawn_count);
    }
}
