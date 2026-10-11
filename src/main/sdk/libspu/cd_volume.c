#include "common.h"

/* GCC_VERSION: 2.6.3 */
/* Attribute fields read at offsets 0x00, 0x08 and 0x0A. */
typedef struct {
    u32 mask;
    u8 pad04[4];
    u16 volume08, volume0A;
} SpuVolumeAttrs;
extern volatile u16 *D_800558E4;
extern u16 D_80055964;
extern u16 D_80055966;

s32 func_80047BE8(SpuVolumeAttrs *arg0) {
    s32 temp_a1;
    s32 temp_a2;

    temp_a1 = arg0->mask;
    temp_a2 = temp_a1 == 0;
    if ((temp_a2 != 0) || (temp_a1 & 2)) {
        D_800558E4[0xC2] = (u16) arg0->volume08;
        D_80055964 = arg0->volume08;
    }
    if ((temp_a2 != 0) || (temp_a1 & 4)) {
        D_800558E4[0xC3] = (u16) arg0->volume0A;
        D_80055966 = arg0->volume0A;
    }
    return 0;
}
