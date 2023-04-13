#include "scefi/system_table_internal.h"
#include <scefi/system_table.h>
#include <scefi/graphics_output.h>
#include <scefi/types.h>

#include <stdarg.h>

void put_str(CHAR16 *String, EFI_SYSTEM_TABLE *ST) {
	ST->ConOut->OutputString(ST->ConOut, String);
}

CHAR16 *number_to_str(int number, EFI_SYSTEM_TABLE *ST) {
	int str_size = 1; /*One for null term*/
	int tmp = 0; /*C 90 and older code*/
	CHAR16 *out = NULL; 

	if(number < 0) {
		str_size++; /*Add one to string size*/
		number *= -1; /*Flip the number to positive*/
	}
	tmp = number; 

	do {
		str_size++;
		tmp /= 10; 
	} while(tmp);
	
	/*allocate a buffer*/ 
	if(ST->BootServices->AllocatePool(EfiLoaderData, str_size, (void **)&out)) {
		put_str((CHAR16 *)L"Failed to allocate UEFI Memory pool\n" , ST);
		return NULL;
	}

	out[str_size - 1] = '\0';
	str_size--;
	do {
		out[str_size - 1] = number % 10 + '0';
		number /= 10;
		str_size--;
	} while(number);

	if(str_size) {
		out[str_size - 1] = '-';
	}

	return out;
}

void put_int(int num, EFI_SYSTEM_TABLE *ST) {
	CHAR16 *str = NULL;
	
	str = number_to_str(num, ST);
	
	put_str(str, ST);

}

EFI_STATUS efi_main(EFI_HANDLE imageHandle, EFI_SYSTEM_TABLE *SystemTable) {
	UINTN x = 0;
	EFI_EVENT event;
	EFI_GUID gopGuid = EFI_GRAPHICS_OUTPUT_PROTOCOL_GUID;	
	EFI_GRAPHICS_OUTPUT_PROTOCOL *gop;

	if(SystemTable->BootServices->LocateProtocol(&gopGuid, NULL, (void **)&gop)) {
		put_str((CHAR16 *)L"Unable to get UEFI GOP Protocol", SystemTable);
		return 0;
	}
	/*TODO: CODE*/
	for(x = 0; x < gop->Mode->FrameBufferSize; x += 4) {
		((UINT8 *)gop->Mode->FrameBufferBase)[x] = 0x36;
		((UINT8 *)gop->Mode->FrameBufferBase)[x + 1] = 0x2a;
		((UINT8 *)gop->Mode->FrameBufferBase)[x + 2] = 0x28;
	}
	
	SystemTable->ConOut->SetCursorPosition(SystemTable->ConOut, 0, 0);

	put_int(gop->Mode->Info->HorizontalResolution, SystemTable);
	put_str((CHAR16 *)L"x", SystemTable);
	put_int(gop->Mode->Info->VerticalResolution, SystemTable);
	SystemTable->BootServices->WaitForEvent(1, &SystemTable->ConIn->WaitForKey, &x);
	return 0;
}
