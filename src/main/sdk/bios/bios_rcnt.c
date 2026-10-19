#include "common.h"
#include "psyq_bios.h"

PSYQ_BIOS_TRAMPOLINE(puts, 0xB0, 0x3F);
PSYQ_BIOS_TRAMPOLINE(ChangeClearRCnt, 0xC0, 0xA);
