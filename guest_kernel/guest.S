.section .text
.global guest_boot
guest_boot:
    auipc a1, 10000
    li a1, 10000
    addi a1, a0, 1
    addi a5, a0, 2
    add a6, a5, a1
    j guest_boot