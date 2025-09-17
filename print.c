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
    putchar('\n');

}

void print_hex(uint64 hex) {

    int i;
    char s;

    putchar('0');
    putchar('x');

    for (i = 60; i >= 0; i -= 4) {        
        int d = (hex >> i) & 0xF;
        if (d < 10)
            s = '0' + d;
        else
            s = 'a' + (d - 10);
        putchar(s);
    }

    putchar('\n');

}