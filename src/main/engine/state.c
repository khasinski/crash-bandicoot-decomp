#include "common.h"
#include "engine_ticks.h"
#define CRASH_ENGINE_STATE_STORAGE
#include "engine_state.h"
#include "resource.h"

/* GCC_VERSION: 2.6.3 */



/* Retail initial value at 0x80056564 is zero; preserve its .sdata placement. */
EngineState *D_80056564 = NULL;
/* Preserved render-state flag, initial retail value 1 at 0x80056568. */
s32 D_80056568 = 1;
extern s32 D_80061978;


/* Lifecycle requests and their BIOS event state. */
typedef EngineEventRequest EventRequest;
s32 func_8003CEF0(s32);
s32 func_8003CAD8(s32);
s32 func_8003CAF8(s32);
void func_8003C9B8(void);
s32 func_8003C3FC(void);
void func_8003CA04(s32);
s32 func_8003CAB0(s32);
void func_8003C900(s32 *);
s32 CORE_VSync(s32);
s32 func_8003E288(s32);
s32 func_8003E1C8(s32);
s32 func_8002F778(s32);

/* Traversal storage and lifecycle share the recovered engine globals. */
#include "object_links.h"

/* GCC_VERSION: 2.6.3 */
typedef EngineMode25State State;
/* Real engine globals in retail address order, 0x800566C4..0x800566FC.
 * The state and grid pointers retain their recovered pointer types. */
asm(".globl D_800566C4, D_800566C8, D_800566CC, D_800566D0, D_800566D4, D_800566D8, D_800566DC, D_800566E0, D_800566E4, D_800566E8, D_800566EC, D_800566F0, D_800566F4, D_800566F8, D_800566FC");
s32 D_800566C4;
s32 D_800566C8;
s32 D_800566CC;
s32 D_800566D0;
s32 D_800566D4;
s32 D_800566D8;
s32 D_800566DC;
State *D_800566E0;
s32 D_800566E4;
s32 D_800566E8;
s32 D_800566EC;
s32 D_800566F0;
s32 *D_800566F4;
s32 D_800566F8;
s32 D_800566FC;

extern void func_80032FDC(s32, s32, s32);
extern void *LIBC_Calloc(int, int);
extern void func_8003D680(s32);
extern s32 D_80056710;
s32 func_80031BAC(void)
{
    State *state;
    if(D_80056710 == 25) {
        state = LIBC_Calloc(1, sizeof(State));
        D_800566E0 = state;
        if(state == NULL) func_8003D680(-1);
    }
    return 0;
}

INCLUDE_ASM("asm/USA/main/nonmatchings/engine/state", func_80031BF8);

s32 func_80015118(s32 *, s32, s32);
s32 func_80015458(s32 *, s32);
void func_80025A60(ResourceItemListView *, u8 *, s32, s32);
extern s32 D_80056400, D_8005640C;
extern s32 D_8006189C[];
extern ResourceSlotStateView D_800580A4[];

/* Change mode flags, recycle pending texture slots 8..14, and initialise
 * the item selected by the resource metadata before releasing the reference. */
void func_80031D50(s32 *reference, s32 mode)
{
    s32 index;
    ResourceItemListView *resource;
    D_80056400 = 0;
    D_8005640C = -1;
    func_8001BA18(func_8001B92C, func_8001D1E0, NULL);
    switch (mode) {
    case 0:
        D_8006189C[0] = (D_8006189C[0] & 0xFFFE3FF0) | 0x20000;
        D_800566E0->word359C = 1;
        break;
    case 1:
        D_8006189C[0] = 0xFFFF;
        D_800566E0->word359C = 0;
        for (index = 8; index < 15; index++) {
            if (D_800580A4[index].state == 30)
                D_800580A4[index].state = 1;
        }
        break;
    case 3:
        D_8006189C[0] = 0x2FFFC;
        D_800566E0->word359C = 1;
        break;
    }
    resource = (ResourceItemListView *)func_80015118(reference, 1, 1);
    func_80025A60(resource,
        resource->items[((ResourceItemSelection *)resource->items[0])->word204], 0, 2);
    func_80015458(reference, 1);
}

INCLUDE_ASM("asm/USA/main/nonmatchings/engine/state", func_80031EB4);

