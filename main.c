#include "types.h"
#include "print.h"
#include "trap.h"
#include "alloc.h"

extern uint8 __bss;
extern uint8 __bss_end;
extern uint8 __stack;
extern uint8 __heap;
extern uint8 __heap_end; 

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
    asm volatile("csrw stvec, %0" : : "r"(trap_handler));
    print_hex((uint64)trap_handler);

    volatile uint64 *uart = (volatile uint64*)0x88888888; // example address
    print_hex((uint64)uart);

    print_hex(__heap);
    print_hex(__heap_end);    

    paddr paddr0 = alloc_pages(1);
    paddr paddr1 = alloc_pages(2);

    print_hex(paddr0);    
    print_hex(paddr1);    


    test_hypervisor();

    while(1) {

    }
    return 0;
}