#pragma once

/*Define MS/EFI Like types*/ 
/*8bit vars*/

#if defined(__cplusplus)
	typedef bool BOOLEAN; /*If Cpp just use bool type*/
#else 
	/*TODO: HANDLE _Bool not existing i.e. OLD C*/
#if __STDC_VERSION__ >= 199901 /*_Bool didn't exist before C99*/
	typedef _Bool BOOLEAN;
#else 
	typedef signed char BOOLEAN; /*Make it a char if we are older than C99*/
#endif /*ENDS __STDC_VERSION__ IF*/
#endif /*ENDS CPP IF*/



#if __STDC_VERSION__ >= 199901
#include <stdint.h>
#else 
/*HACK: These are not guranteed to work on all systems
 * Thus a more proper implementation should be done 
 * to ensure that typedef corresponds to the right type 
 */
typedef signed char int8_t;
typedef unsigned char uint8_t;

typedef signed short int16_t;
typedef unsigned short uint16_t;

typedef signed int int32_t;
typedef unsigned int uint32_t;

typedef signed long int64_t;
typedef unsigned long uint64_t;
#endif 

#define TRUE (BOOLEAN)1
#define FALSE (BOOLEAN)0

typedef int8_t CHAR8;
typedef int8_t INT8;
typedef uint8_t UINT8;

/*16bit vars*/
typedef int16_t CHAR16;
typedef int16_t INT16;
typedef uint16_t UINT16;

/*32bit variables*/
typedef int32_t INT32;
typedef uint32_t UINT32;

/*64bit variables*/
typedef int64_t INT64;
typedef uint64_t UINT64;
#define JOIN(x, y) x ## y 
#define JOIN_PREPROCESSOR(x, y) JOIN(x, y)

#if defined(_WIN32) || defined(_WIN64)
#if defined(_WIN64)
#warning Win64
typedef INT64 INTN;
typedef UINT64 UINTN;

#else

#warning Win32 
typedef INT32 INTN;
typedef UINT32 UINTN;
#endif

#elif defined(__LONG_WIDTH__) 

#warning Warning Unable to determine size of long on system assuming using __LONG_WIDTH__ 

typedef JOIN_PREPROCESSOR(INT, __LONG_WIDTH__) INTN;
typedef JOIN_PREPROCESSOR(INT, __LONG_WIDTH__) UINTN;

#else 

#ifndef __LONG_WIDTH__
	#define __LONG_WIDTH__ 64 
#endif 

#warning __LONG_WIDTH__ is not defined by you compiler assuming 64 bit please manually speficy if this is wrong

typedef JOIN_PREPROCESSOR(INT, __LONG_WIDTH__) INTN;
typedef JOIN_PREPROCESSOR(INT, __LONG_WIDTH__) UINTN;

#endif 


typedef void VOID;
typedef VOID *EFI_HANDLE;
typedef VOID *EFI_EVENT;

typedef UINT64 EFI_LBA;
typedef UINTN EFI_TPL;

typedef UINTN EFI_STATUS;


typedef struct _EFI_TABLE_HEADER {
	UINT64 Signature;
	UINT32 Revision;
	UINT32 HeaderSize;
	UINT32 CRC32;
	UINT32 Reserved;
} EFI_TABLE_HEADER;

typedef struct _EFI_GUID {
	uint32_t data1;
	uint16_t data2;
	uint16_t data3;
	uint8_t data4[8];
} EFI_GUID;

#define EFIAPI /*we compile to MS application so this can be blank*/
#define IN 
#define OUT
#define CONST const
#define OPTIONAL

#define NULL (void *)0

/*Memory Types*/
typedef enum _EFI_ALLOCATE_TYPE {
	AllocateAnyPages, 
	AllocateMaxAddress,
	AllocateAddres, 
	MaxAllocateType
} EFI_ALLOCATE_TYPE;

typedef enum {
	EfiReservedMemoryType,
	EfiLoaderCode,
	EfiLoaderData,
	EfiBootServicesCode,
	EfiBootServicesData,
	EfiRuntimeServicesCode,
	EfiRuntimeServicesData,
	EfiConventionalMemory,
	EfiUnusableMemory,
	EfiACPIReclaimMemory,
	EfiACPIMemoryNVS,
	EfiMemoryMappedIO, 
	EfiMemoryMappedIOPortSpace,
	EfiPalCode,
	EfiPersistentMemory,
	EfiUnacceptedMemoryType,
	EfiMaxMemoryType
} EFI_MEMORY_TYPE;

