/* GCC_VERSION: 2.6.3 */
#include "common.h"
#include "ns.h"



/* GCC_VERSION: 2.6.3 */
#include "common.h"
#include "vector.h"

typedef struct {
    s16 m[3][3];
    s32 t[3];
} Matrix;

typedef struct {
    s16 x, y, z, pad;
} SVector;

typedef struct {
    s32 x, y, z, pad;
} LVector;

void func_80019144(LVector *, Matrix *, LVector *);
s32 func_8003905C(s32);
s32 func_800390D0(s32);
void func_80042C2C(Matrix *, Matrix *);
void func_80042D6C(Matrix *, Vec3 *);
void func_80042E9C(void *);
void func_80042F2C(void *);
void func_80042F4C(s32 *, s32 *, s32 *);
s32 func_80042FBC(SVector *, s16 *, s32 *, s32 *);
void func_80042FEC(SVector *, Vec3 *, s32 *);
s32 func_80026CA8(s32 *, s32 *);
s32 func_80029B90(Vec3 *, Vec3 *);

extern u8 D_8005726C[];
extern u8 D_800577E4[];
extern u8 D_80057844[];
extern s32 D_80057864, D_80057868, D_8005786C;
extern s32 D_80057888, D_8005788C, D_80057890;

void func_8002465C(Vec3 *arg0, Vec3 *arg1, Vec3 *arg2, Vec3 *arg3, Vec3 *arg4)
{
    Matrix m1;
    Matrix m2;
    LVector v_out;
    LVector v_in;
    s16 s1, c1;
    s16 s2, c2;
    s16 s3, c3;

    s1 = func_8003905C(arg2->z & 0xFFF);
    c1 = func_800390D0(arg2->z & 0xFFF);
    m1.m[0][0] = c1;
    m1.m[0][1] = 0;
    m1.m[0][2] = s1;
    m1.m[1][0] = 0;
    m1.m[1][1] = 0x1000;
    m1.m[1][2] = 0;
    m1.m[2][0] = -s1;
    m1.m[2][1] = 0;
    m1.m[2][2] = c1;

    s2 = func_8003905C(arg2->x);
    c2 = func_800390D0(arg2->x);
    m2.m[0][0] = 0x1000;
    m2.m[0][1] = 0;
    m2.m[0][2] = 0;
    m2.m[1][0] = 0;
    m2.m[1][1] = c2;
    m2.m[1][2] = -s2;
    m2.m[2][0] = 0;
    m2.m[2][1] = s2;
    m2.m[2][2] = c2;
    func_80042C2C(&m1, &m2);

    s3 = func_8003905C(-((arg2->z - arg2->y) & 0xFFF));
    c3 = func_800390D0(-((arg2->z - arg2->y) & 0xFFF));
    m2.m[0][0] = c3;
    m2.m[0][1] = 0;
    m2.m[0][2] = s3;
    m2.m[1][0] = 0;
    m2.m[1][1] = 0x1000;
    m2.m[1][2] = 0;
    m2.m[2][0] = -s3;
    m2.m[2][1] = 0;
    m2.m[2][2] = c3;
    func_80042C2C(&m1, &m2);

    if (arg3 != NULL) {
        func_80042D6C(&m1, arg3);
    }

    v_in.x = arg0->x / 16;
    v_in.y = arg0->y / 16;
    v_in.z = arg0->z / 16;
    func_80019144(&v_in, &m1, &v_out);

    v_out.x <<= 4;
    v_out.y <<= 4;
    v_out.z <<= 4;

    arg4->x = v_out.x + arg1->x;
    arg4->y = v_out.y + arg1->y;
    arg4->z = v_out.z + arg1->z;
}

s32 func_800248A0(Vec3 *arg0, Vec3 *arg1, s32 arg2)
{
    SVector sv;
    LVector v;
    s32 flag;

    v.x = arg0->x;
    v.y = arg0->y;
    v.z = arg0->z;
    if (arg2 != 0) {
        func_80042E9C(D_80057844);
    } else {
        func_80042E9C(D_800577E4);
    }
    func_80042F2C(D_8005726C);
    if (arg2 != 0) {
        sv.x = (v.x - D_80057888) >> 8;
        sv.y = (v.y - D_8005788C) >> 8;
        sv.z = (v.z - D_80057890) >> 8;
    } else {
        sv.x = (v.x - D_80057864) >> 8;
        sv.y = (v.y - D_80057868) >> 8;
        sv.z = (v.z - D_8005786C) >> 8;
    }
    func_80042FEC(&sv, arg1, &flag);
    arg1->x <<= 8;
    arg1->y = -(arg1->y << 8);
    arg1->z <<= 8;
    return -0xFF;
}

s32 func_800249E0(Vec3 *arg0, Vec3 *arg1)
{
    SVector sv;
    LVector v;
    s32 sxy;
    s32 p;
    s32 flag;
    s32 otz1;
    s32 otz2;
    s32 otz3;

    v.x = arg0->x;
    v.y = arg0->y;
    v.z = arg0->z;
    func_80042E9C(D_800577E4);
    func_80042F2C(D_8005726C);
    sv.x = (v.x - D_80057864) >> 8;
    sv.y = (v.y - D_80057868) >> 8;
    sv.z = (v.z - D_8005786C) >> 8;
    func_80042FBC(&sv, (s16 *)&sxy, &p, &flag);
    arg1->x = (s16)sxy << 8;
    arg1->y = -(sxy >> 16) << 8;
    func_80042F4C(&otz1, &otz2, &otz3);
    arg1->z = otz3 << 8;
    return -0xFF;
}

typedef struct CollideObj {
    u8 pad00[0x78];
    struct CollideObj *other;
    u8 pad7C[4];
    Vec3 pos;
    u8 pad8C[0x3C];
    u32 flagsC8;
    u8 padCC[0x54];
    u32 flags120;
    u8 pad124[0x24];
    s32 radius;
} CollideObj;

s32 func_80024AD4(CollideObj *arg0, s32 *arg1, CollideObj *arg2, s32 *arg3)
{
    s32 box1[6];
    s32 box2[6];
    CollideObj *other;
    s32 dist;

    other = arg0->other;
    if (other != NULL && other != arg2) {
        if (arg2->flags120 & 0x800) {
            arg2->other = arg0;
            return -0x1C;
        }
        dist = func_80029B90(&arg0->pos, &other->pos);
        if (func_80029B90(&arg0->pos, &arg2->pos) >= dist && !(other->flags120 & 0x800)) {
            return -0x1C;
        }
    }
    arg0->other = arg2;
    arg2->other = arg0;
    if (arg0->radius != 0) {
        box1[0] = arg1[0] + arg0->radius;
        box1[1] = arg1[1];
        box1[2] = arg1[2] + arg0->radius;
        box1[3] = arg1[3] - arg0->radius;
        box1[4] = arg1[4];
        box1[5] = arg1[5] - arg0->radius;
        if (func_80026CA8(box1, arg3) != 0) {
            arg0->flagsC8 |= 0x1000;
        }
    }
    if (arg2->radius != 0) {
        box2[0] = arg3[0] + arg2->radius;
        box2[1] = arg3[1];
        box2[2] = arg3[2] + arg2->radius;
        box2[3] = arg3[3] - arg2->radius;
        box2[4] = arg3[4];
        box2[5] = arg3[5] - arg2->radius;
        if (func_80026CA8(box2, arg1) != 0) {
            arg2->flagsC8 |= 0x1000;
        }
    }
    return -0xFF;
}
