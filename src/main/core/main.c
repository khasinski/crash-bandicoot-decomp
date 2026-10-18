#include "common.h"
#include "render.h"
#include "resource.h"

/* GCC_VERSION: 2.6.3 */

/* Initialise the runtime, run the game loop for initial level 0x19, then shut down. */

void func_8003E0C0(void);
void func_8001652C(void);
void CORE_Loop(s32);
void func_8001668C(void);
extern s32 D_80056410;

s32 CORE_Main(void)
{
    func_8003E0C0();
    D_80056410 = 1;
    func_8001652C();
    CORE_Loop(0x19);
    func_8001668C();
    return 0;
}

typedef struct ZoneHeaderView {
    s32 word00;
    u8 pad04[0x2F8];
    u32 flags;
} ZoneHeaderView;

typedef struct LevelDataView {
    u8 pad00[4];
    s32 level_id;
    u8 pad08[0xC];
    s32 eid14;
    u8 pad18[8];
    s32 eid20;
    s32 eid24;
    s32 eid28;
    u8 pad2C[0x5C];
    s32 eid88;
    u8 pad8C[0x10];
    s32 eid9C;
    u8 padA0[0x44];
    s32 eidE4;
} LevelDataView;

typedef struct NsState {
    u8 pad00[0x14];
    LevelDataView *level;
    u8 pad18[0xC];
    s32 draw_skip;
} NsState;

/* Object storage from the pause object's parent at 0x80060DF0 through the
 * playback mode at 0x80061A30. The loop addresses all three through one base. */
typedef struct PauseStateView {
    u8 pad000[0xACC];
    s32 pause_object;      /* 0x800618BC; also D_800618BC in engine/state */
    u8 padAD0[0xBC4 - 0xAD0];
    s32 pause_override;    /* 0x800619B4: -1 forbids pausing, > 0 forces it */
    u8 padBC8[0xC40 - 0xBC8];
    s32 playback_mode;     /* 0x80061A30: nonzero while playback blocks pausing */
} PauseStateView;

typedef struct DrawStampView {
    u8 pad00[0x7C];
    u32 stamp;
} DrawStampView;

extern NsState D_8005C528;
extern s32 D_80056710;
extern s32 D_800618BC;

void func_800167A4(void);
void func_80015118(void *, s32, s32);
void func_800262DC(s32);
s32 GOOL_CreateObject(void *parent, s32 exec, s32 subtype, s32 argc, s32 *argv, s32 flag);

/* Spawn default HUD objects and load the level's initial resource entries. */
void func_80011DD0(void)
{
    func_800167A4();
    D_800618BC = 0;
    switch (D_80056710) {
    case 0x38:
    case 0x39:
        break;
    case 0x19:
        func_80015118(&D_8005C528.level->eid24, 0, 1);
        func_80015118(&D_8005C528.level->eidE4, 0, 1);
        break;
    case 0x2D:
        func_80015118(&D_8005C528.level->eid88, 0, 1);
        func_80015118(&D_8005C528.level->eid9C, 0, 1);
        func_80015118(&D_8005C528.level->eid20, 0, 1);
        break;
    default:
        D_800618A8 = GOOL_CreateObject(&D_80060DC0, 4, 0, 0, 0, 0);
        D_800618A4 = GOOL_CreateObject(&D_80060DC0, 4, 1, 0, 0, 0);
        D_800618C4 = GOOL_CreateObject(&D_80060DC0, 4, 5, 0, 0, 0);
        func_80015118(&D_8005C528.level->eid14, 0, 1);
        func_80015118(&D_8005C528.level->eid28, 0, 1);
        func_80015118(&D_8005C528.level->eid88, 0, 1);
        if (D_80056710 != 0x2C) {
            func_80015118(&D_8005C528.level->eid9C, 0, 1);
        }
        func_80015118(&D_8005C528.level->eid20, 0, 1);
        func_80015118(&D_8005C528.level->eid24, 0, 1);
        break;
    }
    func_800262DC(1);
}
extern u32 engine_counter[];
extern PauseStateView D_80060DF0;
extern s32 D_8005E71C;
extern s32 D_800619B4;
extern DrawStampView *D_80058408;
extern u32 D_800566B0;
extern void *D_800566B4;
extern s32 D_80056714;
extern s32 D_800618D0;

extern s32 D_800618A0, D_80061A3C, D_800619A0;
extern s32 D_80057974[];
extern s32 D_800618B0;

/* .sdata owned by this unit (gp-addressed only here). */
s32 D_800563FC = 0;
s32 D_80056400 = 0;
s32 D_80056404 = 0x1000;
s32 D_80056408 = 0x200000;
s32 D_8005640C = 0;

/* .sbss owned by this unit. */
asm(".globl D_800565B8, D_800565BC");
u32 D_800565B8;
u32 D_800565BC;

void func_80026140(void);
void func_80015B58(NsState *ns, s32 level);
void func_80011DD0(void);
s32 GOOL_CreateObject(void *parent, s32 exec, s32 subtype, s32 argc, s32 *argv, s32 flag);
void func_80024040(s32 sender, s32 object, s32 event, s32 argc, s32 *argv);
void func_8002E98C(u32 *eid);
void func_80025134(s32, s32, s32, s32, s32);
void func_80016420(NsState *ns);
void func_80025928(void);
void func_80026650(s32 *state);
void func_800134C8(s32);
void func_8002EC68(s32);
void func_8002EBB4(s32);
void func_8002B2BC(void);
void func_80017A14(void);
void func_8001A2E0(u32 *);
void func_8001A0CC(u32 *);
void func_80019BCC(u32 *);
void func_80019DE0(u32 *);
void func_80019F90(u32 *);
void func_80019508(u32 *);
void func_8001D5EC(s32);
void func_800326D8(u32 *);
void func_80016E5C(void);