#define EFI_MEMORY_UC 0x0000000000000001
#define EFI_MEMORY_WC 0x0000000000000002
#define EFI_MEMORY_WT 0x0000000000000004
#define EFI_MEMORY_WB 0x0000000000000008
#define EFI_MEMORY_UCE 0x0000000000000010
#define EFI_MEMORY_WP 0x0000000000001000
#define EFI_MEMORY_RP 0x0000000000002000
#define EFI_MEMORY_XP 0x0000000000004000
#define EFI_MEMORY_NV 0x0000000000008000
#define EFI_MEMORY_MORE_RELIABLE 0x0000000000010000
#define EFI_MEMORY_RO 0x0000000000020000
#define EFI_MEMORY_SP 0x0000000000040000
#define EFI_MEMORY_CPU_CRYPTO 0x0000000000080000
#define EFI_MEMORY_RUNTIME 0x8000000000000000

#define EFI_MEMORY_DESCRIPTOR_VERSION 1 

typedef UINT64 EFI_VIRTUAL_ADDRESS;
typedef UINT64 EFI_PHYSICAL_ADDRESS;

typedef struct { 
	UINT32 Type;
	EFI_PHYSICAL_ADDRESS PhysicalStart;
	EFI_VIRTUAL_ADDRESS VirtualStart;
	UINT64 NumberOfPages;
	UINT64 Attribute;
}EFI_MEMORY_DESCRIPTOR;

typedef struct {
	EFI_HANDLE AgentHandle;
	EFI_HANDLE ControllerHandle;
	UINT32 Attributes;
	UINT32 OpenCount;
} EFI_OPEN_PROTOCOL_INFORMATION_ENTRY;

typedef struct { 
	UINT16 Year;
	UINT8 Month;
	UINT8 Day; 
	UINT8 Hour;
	UINT8 Minute; 
	UINT8 Second;
	uint8_t Pad1;
	UINT32 Nanosecond;
	INT16 TimeZone;
	UINT8 Daylight;
	UINT8 Pad2;
} EFI_TIME;

#define EFI_TIME_ADJUST_DAYLIGHT 0x01 
#define EFI_TIME_IN_DAYLIGHT 0x02 
#define EFI_UNSPECIFIED_TIMEZONE 0x07ff

typedef struct { 
	UINT32 Resolution;
	UINT32 Accuracy;
	BOOLEAN SetsToZero;
} EFI_TIME_CAPABILITIES;

typedef enum {
	EfiResetCold,
	EfiResetWarm,
	EfiResetShutdown,
	EfiResetPlatformSpecific
} EFI_RESET_TYPE;

typedef struct { 
	UINT64 Length;
	union { 
		EFI_PHYSICAL_ADDRESS DataBlock;
		EFI_PHYSICAL_ADDRESS ContinuationPointer;
	}Union;
}EFI_CAPSULE_BLOCK_DESCRIPTOR;

typedef struct {
	EFI_GUID CapsuleGuid;
	UINT32 HeaderSize;
	UINT32 Flags;
	UINT32 CapsuleImageSize;
} EFI_CAPSULE_HEADER;

typedef struct { 
	UINT32 CapsuleArrayNumber;
	VOID *CapsulePtr[1];
} EFI_CAPSULE_TABLE;

#define EFI_MEMORY_RANGE_CAPSULE_GUID \
	{ 0xde9f0ec, 0x88b6, 0x428f, \
	{ 0x97, 0x7a, 0x25, 0x8f, 0x1d, 0xe, 0x5e, 0x72 }}

typedef struct {
	EFI_PHYSICAL_ADDRESS Address;
	UINT64 Length;
} EFI_MEMORY_RANGE;

typedef struct {
	EFI_CAPSULE_HEADER Header;
	UINT32 OsRequestedMemoryType;
	UINT64 NumberOfMemoryRanges;
	EFI_MEMORY_RANGE MemoryRanges[];
} EFI_MEMORY_RANGE_CAPSULE;

typedef struct { 
	UINT64 FirmwareMemoryRequirement;
	UINT64 NumberOfMemoryRanges;
} EFI_MEMORY_RANGE_CAPSULE_RESULT;

#define CAPSULE_FLAGS_PERSIST_ACROSS_RESET 0x00010000 
#define CAPSULE_FLAGS_POPULATE_SYSTEM_TABLE 0x00020000 
#define CAPSULE_FLAGS_INITIATE_RESET 0x00040000
