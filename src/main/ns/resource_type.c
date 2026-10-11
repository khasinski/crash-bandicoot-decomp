/* GCC_VERSION: 2.6.3 */
#include "resource.h"
typedef ResourceHandle Request;
typedef ResourceEntry Entry;
s32 func_8003D740(char *,char *,...);
extern char D_80051728[],D_80056414[],D_80056718[];
extern u8 D_8005671C;
extern s8 D_8005671D;
s32 func_800126C0(Request *arg0) {
    s32 temp_v1;
    s32 var_v1;
    u32 temp_a2;

    temp_v1 = arg0->entry;
    if (!(temp_v1 & 3)) {
        return ((Entry *)temp_v1)->kind;
    }
    temp_a2 = arg0->id;
    var_v1 = 4;
    if (temp_a2 & 1) {
        D_8005671D = 0;
        temp_a2 = temp_a2 >> 1;
        do {
            D_80056718[var_v1] = D_80051728[temp_a2 & 0x3F];
            var_v1 -= 1;
            temp_a2 = temp_a2 >> 6;
        } while (var_v1 >= 0);
    } else {
        func_8003D740(D_80056718, D_80056414, temp_a2);
    }
    switch (D_8005671C) {
    case 0x56:
        return 1;
    case 0x58:
        return 0x14;
    case 0x53:
        return 4;
    case 0x47:
        return 2;
    case 0x57:
        return 3;
    case 0x54:
        return 5;
    case 0x4C:
        return 6;
    case 0x5A:
        return 7;
    case 0x43:
        return 0xB;
    case 0x41:
        return 0xC;
    case 0x4D:
        return 0xD;
    case 0x49:
        return 0x10;
    case 0x4E:
        return 0xE;
    case 0x44:
        return 0xF;
    case 0x50:
        return 0x11;
    case 0x55:
        return 0x12;
    case 0x42:
        return 0x13;
    default:
        return 0;
    }
}
