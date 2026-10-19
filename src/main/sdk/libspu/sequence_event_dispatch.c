/* GCC_VERSION: 2.5.7 */
/* GCC_CPU: r4000 */
#include "common.h"



void EnterCriticalSection(void);
void ExitCriticalSection(void);
s32 SetRCnt();
s32 ResetRCnt(u32);
void *InterruptCallback(s32, void (*)(void));
s32 VSyncCallback(void (*)(void));
void _SsTrapIntrVSync(void);
void _SsSeqCalledTbyT_1per2(void);

void _SsStart(s32 arg0) {
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
            struct { s32 val; u8 pad[9]; u8 flag_d; } *p = (void *)&D_8005625C;
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
            if (*((s32 *)p - 1) < 70) {
                target = 0x204CC0 / *((s32 *)p - 1);
                p->flag_d++;
            } else {
                target = 0x409980 / *((s32 *)p - 1);
            }
        }
        break;
    }
    if (D_80056268 != 0) {
        EnterCriticalSection();
        VSyncCallback(D_80056260);
    } else {
        EnterCriticalSection();
        ResetRCnt(rcnt);
        SetRCnt(rcnt, target, 0x1000);
        if (D_8005626A == 0) {
            D_80056264 = InterruptCallback(0, 0);
            InterruptCallback(D_8005626A, _SsTrapIntrVSync);
        } else if (D_80056269 == 0) {
            InterruptCallback(D_8005626A, D_80056260);
        } else {
            InterruptCallback(D_8005626A, _SsSeqCalledTbyT_1per2);
        }
    }
    ExitCriticalSection();
}