/* Run levels until the exit flag is set: pause toggling, demo playback,
 * level transitions, per-frame update and zone-specific drawing. */
void CORE_Loop(s32 level)
{
    char debug_text[0xA8]; /* reserved in the retail frame, never accessed */
    s32 arg;
    s32 restore;
    s32 id;
    u32 flags;
    ZoneHeaderView *zone;

    func_80026140();
    func_80015B58(&D_8005C528, level);
    func_80011DD0();
    do {
        /* Start toggles pause outside the title, map and intro levels. */
        if ((D_8005E71C & 0x800) && D_80060DF0.playback_mode == 0
            && (((id = D_8005C528.level->level_id) != 0x19 && id != 0x2D && id != 0x38
                 && D_80060DF0.pause_override != -1) || D_800619B4 > 0)) {
            if ((D_80056400 = 1 - D_80056400) != 0) {
                if (D_80060DF0.pause_object == 0) {
                    D_80060DF0.pause_object = GOOL_CreateObject(&D_80060DF0, 4, 4, 0, 0, 0);
                    if (D_80060DF0.pause_object >= -0xFE) {
                        D_80056400 = 0;
                        D_80060DF0.pause_object = 0;
                        goto not_paused;
                    }
                    D_8005640C = 1;
                    D_800565B8 = engine_counter[0];
                    D_800565BC = D_80058408->stamp;
                }
            } else if (D_80060DF0.pause_object != 0) {
                arg = 0;
                func_80024040(0, D_80060DF0.pause_object, 0xC00, 1, &arg);
                D_80060DF0.pause_object = 0;
                D_8005640C = -1;
                engine_counter[0] = D_800565B8;
                D_80058408->stamp = D_800565BC;
            }
        } else {
not_paused:
            D_8005640C = 0;
        }

        /* 0x6396347F is the null resource ID. */
        if (D_800566B4 != 0 && D_800566B0 != 0x6396347F) {
            func_8002E98C(&D_800566B0);
        }

        /* Game over and continue states return to the map (level 0x19). */
        if (D_80056714 == -1 && D_8005C528.level->level_id != 0x19
            && (D_800618D0 == 0x200 || D_800618D0 == 0x300 || D_800618D0 == 0x400)) {
            D_80056714 = 0x19;
        }
        /* Level change; -2 restores the saved level after a bonus round. */
        if (D_80056714 != -1) {
            restore = 0;
            level = D_80056714;
            func_80025134(0, 0x2900, 0, 0, 0);
            if (D_80056714 == -2) {
                level = D_800579A4;
                restore = 1;
                D_80056490 = 1;
            } else {
                D_80056490 = 0;
            }
            D_8005C528.draw_skip = 2;
            func_80016420(&D_8005C528);
            D_80056400 = 0;
            if (level == 0x19) {
                D_800618A0 = 0;
                D_80061A3C = 0;
                D_800618F8 = 0;
                D_800618FC = 0;
                D_80061900 = 0;
                D_800619A0 = -1;
            }
            func_80015B58(&D_8005C528, level);
            func_80011DD0();
            if (restore) {
                D_80056714 = -2;
                func_80025928();
                D_80056714 = -1;
                func_80026650(D_80057974);
            }
            D_80056490 = 0;
        }

        func_800134C8(-1);
        func_80025928();
        if (D_80056400 == 0) {
            if (((ZoneHeaderView *)D_80057914->data)->flags & 0x600) {
                func_8002EC68(0);
            }
            if (D_80056400 == 0) {
                if (((ZoneHeaderView *)D_80057914->data)->flags & 0x100) {
                    func_8002EBB4(0);
                }
                if (D_80056400 == 0) {
                    func_8002B2BC();
                }
            }
        }
        func_80017A14();

        if (D_800618B0 & 1) {
            zone = (ZoneHeaderView *)D_80057914->data;
            if (zone->word00 != 0 && D_800563FC == 0) {
                flags = zone->flags;
                if (flags & 0x400) {
                    func_8001A2E0(D_8005840C->ordering_table);
                } else if ((flags & 0x210) == 0x210) {
                    func_8001A0CC(D_8005840C->ordering_table);
                } else if (flags & 0x10) {
                    func_80019BCC(D_8005840C->ordering_table);
                } else if (flags & 0x100) {
                    func_80019DE0(D_8005840C->ordering_table);
                } else if (flags & 0x200) {
                    func_80019F90(D_8005840C->ordering_table);
                } else {
                    func_80019508(D_8005840C->ordering_table);
                }
            }
        }
        func_8001D5EC(D_80056400 == 0);
        if (D_8005C528.level->level_id == 0x19) {
            func_800326D8(D_8005840C->ordering_table);
        }
        func_80016E5C();
    } while (D_80056428 == 0);

    D_800618B0 = 0;
    func_80016E5C();
    func_80016E5C();
    func_80016420(&D_8005C528);
}
