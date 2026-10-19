/* GCC_VERSION: 2.6.3 */
#include "common.h"
void BIOS_Printf(const char *);
s32 CdReset(s32);
typedef void (*Callback)(void);
Callback CdSyncCallback(Callback);
Callback CdReadyCallback(Callback);
Callback CdDataCallback(Callback);
void def_cbsync(void),def_cbready(void),def_cbread(void);

s32 CdInit(void)
{
    s32 retries = 4;
    while (CdReset(1) != 1) {
        if (--retries == -1) {
            BIOS_Printf(D_8001139C);
            return 0;
        }
    }
    CdSyncCallback(def_cbsync);
    CdReadyCallback(def_cbready);
    CdDataCallback(def_cbread);
    return 1;
}
