/* GCC_VERSION: 2.5.7 */
/* GCC_CPU: r4000 */
#include "common.h"
/* This unit registers addresses; callbacks have different parameter lists. */
typedef void (*Callback)();
s32 func_8003D730(const char *, ...);
s32 func_8004B078(s16, s16, s16, u8 *);

extern Callback D_80058360;
extern Callback D_80058364;
extern Callback D_80058368;
extern Callback D_8005836C;
extern Callback D_80058370;
extern Callback D_80058374;
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
extern Callback D_800583A8;
extern Callback D_800583AC;
extern Callback D_800583B0;
extern Callback D_800583B4;
extern Callback D_800583B8;
extern Callback D_800583BC;
extern Callback D_800583C0;
extern Callback D_800583C4;
extern Callback D_800583C8;
extern Callback D_800583CC;
extern Callback D_800583D0;
extern Callback D_800583D4;
extern Callback D_800583D8;
extern Callback D_800583DC;
extern Callback D_800583E0;
extern Callback D_800583E4;
extern Callback D_800583E8;
extern Callback D_800583EC;
extern Callback D_800583F0;

void func_8002FD30();
void func_8002FD38();
void func_8002FD40();
void func_8002FD48();
void func_8002FD50();
void func_8002FD58();
void func_8002FD60();
void func_8002FD68();
void func_8002FD70();
void func_8002FD78();
void func_8002FD80();
void func_8002FD88();
void func_8002FD90();
void func_8002FD98();
void func_8002FDA0();
void func_8002FDA8();
void func_8002FDB0();
void func_8002FDB8();
void func_8002FDC0();
void func_8002FDC8();
void func_80049BA0();
void func_80049C20();
void func_8004A060();
void func_8004A128();
void func_8004A1EC();
void func_8004A298();
void func_8004A324();
void func_8004A44C();
void func_8004A594();
void func_8004A608();
void func_8004A67C();
void func_8004A740();
void func_8004A7E8();
void func_8004A9FC();
void func_8004AD64();
void func_8004AE44();

s16 func_80049844(s32 data_address, s16 mode, s16 channel_count) {
    s16 next_channel;
    s16 candidate_id;
    s16 channel;
    s16 sequence_id;
    s32 bytes_consumed;
    s32 found;
    s32 cursor;

    cursor = data_address;
    if (D_8005E548 == -1) {
        func_8003D730(D_80011728);
failed:
        return -1;
    }
    candidate_id = 0;
    found = 0;
    D_80058360 = &func_8004AD64;
    D_80058364 = &func_8004AE44;
    D_8005836C = &func_8004A9FC;
    D_80058368 = &func_8004A740;
    D_80058370 = &func_8004A7E8;
    D_80058374 = &func_80049BA0;
    D_8005837C = &func_8004A060;
    D_80058380 = &func_8004A128;
    D_80058384 = &func_8004A1EC;
    D_80058388 = &func_8004A324;
    D_8005838C = &func_8004A44C;
    D_80058390 = &func_8004A594;
    D_80058394 = &func_8004A608;
    D_80058398 = &func_8004A298;
    D_8005839C = &func_8004A67C;
    D_80058378 = &func_80049C20;
    D_800583A4 = &func_8002FD30;
    D_800583A8 = &func_8002FD38;
    D_800583AC = &func_8002FD40;
    D_800583B0 = &func_8002FD48;
    D_800583B4 = &func_8002FD50;
    D_800583B8 = &func_8002FD58;
    D_800583BC = &func_8002FD60;
    D_800583C0 = &func_8002FD68;
    D_800583C4 = &func_8002FD70;
    D_800583C8 = &func_8002FD78;
    D_800583CC = &func_8002FD80;
    D_800583D0 = &func_8002FD88;
    D_800583D4 = &func_8002FD90;
    D_800583D8 = &func_8002FD98;
    D_800583DC = &func_8002FDA0;
    D_800583E0 = &func_8002FDA8;
    D_800583E4 = &func_8002FDB0;
    D_800583E8 = &func_8002FDB8;
    D_800583EC = &func_8002FDC0;
    D_800583F0 = &func_8002FDC8;
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
            bytes_consumed = func_8004B078(sequence_id, channel, mode, (u8 *)cursor);
            if (bytes_consumed == -1) goto failed;
            next_channel = channel + 1;
            channel = next_channel;
            cursor += bytes_consumed;
        } while (next_channel < channel_count);
    }

    return sequence_id;
}
