# RISCV Bare Metal
A RISC-V bare-metal example with uart, exception, interrupt and kvmmap.

The tutorial is at [https://mullerlee.cyou/2020/07/09/riscv-exception-interrupt/](https://mullerlee.cyou/2020/07/09/riscv-exception-interrupt/)

## Requirement
- qemu
- riscv64-linux-gnu-*

## Run
```bash
mkdir build
make
make run
```

## Debug
```bash
mkdir build
make
make debug
riscv64-linux-gnu-gdb -x debug.txt
```
