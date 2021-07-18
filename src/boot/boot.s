MBOOT_HEADER_MAGIC equ 0x1BADB002      ; GRUB 魔数
MBOOT_HEADER_FLAGS equ 0x0
MBOOT_CHECKSUM     equ -MBOOT_HEADER_MAGIC

[BITS 32]

[GLOBAL mboot]
[EXTERN code]
[EXTERN bss]
[EXTERN end]

mboot:
  dd  MBOOT_HEADER_MAGIC
  dd  MBOOT_HEADER_FLAGS
  dd  MBOOT_CHECKSUM
   
  dd  mboot
  dd  code
  dd  bss
  dd  end
  dd  start

[GLOBAL start]                   ; link.ld中将该符号声明为内核执行入口，GRUB把内核载入内存后，跳转到此处
[EXTERN kernal_main]             ; 内核C代码入口

start: 
  cli

  call kernal_main 
  jmp $
