#include "types.h"
#include "alloc.h"
#include "guest_page_table.h"
#include "guest_kernel.h"
#include "print.h"

#define GET_PPN(paddr, flags)  (((paddr) >> PPN_SHIFT << PTE_PPN_SHIFT) | (flags))

uint64 create_entry(uint64 paddr, uint64 flags) {
    uint64 entry;
    uint64 ppn =  paddr >> PPN_SHIFT;

    entry = (ppn << PTE_PPN_SHIFT) | flags;

    return entry;
}

int is_valid(uint64 entry) {
    return (entry & PTE_V) != 0;}

uint64 get_paddr(uint64 entry) {
    return ((entry >> PTE_PPN_SHIFT) << PPN_SHIFT);}

uint64* entry_by_addr(Table *table, uint64 guest_paddr, uint8 level) {
    // Shift by the offset and get 9 bits.
    uint64 index = (guest_paddr >> (12 + 9 * level)) & 0x1ffULL;
    return &table->entry[index];
}

uint64 hgatp(uint64 guest_table_ptr) {
    const uint64 MODE_SV48 = 9ULL;
    return ((MODE_SV48 << 60) | ( (guest_table_ptr) >> PPN_SHIFT ));
}

Table* create_table (uint64 guest_paddr, uint64 host_paddr, uint64 flags) {
    
    // Create a new table
    uint64 guest_table_ptr = alloc_pages(1);
    uint64 current_table_ptr = guest_table_ptr;

    for(int i = 3; i > 0; i--) {
        uint64* entry = entry_by_addr((Table *)current_table_ptr, guest_paddr, i);

        // uint64 new_entry = create_entry(new_table_ptr, PTE_V);
        if(is_valid(*entry)) {
            print_string("Is valid!");
            current_table_ptr = get_paddr(*entry);
        } else {
            print_string("Is not valid");
            print_string("Creating new table....");

            uint64 next_table = alloc_pages(1);

            for (uint8 j=0;j<512;j++) ((uint64*)next_table)[j]=0;
            
            *entry = create_entry(next_table, PTE_V);
            current_table_ptr = next_table;
        }
    }

    uint64* entry = entry_by_addr((Table *)current_table_ptr, guest_paddr, 0);
    *entry = create_entry(host_paddr, flags | PTE_V | PTE_U);

    return (Table *)guest_table_ptr;
}




