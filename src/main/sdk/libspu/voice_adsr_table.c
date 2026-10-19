/* GCC_VERSION: 2.5.7 */
/* GCC_CPU: r4000 */
/* ASPSX_VERSION: 2.34 */
#include "common.h"

typedef struct {
    u16 unk0;
    u16 unk2;
    u16 unk4;
    volatile u16 unk6;
    u8 pad8[19];
    u8 unk1B;
    s16 unk1C;
    u8 pad1E[10];
    s16 unk28;
    u8 pad2A[10];
} VoiceStruct;

extern VoiceStruct D_800572AC[];
extern u16 *g_snd_tempo;


extern u16 g_midi_seq_table[];

void _SpuVmSetNoiseVoice(s32, s32);

void SpuVmFlush(void) {
    s32 i = 0;
    u32 Mask2;
    u32 mask = 0;

    D_8005E744 = (D_8005E744 + 1) & 0xF;
    D_80060D70[D_8005E744] = 0;
    for (i = 0; i < gp_spawn_count; i++) {
        D_800572AC[i].unk6 = g_snd_tempo[i * 8 + 6];
        if (D_800572AC[i].unk6 == 0) {
            D_80060D70[D_8005E744] |= (1 << i);
        }
    }
    if (D_8005E710 == 0) {
        Mask2 = 0xFFFFFFFF;
        for (i = 0; i < 15; i++) {
            Mask2 &= D_80060D70[i];
        }
        for (i = 0; i < gp_spawn_count; i++) {
            if (Mask2 & (1 << i)) {
                if (D_800572AC[i].unk1B == 2) {
                    _SpuVmSetNoiseVoice(0, 0xFFFFFF);
                }
                D_800572AC[i].unk1B = 0;
            }
        }
    }
    i = 0;
    D_8005724C &= ~D_80061A68;
    D_80057254 &= ~D_80061A70;
    for (i = 0; i < 24; i++) {
        if (D_800572AC[i].unk1C != 0) {
            D_8005E708(i);
        }
        if (D_800572AC[i].unk28 != 0) {
            D_8005E550(i);
        }
    }
    for (i = 0; i < 24; i++) {
        if (g_card_ev_table[i] & 1) {
            g_snd_tempo[i * 8 + 0] = g_midi_seq_table[i * 8 + 0];
            g_snd_tempo[i * 8 + 1] = g_midi_seq_table[i * 8 + 1];
        }
        if (g_card_ev_table[i] & 4) {
            g_snd_tempo[i * 8 + 2] = g_midi_seq_table[i * 8 + 2];
        }
        if (g_card_ev_table[i] & 8) {
            g_snd_tempo[i * 8 + 3] = g_midi_seq_table[i * 8 + 3];
        }
        if (g_card_ev_table[i] & 0x10) {
            g_snd_tempo[i * 8 + 4] = g_midi_seq_table[i * 8 + 4];
            g_snd_tempo[i * 8 + 5] = g_midi_seq_table[i * 8 + 5];
        }
        g_card_ev_table[i] = 0;
    }
    g_snd_tempo[0xC6] = D_80061A68;
    g_snd_tempo[0xC7] = D_80061A70;
    g_snd_tempo[0xC4] = D_8005724C;
    g_snd_tempo[0xC5] = D_80057254;
    if (gp_spawn_count < 24) {
        mask = (g_snd_tempo[0xCD] << 16) | g_snd_tempo[0xCC];
        mask &= D_80056274;
    }
    D_80061A68 = 0;
    D_80061A70 = 0;
    D_8005724C = 0;
    D_80057254 = 0;
    g_snd_tempo[0xCC] = D_8005725C | mask;
    g_snd_tempo[0xCD] = D_80057264 | (mask >> 16);
}
