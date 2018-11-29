#include <efi.h>
#include <efilib.h>
#include "util.h"
#include <version.h>

EFI_HANDLE *g_disks;
UINTN g_disk_count;

EFI_STATUS
try_get_protocols() {
	Print(L"Locating handles...");

	// Use LocateHandle in the BootServices (or bullshit for short- wait what?)
	// Should give us a list of things that support Disk I/O.
	
	EFI_HANDLE disks[15]; // Should be enough. FIXME: get this to be dynamic.
	UINTN buf_size = sizeof(disks);
	EFI_GUID protocolID = EFI_BLOCK_IO_PROTOCOL_GUID;
	EFI_STATUS status = uefi_call_wrapper(BS->LocateHandle, 5,
			ByProtocol,
			&protocolID,
			NULL,
			&buf_size,
			disks
			);
	switch(status) {
		case EFI_SUCCESS:
			Print(L"ok." ENDL);
			break;
		case EFI_NOT_FOUND:
			Print(L"no disks." ENDL);
			return EFI_NOT_FOUND;
		case EFI_BUFFER_TOO_SMALL:
			Print(L"too many disks." ENDL);
			Print(L"Increases disks size to get it to run, or fix the bug entirely." ENDL);
			return EFI_BUFFER_TOO_SMALL;
		default:
			Print(L"failed." ENDL);
			Print(L"Unknown error in try_get_protocols; bug." ENDL);
			return status;
	}

	UINT8 disk_count = buf_size / sizeof(EFI_HANDLE);
	Print(L"block devs = %d" ENDL, disk_count);
	
	// Allocte the Disks array, and populate it with the handles to disks
	g_disks = AllocatePool(buf_size);
	g_disk_count = disk_count;

	return status;
}

EFI_STATUS
EFIAPI
efi_main(EFI_HANDLE ImageHandle, EFI_SYSTEM_TABLE *SystemTable) {
	InitializeLib(ImageHandle, SystemTable);
	EFI_STATUS status;
	EFI_INPUT_KEY key;

	ST = SystemTable;
	BS = SystemTable->BootServices;

	// Clear the screen in preparation for the bootloader log
	uefi_call_wrapper(ST->ConOut->ClearScreen, 1, ST->ConOut);

	status = Print(L"MBoot, built for kernel v" MOS_VERSION_NAME L", " MOS_COMMIT L"@" MOS_BRANCH ENDL);
	// Check to see if writing works, if not assume everything is terrible and die a horrible death
	if (EFI_ERROR(status))
		return status;
	
	Print(L"Setting up UEFI protocols..." ENDL);
	status = try_get_protocols();
	if (EFI_ERROR(status)) {
		Print(L"Found no bootable medium; halting here" ENDL);
		return status;
	}
	Print(L"Searching for a MKFS partition..." ENDL);
	Print(L"Loading kernel..." ENDL);
	Print(L"Loading drivers..." ENDL);
	Print(L"Setting up kernel main() params..." ENDL);
	Print(L"Starting the kernel..." ENDL);

	return 0;
}
