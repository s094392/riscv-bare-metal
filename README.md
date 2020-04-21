# RISCV Example
A RISC-V bare-metal example with uart, exception and interrupt.

## Requirement
- qemu
- riscv64-linux-gnu-*

## Run
```bash
make
make run
```

## Debug
```bash
make
make debug
riscv64-linux-gnu-gdb -x debug.txt
```
