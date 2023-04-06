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

#define TRUE (BOOLEAN)1;
#define FALSE (BOOLEAN)0;

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

typedef INT64 INTN;
typedef UINT64 UINTN;

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


#define EFIAPI /*we compile to MS application so this can be blank*/
#define IN 
#define OUT
#define CONST const


