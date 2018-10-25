#define __SYSCALL_32BIT_ARG_BYTES 12

#include "SYS.h"

__SYSCALL(__msync_nocancel, msync_nocancel, 3)
