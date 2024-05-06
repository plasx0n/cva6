

MSTATUS_FS = 0x00006000

.section .init, "ax"
.global _start
_start:
    .cfi_startproc
    .cfi_undefined ra
    .option push
    .option norelax
    la gp, __global_pointer$
    .option pop
    la sp, __stack_top
    add s0, sp, zero

    li t0, MSTATUS_FS
    csrs mstatus, t0

    jal main
    ecall
    .cfi_endproc
    .end