void func_80032244(void)
{
    func_8001BA18(func_8001B92C, func_8001D1E0, NULL);
    if(D_800566E0->word359C != 0)
        func_80032FDC(D_800566E0->word35D0, 0, -1);
}

extern void LIBC_Free(void *);
extern s32 D_80056710;
s32 func_80032298(void)
{
    if(D_800566E0 != NULL) LIBC_Free(D_800566E0);
    D_80056710 = 0;
    return 0;
}


INCLUDE_ASM("asm/USA/main/nonmatchings/engine/state", func_800322CC);
INCLUDE_ASM("asm/USA/main/nonmatchings/engine/state", func_800324D4);
INCLUDE_ASM("asm/USA/main/nonmatchings/engine/state", func_8003263C);
INCLUDE_ASM("asm/USA/main/nonmatchings/engine/state", func_800326D8);
/* Fill 16 rows by 33 columns of three-word coordinate/page entries. */
void func_80032AF4(u32 base_address)
{
    s32 simple_row;
    s32 right_half;
    s32 column;
    s32 y;
    s32 row;
    s32 page;
    s32 index;
    s32 x;
    s32 byte_offset;
    void *entry;

    row = 0;
    do {
        column = 0;
        simple_row = row < 15;
        index = row;
next_column:
        if (simple_row) {
            if (column < 0x1E) {
                right_half = column >= 0xF;
                x = column + right_half;
                y = row;
                page = right_half;
            } else {
                x = row + 0x20;
                y = column - 0x1E;
                page = 2;
            }
        } else {
            page = 3;
            x = (column % 15) + 0x30;
            y = column / 15;
        }
        byte_offset = index * 3;
        column += 1;
        byte_offset = byte_offset << 2;
        entry = (void *)(byte_offset + base_address);
        *(s32 *)((u8 *)entry + 0x0) = x;
        *(s32 *)((u8 *)entry + 0x4) = y;
        *(s32 *)((u8 *)entry + 0x8) = page;
        index += 0x10;
        if (column < 0x21) {
            goto next_column;
        }
        row += 1;
    } while (row < 0x10);
}

