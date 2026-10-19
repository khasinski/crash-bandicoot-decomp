/* GCC_VERSION: 2.6.3 */
/* GCC_CPU: 3000 */
/* GNU_AS_G: 8 */
#include "common.h"
#include "audio_channels.h"

typedef struct {
    u32 mask;
    s16 volume_left, volume_right;
    s16 mode_left, mode_right;
    u8 pad0C[4];
    u16 cd_left, cd_right;
    s32 cd_mix, cd_reverb;
    u16 external_left, external_right;
    s32 external_mix, external_reverb;
} SpuCommonAttributes;

typedef struct {
    s32 unk00;
    u32 b0 : 1;
    u32 b1 : 1;
    u32 b2 : 1;
    u32 b3 : 1;
    u32 b4 : 1;
    u32 b5 : 1;
    u32 b6 : 1;
    u32 b7 : 1;
    u32 b8 : 1;
    u32 b9 : 1;
    u32 b10 : 1;
    u32 b11 : 1;
    s32 unk08;
    void *unk0C;
    u8 unk10;
    u8 unk11;
    u16 unk12;
    u16 unk14;
    u16 unk16;
    s32 unk18;
    s32 unk1C;
    s32 unk20;
    u8 pad24[0x20];
} VoiceEntry;

extern VoiceEntry g_voices[];
extern VoiceEntry g_audio_vol_scale;

extern s32 gp_pbak_mode[];
extern s32 g_cur_map_level[];

void SsInit(void);
void SsSetTableSize(void *, s16, s16);
s32 SpuInitMalloc(s32, void *);
void SpuSetCommonAttr(SpuCommonAttributes *);
void SpuSetTransferMode(s32);
s32 Audio_SetReverbAttr(s32, s16, s16, s32, s32);
void Audio_SetVoiceMVol(s16);
void SsSetMVol(s16, s16);

void Audio_Init(void) {
    s32 i;
    SpuCommonAttributes attr;

    for (i = 0; i < 24; i++) {
        g_voices[i].b3 = 0;
    }
    SsInit();
    SsSetTableSize(g_ss_seq_attr_table, 1, 2);
    SpuInitMalloc(0, gp_spu_malloc_rec);
    attr.mask = 3;
    attr.volume_left = 0x3FFF;
    attr.volume_right = 0x3FFF;
    SpuSetCommonAttr(&attr);
    SpuSetTransferMode(0);
    g_audio_vol_scale.unk0C = NULL;
    g_audio_vol_scale.unk10 = 1;
    g_audio_vol_scale.unk11 = 0x80;
    g_audio_vol_scale.unk12 = 0x3FFF;
    g_audio_vol_scale.unk14 = 0;
    g_audio_vol_scale.unk16 = 0x1000;
    g_audio_vol_scale.unk18 = 0;
    g_audio_vol_scale.unk1C = 0;
    g_audio_vol_scale.unk20 = 0;
    g_audio_vol_scale.b1 = 0;
    g_audio_vol_scale.b0 = 0;
    g_audio_vol_scale.b2 = 0;
    g_audio_vol_scale.b3 = 0;
    g_audio_vol_scale.b4 = 0;
    g_audio_vol_scale.b5 = 0;
    g_audio_vol_scale.b6 = 0;
    g_audio_vol_scale.b7 = 0;
    g_audio_vol_scale.b8 = 0;
    g_audio_vol_scale.b9 = 1;
    g_audio_vol_scale.b10 = 1;
    g_audio_vol_scale.b11 = 0;
    switch (gp_pbak_mode[0]) {
    case 0x5:
    case 0x1C:
    case 0x1D:
    case 0x34:
        Audio_SetReverbAttr(5, 0x2000, 0x2000, 0, 0);
        break;
    case 0x25:
        Audio_SetReverbAttr(3, 0x2000, 0x2000, 0, 0);
        break;
    }
    Audio_SetVoiceMVol((g_cur_map_level[0] * 0x3FFF) >> 8);
    gp_spu_master_vol = 0x3FFF;
    gp_midi_fade_step = 0;
    SsSetMVol(0x7F, 0x7F);
    gp_midi_default_rvol = 0;
}
