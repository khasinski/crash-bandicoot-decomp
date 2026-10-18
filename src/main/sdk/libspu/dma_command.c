/* GCC_VERSION: 2.6.3 */
#include "common.h"

extern u16 D_800558E0;
extern volatile u16 *D_800558E4;

typedef void *va_list;
#define va_start(ap, last) ((ap) = (void *)(&(last) + 1))
#define va_arg(ap, type) ((ap) += 4, ((type *)(ap))[-1])

s32 func_80046A20(s32 mode, ...)
{
    va_list ap;
    s32 i;
    u16 ctrl;
    u32 val;
    u32 cmd;

    va_start(ap, mode);
    switch (mode) {
    case 2:
        val = va_arg(ap, u32);
        D_800558E4[0xD3] = D_800558E0 = val >> D_80055908;
        break;
    case 1:
        D_80055930 = 0;
        i = 0;
        while (D_800558E4[0xD3] != D_800558E0) {
            if (++i > 0xF00) {
                return -2;
            }
        }
        ctrl = D_800558E4[0xD5];
        ctrl = (ctrl & 0xFFCF) | 0x20;
        D_800558E4[0xD5] = ctrl;
        break;
    case 0:
        D_80055930 = 1;
        i = 0;
        while (D_800558E4[0xD3] != D_800558E0) {
            if (++i > 0xF00) {
                return -2;
            }
        }
        ctrl = D_800558E4[0xD5];
        ctrl |= 0x30;
        D_800558E4[0xD5] = ctrl;
        break;
    case 3:
        ctrl = (D_80055930 == 1) ? 0x30 : 0x20;
        i = 0;
        while ((D_800558E4[0xD5] & 0x30) != ctrl) {
            if (++i > 0xF00) {
                return -2;
            }
        }
        if (D_80055930 == 1) {
            *D_800558F8 = (*D_800558F8 & 0xF0FFFFFF) | 0x22000000;
        } else {
            *D_800558F8 = (*D_800558F8 & 0xF0FFFFFF) | 0x20000000;
        }
        val = va_arg(ap, u32);
        D_80055934 = val;
        val = va_arg(ap, u32);
        D_80055938 = (val / 64) + ((val & 0x3F) != 0);
        *D_800558E8 = D_80055934;
        *D_800558EC = (D_80055938 << 16) | 0x10;
        cmd = (D_80055930 == 1) ? 0x01000200 : 0x01000201;
        *D_800558F0 = cmd;
        break;
    }
    return 0;
}
