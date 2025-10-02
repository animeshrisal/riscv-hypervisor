#include "types.h"
#include "alloc.h"
#include "guest_page_table.h"
#include "print.h"

#define GET_PPN(paddr, flags)  (((paddr) >> PPN_SHIFT << PTE_PPN_SHIFT) | (flags))

uint64 create_entry(uint64 paddr, uint64 flags) {
    uint64 entry;
    uint64 ppn =  paddr >> PPN_SHIFT;

    entry = (ppn << PTE_PPN_SHIFT) | flags;

    return entry;
}

int is_valid(uint64 entry) {
    entry & PTE_V != 0;
}

uint64 get_paddr(uint64 entry) {
    (entry >> PTE_PPN_SHIFT) << PPN_SHIFT;
}

uint64* entry_by_addr(Table *table, uint64 guest_paddr, uint8 level) {
    // Shift by the offset and get 9 bits.
    uint64 index = (guest_paddr >> (12 + 9 * level)) & 0x1ff;
    return &table->entry[index];
}

uint64 create_table (uint64 guest_paddr, uint64 host_paddr, uint64 flags) {
    
    // Create a new table
    uint64 guest_table_ptr = alloc_pages(1);
    uint64 new_table_ptr = guest_table_ptr;
    for(int i = 3; i > 0; i--) {
        uint64* entry = entry_by_addr((Table *)new_table_ptr, guest_paddr, i);

        // uint64 new_entry = create_entry(new_table_ptr, PTE_V);
        if(is_valid(*entry)) {
            print_string("Is valid!");
        } else {
            print_string("Is not valid");
            print_string("Creating new table....");
            print_hex(new_table_ptr);
            new_table_ptr = alloc_pages(1);
            *entry = create_entry(new_table_ptr, PTE_V);
        }


    }
}




