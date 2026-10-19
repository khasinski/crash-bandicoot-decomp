/* GCC_VERSION: 2.6.3 */
#include "object_links.h"
Node *GOOL_CreateObject(Node *, s32, s32, s32, s32, s32);      /* extern */
void Solid_TransSmoothStopAtSolid(s32, s32, s32);                           /* extern */
void Shader_ParamsUpdate(s32);                                 /* extern */
extern s32 *g_ns_page_pool;

extern Node D_80060DD0;
extern Node *D_800618AC;

extern s32 g_key_count;
extern s32 D_800619BC;
extern s32 g_cam_rot_xz;

void Level_InitMisc(s32 arg0) {
    Node *root;
    s32 var_a1;
    s32 var_a2;
    s32 temp_v0;

    temp_v0 = g_ns_page_pool[1];
    switch (temp_v0) {
    case 23:
        if (arg0 != 0) {
            D_800618AC = GOOL_CreateObject(&D_80060DD0, 0x27, 4, 0, 0, 1);
        }
        break;
    case 20:
    case 22:
        var_a1 = 0x17;
        if (arg0 != 0) {
            root = &D_80060DD0;
            var_a2 = 6;
            goto create_object;
        }
        break;
    case 5:
        var_a1 = 9;
        if (arg0 != 0) {
            root = &D_80060DD0;
            var_a2 = 4;
            goto create_object;
        }
        break;
    case 34:
    case 46:
        var_a1 = 0x35;
        if (arg0 != 0) {
            root = &D_80060DD0;
            var_a2 = 0xD;
create_object:
            GOOL_CreateObject(root, var_a1, var_a2, 0, 0, 1);
        }
        break;
    case 14:
        break;
    case 40:
    case 42:
        Shader_ParamsUpdate(1);
        break;
    default:
        D_800618AC = 0;
        break;
    }
    D_80061998[0] = 1;
    g_death_count[0] = 0;
    D_80061990 = 0;
    g_level_count = 0;
    if (D_80061A30 != 2) {
        D_800619BC = 0;
    }
    g_key_count = 0;
    Solid_TransSmoothStopAtSolid(0, 0, 0);
    D_80061A38 = 0x20;
    D_8005DFEC = 0;
    if (D_800618D0 != 0x600) {
        g_cam_rot_xz = 0x120;
    }
}
