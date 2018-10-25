clear_dcache:
    mov r2, #0x2000

outside:
    sub r2, r2, #0x40
    mov r1, #0

inside:
    subs r1, r1, #0x40000000
    orr r0, r1, r2
    mcr p15, 0, r0, c7, c10, 2
    bne inside
    cmp r2, #0
    bne outside
    mov r0, #0
    mcr p15, 0, r0, c7, c10, 4
    bx lr


