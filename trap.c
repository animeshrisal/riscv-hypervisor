#include "print.h"
#include "types.h"
#include "riscv.h"
#include "vcpu.h"

uint64 handle_trap(VCpu *vcpu) {

    if(r_scause() == 10) {
    print_string("e call from guest");
    putchar((uint64)vcpu->a0);
    }
    return 0;
}

