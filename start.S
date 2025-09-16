.section .text 
.global boot 
boot:
    la sp, __stack_top
    j main