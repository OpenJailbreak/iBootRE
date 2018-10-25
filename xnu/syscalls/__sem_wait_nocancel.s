#define __SYSCALL_32BIT_ARG_BYTES 4

#include "SYS.h"

__SYSCALL(__sem_wait_nocancel, sem_wait_nocancel, 1)