INCLUDE_ASM("asm/USA/main/nonmatchings/engine/state", func_80032BB4);
INCLUDE_ASM("asm/USA/main/nonmatchings/engine/state", func_80032DFC);
INCLUDE_ASM("asm/USA/main/nonmatchings/engine/state", func_80032FDC);
void func_80033464(void)
{
}
#include "func_8003346C.c"
void func_80033490(void *a, void *b, void *c, u32 color)
{
}
void func_80033498(void)
{
}
INCLUDE_ASM("asm/USA/main/nonmatchings/engine/state", func_800334A0);
INCLUDE_ASM("asm/USA/main/nonmatchings/engine/state", func_80033878);
INCLUDE_ASM("asm/USA/main/nonmatchings/engine/state", func_80033F18);
INCLUDE_ASM("asm/USA/main/nonmatchings/engine/state", func_80033F38);
INCLUDE_ASM("asm/USA/main/nonmatchings/engine/state", func_80033F58);
INCLUDE_ASM("asm/USA/main/nonmatchings/engine/state", func_80033F78);
INCLUDE_ASM("asm/USA/main/nonmatchings/engine/state", func_80033F98);
INCLUDE_ASM("asm/USA/main/nonmatchings/engine/state", func_80033FBC);
INCLUDE_ASM("asm/USA/main/nonmatchings/engine/state", func_80034230);
INCLUDE_ASM("asm/USA/main/nonmatchings/engine/state", func_80034250);
INCLUDE_ASM("asm/USA/main/nonmatchings/engine/state", func_80034270);
INCLUDE_ASM("asm/USA/main/nonmatchings/engine/state", func_80034290);
INCLUDE_ASM("asm/USA/main/nonmatchings/engine/state", func_800342B0);
INCLUDE_ASM("asm/USA/main/nonmatchings/engine/state", func_800342D8);
INCLUDE_ASM("asm/USA/main/nonmatchings/engine/state", func_80034504);
INCLUDE_ASM("asm/USA/main/nonmatchings/engine/state", func_80034520);
INCLUDE_ASM("asm/USA/main/nonmatchings/engine/state", func_80034524);
INCLUDE_ASM("asm/USA/main/nonmatchings/engine/state", func_80034580);
INCLUDE_ASM("asm/USA/main/nonmatchings/engine/state", func_8003460C);
INCLUDE_ASM("asm/USA/main/nonmatchings/engine/state", func_80034B08);
INCLUDE_ASM("asm/USA/main/nonmatchings/engine/state", func_800351C8);
INCLUDE_ASM("asm/USA/main/nonmatchings/engine/state", func_80035370);
INCLUDE_ASM("asm/USA/main/nonmatchings/engine/state", func_800353B0);
INCLUDE_ASM("asm/USA/main/nonmatchings/engine/state", func_80035438);
INCLUDE_ASM("asm/USA/main/nonmatchings/engine/state", func_80035898);
INCLUDE_ASM("asm/USA/main/nonmatchings/engine/state", func_80035E10);
INCLUDE_ASM("asm/USA/main/nonmatchings/engine/state", func_80036340);
INCLUDE_ASM("asm/USA/main/nonmatchings/engine/state", func_80036BF4);
INCLUDE_ASM("asm/USA/main/nonmatchings/engine/state", func_80036D9C);
INCLUDE_ASM("asm/USA/main/nonmatchings/engine/state", func_800375EC);
INCLUDE_ASM("asm/USA/main/nonmatchings/engine/state", func_80037D50);
INCLUDE_ASM("asm/USA/main/nonmatchings/engine/state", func_8003864C);
INCLUDE_ASM("asm/USA/main/nonmatchings/engine/state", func_8003899C);
INCLUDE_ASM("asm/USA/main/nonmatchings/engine/state", func_800389A8);
INCLUDE_ASM("asm/USA/main/nonmatchings/engine/state", func_80038AC4);
INCLUDE_ASM("asm/USA/main/nonmatchings/engine/state", func_80038DF8);
INCLUDE_ASM("asm/USA/main/nonmatchings/engine/state", func_8003905C);
INCLUDE_ASM("asm/USA/main/nonmatchings/engine/state", func_800390D0);
INCLUDE_ASM("asm/USA/main/nonmatchings/engine/state", func_8003913C);
INCLUDE_ASM("asm/USA/main/nonmatchings/engine/state", func_80039BD4);
INCLUDE_ASM("asm/USA/main/nonmatchings/engine/state", func_8003A144);
INCLUDE_ASM("asm/USA/main/nonmatchings/engine/state", func_8003A76C);
INCLUDE_ASM("asm/USA/main/nonmatchings/engine/state", func_8003A94C);
INCLUDE_ASM("asm/USA/main/nonmatchings/engine/state", func_8003AA7C);

s32 func_8003ABA4(void) {
    s32 result;
    D_80056564->word18 = 0;
    if (func_8003CEF0(0) == 1) {
        func_8003CAD8(10);
        func_8003CAF8(0);
        func_8003C9B8();
        result = 1;
    } else {
        if (func_8003C3FC()) {
            func_8003CA04(0);
            func_8003CAD8(6);
            func_8003CAB0(8);
            func_8003CAF8(0);
            result = 1;
        } else {
            result = 0;
        }
    }
    return result;
}

INCLUDE_ASM("asm/USA/main/nonmatchings/engine/state", func_8003AC2C);

s32 func_8003AD84(s32 count,s32 limit,void (*callback)(void *),void *arg) {
    s32 result;
    if (count < limit) result = 0;
    else {callback(arg);result = 1;}
    return result;
}

void func_8003ADB8(s32 **resource) {
    if (func_8003C3FC()) {
        D_80056564->word08 = 0;
        func_8003CAB0(6);
        func_8003CAF8(0);
    }
    func_8003C900(*resource);
}

void func_8003AE08(EventRequest *request) {
    if (func_8003C3FC()) {
        func_8003CAB0(2);
        func_8003CAF8(0);
    }
    func_8003C900(request->resource);
    if (*request->pending) {
        s32 retries;
        s32 status;
        CORE_VSync(60);
        retries = 0;
        do {
            status = func_8003E288(request->event);
            CORE_VSync(20);
            if (status == 1) break;
            retries++;
        } while (retries < 9);
        if (retries < 3) *request->pending = 0;
    }
}

