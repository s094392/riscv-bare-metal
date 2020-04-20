#include "encoding.h"
.equ REGBYTES, 8
.equ STACK_SIZE,  ((1 << 12) - 128) 

    .global _start
_start:
    la     t0, trap_entry
    csrw   mtvec, t0

    csrr   t0, mhartid
    lui    t1, 0
    beq    t0, t1, 2f

1:  wfi
    j      1b

2:
    # initialize global pointer
    la gp, _gp
  
    # initialize stack pointer
    la sp, stack_top
  
    lla t0, 1f
    csrw mepc, t0
    mret
1:
    call   main
    
.align 2
trap_entry:
    addi sp, sp, -16*4
  
    sw ra, 0*REGBYTES(sp)
    sw a0, 1*REGBYTES(sp)
    sw a1, 2*REGBYTES(sp)
    sw a2, 3*REGBYTES(sp)
    sw a3, 4*REGBYTES(sp)
    sw a4, 5*REGBYTES(sp)
    sw a5, 6*REGBYTES(sp)
    sw a6, 7*REGBYTES(sp)
    sw a7, 8*REGBYTES(sp)
    sw t0, 9*REGBYTES(sp)
    sw t1, 10*REGBYTES(sp)
    sw t2, 11*REGBYTES(sp)
    sw t3, 12*REGBYTES(sp)
    sw t4, 13*REGBYTES(sp)
    sw t5, 14*REGBYTES(sp)
    sw t6, 15*REGBYTES(sp)
  
    csrr a0, mcause
    csrr a1, mepc
    jal handle_trap
  
    lw ra, 0*REGBYTES(sp)
    lw a0, 1*REGBYTES(sp)
    lw a1, 2*REGBYTES(sp)
    lw a2, 3*REGBYTES(sp)
    lw a3, 4*REGBYTES(sp)
    lw a4, 5*REGBYTES(sp)
    lw a5, 6*REGBYTES(sp)
    lw a6, 7*REGBYTES(sp)
    lw a7, 8*REGBYTES(sp)
    lw t0, 9*REGBYTES(sp)
    lw t1, 10*REGBYTES(sp)
    lw t2, 11*REGBYTES(sp)
    lw t3, 12*REGBYTES(sp)
    lw t4, 13*REGBYTES(sp)
    lw t5, 14*REGBYTES(sp)
    lw t6, 15*REGBYTES(sp)

    addi sp, sp, 16*4

    mret

