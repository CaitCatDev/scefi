#pragma once

/*system table needs to be defined for boot services but
 * the EFI system table needs boot services to be defined 
 * SO we forward declear what the system table is here and
 * declear it fully in system_table.h Pleas include that file and not 
 * this one as it's only really meant for internal use
 */


typedef struct _EFI_SYSTEM_TABLE EFI_SYSTEM_TABLE;
