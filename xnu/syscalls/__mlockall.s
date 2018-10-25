#define __SYSCALL_32BIT_ARG_BYTES 4

#include "SYS.h"

__SYSCALL(__mlockall, mlockall, 1)
