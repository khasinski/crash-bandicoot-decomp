/* GCC_VERSION: 2.5.7 */
/* GCC_CPU: r4000 */
#include "common.h"

typedef struct {
    s32 form;
    s32 ver;
    s32 id;
    u32 fsize;
    u16 reserved0;
    u16 ps;
    u16 ts;
    u8 vs;
    u8 pad;
    u8 mvol;
    u8 mpan;
    u8 attr1;
    u8 attr2;
    u32 reserved1;
} VabHdr;

typedef struct {
    u8 tones;
    u8 mvol;
    u8 prior;
    u8 mode;
    u8 mpan;
    s8 reserved0;
    s16 attr;
    u32 reserved1;
    u16 reserved2;
    u16 reserved3;
} ProgAtr;

s32 func_8004DDD4(void);
void func_8004DDA8(s32);
s32 func_8005115C(s32);

extern u16 D_80060CE8;

extern VabHdr *D_80057EB0[];
extern ProgAtr *D_80057E70[];

s16 func_80050D60(u8 *addr, s16 vabid, s16 mode, u32 sbaddr) {
    u32 vag_len[256];
    s32 i;
    s16 var_s2;
    VabHdr *vab_hdr;
    ProgAtr *prog_ptr;
    u8 *ptr;
    u32 var_s0;
    u8 num_vags;
    u32 var_a3;

    var_s2 = 0x10;
    if (func_8004DDD4() == 1) {
        return -1;
    }
    func_8004DDA8(1);
    if (vabid < 0x10) {
        if (vabid == -1) {
            for (i = 0; i < 0x10; i++) {
                if (D_8005E578[i] == 0) {
                    goto found;
                }
            }
            goto check_s2;
        found:
            D_8005E578[i] = 1;
            var_s2 = i;
            D_80060CE8 += 1;
        } else {
            if (D_8005E578[vabid] == 0) {
                D_8005E578[vabid] = 1;
                var_s2 = vabid;
                D_80060CE8 += 1;
            }
        }
    } else {
        func_8004DDA8(0);
        return -1;
    }
check_s2:
    if (var_s2 >= 0x10) {
        func_8004DDA8(0);
        return -1;
    }
    ptr = addr;
    D_80057EB0[var_s2] = (VabHdr *)ptr;
    ptr += 0x20;
    vab_hdr = D_80057EB0[var_s2];
    if (((u32)vab_hdr->form >> 8) != 0x564142) {
        D_8005E578[var_s2] = 0;
        func_8004DDA8(0);
        D_80060CE8 -= 1;
        return -1;
    }
    if ((vab_hdr->form & 0xFF) == 0x70) {
        if (vab_hdr->ver < 5) {
            D_8005CFC4 = 0x40;
        } else {
            D_8005CFC4 = 0x80;
        }
    } else {
        D_8005CFC4 = 0x40;
    }
    if (vab_hdr->ps > D_8005CFC4) {
        D_8005E578[var_s2] = 0;
        func_8004DDA8(0);
        D_80060CE8 -= 1;
        return -1;
    }
    D_80057E70[var_s2] = (ProgAtr *)ptr;
    prog_ptr = (ProgAtr *)ptr;
    ptr += D_8005CFC4 * 0x10;
    var_s0 = 0;
    for (i = 0; i < D_8005CFC4; i++) {
        prog_ptr[i].reserved1 = var_s0;
        if (prog_ptr[i].tones != 0) {
            var_s0 += 1;
            var_a3 = i;
        }
    }
    D_80057EF8[var_s2] = ptr;
    var_s0 = 0;
    ptr += vab_hdr->ps << 9;
    num_vags = vab_hdr->vs;
    for (i = 0; i < 256; i++) {
        if (i <= num_vags) {
            u16 raw_len = *(u16 *)ptr;
            if (vab_hdr->ver >= 5) {
                vag_len[i] = raw_len << 3;
            } else {
                vag_len[i] = raw_len << 2;
            }
            var_s0 += vag_len[i];
        }
        ptr += 2;
    }
    D_80060D30[var_s2] = ptr;
    if (mode == 0) {
        var_a3 = func_8005115C(var_s0);
        if (var_a3 == -1) {
            D_8005E578[var_s2] = 0;
            func_8004DDA8(0);
            D_80060CE8 -= 1;
            return -1;
        }
    } else {
        var_a3 = sbaddr;
    }
    if ((u32)(var_a3 + var_s0) > 0x80000U) {
        D_8005E578[var_s2] = 0;
        func_8004DDA8(0);
        D_80060CE8 -= 1;
        return -1;
    }
    D_80060CF0[var_s2] = var_a3;
    var_s0 = 0;
    for (i = 0; i <= num_vags; i++) {
        var_s0 += vag_len[i];
        if ((i & 1) == 0) {
            prog_ptr[i / 2].reserved2 = (var_a3 + var_s0) >> 3;
        } else {
            prog_ptr[i / 2].reserved3 = (var_a3 + var_s0) >> 3;
        }
    }
    D_80060CA8[var_s2] = var_s0;
    D_8005E578[var_s2] = 2;
    return var_s2;
}
