#include "common.h"

/* GCC_VERSION: 2.6.3 */
/* Mask followed by the 32 halfwords written to SPU offsets 0x1C0..0x1FE. */
typedef struct {
    s32 mask;
    u16 values[32];
} SpuReverbRegisters;
extern volatile u16 *D_800558E4;

void func_80047718(SpuReverbRegisters *arg0) {
    s32 mask;
    s32 all_registers;

    mask = arg0->mask;
    all_registers = mask == 0;
    if ((all_registers != 0) || (mask & 1)) {
        D_800558E4[0xE0] = (u16) arg0->values[0];
    }
    if ((all_registers != 0) || (mask & 2)) {
        D_800558E4[0xE1] = (u16) arg0->values[1];
    }
    if ((all_registers != 0) || (mask & 4)) {
        D_800558E4[0xE2] = (u16) arg0->values[2];
    }
    if ((all_registers != 0) || (mask & 8)) {
        D_800558E4[0xE3] = (u16) arg0->values[3];
    }
    if ((all_registers != 0) || (mask & 0x10)) {
        D_800558E4[0xE4] = (u16) arg0->values[4];
    }
    if ((all_registers != 0) || (mask & 0x20)) {
        D_800558E4[0xE5] = (u16) arg0->values[5];
    }
    if ((all_registers != 0) || (mask & 0x40)) {
        D_800558E4[0xE6] = (u16) arg0->values[6];
    }
    if ((all_registers != 0) || (mask & 0x80)) {
        D_800558E4[0xE7] = (u16) arg0->values[7];
    }
    if ((all_registers != 0) || (mask & 0x100)) {
        D_800558E4[0xE8] = (u16) arg0->values[8];
    }
    if ((all_registers != 0) || (mask & 0x200)) {
        D_800558E4[0xE9] = (u16) arg0->values[9];
    }
    if ((all_registers != 0) || (mask & 0x400)) {
        D_800558E4[0xEA] = (u16) arg0->values[10];
    }
    if ((all_registers != 0) || (mask & 0x800)) {
        D_800558E4[0xEB] = (u16) arg0->values[11];
    }
    if ((all_registers != 0) || (mask & 0x1000)) {
        D_800558E4[0xEC] = (u16) arg0->values[12];
    }
    if ((all_registers != 0) || (mask & 0x2000)) {
        D_800558E4[0xED] = (u16) arg0->values[13];
    }
    if ((all_registers != 0) || (mask & 0x4000)) {
        D_800558E4[0xEE] = (u16) arg0->values[14];
    }
    if ((all_registers != 0) || (mask & 0x8000)) {
        D_800558E4[0xEF] = (u16) arg0->values[15];
    }
    if ((all_registers != 0) || (mask & 0x10000)) {
        D_800558E4[0xF0] = (u16) arg0->values[16];
    }
    if ((all_registers != 0) || (mask & 0x20000)) {
        D_800558E4[0xF1] = (u16) arg0->values[17];
    }
    if ((all_registers != 0) || (mask & 0x40000)) {
        D_800558E4[0xF2] = (u16) arg0->values[18];
    }
    if ((all_registers != 0) || (mask & 0x80000)) {
        D_800558E4[0xF3] = (u16) arg0->values[19];
    }
    if ((all_registers != 0) || (mask & 0x100000)) {
        D_800558E4[0xF4] = (u16) arg0->values[20];
    }
    if ((all_registers != 0) || (mask & 0x200000)) {
        D_800558E4[0xF5] = (u16) arg0->values[21];
    }
    if ((all_registers != 0) || (mask & 0x400000)) {
        D_800558E4[0xF6] = (u16) arg0->values[22];
    }
    if ((all_registers != 0) || (mask & 0x800000)) {
        D_800558E4[0xF7] = (u16) arg0->values[23];
    }
    if ((all_registers != 0) || (mask & 0x01000000)) {
        D_800558E4[0xF8] = (u16) arg0->values[24];
    }
    if ((all_registers != 0) || (mask & 0x02000000)) {
        D_800558E4[0xF9] = (u16) arg0->values[25];
    }
    if ((all_registers != 0) || (mask & 0x04000000)) {
        D_800558E4[0xFA] = (u16) arg0->values[26];
    }
    if ((all_registers != 0) || (mask & 0x08000000)) {
        D_800558E4[0xFB] = (u16) arg0->values[27];
    }
    if ((all_registers != 0) || (mask & 0x10000000)) {
        D_800558E4[0xFC] = (u16) arg0->values[28];
    }
    if ((all_registers != 0) || (mask & 0x20000000)) {
        D_800558E4[0xFD] = (u16) arg0->values[29];
    }
    if ((all_registers != 0) || (mask & 0x40000000)) {
        D_800558E4[0xFE] = (u16) arg0->values[30];
    }
    if ((all_registers != 0) || (mask < 0)) {
        D_800558E4[0xFF] = (u16) arg0->values[31];
    }
}
