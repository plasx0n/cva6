

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

    fssr    x0
    fmv.w.x f0, x0
    fmv.w.x f1, x0
    fmv.w.x f2, x0
    fmv.w.x f3, x0
    fmv.w.x f4, x0
    fmv.w.x f5, x0
    fmv.w.x f6, x0
    fmv.w.x f7, x0
    fmv.w.x f8, x0
    fmv.w.x f9, x0
    fmv.w.x f10,x0
    fmv.w.x f11,x0
    fmv.w.x f12,x0
    fmv.w.x f13,x0
    fmv.w.x f14,x0
    fmv.w.x f15,x0
    fmv.w.x f16,x0
    fmv.w.x f17,x0
    fmv.w.x f18,x0
    fmv.w.x f19,x0
    fmv.w.x f20,x0
    fmv.w.x f21,x0
    fmv.w.x f22,x0
    fmv.w.x f23,x0
    fmv.w.x f24,x0
    fmv.w.x f25,x0
    fmv.w.x f26,x0
    fmv.w.x f27,x0
    fmv.w.x f28,x0
    fmv.w.x f29,x0
    fmv.w.x f30,x0
    fmv.w.x f31,x0

    jal main
    ecall
    .cfi_endproc
    .end
