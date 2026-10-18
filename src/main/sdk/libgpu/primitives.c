#include "common.h"

/* GCC_VERSION: 2.6.3 */

/* Set length and command for flat, textured-flat and Gouraud-shaded triangles. */

#include "gpu.h"

void func_8003F840(GpuPacketHeader *packet)
{
    packet->length = 4;
    packet->command = 0x20;
}

void func_8003F854(GpuPacketHeader *packet)
{
    packet->length = 7;
    packet->command = 0x24;
}

void func_8003F868(GpuPacketHeader *packet)
{
    packet->length = 6;
    packet->command = 0x30;
}

/* Additional polygon, line, sprite and tile packet headers, including polyline terminators. */

void func_8003F87C(GpuPacketHeader *packet)
{
    packet->length=9;
    packet->command=0x34;
}

void func_8003F890(GpuPacketHeader *packet)
{
    packet->length=5;
    packet->command=0x28;
}

void func_8003F8A4(GpuPacketHeader *packet)
{
    packet->length=9;
    packet->command=0x2C;
}

void func_8003F8B8(GpuPacketHeader *packet)
{
    packet->length=8;
    packet->command=0x38;
}

void func_8003F8CC(GpuPacketHeader *packet)
{
    packet->length=12;
    packet->command=0x3C;
}

void func_8003F8E0(GpuPacketHeader *packet)
{
    packet->length=3;
    packet->command=0x74;
}

void func_8003F8F4(GpuPacketHeader *packet)
{
    packet->length=3;
    packet->command=0x7C;
}

void func_8003F908(GpuPacketHeader *packet)
{
    packet->length=4;
    packet->command=0x64;
}

void func_8003F91C(GpuPacketHeader *packet)
{
    packet->length=2;
    packet->command=0x68;
}

void func_8003F930(GpuPacketHeader *packet)
{
    packet->length=2;
    packet->command=0x70;
}

void func_8003F944(GpuPacketHeader *packet)
{
    packet->length=2;
    packet->command=0x78;
}

void func_8003F958(GpuPacketHeader *packet)
{
    packet->length=3;
    packet->command=0x60;
}

void func_8003F96C(GpuPacketHeader *packet)
{
    packet->length=3;
    packet->command=0x40;
}

void func_8003F980(GpuPacketHeader *packet)
{
    packet->length=4;
    packet->command=0x50;
}

typedef struct GpuLineF3 {
    GpuPacketHeader header;
    u32 v[3];
    u32 pad;
} GpuLineF3;

typedef struct GpuLineG3 {
    GpuPacketHeader header;
    u32 v[5];
    u32 pad;
} GpuLineG3;

typedef struct GpuLineF4 {
    GpuPacketHeader header;
    u32 v[4];
    u32 pad;
} GpuLineF4;

typedef struct GpuLineG4 {
    GpuPacketHeader header;
    u32 v[7];
    u32 pad;
} GpuLineG4;

typedef struct GpuMaskPacket {
    GpuPacketHeader header;
    u32 mask;
} GpuMaskPacket;

void func_8003F994(GpuLineF3 *packet)
{
    u32 terminator=0x55555555;
    packet->header.length=5;
    packet->header.command=0x48;
    packet->pad=terminator;
}

void func_8003F9B4(GpuLineG3 *packet)
{
    u32 terminator=0x55555555;
    packet->header.length=7;
    packet->header.command=0x58;
    packet->pad=terminator;
}

void func_8003F9D4(GpuLineF4 *packet)
{
    u32 terminator=0x55555555;
    packet->header.length=6;
    packet->header.command=0x4C;
    packet->pad=terminator;
}

void func_8003F9F4(GpuLineG4 *packet)
{
    u32 terminator=0x55555555;
    packet->header.length=9;
    packet->header.command=0x5C;
    packet->pad=terminator;
}

void func_8003FA14(GpuPacketHeader *packet)
{
    packet->length=3;
    packet->command=0x2;
}

void func_8003FA28(GpuMaskPacket *packet)
{
    packet->header.length=5;
    packet->header.command=0x1;
    packet->mask=0x80000000;
}
