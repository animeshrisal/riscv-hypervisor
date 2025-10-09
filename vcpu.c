
#include "vcpu.h"
#include "types.h"
#include "guest_page_table.h"
#include "print.h"
#include "alloc.h"

void create_cpu(VCpu *cpu, Table *table, uint64 guest_entry) {
    
    uint64 hstatus = 0, sstatus = 0;
    
    hstatus |= 2ULL << 32;
    hstatus |= 1ULL << 7;

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

    uint64 stack_size = 512*1024;
    cpu->host_sp = alloc_pages(128) + stack_size;

    cpu->hstatus = hstatus;
    cpu->hgatp = hgatp((uint64)table);
    cpu->sstatus = sstatus;
    cpu->sepc = guest_entry;
    cpu->hedeleg = hedeleg;
}

void run_cpu(VCpu *cpu) {
    asm volatile("csrw hstatus, %0" : : "r"(cpu->hstatus));
    asm volatile("csrw sstatus, %0" : : "r"(cpu->sstatus));
    asm volatile("csrw hedeleg, %0" : : "r"(cpu->hedeleg));
    asm volatile("csrw hgatp, %0" : : "r"(cpu->hgatp));
    asm volatile("csrw sepc, %0" : : "r"(cpu->sepc));
    asm volatile("csrw sscratch, %0" : : "r"(cpu));

    asm volatile("sret");
}