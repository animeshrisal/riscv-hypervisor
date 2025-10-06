#include "print.h"
#include "types.h"
#include "riscv.h"

uint64 trap_handler() {
    uint64 x;
    print_string("Error");
    asm volatile("csrr %0, scause" : "=r"(x));
    print_hex(x);
    return 0;
}
