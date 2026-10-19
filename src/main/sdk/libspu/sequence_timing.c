#include "common.h"

/* GCC_VERSION: 2.5.7 */

/* Select sequence timing using the mode returned by the video-mode query.
 * Flag 0x1000 is stored separately; values below six select preset timings.
 */
s32 GetVideoMode(void);

void SsSetTickMode(s32 arg0)
{
    s32 mode = GetVideoMode();

    if (arg0 & 0x1000) {
        D_8005625C = 1;
        D_80056258 = arg0 & 0xFFF;
    } else {
        D_8005625C = 0;
        D_80056258 = arg0;
    }
    if (D_80056258 < 6) {
        switch (D_80056258) {
        case 4:
            g_spawns_base = 50;
            if (mode == 1) {
                D_80056258 = 5;
            } else {
                D_80056258 = 50;
            }
            break;
        case 1:
            g_spawns_base = 60;
            if (mode == 0) {
                D_80056258 = 5;
            } else {
                D_80056258 = 60;
            }
            break;
        case 3:
            g_spawns_base = 120;
            break;
        case 2:
            g_spawns_base = 240;
            break;
        case 5:
            switch (mode) {
            case 0:
                g_spawns_base = 60;
                break;
            case 1:
                g_spawns_base = 50;
                break;
            default:
                g_spawns_base = 60;
                break;
            }
            break;
        case 0:
            if (mode == 0) {
                g_spawns_base = 60;
            } else if (mode == 1) {
                g_spawns_base = 50;
            } else {
                g_spawns_base = 60;
            }
            break;
        default:
            g_spawns_base = 60;
            break;
        }
    } else {
        g_spawns_base = D_80056258;
    }
}
