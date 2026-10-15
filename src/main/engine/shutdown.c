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

