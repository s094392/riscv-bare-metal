#ifndef TRAP_H
#define TRAP_H
#include <stdint.h>
void handle_interrupt(uint64_t mcause);
void handle_exception(uint64_t mcause);
void handle_trap(uintptr_t* regs, uintptr_t mcause, uintptr_t mepc);
#endif
