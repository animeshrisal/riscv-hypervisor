#!/bin/bash
set -xue

# QEMU file path
QEMU=qemu-system-riscv64

# Start QEMU
$QEMU -machine virt -bios default -smp 1 -m 128M -nographic -d cpu_reset,unimp,guest_errors,int -D qemu.log -serial mon:stdio --no-reboot -kernel hypervisor.elf