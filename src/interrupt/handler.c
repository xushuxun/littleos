/*
 * isr.c -- High level interrupt service routines and interrupt request handlers.
 * Part of this code is modified from Bran's kernel development tutorials.
 * Rewritten for JamesM's kernel development tutorials.
 */
#include "common.h"
#include "isr.h"
#include "io.h"

isrhdl_t interrupt_handlers[256];

// 处理内部中断
void isr_handler(struct cpu_regs* regs)
{
	printf("handle interrupt %d\n", regs->int_no);
	
    if (interrupt_handlers[regs->int_no]) {
        isrhdl_t handler = interrupt_handlers[regs->int_no];
		handler(regs);
    } 
}

// 处理外部中断
void irq_handler(struct cpu_regs* regs) {
	// 发送重置信号给 8259A
	if (regs->int_no >= 40) {
 		outb(0xA0, 0x20); // 从芯片
	}
	outb(0x20, 0x20);     // 主芯片

	if (interrupt_handlers[regs->int_no]) {
        isrhdl_t handler = interrupt_handlers[regs->int_no];
		handler(regs);
    } 
}


void register_interrupt_handler(uint32_t n, isrhdl_t handler)
{
	interrupt_handlers[n] = handler;
}
