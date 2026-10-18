/* GCC_VERSION: 2.6.3 */
#include "common.h"
#include "zone.h"

typedef struct {
    s16 v[3][3];
    s16 b[3];
    s16 c[3][3];
    s16 a[3];
} LightMat;

typedef struct LevelHeader {
    s32 unk0;
    s32 level_id;
} LevelHeader;

extern LevelHeader *D_8005C53C[];

typedef struct SaveVec {
    s32 x, y, z;
} SaveVec;

typedef struct SaveTransform {
    SaveVec trans;
    SaveVec rot;
    SaveVec scale;
} SaveTransform;

typedef struct SaveObj {
    u8 pad00[0x28];
    ResourceEntry *entry;
    u8 pad2C[0x4C];
    struct SaveObj *unk78;
    u8 pad7C[4];
    SaveTransform transform;
    s32 unkA4;
    s32 unkA8;
    s32 unkAC;
    s32 unkB0;
    s32 unkB4;
    u8 padB8[0x10];
    u32 status_a;
    u32 status_b;
    u8 padD0[0x54];
    s32 unk124;
    u8 pad128[8];
    s32 unk130;
} SaveObj;

extern SaveObj *D_800566B4;

extern s32 D_80056400;
extern SaveObj *D_800618CC;

extern s32 frame_counter;

s32 D_800564C8 = -1;
s32 D_800564CC = 0;

static s32 D_800565EC;
static s32 D_800565F0;
static s32 D_800565F4;
static s32 D_800565F8;
static s32 D_800565FC;
static s32 D_80056600;
static s32 D_80056604;
static s32 D_80056608;
static s32 D_8005660C;
static s32 D_80056610;
static s32 D_80056614;
static s32 D_80056618;
static s32 D_8005661C;
static s32 D_80056620;
static s32 D_80056624;
static s32 D_80056628;
static s32 D_8005662C;
static s32 D_80056630;
static s32 D_80056634[2];

void func_80019DE0(s32);
s32 func_8002F778(s32);
void func_80030840(s32, s32, s32 *, s32);
void func_800304C8(s32, s32 *, s32);

void func_8002EBB4(s32 arg0)
{
    switch (D_8005C53C[0]->level_id) {
    case 0xF:
    case 0x18:
        D_80056474 = 0xA;
        D_80056478 = 0x7F;
        break;
    case 0x17:
        D_80056474 = 0xA;
        D_80056478 = 0x7F;
        break;
    case 0x24:
    case 0x33:
        D_80056474 = 4;
        D_80056478 = 0x7F;
        break;
    default:
        D_80056474 = 1;
        D_80056478 = 0x17;
        break;
    }
    if (arg0 != 0) {
        func_80019DE0(0);
    }
}

