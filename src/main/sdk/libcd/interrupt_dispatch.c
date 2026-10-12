/* GCC_VERSION: 2.6.3 */
/* ASPSX_VERSION: 2.21 */
/* GNU_AS_G: 0 */
#include "common.h"

s32 func_8003D730(const char *, ...), func_8003E6D4(const char *, ...);
extern s32 D_800555AC, D_800555B0, D_800555B4, D_800555B8;
extern u8 D_800555C1[];
extern const char *D_800555C4[];
extern s32 D_80055664[], D_80055764[];
extern volatile u8 *D_80055864[], *D_80055868[], *D_80055870[];
extern volatile s8 *D_8005586C[];
extern volatile u8 D_8005587C[], D_8005587D, D_8005587E;
extern u8 D_80057198[], D_800571A0[], D_800571A8[];
extern const char D_80011524[], D_80011530[], D_8001154C[], D_80011560[];
/* The SDK uses both scalar and array views of these event bytes. */
extern volatile u8 cd_sync_status __asm__("D_8005587C");
extern volatile u8 cd_ready_status[] __asm__("D_8005587D");

static inline void cd_publish_response(u8 *destination, u8 *source)
{
    s32 count;
    if (destination) {
        count = 7;
        do {
            u8 value = *source++;
            count--;
            *destination++ = value;
        } while (count != -1);
    }
}

s32 func_80043BA8(void)
{
    volatile u8 interrupt;
    u8 response[8];
    s32 status, count, errors, status_mask;
    u8 *write, *remaining;
    u8 sampled;

    *D_80055864[0] = 1;
    sampled = *D_80055870[0] & 7;
    interrupt = sampled;
    errors = 0;
    if (interrupt == 0) return 0;
    while (interrupt != (*D_80055870[0] & 7)) {
        interrupt = *D_80055870[0] & 7;
    }
    write = response;
    count = 0;
read_response:
    if (*D_80055864[0] & 0x20) {
        count++;
        *write = *D_80055868[0];
        write++;
        if (count < 8) goto read_response;
    }
    /* The SDK caches the response status in a word after byte normalization. */
    status_mask = 0xFF;
    if (count < 8) {
        remaining = (u8 *)((u32)count + (u32)response);
        do {
            *remaining = 0;
            count++;
            remaining++;
        } while (count < 8);
    }
    *D_80055864[0] = 1;
    *D_80055870[0] = 7;
    *D_8005586C[0] = 7;
    if ((interrupt & 0xFF) != 3 || D_80055764[D_800555C1[0]] != 0) {
        if (!(D_800555B0 & 0x10) && (response[0] & 0x10)) D_800555B8++;
        status = response[0] & status_mask;
        errors = status & 0x1D;
        D_800555B0 = status;
        D_800555B4 = response[1];
    }
    if ((interrupt & 0xFF) == 5) {
        func_8003E6D4(D_80011524);
        if (D_800555AC > 0)
            func_8003D730(D_80011530, D_800555C4[D_800555C1[0]], D_800555B0, D_800555B4);
    }
    switch (interrupt) {
    case 3:
        if (errors) {
            D_8005587C[0] = 5;
            cd_publish_response(D_80057198, response);
            return 2;
        }
        if (D_80055664[D_800555C1[0]]) {
            D_8005587C[0] = 3;
            cd_publish_response(D_80057198, response);
            return 1;
        }
        D_8005587C[0] = 2;
        cd_publish_response(D_80057198, response);
        return 2;
    case 2:
        cd_sync_status = errors ? 5 : 2;
        cd_publish_response(D_80057198, response);
        return 2;
    case 1:
        D_8005587D = errors ? 5 : 1;
        cd_publish_response(D_800571A0, response);
        return 4;
    case 4:
        D_8005587E = 4;
        cd_ready_status[0] = D_8005587E;
        cd_publish_response(D_800571A8, response);
        cd_publish_response(D_800571A0, response);
        return 4;
    case 5:
        D_8005587D = 5;
        D_8005587C[0] = D_8005587D;
        cd_publish_response(D_80057198, response);
        cd_publish_response(D_800571A0, response);
        return 6;
    default:
        func_8003E6D4(D_8001154C);
        func_8003D730(D_80011560, (s32)interrupt);
        return -1;
    }
}
