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

void Gfx_Transform(LVector *, Matrix *, LVector *);
s32 sin(s32);
s32 cos(s32);
void MulMatrix(Matrix *, Matrix *);
void ScaleMatrix(Matrix *, Vec3 *);
void SetRotMatrix(void *);
void SetTransMatrix(void *);
void ReadSZfifo3(s32 *, s32 *, s32 *);
s32 RotTransPers(SVector *, s16 *, s32 *, s32 *);
void RotTrans(SVector *, Vec3 *, s32 *);
s32 Level_TestBoundIntersection(s32 *, s32 *);
s32 Math_ApxDist(Vec3 *, Vec3 *);

extern u8 D_80057844[];
extern s32 D_80057864;

void Gool_Transform(Vec3 *arg0, Vec3 *arg1, Vec3 *arg2, Vec3 *arg3, Vec3 *arg4)
{
    Matrix m1;
    Matrix m2;
    LVector v_out;
    LVector v_in;
    s16 s1, c1;
    s16 s2, c2;
    s16 s3, c3;

    s1 = sin(arg2->z & 0xFFF);
    c1 = cos(arg2->z & 0xFFF);
    m1.m[0][0] = c1;
    m1.m[0][1] = 0;
    m1.m[0][2] = s1;
    m1.m[1][0] = 0;
    m1.m[1][1] = 0x1000;
    m1.m[1][2] = 0;
    m1.m[2][0] = -s1;
    m1.m[2][1] = 0;
    m1.m[2][2] = c1;

    s2 = sin(arg2->x);
    c2 = cos(arg2->x);
    m2.m[0][0] = 0x1000;
    m2.m[0][1] = 0;
    m2.m[0][2] = 0;
    m2.m[1][0] = 0;
    m2.m[1][1] = c2;
    m2.m[1][2] = -s2;
    m2.m[2][0] = 0;
    m2.m[2][1] = s2;
    m2.m[2][2] = c2;
    MulMatrix(&m1, &m2);

    s3 = sin(-((arg2->z - arg2->y) & 0xFFF));
    c3 = cos(-((arg2->z - arg2->y) & 0xFFF));
    m2.m[0][0] = c3;
    m2.m[0][1] = 0;
    m2.m[0][2] = s3;
    m2.m[1][0] = 0;
    m2.m[1][1] = 0x1000;
    m2.m[1][2] = 0;
    m2.m[2][0] = -s3;
    m2.m[2][1] = 0;
    m2.m[2][2] = c3;
    MulMatrix(&m1, &m2);

    if (arg3 != NULL) {
        ScaleMatrix(&m1, arg3);
    }

    v_in.x = arg0->x / 16;
    v_in.y = arg0->y / 16;
    v_in.z = arg0->z / 16;
    Gfx_Transform(&v_in, &m1, &v_out);

    v_out.x <<= 4;
    v_out.y <<= 4;
    v_out.z <<= 4;

    arg4->x = v_out.x + arg1->x;
    arg4->y = v_out.y + arg1->y;
    arg4->z = v_out.z + arg1->z;
}

s32 Gool_Transform2(Vec3 *arg0, Vec3 *arg1, s32 arg2)
{
    SVector sv;
    LVector v;
    s32 flag;

    v.x = arg0->x;
    v.y = arg0->y;
    v.z = arg0->z;
    if (arg2 != 0) {
        SetRotMatrix(D_80057844);
    } else {
        SetRotMatrix(g_m_view);
    }
    SetTransMatrix(g_cams);
    if (arg2 != 0) {
        sv.x = (v.x - D_80057888[0]) >> 8;
        sv.y = (v.y - D_8005788C[0]) >> 8;
        sv.z = (v.z - D_80057890[0]) >> 8;
    } else {
        sv.x = (v.x - D_80057864) >> 8;
        sv.y = (v.y - D_80057868) >> 8;
        sv.z = (v.z - D_8005786C) >> 8;
    }
    RotTrans(&sv, arg1, &flag);
    arg1->x <<= 8;
    arg1->y = -(arg1->y << 8);
    arg1->z <<= 8;
    return -0xFF;
}

s32 Gool_Project(Vec3 *arg0, Vec3 *arg1)
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
    SetRotMatrix(g_m_view);
    SetTransMatrix(g_cams);
    sv.x = (v.x - D_80057864) >> 8;
    sv.y = (v.y - D_80057868) >> 8;
    sv.z = (v.z - D_8005786C) >> 8;
    RotTransPers(&sv, (s16 *)&sxy, &p, &flag);
    arg1->x = (s16)sxy << 8;
    arg1->y = -(sxy >> 16) << 8;
    ReadSZfifo3(&otz1, &otz2, &otz3);
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

s32 Gool_Collide(CollideObj *arg0, s32 *arg1, CollideObj *arg2, s32 *arg3)
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
        dist = Math_ApxDist(&arg0->pos, &other->pos);
        if (Math_ApxDist(&arg0->pos, &arg2->pos) >= dist && !(other->flags120 & 0x800)) {
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
        if (Level_TestBoundIntersection(box1, arg3) != 0) {
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
        if (Level_TestBoundIntersection(box2, arg1) != 0) {
            arg2->flagsC8 |= 0x1000;
        }
    }
    return -0xFF;
}
