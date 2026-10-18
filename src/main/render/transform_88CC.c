/* GCC_VERSION: 2.6.3 */
/* CC1_FLAGS: -O2 */
/* GNU_AS_G: 8 */
#include "common.h"
extern s32 D_800618B8[];

typedef struct GoolVectors {
    s32 trans[3];
    s32 rot[3];
    s32 scale[3];
} GoolVectors;

typedef struct LightMat88CC {
    s16 v[3][3];
    s16 b[3];
    u16 c[12];
} LightMat88CC;

typedef struct GoolObj88CC {
    s32 kind;
    s32 unk04;
    s32 bound[6];
    void *exec;
    s32 unk24;
    void *zone;
    s32 unk2C;
    LightMat88CC light;
    u8 pad60[0x80 - 0x60];
    GoolVectors vectors;
    u8 padA4[0xCC - 0xA4];
    s32 status_b;
} GoolObj88CC;

typedef struct ZoneHeader88CC {
    u8 pad000[0x2E4];
    s32 light_mode;
    s32 far_clip;
    u8 pad2EC[0x318 - 0x2EC];
    u16 light_src[24];
} ZoneHeader88CC;

typedef struct ResourceEntry88CC {
    u8 pad00[0x10];
    ZoneHeader88CC *data;
} ResourceEntry88CC;

extern u8 D_80057844[];

extern u8 D_80057824[];
extern s32 D_80057888[], D_8005788C[], D_80057890[];
extern s32 D_800578D0[];
extern s32 D_800618B0[];

extern GoolObj88CC *D_800618CC[];
extern GoolObj88CC *D_800566B4[];
extern ResourceEntry88CC *D_80057914[];

void func_80042E9C(void *);
void func_80042F2C(void *);
void func_80042FEC(void *, void *, void *);
void func_800351C8(void *, void *, void *, void *);
s32 func_80042B9C(s32);
void func_8003913C(void *, void *, void *, void *);
void func_80039BD4(void *, void *, void *, void *);

typedef struct Matrix88CC {
    s16 m[3][3];
    s32 t[3];
} Matrix88CC;

