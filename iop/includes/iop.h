/*
 *
 *  greenpois0n - hardware/s5l8920x/iop.h
 *  (c) 2009 Chronic-Dev Team
 *
 */

// base addresses
#define IOP_BASE      0x86300000
#define IOP_INT0_BASE 0xBF300000
#define IOP_INT1_BASE 0xBF310000
#define IOP_INT2_BASE 0xBF320000
#define IOP_INT3_BASE 0xBF330000

// iop main registers
/* todo */

// iop interrupt types
#define IOPINT_IRQ_INT  0x0
#define IOPINT_FIQ_INT  0x1

// iop interrupt controller registers
#define IOPINT_IRQ_STATUS 0x000
#define IOPINT_FIQ_STATUS 0x004
#define IOPINT_RAW_STATUS 0x008
#define IOPINT_SELECT     0x00C
#define IOPINT_ENABLE     0x010
#define IOPINT_CLEAR      0x014
#define IOPINT_SOFT_INT   0x018
#define IOPINT_SOFT_CLEAR 0x01C
#define IOPINT_PROTECTION 0x020
#define IOPINT_VEC_ADDR   0xF00

// iop interrupt numbers
#define INT_NMI  0x2  // NAND Management Interface, should be set up as fiq
#define INT_DMA  0x3  // DMA, should be set up as irq
#define INT_PMU  0x5  // PMU, not set as irq/fiq, defaults to irq(?)
#define INT_FMI1 0x1E // Flash Management Interface 1, should be set up as irq
#define INT_FMI0 0x1F // Flash Management Interface 0, should be set up as irq