void func_8002EC68(s32 arg0)
{
    u8 name[8];
    s32 sp18;
    s32 sp1C;
    s32 v1, v2, v3;

    if (arg0 != 0) {
        D_8005644C = 0x800;
        D_80056450 = 0xFF;
        D_80056454 = 0xFF;
        D_80056458 = 0xFF;
        D_8005645C = 0x800;
        D_80056440 = 0;
        D_80056444 = 0;
        D_80056448 = 0;
        D_800564CC = 0;
        D_800564C8 = -1;
        switch (D_8005C53C[0]->level_id) {
        case 0x21:
            D_8005644C = 0;
            D_80056450 = 0xC8;
            D_80056454 = 0x50;
            D_80056458 = 0;
            break;
        case 0x20:
        case 0x23:
            D_8005644C = 0;
            D_8005645C = 0x640;
            D_80056600 = 0xA5;
            D_80056604 = 0x5A;
            D_80056608 = 0x64;
            D_8005660C = 0xFF;
            D_80056610 = 0x4B;
            D_80056614 = 0;
            D_800565F4 = 0xA5;
            D_800565F8 = 0x5A;
            D_800565FC = 0x64;
            break;
        case 5:
            D_8005644C = 0;
            D_80056450 = 0xEE;
            D_80056454 = 0xEE;
            D_80056458 = 0x3C;
            break;
        case 0x13:
            D_8005644C = 0;
            D_80056450 = 0;
            D_80056454 = 0xF0;
            D_80056458 = 0xFF;
            break;
        case 0xA:
        case 0x1C:
        case 0x1D:
            D_8005644C = 0;
            D_80056450 = 0xFF;
            D_80056454 = 0x64;
            D_80056458 = 0;
            break;
        case 3:
        case 6:
        case 7:
        case 0x37:
            D_8005644C = 0;
            D_80056450 = 0xFF;
            D_80056454 = 0x2B;
            D_80056458 = 0xB;
            break;
        case 0x28:
        case 0x2A:
            D_80056618 = 0;
            D_80056460 = 0;
            D_80056464 = 0xA;
            D_80056624 = 0xFFF;
            D_80056630 = 0x7D0;
            D_8005646C = -0x36B0;
            break;
        }
    } else {
        switch (D_8005C53C[0]->level_id) {
        case 0x28:
        case 0x2A:
            if ((v1 = (s32)D_800618CC) != 0) {
                D_800566D4 = ((SaveObj *)v1)->transform.trans.x;
                D_800566D8 = ((SaveObj *)v1)->transform.trans.y;
                D_800566DC = ((SaveObj *)v1)->transform.trans.z;
            } else {
                D_800566D4 = D_800566B4->transform.trans.x;
                D_800566D8 = D_800566B4->transform.trans.y;
                D_800566DC = D_800566B4->transform.trans.z;
            }
            v1 = D_80061964;
            if (v1 != 0) {
                if (v1 != D_80056618) {
                    D_8005661C = -0x1F40;
                    D_80056620 = -0x1F4;
                    D_80056628 = 0x4B;
                    D_8005662C = -0x4B;
                }
            } else {
                if (D_80056618 != 0) {
                    D_8005661C = 0xFFF;
                    D_80056620 = 0x64;
                    D_80056628 = 0x7D0;
                    D_8005662C = 0x14;
                }
            }
            D_80056618 = v1;
            if (D_80056624 != D_8005661C) {
                if ((D_80056624 < D_8005661C && D_80056624 + D_80056620 >= D_8005661C) ||
                    (D_80056624 > D_8005661C && D_80056624 + D_80056620 <= D_8005661C)) {
                    D_80056620 = 0;
                    D_80056624 = D_8005661C;
                } else {
                    D_80056624 += D_80056620;
                }
            }
            if (D_80056630 != D_80056628) {
                if ((D_80056630 < D_80056628 && D_80056630 + D_8005662C >= D_80056628) ||
                    (D_80056630 > D_80056628 && D_80056630 + D_8005662C <= D_80056628)) {
                    D_8005662C = 0;
                    D_80056630 = D_80056628;
                } else {
                    D_80056630 += D_8005662C;
                }
            }
            D_80056468 = D_80056624;
            D_80056470 = D_80056630;
            break;
        case 0x21:
            switch (D_800564CC) {
            case 0:
                D_800565EC = func_8002F778(1000);
                D_800565F0 = (D_800565EC - D_8005645C) / 4;
                D_8005645C += D_800565F0;
                break;
            case 1:
            case 2:
            case 3:
                D_8005645C += D_800565F0;
                break;
            }
            D_800564CC = ++D_800564CC % 4;
            break;
        case 5:
        case 0xA:
        case 0x1C:
        case 0x1D:
            switch (D_800564CC) {
            case 0:
                D_800565EC = func_8002F778(0x5DC);
                D_8005645C += (D_800565EC - D_8005645C) / 2;
                break;
            case 1:
                D_8005645C = D_800565EC;
                break;
            }
            D_800564CC = (D_800564CC + 1) % 2;
            break;
        case 0x20:
        case 0x23:
            switch (D_800564CC) {
            case 0:
                D_800565EC = func_8002F778(100);
                D_800565F4 = D_80056600 + (D_8005660C - D_80056600) * D_800565EC / 100;
                D_800565F8 = D_80056604 + (D_80056610 - D_80056604) * D_800565EC / 100;
                D_800565FC = D_80056608 + (D_80056614 - D_80056608) * D_800565EC / 100;
                D_80056450 += (D_800565F4 - D_80056450) / 2;
                D_80056454 += (D_800565F8 - D_80056454) / 2;
                D_80056458 += (D_800565FC - D_80056458) / 2;
                break;
            case 1:
                D_80056450 = D_800565F4;
                D_80056454 = D_800565F8;
                D_80056458 = D_800565FC;
                break;
            }
            D_800564CC = (D_800564CC + 1) % 2;
            break;
        case 3:
        case 6:
        case 7:
        case 0x37:
            if (D_80052D74[D_800564CC] == -1) {
                D_800564CC = 0;
            }
            D_8005645C = D_80052D74[D_800564CC++];
            break;
        case 0x13:
            if (D_80052D74[D_800564CC] == -1) {
                D_800564CC = 0;
            }
            D_8005645C = D_80052D74[D_800564CC++] >> 1;
            break;
        case 0x1B:
        case 0x22:
        case 0x2E:
            if (D_800564C8 != -1) {
                v2 = D_80053054[D_800564C8][D_800564CC];
                if (v2 == -1) {
                    *(volatile s32 *)&D_8005644C = 0;
                    D_8005645C = 0;
                    D_800564C8 = -1;
                } else {
                    D_8005644C = v2;
                    D_8005645C = D_80053054[D_800564C8][D_800564CC++];
                }
            } else {
                D_8005644C = 0;
                D_8005645C = 0;
                if (func_8002F778(1000) < 0x19) {
                    if (D_8005C53C[0]->level_id == 0x22 || D_8005C53C[0]->level_id == 0x2E) {
                        switch (func_8002F778(3)) {
                        case 0:
                            D_800564C8 = 5;
                            break;
                        case 1:
                            D_800564C8 = 4;
                            break;
                        case 2:
                            D_800564C8 = func_8002F778(4);
                            break;
                        }
                    } else {
                        D_800564C8 = func_8002F778(6);
                    }
                    D_800564CC = 0;
                    if (D_80056400 == 0 &&
                        (D_8005C53C[0]->level_id == 0x1B || D_8005C53C[0]->level_id == 0x22 || D_8005C53C[0]->level_id == 0x2E) &&
                        (v3 = frame_counter) - D_80056634[1] > 0x1800) {
                        __builtin_memcpy(name, D_800564D0, 6);
                        for (sp18 = 0; sp18 < 1; sp18++) {
                            D_80056634[sp18 + 1] = D_80056634[sp18];
                        }
                        D_80056634[0] = v3;
                        name[2] += func_8002F778(3);
                        sp1C = func_80012660(name);
                        sp18 = (func_8002F778(0x4CC) + 0xD99) >> 3;
                        func_80030840(0, 1, &sp18, 0);
                        sp18 = func_8002F778(0xF) + 1;
                        func_80030840(0, 7, &sp18, 0);
                        sp18 = func_8002F778(0x14) + 0x14;
                        if (func_8002F778(100) >= 0x15) {
                            sp18 += func_8002F778(0x32);
                        }
                        func_800304C8(0, &sp1C, sp18 * 0x3FFF / 100);
                    }
                }
            }
            break;
        }
    }
}
