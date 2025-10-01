#include "types.h"

typedef struct Entry {
    uint64 VADDR;
} Entry;

typedef struct Table {
    Entry entry[512];
} Table;



uint64 create_table (Table *table, uint64 guest_paddr, uint64 host_paddr, uint64 flags);
Entry* entry_by_addr(Table *table, uint64 guest_paddr, uint8 level);