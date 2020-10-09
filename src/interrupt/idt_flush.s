[GLOBAL idt_flush]
idt_flush:
	mov eax, [esp+4]  ; 获取idt_ptr参数
	lidt [eax]        ; 加载idt_ptr到寄存器
	ret
