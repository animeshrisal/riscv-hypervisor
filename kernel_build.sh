riscv64-unknown-elf-gcc \
    -Wall -Wextra -ffreestanding -nostdlib \
    -c guest_kernel/guest.S -o guest_kernel/guest.o

riscv64-unknown-elf-objcopy --input binary --output elf64-littleriscv \
    --binary-architecture riscv:rv64 guest_kernel/guest.o guest_kernel/guest_data.o
