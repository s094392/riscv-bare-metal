    .global _start

_start:
    la     sp, stack_top
    csrr   t0, mhartid
    lui    t1, 0
    beq    t0, t1, 2f

1:  wfi
    j      1b

2:
    call   main
    
finish:
    beq    t1, t1, finish
