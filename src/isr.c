/*
 * isr.c -- High level interrupt service routines and interrupt request handlers.
 * Part of this code is modified from Bran's kernel development tutorials.
 * Rewritten for JamesM's kernel development tutorials.
 */
#include "types.h"
#include "isr.h"
#include "io.h"
#include "monitor.h"

isrhdl_t interrupt_handlers[256];

/* This gets called from our ASM interrupt handler stub. */
void
isr_handler(struct cpu_regs* regs)
{
    if (interrupt_handlers[regs->int_no]) {
        isrhdl_t handler = interrupt_handlers[regs->int_no];
		handler(regs);
    } else {
        char s[] = "unhandle interrupt";
        mon_write(s);
    }
}

/* This gets called from our ASM interrupt handler stub. */
void
irq_handler(struct cpu_regs* regs) {
	/* Send an EOI (end of interrupt) signal to the PICs. If this interrupt
	   involved the slave. */
	if (regs->int_no >= 40) {
		/* Send reset signal to slave.*/
		outb(0xA0, 0x20);
	}
	/* Send reset signal to master. */
	outb(0x20, 0x20);

	if (interrupt_handlers[regs->int_no] != 0) {
		isrhdl_t handler = interrupt_handlers[regs->int_no];
		handler(regs);
	}
}


void
register_interrupt_handler(uint32_t n, isrhdl_t handler)
{
	interrupt_handlers[n] = handler;
}
