/* GCC_VERSION: 2.6.3 */
/* ASPSX_VERSION: 2.21 */
/* GNU_AS_G: 0 */
#include "common.h"

typedef void (*CdCallback)(s32, u8 *);

typedef struct CdReadState {
    volatile s32 state;
    s32 buffer;
    s32 count;
    volatile s32 cursor;
    volatile s32 mode;
    s32 size;
    volatile s32 remaining;
    s32 time;
    CdCallback word20;
    CdCallback word24;
} CdReadState;
extern CdReadState D_80055880;

typedef struct {
    u8 sync;
    u8 ready;
    u8 data;
    u8 pad[13];
} CdStatus;

extern CdCallback D_800555A0;
extern CdCallback D_800555A4;
extern s32 D_800555B0;

extern u8 D_800555C0;
extern u8 D_800555C1[];
extern volatile u8 *D_80055864;
extern volatile u8 *D_8005586C;
extern volatile u8 *D_80055870;

extern volatile CdStatus D_8005587C;

extern const char D_800115B4[];
extern const char D_800115C4[];

s32 VSync(s32);
s32 func_8003D730(const char *, ...);
s32 func_8003E6D4(const char *, ...);
s32 func_8003E6F4(void);
s32 func_8003E724(s32, void (*)(void));
s32 func_800440EC(s32, u8 *);
s32 func_80044640(u8, u8 *, u8 *, s32);
void func_80045B24(void);
void func_80045C04(s32, u8 *);

static inline void cd_sync_disc(void)
{
    CdCallback saved_callback;
    s32 poll_count = 0;

    if (D_800558A8 < D_800555B8) {
        saved_callback = D_800555A0;
        D_800555A0 = NULL;
        while (D_800555B0 & 0x10) {
            if ((poll_count++ & 0xFF) == 0) {
                func_8003E6D4(D_800115B4);
            }
            func_80044640(1, NULL, NULL, 0);
        }
        while (func_80044640(0x16, D_800558AC, NULL, 0) != 0) {
            func_80044640(1, NULL, NULL, 0);
            func_8003E6D4(D_800115C4);
        }
        D_800555A0 = saved_callback;
        D_800558A8 = D_800555B8;
    }
}

static inline void cd_reset_hw(void)
{
    *D_80055864 = 1;
    while (*D_80055870 & 7) {
        *D_80055864 = 1;
        *D_80055870 = 7;
        *D_8005586C = 7;
    }
    D_800555C0 = 0;
    D_8005587C.ready = (D_8005587C.data = 0);
    D_8005587C.sync = 2;
    *D_80055864 = 0;
    *D_80055870 = 0;
    *D_80055874 = 0x1325;
}

static inline void cd_init_callbacks(void)
{
    s32 *ptr = (s32 *)&D_80055880;
    s32 count = 9;
    D_800555A4 = NULL;
    D_800555A0 = NULL;
    D_800555B4 = 0;
    D_800555B0 = 0;
    do {
        *ptr = 0;
        count--;
        ptr++;
    } while (count != -1);
    func_8003E6F4();
    func_8003E724(2, &func_80045B24);
}

s32 func_80044E8C(void)
{
    func_8003E6D4(D_80011608);
    func_8003D730(D_80011614, D_800558B0);
    D_800555C1[0] = 0;
    D_800555C0 = 0;
    cd_init_callbacks();
    cd_reset_hw();
    func_80044640(1, NULL, NULL, 0);
    if (D_800555B0 & 0x10) {
        func_80044640(1, NULL, NULL, 0);
    }
    cd_sync_disc();
    if (func_80044640(0x0A, NULL, NULL, 0) != 0) {
        return -1;
    }
    if (func_80044640(0x0C, NULL, NULL, 0) != 0) {
        return -1;
    }
    return -(func_800440EC(0, NULL) != 2);
}

s32 func_8004519C(void)
{
    u8 mode;
    D_800555A4 = NULL;
    D_800555A0 = NULL;
    while (D_80055880.state-- > 0) {
        if (D_80055880.state < 7) {
            func_8003E6D4(D_80011620);
            func_8003D730(D_80011630, D_80055880.state, D_800555BC[0], D_800555BC[1], D_800555BC[2]);
            cd_sync_disc();
            if (func_80044640(9, NULL, NULL, 0) != 0) {
                continue;
            }
            if (func_80044640(2, D_800555BC, NULL, 0) != 0) {
                continue;
            }
        }
        cd_reset_hw();
        if ((mode = D_80055880.mode) != D_800555C0) {
            if (func_80044640(0x0E, &mode, NULL, 0) != 0) {
                continue;
            }
        }
        D_800555A4 = func_80045C04;
        D_80055880.cursor = D_80055880.count;
        func_80044640(6, NULL, NULL, 1);
        D_80055880.remaining = D_80055880.buffer;
        D_80055880.time = VSync(-1) + 0x1E0;
        return D_80055880.remaining;
    }
    return D_80055880.remaining = -1;
}
