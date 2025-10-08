#ifndef GUEST_PAGE_TABLE_H
#define GUEST_PAGE_TABLE_H
#include "types.h"

#define PTE_V 1ULL << 0
#define PTE_R 1ULL << 1
#define PTE_W 1ULL << 2
#define PTE_X 1ULL << 3
#define PTE_U 1ULL << 4
#define PTE_ALL PTE_V | PTE_R | PTE_W | PTE_X | PTE_U
#define PPN_SHIFT 12
#define PTE_PPN_SHIFT 10

typedef struct Table {
    uint64 entry[512];
} Table;

Table* create_table (uint64 guest_paddr, uint64 host_paddr, uint64 flags);
uint64* entry_by_addr(Table *table, uint64 guest_paddr, uint8 level);
uint64 hgatp(uint64 guest_table_ptr);
#endif