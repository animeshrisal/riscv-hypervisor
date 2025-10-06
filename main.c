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

int main() {
    asm volatile("csrw stvec, %0" : : "r"(trap_handler));

    uint64 guest_entry = 0x100000;
    uint64 kernel = alloc_pages(1);

    uint8 *dst = (uint8 *)kernel;
    for(int i = 0; i < guest_kernel_guest_bin_len; i++) {
        dst[i] = guest_kernel_guest_bin[i];
    }

    Table* table = create_table(guest_entry, kernel, PTE_R | PTE_W | PTE_X);
    
    uint64 hstatus = 0;
    hstatus |= 2ULL << 32;
    hstatus |= 1ULL << 7;

    asm volatile("csrw hstatus, %0" : : "r"(hstatus));
    asm volatile("csrw hgatp, %0" : : "r"(hgatp((uint64)table)));
    asm volatile("csrw sepc, %0" : : "r"(guest_entry));
    asm volatile("sret");

    return 0;
}