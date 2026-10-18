/* GCC_VERSION: 2.6.3 */
/* ASPSX_VERSION: 2.21 */
/* GNU_AS_G: 0 */
#include "common.h"

typedef void (*CdCallback)(s32, u8 *);

typedef struct {
    u8 sync;
    u8 ready;
    u8 data;
    u8 pad[13];
} CdStatus;

typedef struct {
    s32 ack_clear[32];
    s32 unused[32];
    s32 param_count[32];
} CdCmdTable;

extern CdCallback D_800555A0;
extern CdCallback D_800555A4;

extern u8 D_800555C0;
extern u8 D_800555C1[];
extern const char * const D_800555C4[];

extern CdCmdTable D_800556E4;
extern volatile u8 *D_80055864;
extern volatile u8 *D_80055868;
extern volatile u8 *D_8005586C;
extern volatile CdStatus D_8005587C;
extern u8 D_80057198[8];
extern u8 D_800571A0[8];
extern u8 D_800571A8[8];

s32 VSync(s32);
s32 func_8003D730(const char *, ...);
s32 func_8003E6D4(const char *, ...);
s32 func_8003E848(void);
s32 func_80043BA8(void);
void func_80044C40(void);

static inline void cd_set_timeout(const char *name)
{
    D_800571B0 = VSync(-1) + 0x1E0;
    D_800571B4 = 0;
    D_800571B8[0] = name;
}

static inline s32 cd_check_timeout(void)
{
    if (VSync(-1) > D_800571B0 || D_800571B4++ > 0x1E0000) {
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

s32 func_800440EC(s32 mode, u8 *result)
{
    s32 status;
    cd_set_timeout(D_80011580);
    do {
        if (cd_check_timeout() != 0) {
            return -1;
        }
        if (func_8003E848() != 0) {
            cd_poll_interrupts();
        }
        status = D_8005587C.sync;
        if (status == 2 || status == 5) {
            D_8005587C.sync = 2;
            cd_publish_response(result, D_80057198);
            return status;
        }
    } while (mode == 0);
    return 0;
}

s32 func_80044370(s32 mode, u8 *result)
{
    s32 status;
    cd_set_timeout(D_80011588);
    do {
        if (cd_check_timeout() != 0) {
            return -1;
        }
        if (func_8003E848() != 0) {
            cd_poll_interrupts();
        }
        status = D_8005587C.data;
        if (status != 0) {
            D_8005587C.data = 0;
            cd_publish_response(result, D_800571A8);
            return status;
        }
        status = D_8005587C.ready;
        if (status != 0) {
            D_8005587C.ready = 0;
            cd_publish_response(result, D_800571A0);
            return status;
        }
    } while (mode == 0);
    return 0;
}

s32 func_80044640(u8 com, u8 *param, u8 *result, s32 arg3)
{
    s32 i;
    if (D_800555AC >= 2) {
        func_8003D730(D_80011594, D_800555C4[com]);
    }
    if (D_800556E4.param_count[com] != 0 && param == NULL) {
        if (D_800555AC > 0) {
            func_8003D730(D_8001159C, D_800555C4[com]);
        }
        return -2;
    }
    func_800440EC(0, NULL);
    if (com == 2) {
        for (i = 0; i < 4; i++) {
            D_800555BC[i] = param[i];
        }
    }
    D_8005587C.sync = 0;
    if (D_800556E4.ack_clear[com] != 0) {
        D_8005587C.ready = 0;
    }
    *D_80055864 = 0;
    for (i = 0; i < D_800556E4.param_count[com]; i++) {
        *D_8005586C = param[i];
    }
    D_800555C1[0] = com;
    *D_80055868 = com;
    if (arg3 != 0) {
        return 0;
    }
    cd_set_timeout(D_800115AC);
    while (D_8005587C.sync == 0) {
        if (cd_check_timeout() != 0) {
            return -1;
        }
        if (func_8003E848() != 0) {
            cd_poll_interrupts();
        }
    }
    if (D_8005587C.sync == 2 && com == 0x0E) {
        D_800555C0 = *param;
    }
    cd_publish_response(result, D_80057198);
    return -(D_8005587C.sync == 5);
}
