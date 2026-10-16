/* GCC_VERSION: 2.6.3 */
#include "common.h"
#include "ns.h"
/* GNU_AS_G: 8 */
void func_80016718(s32);
void func_80016A6C(void);
void func_8002F75C(void);
void func_8002F8C4(void);
void func_80034504(void);
void func_8003CB9C(void);
s32 func_8003CD3C(void);
s32 func_8003E1A8(u32, s32, s32, void (*)(void));
void func_8003E1B8(s32);
void func_8003E1D8(s32);
void func_8003E1E8(s32);
void func_8003E1F8(void);
void func_8003E208(void);
void func_8003E298(u32, s32, s32);
void func_8003E370(u32);
void func_8003E3A4(u32);
void func_8003E410(s32);
void func_8003E490(void);
void func_8003E6F4(void);
void func_8003E7E8(void);
void func_8003F224(s32);
s32 func_8003FDC0(s32);
void func_80042B1C(void);
void func_8004324C(void);
s32 func_80043520(u8, u8 *, u8 *);
/* External word view: this unit uses an absolute reference to the flag. */
extern s32 D_80056410[];
extern s32 D_80056708;
extern u32 D_8005728C[];

typedef struct {
    u32 word00;
    u32 word04;
    u32 word08;
    u32 word0C;
    u32 word10;
} PadSlot;

typedef struct {
    s32 count;
    PadSlot slots[2];
} PadState;

extern PadState D_8005E718;

s32 func_8001652C(void)
{
    s32 i;

    for (i = 0; i < 0x400; i++) {
        ((u8 *)0x1F800000)[i] = 0;
    }
    func_8003F224(0);
    func_80042B1C();
    if (D_80056410[0] != 0) {
        func_8003E6F4();
        func_8004324C();
    }
    func_80016718(2);
    func_8003CB9C();
    func_8003E1F8();
    func_8003E3A4(0xF2000002);
    D_80056708 = func_8003E1A8(0xF2000002, 2, 0x1000, func_80034504);
    func_8003E1D8(D_80056708);
    func_8003E298(0xF2000002, 0x1000, 0x1000);
    func_8003E370(0xF2000002);
    func_8003E208();
    func_80016A6C();
    func_8002F75C();
    D_8005C528.draw_skip = 0;
    for (i = 0; i < 4; i++) {
        D_8005728C[i] = 0x6396347F;
    }
    for (i = 0; i < 16; i++) {
        D_800580A0[i].word18 = 0x6396347F;
    }
    if (D_80056410[0] != 0) {
        func_8002F8C4();
    }
    return -0xFF;
}

s32 func_8001668C(void)
{
    if (D_80056410[0] != 0) {
        func_80043520(8, NULL, NULL);
        func_8003E7E8();
    }
    func_8003CD3C();
    func_8003E490();
    func_8003FDC0(3);
    func_8003E1F8();
    func_8003E3A4(0xF2000002);
    func_8003E1E8(D_80056708);
    func_8003E1B8(D_80056708);
    func_8003E208();
    return -0xFF;
}

void func_80016718(s32 count)
{
    PadState *state = &D_8005E718;
    s32 i;

    state->count = count;
    for (i = 0; i < count; i++) {
        state->slots[i].word10 = 0;
        state->slots[i].word08 = 0;
        state->slots[i].word04 = 0;
        D_8005E718.slots[i].word00 = 0;
        func_8003E410(i);
    }
}

typedef struct {
    u32 frame;
    u32 buttons;
} DemoInput;

typedef struct {
    s32 count;
    u8 pad04[0x524];
    s32 seed;
    DemoInput inputs[1];
} DemoRecording;

typedef struct {
    u8 pad00[0x84];
    s32 word84;
} DemoBufferView;

typedef struct {
    s32 player;
    u8 pad04[0x70];
    s32 playback_mode;
} PlaybackState;

void func_80024040(s32, s32, s32, s32, s32 *);
u32 func_8003E460(s32);
extern DemoInput *D_800566A8;
extern DemoRecording *D_80056704;
extern DemoBufferView *D_80058404[];
extern PlaybackState D_800619BC;

void func_800167A4(void)
{
    s32 i = 0;
    s32 arg[4];

    if (D_8005E718.count > 0) {
        do {
            PadSlot *slot = &D_8005E718.slots[i];
            u32 raw;
            u32 buttons;

            slot->word10 = slot->word08;
            slot->word08 = slot->word04;
            slot->word0C = slot->word00;
            raw = func_8003E460(i);
            if (i == 0) {
                buttons = raw & 0xFFFF;
            } else {
                buttons = raw >> 16;
            }
            slot->word04 = buttons;
            if (slot->word04 & 0x1000) {
                slot->word04 &= 0xBFFF;
            }
            if (slot->word04 & 0x8000) {
                slot->word04 &= ~0x2000;
            }
            if (i == 0) {
                if (D_800619BC.playback_mode != 2) {
                    if (D_800619BC.playback_mode == 3) {
                        slot->word04 = 0;
                    }
                } else {
                    u32 pressed = slot->word04;
                    s32 player;

                    if (D_800566A8 == D_80056704->inputs) {
                        D_80058404[0]->word84 = D_80056704->seed;
                    }
                    slot->word04 = D_800566A8->buttons;
                    D_800566A8++;
                    if ((pressed & 0x9F0) || D_800566A8 >= &D_80056704->inputs[D_80056704->count]) {
                        arg[0] = 0;
                        if ((player = D_800619BC.player) != 0) {
                            func_80024040(0, player, 0xE00, 1, arg);
                            D_800619BC.playback_mode = 3;
                        } else {
                            D_800619BC.playback_mode = 0;
                        }
                    }
                }
            }
            slot->word00 = ~slot->word08 & slot->word04 & 0xF9FF;
            i++;
        } while (i < D_8005E718.count);
    }
}

