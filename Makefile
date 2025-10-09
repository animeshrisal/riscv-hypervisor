CC=riscv64-unknown-elf-gcc
CFLAGS=-g -mcmodel=medany -mno-relax -I. -ffreestanding

DEPS=types.h trap.h print.h alloc.h guest_page_table.h guest_kernel.h vcpu.h
OBJS= start.o main.o trap.o print.o alloc.o guest_page_table.o vcpu.o trap_handler.o

hypervisor: $(OBJS) $(DEPS)
	$(CC) $(CFLAGS) -c main.c
	$(CC) $(CFLAGS) -c start.S
	$(CC) $(CFLAGS) -c trap_handler.S
	$(CC) -g -ffreestanding -fno-common -mno-relax -nostdlib -mcmodel=medany   -Wl,-T hypervisor.ld $(OBJS) -o hypervisor.elf

clean:
	-@rm -f *.o *.bin *.elf guest_kernel/guest.o
