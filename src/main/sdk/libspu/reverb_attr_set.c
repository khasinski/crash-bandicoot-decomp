/* GCC_VERSION: 2.6.3 */
#include "common.h"

typedef struct {
    u32 mask;
    s32 mode;
    s16 depth_left;
    s16 depth_right;
    s32 delay;
    s32 feedback;
} SpuReverbAttr;

typedef struct {
    u32 mask;
    s16 values[32];
} SpuReverbRegisters;

extern s32 func_80047190(u32);
extern void func_80047718(SpuReverbRegisters *);
extern s32 func_80047D38(u32);
extern void func_80046DB8(s32, u32, s32);

extern volatile u16 *D_800558E4;
extern u32 D_80055958;
extern s32 D_80055960;
extern volatile s16 D_80055964;
extern volatile s16 D_80055966;
extern s32 D_80055968;
extern s32 D_8005596C;
extern u32 D_80055DAC[];
extern SpuReverbRegisters D_80055DFC[];

s32 func_80047208(SpuReverbAttr *arg0)
{
    SpuReverbRegisters param;
    s32 clear_mode;
    u32 mask;
    s32 all;
    s32 set_mode;
    s32 set_delay;
    s32 set_feedback;
    s32 was_on;
    s32 mode;
    s32 delay_offset;
    u16 ctrl;

    was_on = 0;
    set_mode = 0;
    set_delay = 0;
    clear_mode = 0;
    mask = arg0->mask;
    set_feedback = 0;
    all = (mask == 0);
    param.mask = 0;
    if (all || (mask & 1)) {
        mode = arg0->mode;
        if (mode & 0x100) {
            mode &= ~0x100;
            clear_mode = 1;
        }
        if ((u32)mode >= 0xA || func_80047190(D_80055DAC[mode]) != 0) {
            return -1;
        }
        set_mode = 1;
        D_80055960 = mode;
        {
            u8 *dst = (u8 *)&param;
            s32 i = 0x43;
            s32 idx = *(volatile s32 *)&D_80055960;
            u8 *src;
            D_80055958 = D_80055DAC[idx];
            src = (u8 *)&D_80055DFC[idx];
            do {
                *dst++ = *src++;
            } while (--i != -1);
        }
        switch (D_80055960) {
        case 7:
            D_8005596C = 0x7F;
            D_80055968 = 0x7F;
            break;
        case 8:
            D_8005596C = 0;
            D_80055968 = 0x7F;
            break;
        default:
            D_8005596C = 0;
            D_80055968 = 0;
            break;
        }
    }
    if (all || (mask & 8)) {
        switch (D_80055960) {
        case 7:
        case 8:
            set_delay = 1;
            if (set_mode == 0) {
                u8 *dst = (u8 *)&param;
                s32 i = 0x43;
                u8 *src = (u8 *)&D_80055DFC[*(volatile s32 *)&D_80055960];
                do {
                    *dst++ = *src++;
                } while (--i != -1);
                param.mask = 0x0C011C00;
            }
            D_80055968 = arg0->delay;
            param.values[10] = ((D_80055968 << 13) / 127) - param.values[0];
            delay_offset = (D_80055968 << 12) / 127;
            param.values[11] = delay_offset - param.values[1];
            param.values[12] = delay_offset + param.values[13];
            param.values[16] = delay_offset + param.values[17];
            param.values[26] = delay_offset + param.values[28];
            param.values[27] = delay_offset + param.values[29];
            break;
        default:
            D_80055968 = 0;
            break;
        }
    }
    if (all || (mask & 0x10)) {
        switch (D_80055960) {
        case 7:
        case 8:
            set_feedback = 1;
            if (set_mode == 0) {
                if (set_delay == 0) {
                    u8 *dst = (u8 *)&param;
                    s32 i = 0x43;
                    u8 *src = (u8 *)&D_80055DFC[*(volatile s32 *)&D_80055960];
                    do {
                        *dst++ = *src++;
                    } while (--i != -1);
                    param.mask = 0x80;
                } else {
                    param.mask |= 0x80;
                }
            }
            D_8005596C = arg0->feedback;
            param.values[7] = (D_8005596C * 33024) / 127;
            break;
        default:
            D_8005596C = 0;
            break;
        }
    }
    if (set_mode != 0) {
        was_on = (D_800558E4[0xD5] >> 7) & 1;
        if (was_on != 0) {
            ctrl = D_800558E4[0xD5];
            ctrl &= 0xFF7F;
            D_800558E4[0xD5] = ctrl;
        }
        goto clear_depth;
    }
    if (all || (mask & 2)) {
        D_800558E4[0xC2] = arg0->depth_left;
        D_80055964 = arg0->depth_left;
    }
    if (all || (mask & 4)) {
        D_800558E4[0xC3] = arg0->depth_right;
        D_80055966 = arg0->depth_right;
    }
    if (0) {
clear_depth:
        D_800558E4[0xC2] = 0;
        D_800558E4[0xC3] = 0;
        D_80055964 = 0;
        D_80055966 = 0;
    }
    if (set_mode || set_delay || set_feedback) {
        func_80047718(&param);
    }
    if (clear_mode) {
        func_80047D38(D_80055960);
    }
    if (set_mode) {
        func_80046DB8(0xD1, D_80055958, 0);
        if (was_on) {
            ctrl = D_800558E4[0xD5];
            ctrl |= 0x80;
            D_800558E4[0xD5] = ctrl;
        }
    }
    return 0;
}
