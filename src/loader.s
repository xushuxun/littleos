global loader                   ; the entry symbol for ELF

MAGIC_NUMBER equ 0x1BADB002     ; define the magic number constant
FLAGS        equ 0x0            ; multiboot flags
CHECKSUM     equ -MAGIC_NUMBER  ; calculate the checksum
                                ; (magic number + checksum + flags should equal 0)

section .text:                  ; start of the text (code) section
align 4                         ; the code must be 4 byte aligned
    dd MAGIC_NUMBER             ; write the magic number to the machine code,
    dd FLAGS                    ; the flags,
    dd CHECKSUM                 ; and the checksum

[GLOBAL glb_mboot_ptr]
[EXTERN kern_entry]

loader: 
    cli

    mov esp, STACK_TOP
    mov ebp, 0
    and esp, 0FFFFFFF0H
    mov [glb_mboot_ptr], ebx
    call kern_entry

stop:
    hlt
    jmp stop

section .bss
stack:
    resb 32768
glb_mboot_ptr:
    resb 4

STACK_TOP equ $-stack-1
