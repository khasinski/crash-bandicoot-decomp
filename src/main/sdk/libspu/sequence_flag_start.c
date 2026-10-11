/* GCC_VERSION: 2.5.7 */
/* GCC_CPU: r4000 */
#include "common.h"
extern u8 *D_80060418[];
void func_8004B5E0(s16 sequence,s16 channel) {
    s32 index=sequence;
    u32 table=(u32)D_80060418;
    u8 **entry=(u8 **)(table+index*4);
    s32 offset=channel*0xAC;
    u8 *state=*entry+offset;
    u8 *updated;
    u32 word=*(s32 *)(state+0x90);
    if (!(word&0x204)) {
        if (!(word&0x100)) {
            *(s32 *)(state+0x90)=word&~2;
            /* Reload the table after writing channel flags. */
            word=(u32)*entry;
            updated=(u8 *)(offset+word);
            *(s32 *)(updated+0x90)|=8;
            word=(u32)*entry;
            updated=(u8 *)(offset+word);
            *(s32 *)(updated+0x90)|=1;
        }
    }
}
