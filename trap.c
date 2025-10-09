#include "print.h"
#include "types.h"
#include "riscv.h"
#include "vcpu.h"

void handle_trap(VCpu *vcpu) {

    if(r_scause() == 10) {
        putchar((uint64)vcpu->a0);
    }
    vcpu->sepc = r_sepc() + 4;
    run_cpu(vcpu);
}