void func_8003AED8(EventRequest *request) {
    if (func_8003C3FC()) {
        func_8003CAB0(2);
        func_8003CAF8(0);
    }
    func_8003C900(request->resource);
}

INCLUDE_ASM("asm/USA/main/nonmatchings/engine/state", func_8003AF24);

INCLUDE_ASM("asm/USA/main/nonmatchings/engine/state", func_8003B5E0);

INCLUDE_ASM("asm/USA/main/nonmatchings/engine/state", func_8003B74C);

INCLUDE_ASM("asm/USA/main/nonmatchings/engine/state", func_8003B8B8);

INCLUDE_ASM("asm/USA/main/nonmatchings/engine/state", func_8003BE40);

INCLUDE_ASM("asm/USA/main/nonmatchings/engine/state", func_8003BF34);

#include "checksum.c"

INCLUDE_ASM("asm/USA/main/nonmatchings/engine/state", func_8003C038);

extern char D_80056574[];
s32 func_8003E258(const char *);
s32 func_8003C3FC(void);
s32 func_8003CAD8(s32);
s32 func_8003CAB0(s32);
s32 func_8003CAF8(s32);
void func_8003C358(void) {
    s32 ready;
    s32 state;
    /* Preserve the retail counter samples around the BIOS call. */
    (void)D_80034520;
    ready = func_8003E258(D_80056574);
    (void)D_80034520;
    if (ready == 1) {
        func_8003CAD8(2);
        state = 4;
    } else {
        if (func_8003C3FC() == 0) return;
        state = 2;
    }
    func_8003CAB0(state);
    func_8003CAF8(0);
}

void func_8003C3CC(void)
{
}

void func_8003C3D4(void)
{
}

void func_8003C3DC(void)
{
}

s32 func_8003C3E4(s32 arg0)
{
    D_80056564->word14 = 0;
    D_80056564->word10 = arg0;
    return 0;
}

s32 func_8003C3FC(void) {
    s32 temp_v0;

    temp_v0 = D_80056564->word14 + 1;
    D_80056564->word14 = temp_v0;
    return temp_v0 >= D_80056564->word10;
}

s32 func_8003C420(void) {
 func_8002F778(999);
 if (func_8003E1C8(D_800566C4)==1) return 0;
 if (func_8003E1C8(D_800566C8)==1) return 1;
 if (func_8003E1C8(D_800566CC)==1) return 2;
 if (func_8003E1C8(D_800566D0)==1) {func_8003CAB0(16);return 3;}
 return -1;
}

s32 func_8003C4A4(void) {
 s32 result;
 do {
  func_8002F778(999);
  if (func_8003E1C8(D_800566C4)==1) result=0;
  else if (func_8003E1C8(D_800566C8)==1) result=1;
  else if (func_8003E1C8(D_800566CC)==1) result=2;
  else if (func_8003E1C8(D_800566D0)==1) {func_8003CAB0(16);result=3;}
  else result=-1;
 } while (result==-1);
 return result;
}

#include "state_event_test.c"

s32 func_8003C580(void) {
 func_8002F778(999);
 if (func_8003E1C8(D_800566EC)==1) return 0;
 if (func_8003E1C8(D_800566F0)==1) return 1;
 if (func_8003E1C8(D_800566F8)==1) return 2;
 if (func_8003E1C8(D_800566FC)==1) return 3;
 return -1;
}

s32 func_8003C608(void) {
 s32 result;
 do {
  func_8002F778(999);
  if (func_8003E1C8(D_800566EC)==1) result=0;
  else if (func_8003E1C8(D_800566F0)==1) result=1;
  else if (func_8003E1C8(D_800566F8)==1) result=2;
  else if (func_8003E1C8(D_800566FC)==1) result=3;
  else result=-1;
 } while (result==-1);
 return result;
}

void func_8003C69C(void) {
    func_8003E1C8(D_800566EC);
    func_8003E1C8(D_800566F0);
    func_8003E1C8(D_800566F8);
    func_8003E1C8(D_800566FC);
}

s32 BIOS_StrNCmp(const char *, const char *, s32);                      /* extern */
extern char D_80010E88[];

s32 func_8003C6E4(const char *arg0) {
    return BIOS_StrNCmp(D_80010E88, arg0, 0xC) == 0;
}

INCLUDE_ASM("asm/USA/main/nonmatchings/engine/state", func_8003C714);

