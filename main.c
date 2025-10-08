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
    asm volatile("csrw stvec, %0" : : "r"((uint64)trap_handler));

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

    uint64 sstatus = 0;
    sstatus |= 1ULL << 8;
    uint64 hedeleg = 0;
    hedeleg |= 1ULL << 0; // Instruction address misaligned
    hedeleg |= 1ULL << 1; // Instruction access fault
    hedeleg |= 1ULL << 2; // Illegal instruction
    hedeleg |= 1ULL << 3; // Breakpoint
    hedeleg |= 1ULL << 4; // Load address misaligned
    hedeleg |= 1ULL << 5; // Load access fault
    hedeleg |= 1ULL << 6; // Store/AMO address misaligned
    hedeleg |= 1ULL << 7; // Store/AMO access fault
    hedeleg |= 1ULL << 8; // Environment call from U-mode
    hedeleg |= 1ULL << 12; // Instruction page fault
    hedeleg |= 1ULL << 13; // Load page fault
    hedeleg |= 1ULL << 15; // Store/AMO page fault

    asm volatile("csrw hstatus, %0" : : "r"(hstatus));
    asm volatile("csrw sstatus, %0" : : "r"(sstatus));
    asm volatile("csrw hedeleg, %0" : : "r"(hedeleg));
    asm volatile("csrw hgatp, %0" : : "r"(hgatp((uint64)table)));
    asm volatile("csrw sepc, %0" : : "r"(guest_entry));

    asm volatile("sret");

    return 0;
}