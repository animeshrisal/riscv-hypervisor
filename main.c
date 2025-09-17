#include "types.h"
#include "print.h"
#include "trap.h"

extern uint8 __bss;
extern uint8 __bss_end;
extern uint8 __stack;

void test_hypervisor() {
    uint64 hstatus = 0;
    hstatus |= 2 << 32;
    hstatus |= 1 << 7;

    uint64 sepc = 0x1234abcd;

    asm volatile("csrw hstatus, %0" : : "r"(hstatus));
    asm volatile("csrw sepc, %0" : : "r"(sepc));
    asm volatile("sret");
}

int main() {
    asm volatile("csrw stvec, %0" : : "r"((uint64)trap_handler));
    test_hypervisor();
    while(1) {

    }
    return 0;
}