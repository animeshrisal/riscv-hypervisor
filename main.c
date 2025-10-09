#include "types.h"
#include "print.h"
#include "trap.h"
#include "alloc.h"
#include "vcpu.h"
#include "guest_page_table.h"

extern uint8 __bss;
extern uint8 __bss_end;
extern uint8 __stack;
extern uint8 __heap;
extern uint8 __heap_end; 

extern unsigned char guest_kernel_guest_bin[];
extern unsigned int guest_kernel_guest_bin_len;
extern void ex(void);

int main() {
    asm volatile("csrw stvec, %0" : : "r"((uint64)ex));
    uint64 guest_entry = 0x100000;
    uint64 kernel = alloc_pages(1);
    uint8 *dst = (uint8 *)kernel;
    for(int i = 0; i < guest_kernel_guest_bin_len; i++) {
        dst[i] = guest_kernel_guest_bin[i];
    } 

    VCpu cpu;
    Table* table = create_table(guest_entry, kernel, PTE_R | PTE_W | PTE_X);
    create_cpu(&cpu, table, guest_entry);    
    run_cpu(&cpu);

    return 0;
}