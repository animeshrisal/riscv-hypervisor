.section .text
.global guest_boot
guest_boot:
    addi a0, x0, 1
    addi a0, a0, 1
    add a5, a5, a0
    add a6, a6, a0
    j guest_boot