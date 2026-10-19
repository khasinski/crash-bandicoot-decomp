#include "common.h"
/* Complete common-attribute record; mask 3 selects master volume only. */
typedef struct {
    u32 mask;
    s16 volume_left,volume_right;
    s16 mode_left,mode_right;
    u8 reserved_0c[4];
    u16 cd_left,cd_right;
    s32 cd_mix,cd_reverb;
    u16 external_left,external_right;
    s32 external_mix,external_reverb;
} SpuCommonAttributes;
void SsSetMVol(s16 left, s16 right) {
    SpuCommonAttributes attributes;
    attributes.mask = 3;
    attributes.volume_left = left * 129;
    attributes.volume_right = right * 129;
    SpuSetCommonAttr(&attributes);
}
