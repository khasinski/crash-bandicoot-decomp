#include "common.h"
#include "psyq_bios.h"

PSYQ_BIOS_TRAMPOLINE(StopPAD, 0xB0, 0x14);
PSYQ_BIOS_TRAMPOLINE(PAD_init, 0xB0, 0x15);
PSYQ_BIOS_TRAMPOLINE(PAD_dr, 0xB0, 0x16);
PSYQ_BIOS_TRAMPOLINE(ChangeClearPAD, 0xB0, 0x5B);
