[GLOBAL gdt_flush]

gdt_flush:
    mov eax, [esp+4]  ; 获取gdt_ptr参数
    lgdt [eax]        ; 加载gdt_ptr到寄存器

    jmp .flush
    
.flush:
    ret
