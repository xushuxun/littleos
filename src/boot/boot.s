global start                     ; link.ld中将该符号声明为内核执行入口，GRUB把内核载入内存后，跳转到此处


MAGIC_NUMBER equ 0x1BADB002      ; GRUB 魔数
FLAGS        equ 0x0
CHECKSUM     equ -MAGIC_NUMBER

section .text:
align 4
    dd MAGIC_NUMBER
    dd FLAGS
    dd CHECKSUM


[EXTERN kernal_main]             ; 内核C代码入口

start: 
    cli

    call kernal_main 
    jmp $
