#include "common.h"

/* GCC_VERSION: 2.5.7 */

/* Select sequence timing using the mode returned by the video-mode query.
 * Flag 0x1000 is stored separately; values below six select preset timings.
 */
s32 func_8003F23C(void);

void func_8004CB6C(s32 arg0)
{
    s32 mode = func_8003F23C();

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
            D_8005FF4C = 50;
            if (mode == 1) {
                D_80056258 = 5;
            } else {
                D_80056258 = 50;
            }
            break;
        case 1:
            D_8005FF4C = 60;
            if (mode == 0) {
                D_80056258 = 5;
            } else {
                D_80056258 = 60;
            }
            break;
        case 3:
            D_8005FF4C = 120;
            break;
        case 2:
            D_8005FF4C = 240;
            break;
        case 5:
            switch (mode) {
            case 0:
                D_8005FF4C = 60;
                break;
            case 1:
                D_8005FF4C = 50;
                break;
            default:
                D_8005FF4C = 60;
                break;
            }
            break;
        case 0:
            if (mode == 0) {
                D_8005FF4C = 60;
            } else if (mode == 1) {
                D_8005FF4C = 50;
            } else {
                D_8005FF4C = 60;
            }
            break;
        default:
            D_8005FF4C = 60;
            break;
        }
    } else {
        D_8005FF4C = D_80056258;
    }
}
