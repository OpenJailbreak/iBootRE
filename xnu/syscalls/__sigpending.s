#define __SYSCALL_32BIT_ARG_BYTES 4

#include "SYS.h"

__SYSCALL(__sigpending, sigpending, 1)