INCLUDE_ASM("asm/USA/main/nonmatchings/engine/state", func_8003C7A8);

extern s32 func_8003E248(s32);

void func_8003C900(s32 *arg0) {
    s32 temp_a0;

    temp_a0 = *arg0;
    if (temp_a0 >= 0) {
        func_8003E248(temp_a0);
    }
    *arg0 = -1;
}

void func_8003C944(u32 ticks) {
    u32 start = D_80034520;
    /* Preserve the retail unsigned subtraction order. */
    do {
    } while ((u32)(start - D_80034520) < ticks);
}

void func_8003C970(u8 *arg0) {
    u8 *var_a0;
    u8 temp_v1;

    var_a0 = arg0;
    if (*var_a0 != 0) {
        do {
            temp_v1 = *var_a0;
            if ((u32) (temp_v1 - 0x61) < 0x1AU) {
                *var_a0 = temp_v1 + 0xE0;
            }
            var_a0 += 1;
        } while (*var_a0 != 0);
    }
}

INCLUDE_ASM("asm/USA/main/nonmatchings/engine/state", func_8003C9B8);

INCLUDE_ASM("asm/USA/main/nonmatchings/engine/state", func_8003CA04);

void func_8001A754(s32, s32, void *, s32, s32);
extern u8 D_80056588[];
extern s32 D_800619CC;
void func_8003CA50(void)
{
    s32 channel;
    for (channel = 0; channel < 15; channel++) {
        func_8001A754(D_800619CC, channel << 8, D_80056588, 0x28, 1);
    }
}


s32 func_8003CAB0(s32 arg0) {
    s32 temp_a0;

    temp_a0 = arg0 | D_80056564->word04;
    D_80056564->word04 = temp_a0;
    D_80061978 = temp_a0;
    return 0;
}

s32 func_8003CAD8(s32 arg0)
{
    D_80056564->word04 = ~arg0 & D_80056564->word04;
    return 0;
}

s32 func_8003CAF8(s32 arg0) {
    s32 temp_v0;

    D_80056564->word00 = arg0;
    if (arg0 >= 0) {
        if ((arg0 < 2) || (arg0 == 4)) {
            D_80056564->word18 = 1;
        }
        if (D_80056564->word00 == 0) {
            D_80056564->word04 = (s32) (D_80056564->word04 & ~1);
        } else {
            goto block_6;
        }
    } else {
block_6:
        temp_v0 = D_80056564->word04 | 1;
        D_80056564->word04 = temp_v0;
        D_80061978 = temp_v0;
    }
    return 0;
}

s32 func_8003CB74(void)
{
    return D_80056564->word00;
}

s32 func_8003CB88(void)
{
    return D_80056564->word04;
}

s32 func_8003E1A8(u32,s32,s32,void (*)(void));
void func_8003E1F8(void),func_8003E208(void),func_80051454(void),func_8003E198(void);
void func_80051444(s32);
s32 func_8003E1D8(s32);
void func_8003CB9C(void) {
func_8003E1F8();
D_800566C4=func_8003E1A8(0xF4000001,4,0x2000,NULL);
D_800566C8=func_8003E1A8(0xF4000001,32768,0x2000,NULL);
D_800566CC=func_8003E1A8(0xF4000001,256,0x2000,NULL);
D_800566D0=func_8003E1A8(0xF4000001,8192,0x2000,NULL);
D_800566EC=func_8003E1A8(0xF0000011,4,0x2000,NULL);
D_800566F0=func_8003E1A8(0xF0000011,32768,0x2000,NULL);
D_800566F8=func_8003E1A8(0xF0000011,256,0x2000,NULL);
D_800566FC=func_8003E1A8(0xF0000011,8192,0x2000,NULL);
func_8003E208();
CORE_VSync(5);
func_80051444(1);
CORE_VSync(5);
func_80051454();
CORE_VSync(5);
func_8003E198();
CORE_VSync(5);
func_8003E1D8(D_800566C4);
func_8003E1D8(D_800566C8);
func_8003E1D8(D_800566CC);
func_8003E1D8(D_800566D0);
func_8003E1D8(D_800566EC);
func_8003E1D8(D_800566F0);
func_8003E1D8(D_800566F8);
func_8003E1D8(D_800566FC);
}

