/* GCC_VERSION: 2.5.7 */
/* GCC_CPU: r4000 */
#include "common.h"

typedef void (*Callback)(void);
void EnterCriticalSection(void);
void ExitCriticalSection(void);
Callback InterruptCallback(s32, Callback);
s32 VSyncCallback(s32);



void SsQuit(void)
{
    if (D_8005625C == 0) {
        D_80056269 = 0;
        if (D_8005626A != 0x7F) {
            EnterCriticalSection();
            if (D_80056268 != 0) {
                VSyncCallback(0);
                D_80056268 = 0;
            } else if (D_8005626A == 0) {
                InterruptCallback(0, D_80056264);
                D_80056264 = NULL;
            } else {
                InterruptCallback(6, NULL);
            }
            ExitCriticalSection();
            D_8005626A = 0x7F;
        }
    }
}
