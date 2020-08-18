.equ REGBYTES, 8
.equ STACK_SIZE,  ((1 << 12) - 128) 

.section .text.start

.globl _start
_start:
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
    call   start

