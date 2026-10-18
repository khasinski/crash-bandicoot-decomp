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
extern u8 D_800555C1[];
extern const char * const D_800555C4[];
extern const char *D_80055644[];
extern volatile u8 *D_80055864;
extern volatile CdStatus D_8005587C;
extern volatile u32 *D_800558D8;
extern u8 D_80057198[8];
extern u8 D_800571A0[8];
extern s32 D_800571B0;
extern s32 D_800571B4;
extern const char *D_800571B8[];
extern const char D_800114F8[];
extern const char D_80011508[];
extern const char D_8001164C[];
extern const char D_80011654[];

s32 CORE_VSync(s32);
s32 func_8003D730(const char *, ...);
s32 func_8003E6D4(const char *, ...);
s32 func_8003E848(void);
s32 func_80043BA8(void);
void func_80044C40(void);
s32 func_8004519C(void);
s32 func_800458C8(s32);

static inline void cd_set_timeout(const char *name)
{
    D_800571B0 = CORE_VSync(-1) + 0x1E0;
    D_800571B4 = 0;
    D_800571B8[0] = name;
}

static inline s32 cd_check_timeout(void)
{
    if (CORE_VSync(-1) > D_800571B0 || D_800571B4++ > 0x1E0000) {
        func_8003E6D4(D_800114F8);
        func_8003D730(D_80011508, D_800571B8[0], D_800555C4[D_800555C1[0]], D_80055644[D_8005587C.sync], D_80055644[D_8005587C.ready]);
        func_80044C40();
        return -1;
    }
    return 0;
}

static inline void cd_poll_interrupts(void)
{
    s32 event;
    u8 bank = *D_80055864 & 3;
    while ((event = func_80043BA8()) != 0) {
        if ((event & 4) && D_800555A4 != NULL) {
            D_800555A4(D_8005587C.ready, D_800571A0);
        }
        if ((event & 2) && D_800555A0 != NULL) {
            D_800555A0(D_8005587C.sync, D_80057198);
        }
    }
    *D_80055864 = bank;
}

static inline void cd_publish_response(u8 *dst, u8 *src)
{
    s32 count;
    if (dst != NULL) {
        s32 end;
        count = 7;
        end = -1;
        do {
            u8 val = *src++;
            count--;
            *dst++ = val;
        } while (count != end);
    }
}

s32 func_80045610(s32 mode, u8 *result)
{
    cd_set_timeout(D_8001164C);
    while (1) {
        if (cd_check_timeout() != 0) {
            return;
        }
        if (func_8003E848() != 0) {
            cd_poll_interrupts();
        }
        cd_publish_response(result, D_800571A0);
        if (CORE_VSync(-1) > D_80055880.time + 0x3C) {
            func_8004519C();
        }
        if (D_80055880.remaining == 0) {
            func_800458C8(0);
        }
        if (mode == 0 && D_80055880.remaining > 0) {
            continue;
        }
        return D_80055880.remaining;
    }
}

s32 func_800458C8(s32 mode)
{
    s32 ret;
    cd_set_timeout(D_80011654);
    do {
        if (cd_check_timeout() != 0) {
            return -1;
        }
        if ((*D_800558D8 & 0x01000000) == 0) {
            ret = 0;
            goto done;
        }
    } while (mode == 0);
    ret = 1;
done:
    return ret;
}
