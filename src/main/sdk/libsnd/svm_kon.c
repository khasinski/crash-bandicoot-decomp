/* GCC_VERSION: 2.5.7 */
/* GCC_CPU: r4000 */
/* ASPSX_VERSION: 2.34 */
#include "common.h"

typedef struct {
    u16 unk0;
    u16 unk2;
    u8 pad4[2];
    u16 unk6;
    u8 pad8[16];
    s16 unk18;
    u8 pad1A;
    u8 unk1B;
    u8 pad1C[24];
} VoiceStruct;

typedef struct { u16 value; u8 pad[50]; } VoiceU16;
typedef struct { s16 value; u8 pad[50]; } VoiceS16;
typedef struct { u8 value; u8 pad[51]; } VoiceU8;

typedef struct {
    u8 unk0[7];
    u8 unk7;
    u8 unk8[4];
    u8 unkC;
    u8 unkD[2];
    u8 unkF;
    u8 unk10[8];
    s16 unk18;
    s16 unk1A;
    s16 unk1C;
    s16 unk1E;
} SvmCur;

extern SvmCur g_midi_sep;
extern VoiceU16 g_spu_vm_voice_envx[];


void _SpuVmSetNoiseVoice(s32, s32);

void SpuVmDoAllocate(void) {
    s32 var_t0;
    s32 pad[2];

    g_midi_sep.unk1C = g_midi_sep.unk1A * 8;
    g_midi_sep.unk1E = (g_midi_sep.unk7 << 4) + g_midi_sep.unkC;
    g_spu_vm_voice_envx[g_midi_sep.unk1A].value = 0x7FFF;
    for (var_t0 = 0; var_t0 < 0x10; var_t0++) {
        g_spu_vm_seq_voice_mask[var_t0] &= ~(1 << g_midi_sep.unk1A);
    }
    if ((g_midi_sep.unk18 & 1) > 0) {
        g_spu_vm_alloc_prog_attr[g_midi_sep.unk1C] = *(u16 *)(g_vab_cur_prog_table + ((((s16) g_midi_sep.unk18 - 1) / 2) * 0x10) + 0xC);
        g_card_ev_table[g_midi_sep.unk1A] |= 8;
    } else {
        g_spu_vm_alloc_prog_attr[g_midi_sep.unk1C] = *(u16 *)(g_vab_cur_prog_table + ((((s16) g_midi_sep.unk18 - 1) / 2) * 0x10) + 0xE);
        g_card_ev_table[g_midi_sep.unk1A] |= 8;
    }
    g_spu_vm_alloc_adsr1[g_midi_sep.unk1C] = *(u16 *)(((((g_midi_sep.unk7 << 4) + g_midi_sep.unkC) << 5) + (*(u32 *)&g_ns_vpage_pool)) + 0x10);
    g_spu_vm_alloc_adsr2[g_midi_sep.unk1C] = *(u16 *)(((((g_midi_sep.unk7 << 4) + g_midi_sep.unkC) << 5) + (*(u32 *)&g_ns_vpage_pool)) + 0x12) + g_spu_vm_damper_mask;
    g_card_ev_table[g_midi_sep.unk1A] |= 0x30;
}
