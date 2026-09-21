
    .equ STACK_SHIFT, 12        
    .equ LANE_BITS,   5         

    .section .text.init, "ax"
    .globl _start
_start:

    .option push
    .option norelax
    la      gp, __global_pointer$
    .option pop


    .insn r 0x0B, 0, 1, t0, x0, x0      /* t0 = warpid() */
    .insn r 0x0B, 0, 0, t1, x0, x0      /* t1 = laneid() */
    slli    t0, t0, LANE_BITS
    add     t0, t0, t1
    slli    t0, t0, STACK_SHIFT
    la      sp, __stack_top
    sub     sp, sp, t0


    .insn r 0x0B, 0, 1, t0, x0, x0
    bnez    t0, .Lmain

    la      t1, __bss_start
    la      t2, __bss_end
.Lbss:
    bgeu    t1, t2, .Lmain
    sw      x0, 0(t1)
    addi    t1, t1, 4
    j       .Lbss

.Lmain:
    call    main
.Lhang:
    j       .Lhang
