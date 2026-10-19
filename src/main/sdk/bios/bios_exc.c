#include "common.h"
#include "psyq_bios.h"

PSYQ_BIOS_TRAMPOLINE(setjmp, 0xA0, 0x13);
PSYQ_BIOS_TRAMPOLINE(_96_remove, 0xA0, 0x72);
PSYQ_BIOS_TRAMPOLINE(ReturnFromException, 0xB0, 0x17);
PSYQ_BIOS_TRAMPOLINE(ResetEntryInt, 0xB0, 0x18);
PSYQ_BIOS_TRAMPOLINE(HookEntryInt, 0xB0, 0x19);
