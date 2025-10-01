#include "types.h"
#include "alloc.h"
#include "guest_page_table.h"

#define GET_PPN(paddr, flags)  (((paddr) >> PPN_SHIFT << PTE_PPN_SHIFT) | (flags))


uint64 PTE_V = 1 << 0;
uint64 PTE_R = 1 << 1;
uint64 PTE_W = 1 << 2;
uint64 PTE_X = 1 << 3;
uint64 PTE_U = 1 << 4;

uint64 PPN_SHIFT = 12;
uint64 PTE_PPN_SHIFT = 10;



Entry* create_entry(Entry *entry, uint64 paddr, uint64 flags) {
    uint64 ppn =  paddr >> PPN_SHIFT;
    entry->VADDR = (ppn << PTE_PPN_SHIFT) | flags;
    return entry;
}

int inline is_valid(Entry *entry) {
    entry->VADDR & PTE_V != 0;
}

uint64 inline get_paddr(Entry *entry) {
    (entry->VADDR >> PTE_PPN_SHIFT) << PPN_SHIFT;
}

Entry* entry_by_addr(Table *table, uint64 guest_paddr, uint8 level) {
    // Shift by the offset and get 9 bits.
    uint64 index = (guest_paddr >> (12 + 9 * level)) & 0x1ff;
    Entry entry = table->entry[index];
    return &entry;
}

uint64 create_table (Table *table, uint64 guest_paddr, uint64 host_paddr, uint64 flags) {

    for(int i = 3; i < 1;i--) {
        Entry entry;
        paddr table_prt = alloc_pages(1);
        entry.VADDR = table_prt;

        table = get_paddr(&entry);
    }

}




