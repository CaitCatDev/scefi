#include <scefi/types.h>
#include <scefi/system_table.h>

EFI_STATUS efi_main(EFI_HANDLE imageHandle, EFI_SYSTEM_TABLE *SystemTable) {
	EFI_SYSTEM_TABLE *ST = SystemTable;

	ST->ConOut->ClearScreen(ST->ConOut);

	ST->ConOut->EnableCursor(ST->ConOut, TRUE);

	ST->ConOut->OutputString(ST->ConOut, ST->FirmwareVender);

	while(1) { 
	}; 

	return 0;
}
