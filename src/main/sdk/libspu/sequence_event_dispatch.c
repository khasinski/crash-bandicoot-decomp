/* GCC_VERSION: 2.5.7 */
/* GCC_CPU: r4000 */
#include "common.h"

extern s32 D_80056258;
extern s32 D_8005625C;
extern void (*D_80056260)(void);
extern void (*D_80056264)(void);
extern u8 D_80056268;
extern u8 D_80056269;
extern u8 D_8005626A;

extern void func_8003E1F8(void);
extern void func_8003E208(void);
extern s32 func_8003E298();
extern s32 func_8003E3D8(u32);
extern void *func_8003E724(s32, void (*)(void));
extern s32 func_8003E784(void (*)(void));
extern void func_8004B828(void);
extern void func_8004B868(void);

void func_8004B8B8(s32 arg0) {
    s32 i;
    u16 target;
    u32 rcnt;
    u8 *flag_p;

    i = 0;
loop:
    i += 3;
    if (i < 3000) {
        goto loop;
    }
    flag_p = &D_80056268;
    *flag_p = 0;
    D_80056269 = 0;
    D_80056264 = 0;
    D_8005626A = 6;
    rcnt = 0xF2000002;
    switch (D_80056258) {
    case 0:
        D_8005626A = 0x7F;
        return;
    case 5:
        D_8005626A = 0;
        if (arg0 == 0) {
            *flag_p = 1;
        } else {
            rcnt = 0xF2000003;
            target = 1;
        }
        break;
    case 3:
        target = 0x89D0;
        break;
    case 2:
        target = 0x44E8;
        break;
    default:
        {
            u8 *p = (u8 *)&D_8005625C;
            s32 tmp;
            if (*(s32 *)p != 0) {
                return;
            }
            tmp = (s32)p & 1;
            if ((tmp >> 1) == 0) {
                goto L_after;
            }
            if (*flag_p) {
                goto L_after;
            }
            *flag_p = 0;
            return;
        L_after:
            if (*(s32 *)(p - 4) < 70) {
                target = 0x204CC0 / *(s32 *)(p - 4);
                p[0xD]++;
            } else {
                target = 0x409980 / *(s32 *)(p - 4);
            }
        }
        break;
    }
    if (D_80056268 != 0) {
        func_8003E1F8();
        func_8003E784(D_80056260);
    } else {
        func_8003E1F8();
        func_8003E3D8(rcnt);
        func_8003E298(rcnt, target, 0x1000);
        if (D_8005626A == 0) {
            D_80056264 = func_8003E724(0, 0);
            func_8003E724(D_8005626A, func_8004B828);
        } else if (D_80056269 == 0) {
            func_8003E724(D_8005626A, D_80056260);
        } else {
            func_8003E724(D_8005626A, func_8004B868);
        }
    }
    func_8003E208();
}
