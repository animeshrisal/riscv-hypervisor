#include "types.h"
#include "print.h"
#include "trap.h"
#include "alloc.h"
#include "guest_page_table.h"

extern uint8 __bss;
extern uint8 __bss_end;
extern uint8 __stack;
extern uint8 __heap;
extern uint8 __heap_end; 

extern unsigned char guest_kernel_guest_bin[];
extern unsigned int guest_kernel_guest_bin_len;



void test_hypervisor() {

    // Set mode
    uint64 hstatus = 0;
    hstatus |= 2 << 32;
    hstatus |= 1 << 7;

    uint64 sepc = 0x1234abcd;

    asm volatile("csrw hstatus, %0" : : "r"(hstatus));
    asm volatile("csrw sepc, %0" : : "r"(sepc));
    asm volatile("sret");
}

int main() {
    paddr paddr0 = alloc_pages(1);
    paddr paddr1 = alloc_pages(2);

    asm volatile("csrw stvec, %0" : : "r"(trap_handler));
    // print_hex((uint64)trap_handler);

    volatile uint64 *uart = (volatile uint64*)0x88888888; // example address
    // print_hex((uint64)uart);

    // print_hex(__heap);
    // print_hex(__heap_end);    


    uint64 guest_entry = 0x100000;
    uint64 kernel = alloc_pages(1);

    uint8 *dst = (uint8 *)kernel;
    for(int i = 0; i < guest_kernel_guest_bin_len; i++) {
        dst[i] = guest_kernel_guest_bin[i];
    }

    Table* table = create_table(guest_entry, kernel, PTE_R | PTE_W | PTE_X);
    


    // print_hex(paddr1);    
    // test_hypervisor();

    uint64 hstatus = 0;
    hstatus |= (uint64)2 << 32; // VSXL: XLEN for VS-mode (64-bit)
    hstatus |= (uint64)1 << 7; // SPV: Supervisor Previous Virtualization mode (HS-mode)

    print_hex(hstatus);
    print_hex(hgatp((uint64) table));    
    print_hex(guest_entry);
    uint64 sepc;

    asm volatile("csrw hstatus, %0" : : "r"(hstatus));
    asm volatile("csrw hgatp, %0" : : "r"(hgatp((uint64)table)));
    asm volatile("csrw sepc, %0" : : "r"(guest_entry));
    asm volatile("csrr %0, sepc" : : "r"(sepc));
    asm volatile("sret");
    return 0;
}