extern void func_80051464(void);

s32 func_8003CD3C(void) {
    func_80051464();
    return 0;
}

INCLUDE_ASM("asm/USA/main/nonmatchings/engine/state", func_8003CD60);

/* Six-byte state copied as an unaligned record in retail. */
typedef EngineByteRecord ByteRecord;
extern ByteRecord D_80056590, D_8005703C;

void func_8003CD60(s32);
s32 func_8003D740(char *, char *, ...);

s32 func_8003CE20(void)
{
    EngineState *state = LIBC_Calloc(1, 0x6F4);
    D_80056564 = state;
    if (D_80056568 != 0) {
        state->word04 |= 0x10;
        D_80061978 = state->word04;
        func_8003D740((char *)&D_8005703C, (char *)&D_80056590);
    } else {
        state->word04 &= ~0x10;
    }
    func_8003CD60(4);
    return 0;
}

s32 func_8003CEA8(void)
{
    D_80056568 = ((u32)D_80056564->word04 >> 4) & 1;
    if (D_80056564 != NULL) {
        LIBC_Free(D_80056564);
        D_80056564 = NULL;
    }
    return 0;
}

INCLUDE_ASM("asm/USA/main/nonmatchings/engine/state", func_8003CEF0);

s32 func_8003D008(void)
{
    D_80056564->word04 &= ~0x20;
    return 0;
}


INCLUDE_ASM("asm/USA/main/nonmatchings/engine/state", func_8003D028);
INCLUDE_ASM("asm/USA/main/nonmatchings/engine/state", func_8003D094);

s32 func_8003D1B4(void) {
    D_8005703C = D_80056590;
    return 0;
}

s32 BIOS_StrCmp(char *, char *);
void func_80051424(s32);

s32 func_8003D1F0(void)
{
    s32 event;

    if (D_80056564 ? (D_80056564->word04 & 16) : D_80056568) {
        return 1;
    }
    if (BIOS_StrCmp((char *)&D_8005703C, (char *)&D_80056590) == 0) {
        return 1;
    }

    func_8003E1C8(D_800566C4);
    func_8003E1C8(D_800566C8);
    func_8003E1C8(D_800566CC);
    func_8003E1C8(D_800566D0);
    func_80051424(0);

again:
    {
        func_8002F778(999);
        if (func_8003E1C8(D_800566C4) == 1) {
            event = 0;
        } else if (func_8003E1C8(D_800566C8) == 1) {
            event = 1;
        } else if (func_8003E1C8(D_800566CC) == 1) {
            event = 2;
        } else if (func_8003E1C8(D_800566D0) == 1) {
            func_8003CAB0(16);
            event = 3;
        } else {
            event = -1;
        }
    }
    if (event == -1) {
        goto again;
    }
    switch (event) {
    case 0:
        return 0;
    case 1:
    case 2:
    case 3:
        return 1;
    default:
        return 1;
    }
}

s32 func_8003D308(void)
{
    s32 event;

    func_8003E1C8(D_800566C4);
    func_8003E1C8(D_800566C8);
    func_8003E1C8(D_800566CC);
    func_8003E1C8(D_800566D0);
    func_80051424(0);

again:
    {
        func_8002F778(999);
        if (func_8003E1C8(D_800566C4) == 1) {
            event = 0;
        } else if (func_8003E1C8(D_800566C8) == 1) {
            event = 1;
        } else if (func_8003E1C8(D_800566CC) == 1) {
            event = 2;
        } else if (func_8003E1C8(D_800566D0) == 1) {
            func_8003CAB0(16);
            event = 3;
        } else {
            event = -1;
        }
    }
    if (event == -1) {
        goto again;
    }
    {
        s32 result = event;
        if (result != 2) {
            result = 0;
        } else {
            result = 1;
        }
        return result;
    }
}
INCLUDE_ASM("asm/USA/main/nonmatchings/engine/state", func_8003D3D8);
INCLUDE_ASM("asm/USA/main/nonmatchings/engine/state", func_8003D444);


s32 func_8003D4AC(void) {
    s32 result;
    if (D_80056564) {
        func_8003CD60((D_80056564->word04 & 0x10) | 4);
        result = 0;
    } else {
        result = 1;
    }
    return result;
}
