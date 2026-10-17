/* GCC_VERSION: 2.6.3 */
/* CC1_FLAGS: -O2 */
#include "common.h"
#include "gpu.h"

/* =========================================================================
 * 1. func_80016E5C (asm/USA/main/text_765C.s)
 * ========================================================================= */

typedef struct RenderBufferFull {
    u32 word00;
    GpuDisplayEnv display;
    GpuDrawing drawing;
    s32 word74;
    s32 word78;
    u32 word7C;
    u32 word80;
    s32 word84;
    u32 ordering_table[0x800];
} RenderBufferFull;

typedef struct {
    u8 bytes[4];
} BufferToken;

extern volatile u32 frame_counter __asm__("func_80034520");
extern BufferToken D_80057968[];
extern BufferToken D_8005796C;
extern s32 D_80056400;
extern u32 D_800618B0;
extern u32 D_8006189C;
extern s32 D_80057960;
extern s32 D_80061A34[];
extern s32 D_80061A38;
extern s32 D_80061A30;
extern s32 D_80061938;
extern s32 D_8005C54C[];
extern struct { RenderBufferFull *buf; } D_80058404;
extern RenderBufferFull *D_80058408;
extern RenderBufferFull *D_8005840C;

extern s32 D_8005642C;
asm(".sdata\n.size D_8005642C,4\n.text");
extern s32 *D_800566A8;
asm(".sdata\n.size D_800566A8,4\n.text");

typedef struct ZoneHeader8214 {
    u8 pad00[0x2E0];
    s32 word2E0;
    u8 pad2E4[0x18];
    u32 flags2FC;
    u8 pad300[0x10];
    u8 r310;
    u8 g311;
    u8 b312;
    u8 pad313;
    u8 r314;
    u8 g315;
    u8 b316;
} ZoneHeader8214;

typedef struct ZoneEntry8214 {
    u8 pad00[0x10];
    ZoneHeader8214 *header;
} ZoneEntry8214;

extern ZoneEntry8214 *D_80057914[];

void func_80017448(u32);
void func_80017358(s32, s32, s32, s32, u8, u8, u8);
void func_80030CC0(void);
void func_8004025C(s32);
s32 CORE_VSync(s32);
void func_8003E1F8(void);
void func_8003E3A4(u32);
void func_8003E370(u32);
void func_8003E208(void);
void func_8003A94C(void);
s32 func_800175D0(s32);
void *func_80040A0C(GpuDisplayEnv *);
void *func_80040834(GpuDrawing *);
void func_800407C0(u32 *);
void func_800342D8(void *, s32);

static __inline__ BufferToken *func_80016E28_inline(void)
{
    D_80057968[0] = D_8005796C;
    (void)frame_counter;
    return &D_80057968[0];
}

void func_80016E5C(void)
{
    BufferToken *token;
    RenderBufferFull *swap;

    token = func_80016E28_inline();
    if (D_80056400 == 0 && (D_800618B0 & 0x1000)) {
        D_80057960++;
    }
    if (D_80061A34[0] != 0) {
        if (D_80061A34[0] > 0) {
            D_80061A34[0] -= D_80061A38;
            func_80017448(D_80061A34[0]);
        } else if (D_80061A34[0] >= -2) {
            func_80017448(0x100);
            D_80061A34[0] = -1;
        } else {
            D_80061A34[0] += D_80061A38;
            func_80017448(D_80061A34[0] + 0x100);
            if (D_80061A34[0] == 0 && !(D_800618B0 & 0x200000)) {
                D_80061A34[0] = -2;
            }
        }
    }
    if (!(D_800618B0 & 0x80000)) {
        if (D_800618B0 & 0x2000) {
            func_80017358(0, 0, 0x200, D_80057914[0]->header->word2E0, token->bytes[0], token->bytes[1], token->bytes[2]);
            func_80017358(0, D_80057914[0]->header->word2E0, 0x200, 0xD8 - D_80057914[0]->header->word2E0, D_80057914[0]->header->r310, D_80057914[0]->header->g311, D_80057914[0]->header->b312);
        } else {
            func_80017358(0, 0, 0x200, 0xD8, 0, 0, 0);
        }
    }
    func_80030CC0();
    D_80058408->word80 = frame_counter;
    func_8004025C(0);
    if (D_80061A30 == 0) {
        D_80061938 = frame_counter - D_80058408->word7C;
    } else {
        D_80061938 = 0x11;
    }
    if (D_8005C54C[0] == 0) {
        swap = D_80058408;
        D_80058404.buf = swap;
        D_80058408 = D_8005840C;
        D_8005840C = swap;
    }
    CORE_VSync(0);
    if ((u32)(frame_counter - D_80058404.buf->word7C) < 0x19) {
        CORE_VSync(0);
    }
    if (D_800618B0 & 0x100000) {
        if (!D_8005642C) {
            func_8003E1F8();
            func_8003E3A4(0xF2000002);
            func_8003E208();
        }
        D_8005642C = 1;
        func_8003A94C();
        frame_counter += 0x22;
    } else {
        if (D_8005642C) {
            func_8003E1F8();
            func_8003E370(0xF2000002);
            func_8003E208();
        }
        D_8005642C = 0;
    }
    func_8003E1F8();
    if (D_80061A30 == 2) {
        frame_counter = *D_800566A8;
    }
    D_80058408->word7C = frame_counter;
    func_8003E208();
    D_80058404.buf->word84 = func_800175D0(D_80058408->word7C - D_80058404.buf->word7C);
    func_80040A0C(&D_80058404.buf->display);
    func_80040834(&D_80058408->drawing);
    if (D_8005C54C[0] > 0) {
        D_8005C54C[0]--;
    }
    if (D_8005C54C[0] == 0) {
        func_800407C0(D_80058408->ordering_table);
    }
    D_8005840C->word78 = D_8005840C->word74;
    func_800342D8(D_8005840C->ordering_table, 0x800);
    D_800618B0 = D_8006189C;
}

