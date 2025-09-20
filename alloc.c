#include "types.h"

#define HBASE 0x80200000L 
#define PHYSTOP (HBASE + 128 * 1024 *1024)
#define PGSIZE 4096

extern uint8 __heap[];
extern char __heap_end[]; 

static paddr next_paddr = (paddr) __heap;

struct run {
    struct run *next;
};

struct {
    struct run *freelist;
} kmem;

void freerange(void *pa_start, void *pa_end) {
    char *p;



}


void einit() {
    
}

void* setmem(void *dst, int c, int n) {
    char *cdst = (char *) dst;

    for (int i = 0; i < n; i++) {
        cdst[i] = c;
    }

    return dst;
}

 paddr alloc_pages(uint32 size) {
    paddr paddr = next_paddr;
    next_paddr += size * PGSIZE;

    if(next_paddr > __heap_end) {
        // KERNEL PANIC
    }

    setmem((void *)next_paddr, 0, size * PGSIZE);
    return paddr;
}

void ealloc(uint16 size) {
    uint16 totalSize;

    
}