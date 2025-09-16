#include "types.h"

extern uint8 __bss;
extern uint8 __bss_end;
extern uint8 __stack;

void putchar(uint8 ch) {
    asm volatile("li a6, 0");
    asm volatile("li a7, 1");
    asm volatile("mv a0, %0" : : "r"(ch));
    asm volatile("li a2, 0");
    asm volatile("ecall");
}

int main() {

    char test[] = "Hello World";

    for(int i = 0; i <=10; i++) {
        putchar(test[i]);
    }
    while(1) {

    }
    return 0;
}