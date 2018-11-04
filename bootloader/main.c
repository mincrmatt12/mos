#include <efi.h>
#include <efilib.h>
#include "util.h"

EFI_STATUS
EFIAPI
efi_main(EFI_HANDLE ImageHandle, EFI_SYSTEM_TABLE *SystemTable) {
	EFI_STATUS status;
	EFI_INPUT_KEY key;

	ST = SystemTable;

	status = bwrite("MBoot v0");
	if (EFI_ERROR(status))
		return status;
	
	return 0;
}
