/* GCC_VERSION: 2.6.3 */
/* GCC_CPU: 3000 */
/* GNU_AS_G: 8 */
#include "common.h"
#include "audio_channels.h"

typedef struct {
    u16 count;
    u16 pad02;
    s32 bank_ref;
    s32 refs[7];
} MidiHeaderItem;

typedef struct {
    u32 word00;
    s32 id;
    s32 kind;
    s32 word0C;
    MidiHeaderItem *header;
    void *vh;
    void *sep;
} MidiResourceEntry;


MidiResourceEntry *Ns_Open(s32 *, s32, s32);
s32 Ns_Close(s32 *, s32);
void SsSepClose(s16);
s16 SsVabFakeHead(void *, s32, s32);
typedef void noreturn_fn(s32);
volatile noreturn_fn BIOS_Abs;
s16 SsVabFakeBody(s16);
void SsStart(void);
s16 SsSepOpen(void *, s16, s16);
void Midi_SeqInit(AudioChannel *, s32, s32, s32);
void SsSepSetCrescendo(s16, s16, s16, s32);
s32 Midi_Control(AudioChannel *, s32, s32);

s32 Midi_OpenAndPlay(s32 *arg0) {
    s32 sp10;
    s32 i;
    MidiResourceEntry *entry;
    s32 arg3;
    s32 is_new;

    is_new = (D_80056658 == -1);
    if (D_8005666C != 0) {
        return -1;
    }
    if (gp_card_chan == 1) {
        if (D_80056650 != 0x6396347F) {
            SsSepClose(gp_midi_vol);
            sp10 = D_80056650;
            Ns_Close(&sp10, 1);
        }
        if (*arg0 != 0x6396347F) {
            entry = Ns_Open(arg0, 1, 1);
            D_80056650 = entry->id;
            for (i = 0; i < 7; i++) {
                if (entry->header->refs[i] != 0x6396347F) {
                    Ns_Open(&entry->header->refs[i], 0, 1);
                }
            }
        } else {
            D_80056650 = *arg0;
            return 0;
        }
    }
    gp_card_chan = 2;
    entry = Ns_Open(arg0, 1, 0);
    gp_midi_vab_id = 0;
    for (i = 0; i < 7; i++) {
        if (entry->header->refs[i] != 0x6396347F) {
            if (Ns_Close(&entry->header->refs[i], 0) == 0) {
                return 0;
            }
        }
    }
    gp_card_chan = 3;
    D_8005665C = entry->header->count;
    if (D_80056658 == -1) {
        Ns_Open(&entry->header->bank_ref, 1, 1);
        D_80056658 = SsVabFakeHead(entry->vh, -1, (D_8005CFB0[0] << 16) | 0x2000);
        if (D_80056658 == -1) {
            BIOS_Abs(-1);
        }
        D_80056658 = SsVabFakeBody(D_80056658);
        if (D_80056658 == -1) {
            BIOS_Abs(-1);
        }
        SsStart();
    }
    gp_midi_vol = SsSepOpen(entry->sep, D_80056658, D_8005665C);
    if (gp_midi_vol == -1) {
        BIOS_Abs(-1);
    }
    for (i = 0; i < D_8005665C; i++) {
        if (is_new) {
            s32 vol = (s16)D_80056648 >> 7;
            Midi_SeqInit(&D_80056EBC[i], vol | (vol << 16), i, arg3);
        } else {
            Midi_SeqInit(&D_80056EBC[i], 0, i, arg3);
            SsSepSetCrescendo(gp_midi_vol, D_80056EBC[i].channel, (s16)D_80056648 >> 7, 30);
        }
    }
    return Midi_Control(D_80056EBC, 0, 0);
}
