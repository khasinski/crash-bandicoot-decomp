/* GCC_VERSION: 2.5.7 */
/* GCC_CPU: r4000 */
#include "common.h"

extern s16 g_spu_vm_voice_seq_sep[][26];
void SpuVmSeqKeyOff(s16 selector) {
    u8 voice=0;
    if (gp_spawn_count!=0) {
        do {
            if (g_spu_vm_voice_seq_sep[voice&0xFF][0]==selector) {
                g_spu_vm_last_voice[0]=voice&0xFF;
                SpuVmKeyOffNow(0);
            }
            voice++;
        } while ((u32)(voice&0xFF)<gp_spawn_count);
    }
}
