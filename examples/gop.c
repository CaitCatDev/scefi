#include "scefi/system_table_internal.h"
#include <scefi/system_table.h>
#include <scefi/graphics_output.h>
#include <scefi/types.h>

#include <stdarg.h>

void put_str(CHAR16 *String, EFI_SYSTEM_TABLE *ST) {
	ST->ConOut->OutputString(ST->ConOut, String);
}

EFI_STATUS efi_main(EFI_HANDLE imageHandle, EFI_SYSTEM_TABLE *SystemTable) {
	EFI_GUID gopGuid = EFI_GRAPHICS_OUTPUT_PROTOCOL_GUID;	
	EFI_GRAPHICS_OUTPUT_PROTOCOL *gop;

	if(SystemTable->BootServices->LocateProtocol(&gopGuid, NULL, (void **)&gop)) {
		put_str((CHAR16 *)L"Unable to get UEFI GOP Protocol", SystemTable);
		return 0;
	}
	/*TODO: CODE*/
	return 0;
}
