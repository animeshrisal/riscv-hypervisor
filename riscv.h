#include "types.h"

static inline uint64 r_sstatus() {
  uint64 x;
  asm volatile("csrr %0, sstatus" : "=r"(x));
  return x;
}

uint64 r_scause() {
  uint64 x;
  asm volatile("csrr %0, scause" : "=r"(x));
  return x;
}

uint64 r_sepc() {
  uint64 x;
  asm volatile("csrr %0, sepc" : "=r"(x));
  return x;
}