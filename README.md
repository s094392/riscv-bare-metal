# RISCV Bare Metal
A RISC-V bare-metal example with uart, exception, interrupt and kvmmap.

The tutorial is at [https://muller.nctu.me/2020/07/09/riscv-exception-interrupt/](https://muller.nctu.me/2020/07/09/riscv-exception-interrupt/)

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
