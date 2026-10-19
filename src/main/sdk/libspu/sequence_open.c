/* GCC_VERSION: 2.5.7 */
/* GCC_CPU: r4000 */
#include "common.h"
/* This unit registers addresses; callbacks have different parameter lists. */
typedef void (*Callback)();
s32 BIOS_Printf(const char *, ...);
s32 _SsInitSoundSep(s16, s16, s16, u8 *);

extern Callback D_80058378;
extern Callback D_8005837C;
extern Callback D_80058380;
extern Callback D_80058384;
extern Callback D_80058388;
extern Callback D_8005838C;
extern Callback D_80058390;
extern Callback D_80058394;
extern Callback D_80058398;
extern Callback D_8005839C;
extern Callback D_800583A4;

void Cd_Stub_01();
void Cd_Stub_02();
void Cd_Stub_03();
void Cd_Stub_04();
void Cd_Stub_05();
void Cd_Stub_06();
void Cd_Stub_07();
void Cd_Stub_08();
void Cd_Stub_09();
void Cd_Stub_10();
void Cd_Stub_11();
void Cd_Stub_12();
void Cd_Stub_13();
void Cd_Stub_14();
void Cd_Stub_15();
void Cd_Stub_16();
void Cd_Stub_17();
void Cd_Stub_18();
void Cd_Stub_19();
void Cd_Stub_20();
void _SsSetProgramChange();
void _SsSetControlChange();
void _SsContModulation();
void _SsContPortaTime();
void _SsContPortamento();
void _SsContResetAll();
void _SsContNrpn1();
void _SsContNrpn2();
void _SsContRpn1();
void _SsContRpn2();
void _SsContDataEntry();
void _SsSetPitchBend();
void _SsGetSeqData();
void _SsGetMetaEvent();
void _SsNoteOn();
void _SsNoteOff();

s16 SsSepOpen(s32 data_address, s16 mode, s16 channel_count) {
    s16 next_channel;
    s16 candidate_id;
    s16 channel;
    s16 sequence_id;
    s32 bytes_consumed;
    s32 found;
    s32 cursor;

    cursor = data_address;
    if (D_8005E548 == -1) {
        BIOS_Printf(D_80011728);
failed:
        return -1;
    }
    candidate_id = 0;
    found = 0;
    g_Snd_FnTable[0] = &_SsNoteOn;
    D_80058364 = &_SsNoteOff;
    D_8005836C = &_SsGetMetaEvent;
    D_80058368 = &_SsSetPitchBend;
    D_80058370 = &_SsGetSeqData;
    D_80058374 = &_SsSetProgramChange;
    D_8005837C = &_SsContModulation;
    D_80058380 = &_SsContPortaTime;
    D_80058384 = &_SsContPortamento;
    D_80058388 = &_SsContNrpn1;
    D_8005838C = &_SsContNrpn2;
    D_80058390 = &_SsContRpn1;
    D_80058394 = &_SsContRpn2;
    D_80058398 = &_SsContResetAll;
    D_8005839C = &_SsContDataEntry;
    D_80058378 = &_SsSetControlChange;
    D_800583A4 = &Cd_Stub_01;
    D_800583A8 = &Cd_Stub_02;
    D_800583AC = &Cd_Stub_03;
    D_800583B0 = &Cd_Stub_04;
    D_800583B4 = &Cd_Stub_05;
    D_800583B8 = &Cd_Stub_06;
    D_800583BC = &Cd_Stub_07;
    D_800583C0 = &Cd_Stub_08;
    D_800583C4 = &Cd_Stub_09;
    D_800583C8 = &Cd_Stub_10;
    D_800583CC = &Cd_Stub_11;
    D_800583D0 = &Cd_Stub_12;
    D_800583D4 = &Cd_Stub_13;
    D_800583D8 = &Cd_Stub_14;
    D_800583DC = &Cd_Stub_15;
    D_800583E0 = &Cd_Stub_16;
    D_800583E4 = &Cd_Stub_17;
    D_800583E8 = &Cd_Stub_18;
    D_800583EC = &Cd_Stub_19;
    D_800583F0 = &Cd_Stub_20;
    do {
        if (!((1 << candidate_id) & D_8005E548)) {
            sequence_id = candidate_id;
            found = 1;
        }
        candidate_id += 1;
    } while ((found & 255) == 0);
    D_8005E548 |= 1 << sequence_id;
    channel = 0;
    if (channel_count > 0) {
        do {
            bytes_consumed = _SsInitSoundSep(sequence_id, channel, mode, (u8 *)cursor);
            if (bytes_consumed == -1) goto failed;
            next_channel = channel + 1;
            channel = next_channel;
            cursor += bytes_consumed;
        } while (next_channel < channel_count);
    }

    return sequence_id;
}
