/* GCC_VERSION: 2.6.3 */
/* CC1_FLAGS: -O2 */
#include "common.h"
#include "gpu.h"
extern s32 D_80057960;

extern s16 D_800577C4;

extern s16 D_800577E4;
extern s16 D_80057824;

extern s16 D_80057844;
extern s32 D_80057868;

extern s32 D_80061894, D_8006193C, D_80061940;

typedef struct Copy32 {
    s32 w[8];
} Copy32;

typedef struct Copy12 {
    s32 w[3];
} Copy12;

typedef struct ShortMat {
    s16 m[9];
} ShortMat;

extern Copy12 D_80057864;
extern Copy12 D_80057930;

typedef struct ZoneCamData {
    u8 pad000[0x2FC];
    u32 flags;
    u8 pad300[0x314 - 0x300];
    u8 bg_color[3];
} ZoneCamData;

typedef struct ZoneCamEntry {
    u8 pad00[0x10];
    ZoneCamData *data;
} ZoneCamEntry;

typedef struct CamBlock {
    Copy32 m804;
    u8 pad824[0x80057888 - 0x80057824];
    Copy12 m888;
    u8 pad894[0x80057914 - 0x80057894];
    ZoneCamEntry *z914;
    u8 pad918[0x80057938 - 0x80057918];
    s32 w938;
} CamBlock;

extern CamBlock D_80057804;

void func_80026138(void);
s32 func_8003905C(s32);
s32 func_800390D0(s32);
void func_80042C2C(void *, void *);
void func_80042F6C(u32, u32, u32);
void func_80042D3C(void *, void *);
void func_80042F8C(s32, s32);

typedef struct WgeoHeader {
    s32 x;
    s32 y;
    s32 z;
    s32 unk0C;
    s32 unk10;
    s32 unk14;
    u32 tpage_count;
    s32 flags;
    u32 tpages[8];
} WgeoHeader;

typedef struct ZoneWorld {
    u32 eid;
    s32 trans[3];
    WgeoHeader *wgeo;
    void *item1;
    void *item2;
    void *polys;
    void *tpages[8];
} ZoneWorld;

typedef struct ZoneHeader9A2C {
    s32 world_count;
    ZoneWorld worlds[8];
} ZoneHeader9A2C;

void func_8001922C(ZoneHeader9A2C *arg0);

void func_80017A14(void)
{
    s16 sp10[16];
    s32 sp30[4];
    s16 s0_1, s0_2, s0_3, s0_4, v0, v0_2, v0_3, v0_4;
    s32 val;
    Copy32 *cam;
    s16 *m;
    s32 *t1;
    s32 *s0_5;

    func_80026138();
    s0_1 = func_8003905C(-D_80057878);
    v0 = func_800390D0(-D_80057878);
    asm("" : "=r"(cam) : "0"((Copy32 *)&D_80057864));
    m = (s16 *)(cam - 5);
    *m = v0;
    D_800577C6 = -s0_1;
    D_800577C8 = 0;
    D_800577CA = s0_1;
    D_800577CC = v0;
    D_800577CE = 0;
    D_800577D0 = 0;
    D_800577D2 = 0;
    D_800577D4 = 0x1000;

    s0_2 = func_8003905C(-D_80057870);
    v0_2 = func_800390D0(-D_80057870);
    sp10[0] = 0x1000;
    sp10[1] = 0;
    sp10[2] = 0;
    sp10[3] = 0;
    sp10[4] = v0_2;
    sp10[5] = -s0_2;
    sp10[6] = 0;
    sp10[7] = s0_2;
    sp10[8] = v0_2;
    func_80042C2C(m, sp10);

    s0_3 = func_8003905C(-D_80057874);
    v0_3 = func_800390D0(-D_80057874);
    sp10[0] = v0_3;
    sp10[1] = 0;
    sp10[2] = s0_3;
    sp10[3] = 0;
    sp10[4] = 0x1000;
    sp10[5] = 0;
    sp10[6] = -s0_3;
    sp10[7] = 0;
    sp10[8] = v0_3;
    func_80042C2C(m, sp10);

    func_80042F6C(D_80057804.z914->data->bg_color[0], D_80057804.z914->data->bg_color[1], D_80057804.z914->data->bg_color[2]);
    sp30[0] = *(s32 *)cam >> 8;
    sp30[1] = D_80057868 >> 8;
    sp30[2] = D_8005786C >> 8;
    func_80042D3C(m, sp30);

    D_800577E4 = D_800577C4;
    D_800577E6 = D_800577C6;
    D_800577E8 = D_800577C8;
    D_800577EA = -(D_800577CA * 5) >> 3;
    D_800577EC = -(D_800577CC * 5) >> 3;
    D_800577EE = -(D_800577CE * 5) >> 3;
    D_800577F0 = -D_800577D0;
    D_800577F2 = -D_800577D2;
    D_800577F4 = -D_800577D4;

    D_80057804.m804 = *(cam - 4);

    if (D_80057804.z914->data->flags & 0x1000) {
        *(((s32 *)cam) + 10) = __builtin_abs(((D_80057960 % 128) - 64) * 800) + 0xDC1E0;
        s0_4 = func_8003905C(0x7D);
        v0_4 = func_800390D0(0x7D);
        *(((s16 *)cam) - 0x20) = 0x1000;
        *(((s16 *)cam) - 0x1F) = 0;
        *(((s16 *)cam) - 0x1E) = 0;
        *(((s16 *)cam) - 0x1D) = 0;
        *(((s16 *)cam) - 0x1C) = v0_4;
        *(((s16 *)cam) - 0x1B) = -s0_4;
        *(((s16 *)cam) - 0x1A) = 0;
        ((ShortMat *)(cam - 2))->m[7] = s0_4;
        ((ShortMat *)(cam - 2))->m[8] = v0_4;

        D_80057844 = D_80057824;
        D_80057846 = D_80057826;
        D_80057848 = D_80057828;
        D_8005784A = -(D_8005782A * 5) >> 3;
        D_8005784C = -(D_8005782C * 5) >> 3;
        D_8005784E = -(D_8005782E * 5) >> 3;
        D_80057850 = -D_80057830;
        D_80057852 = -D_80057832;
        D_80057854 = -D_80057834;
    } else {
        *(cam - 2) = *(cam - 5);
        *(cam - 1) = *(cam - 4);
    }

    func_80042F8C(D_8006193C, (D_80061894 >> 8) + D_80061940);
    val = D_80061894 >> 8;
    if (val == 0) {
        D_80061894 = 0;
    } else {
        if (val > 0) {
            val = -val + 1;
        } else {
            val = ~val;
        }
        D_80061894 = val << 8;
    }

    t1 = &D_80057864.w[0];
    D_80061920 = *t1;
    D_80061924 = D_80057868;
    D_80061928 = D_8005786C;
    D_8006192C = D_80057870;
    D_80061930 = D_80057874;
    D_80061934 = D_80057878;

    if (!(*(u32 *)(void *)&(*(ZoneCamData **)(void *)&D_80057804.z914->data)->flags & 0x1000)) {
        D_80057804.m888 = *(Copy12 *)t1;
        D_80057930.w[0] = D_80057804.w938 & 0xFFF;
    } else {
        D_80057930.w[0] = 0;
    }

    s0_5 = &D_80057930.w[0];
    D_800618C8 = *s0_5;
    D_8005794C = func_8003905C(*s0_5) >> 4;
    D_80057950 = 0;
    D_80057954 = func_800390D0(*s0_5) >> 4;
    func_8001922C(*(ZoneHeader9A2C **)(void *)&D_80057804.z914->data);
}
