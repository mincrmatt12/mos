#ifndef BOOT_GPT_H
#define BOOT_GPT_H

#define GPT_HEADER 0x5452415020494645 
#include <efi.h>

int has_gpt(EFI_HANDLE t);

#endif /* ifndef MOS_BOOTLOADER_GPT */
