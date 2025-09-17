#include "types.h"

void putchar(uint8 ch) {
    asm volatile("li a6, 0");
    asm volatile("li a7, 1");
    asm volatile("mv a0, %0" : : "r"(ch));
    asm volatile("li a2, 0");
    asm volatile("ecall");
}

void print_string(char *str) {
    int i = 0;
    while(str[i] != '\0') {
        putchar(str[i++]);
    }
}
