riscv64-unknown-elf-gcc \
    -Wall -Wextra -ffreestanding -nostdlib \
    -c guest_kernel/guest.S -o guest_kernel/guest.o

riscv64-unknown-elf-objcopy -O binary guest_kernel/guest.o guest_kernel/guest.bin

xxd -i guest_kernel/guest.bin > guest_kernel.h