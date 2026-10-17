/* GCC_VERSION: 2.6.3 */
/* GCC_CPU: 3000 */
/* GNU_AS_G: 8 */
#include "common.h"
#include "audio_channels.h"


extern s32 D_8005666C;
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

extern s32 D_800564FC;
extern u16 D_80056648;
extern s32 D_80056650;
extern s16 D_80056654;
extern s16 D_80056658;
extern s16 D_8005665C;
extern s32 D_800566C0;
extern s32 D_8005CFB0[];

MidiResourceEntry *func_80015118(s32 *, s32, s32);
s32 func_80015458(s32 *, s32);
void func_80049404(s16);
s16 func_80050D30(void *, s32, s32);
typedef void noreturn_fn(s32);
volatile noreturn_fn func_8003D680;
s16 func_80050C64(s16);
void func_8004BB3C(void);
s16 func_80049844(void *, s16, s16);
void func_80031964(AudioChannel *, s32, s32, s32);
void func_80049504(s16, s16, s16, s32);
s32 func_80031A40(AudioChannel *, s32, s32);

extern AudioChannel D_80056EBC[];

s32 func_800314C4(s32 *arg0) {
    s32 sp10;
    s32 i;
    MidiResourceEntry *entry;
    s32 arg3;
    s32 is_new;

    is_new = (D_80056658 == -1);
    if (D_8005666C != 0) {
        return -1;
    }
    if (D_800566C0 == 1) {
        if (D_80056650 != 0x6396347F) {
            func_80049404(D_80056654);
            sp10 = D_80056650;
            func_80015458(&sp10, 1);
        }
        if (*arg0 != 0x6396347F) {
            entry = func_80015118(arg0, 1, 1);
            D_80056650 = entry->id;
            for (i = 0; i < 7; i++) {
                if (entry->header->refs[i] != 0x6396347F) {
                    func_80015118(&entry->header->refs[i], 0, 1);
                }
            }
        } else {
            D_80056650 = *arg0;
            return 0;
        }
    }
    D_800566C0 = 2;
    entry = func_80015118(arg0, 1, 0);
    D_800564FC = 0;
    for (i = 0; i < 7; i++) {
        if (entry->header->refs[i] != 0x6396347F) {
            if (func_80015458(&entry->header->refs[i], 0) == 0) {
                return 0;
            }
        }
    }
    D_800566C0 = 3;
    D_8005665C = entry->header->count;
    if (D_80056658 == -1) {
        func_80015118(&entry->header->bank_ref, 1, 1);
        D_80056658 = func_80050D30(entry->vh, -1, (D_8005CFB0[0] << 16) | 0x2000);
        if (D_80056658 == -1) {
            func_8003D680(-1);
        }
        D_80056658 = func_80050C64(D_80056658);
        if (D_80056658 == -1) {
            func_8003D680(-1);
        }
        func_8004BB3C();
    }
    D_80056654 = func_80049844(entry->sep, D_80056658, D_8005665C);
    if (D_80056654 == -1) {
        func_8003D680(-1);
    }
    for (i = 0; i < D_8005665C; i++) {
        if (is_new) {
            s32 vol = (s16)D_80056648 >> 7;
            func_80031964(&D_80056EBC[i], vol | (vol << 16), i, arg3);
        } else {
            func_80031964(&D_80056EBC[i], 0, i, arg3);
            func_80049504(D_80056654, D_80056EBC[i].channel, (s16)D_80056648 >> 7, 30);
        }
    }
    return func_80031A40(D_80056EBC, 0, 0);
}