s32 func_800180CC(u8 *arg0, void *arg1, GoolObj88CC *arg2, s32 arg3, s32 *arg4)
{
    s16 sp10[4];
    Matrix88CC sp18;
    u8 sp38[0x50];
    s32 sp88;
    u8 *p1, *p2;
    GoolVectors *vectors;
    s32 far_z;
    s32 status_b;
    s32 z, h;
    s32 *d;
    s32 x0, y0, x1, y1;
    s32 sx, sy;
    ZoneHeader88CC *header;
    s32 diff, i, val;
    u16 *src, *dst;
    LightMat88CC *light;
    s32 tx, ty, tz;
    s32 ox, oy, oz;
    s32 dx, dy, dz, dist, atten;
    s32 i4, val4;
    s32 i3, val3;
    u16 *src3;

    p1 = arg0;
    p2 = p1;
    vectors = &arg2->vectors;
    if (arg4 != NULL) {
        *arg4 = 0;
    }
    func_80042E9C(D_80057844);
    func_80042F2C(D_8005726C);
    sp10[0] = (arg2->vectors.trans[0] - (*D_80057888)) >> 8;
    sp10[1] = (arg2->vectors.trans[1] - (*D_8005788C)) >> 8;
    sp10[2] = (arg2->vectors.trans[2] - (*D_80057890)) >> 8;
    func_80042FEC(sp10, sp18.t, &sp88);

    if (!((*D_800618B0) & 0x10000)) {
        far_z = (*D_80057914)->data->far_clip >> 8;
        sp88 = far_z;
        if (far_z != 0 && sp18.t[2] > far_z) {
            return 0;
        }
        if (far_z == 0 && sp18.t[2] > 0x2EE0) {
            return 0;
        }
        status_b = arg2->status_b;
        if (!(status_b & 0x40000)) {
            d = D_800578D0;
            z = sp18.t[2];
            h = *d;
            if (z <= h) {
                return 0;
            }
            if (status_b < 0) {
                func_800351C8(arg2->bound, arg3 ? (p2 + 0x2C) : (p1 + 0x2C), vectors, (u8 *)d - 0x48);
                x0 = *(s32 *)0x1F800048;
                y0 = *(s32 *)0x1F80004C;
                x1 = *(s32 *)0x1F800050;
                y1 = *(s32 *)0x1F800054;
                if ((x0 < -0x100 && x1 < -0x100)
                    || (x0 > 0x100 && x1 > 0x100)
                    || (y0 < -0x6C && y1 < -0x6C)
                    || (y0 > 0x6C && y1 > 0x6C)) {
                    return 0;
                }
            } else {
                sx = sp18.t[0];
                sx = (sx * h) / z;
                sy = sp18.t[1];
                sy = (sy * h) / z;
                if (__builtin_abs(sx) >= 0x13D || (u32)(sy + 0x8A) >= 0x147) {
                    return 0;
                }
            }
        }
        if (arg2 != (*D_800566B4) && !(arg2->status_b & 0x400)) {
            header = (*D_80057914)->data;
            switch (header->light_mode) {
            case 2:
                dst = (u16 *)&arg2->light;
                src = header->light_src;
                diff = sp18.t[2] - (*D_800618B8);
                if (diff > 0) {
                    diff <<= 3;
                    if (diff > 0x7FFF) {
                        return 0;
                    }
                } else {
                    diff = 0;
                }
                for (i = 0; i < 12; i++) {
                    val = src[i] + diff;
                    if (val > 0x7FFF) {
                        val = 0x7FFF;
                    }
                    dst[i] = val;
                }
                for (i = 12; i < 24; i++) {
                    val = src[i] + diff;
                    if (val > 0x1000) {
                        val = 0x1000;
                    }
                    dst[i] = val;
                }
                break;
            case 4:
                light = &arg2->light;
                if ((*D_800618CC) != NULL) {
                    tx = (*D_800618CC)->vectors.trans[0];
                    ty = (*D_800618CC)->vectors.trans[1];
                    tz = (*D_800618CC)->vectors.trans[2];
                } else {
                    tx = (*D_800566B4)->vectors.trans[0];
                    ty = (*D_800566B4)->vectors.trans[1];
                    tz = (*D_800566B4)->vectors.trans[2];
                }
                light->b[0] = 0;
                light->b[1] = 0;
                light->b[2] = 0;
                light->v[0][0] = 0;
                light->v[0][1] = 0;
                light->v[0][2] = 0;
                light->v[1][0] = 0;
                light->v[1][1] = 0;
                light->v[1][2] = 0;
                light->v[2][0] = 0;
                light->v[2][1] = 0;
                light->v[2][2] = 0;
                ox = arg2->vectors.trans[0];
                dx = (ox - tx) >> 8;
                oy = arg2->vectors.trans[1];
                oy -= 0x32000;
                dy = (oy - ty) >> 8;
                oz = arg2->vectors.trans[2];
                dz = (oz - tz) >> 8;
                dist = func_80042B9C(dx * dx + dy * dy + dz * dz);
                if (D_80056470 <= 0) {
                    D_80056470 = 1;
                }
                if (dist <= 0) {
                    dist = 1;
                }
                ox = ((tx - ox) << 8) / dist;
                oy = ((ty - oy) << 8) / dist;
                atten = 0x1770 - dist;
                oz = ((tz - oz) << 8) / dist;
                if (atten < 0) {
                    atten = 0;
                }
                ox = (ox * atten) >> 8;
                oy = (oy * atten) >> 8;
                oz = (oz * atten) >> 8;
                ox /= D_80056470;
                oy /= D_80056470;
                oz /= D_80056470;
                if (ox > 0x1770) {
                    ox = 0x1770;
                }
                if (ox < -0x1770) {
                    ox = -0x1770;
                }
                if (oy > 0x1770) {
                    oy = 0x1770;
                }
                if (oy < -0x1770) {
                    oy = -0x1770;
                }
                if (oz > 0x1770) {
                    oz = 0x1770;
                }
                if (oz < -0x1770) {
                    oz = -0x1770;
                }
                for (i4 = 0; i4 < 3; i4++) {
                    light->v[i4][0] = ox;
                    light->v[i4][1] = oy;
                    light->v[i4][2] = oz;
                }
                val4 = func_80042B9C(ox * ox + oy * oy + oz * oz) >> 5;
                light->b[0] = val4;
                light->b[1] = val4;
                light->b[2] = val4;
                break;
            case 3:
                if (arg3 != 0) {
                    dst = (u16 *)&arg2->light;
                    src3 = header->light_src;
                    diff = sp18.t[2] - (*D_800618B8);
                    if (diff > 0) {
                        diff >>= 2;
                        if (diff >= 0x6D61) {
                            return 0;
                        }
                    } else {
                        diff = 0;
                    }
                    for (i3 = 0; i3 < 24; i3++) {
                        val3 = src3[i3] - diff;
                        if (val3 < 0) {
                            val3 = 0;
                        }
                        dst[i3] = val3;
                    }
                } else {
                    val3 = (sp18.t[2] - (*D_800618B8)) / 200;
                    *arg4 = val3;
                    if (val3 < 0) {
                        *arg4 = 0;
                    }
                    if (*arg4 >= 9) {
                        *arg4 = 8;
                    }
                }
                break;
            }
        }
    }
    {
        s32 z = (s32)vectors & 1;
        if (z >> 1) {
            arg4 = NULL;
        }
    }
    if (arg3 != 0) {
        func_8003913C(D_80057824, arg1, vectors, &arg2->light);
    } else {
        func_80039BD4(D_80057824, arg1, vectors, &arg2->light);
    }
    func_80042F2C(&sp18);
    return 1;
}
