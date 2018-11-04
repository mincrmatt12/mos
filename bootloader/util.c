#include <efi.h>
#include <efiapi.h>

EFI_STATUS bwrite(const wchar_t * f) {
	return uefi_call_wrapper(ST->ConOut->OutputString, 2, ST->ConOut, f);
}
