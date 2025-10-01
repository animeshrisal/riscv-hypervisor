#ifndef GUEST_PAGE_TABLE_H
#define GUEST_PAGE_TABLE_H
#include "types.h"

#define PTE_V 1 << 0
#define PTE_R 1 << 1
#define PTE_W 1 << 2
#define PTE_X 1 << 3
#define PTE_U 1 << 4

#define PPN_SHIFT 12
#define PTE_PPN_SHIFT 10

typedef struct Table {
    uint64 entry[512];
} Table;

uint64 create_table (uint64 guest_paddr, uint64 host_paddr, uint64 flags);
uint64* entry_by_addr(Table *table, uint64 guest_paddr, uint8 level);

#endif