#ifndef IDT_H
#define IDT_H

#include "types.h"

/* A struct describing an interrupt gate. */
struct idt_entry
{
	uint16_t	ie_base_lo; /* The lower 16 bits of the address to jump to when this interrupt fires. */
	uint16_t	ie_sel;     /* Kernel segment selector. */
	uint8_t		ie_always0; /* This must always be zero. */
	uint8_t		ie_flags;   /* More flags. See documentation. */
	uint16_t	ie_base_hi; /* The upper 16 bits of the address to jump to. */
} __attribute__((packed));

/* A struct describing a pointer to an array of interrupt handlers.
   This is in a format suitable for giving to 'lidt'. */
struct idt_ptr
{
	uint16_t	ip_limit;
	uint32_t	ip_base;  /* The address of the first element in our idt_entry_t array. */
} __attribute__((packed));

void init_idt();

/* These extern directives let us access the addresses of our ASM ISR
   handlers. */
extern void  isr0(void);
extern void  isr1(void);
extern void  isr2(void);
extern void  isr3(void);
extern void  isr4(void);
extern void  isr5(void);
extern void  isr6(void);
extern void  isr7(void);
extern void  isr8(void);
extern void  isr9(void);
extern void isr10(void);
extern void isr11(void);
extern void isr12(void);
extern void isr13(void);
extern void isr14(void);
extern void isr15(void);
extern void isr16(void);
extern void isr17(void);
extern void isr18(void);
extern void isr19(void);
extern void isr20(void);
extern void isr21(void);
extern void isr22(void);
extern void isr23(void);
extern void isr24(void);
extern void isr25(void);
extern void isr26(void);
extern void isr27(void);
extern void isr28(void);
extern void isr29(void);
extern void isr30(void);
extern void isr31(void);
extern void  irq0(void);
extern void  irq1(void);
extern void  irq2(void);
extern void  irq3(void);
extern void  irq4(void);
extern void  irq5(void);
extern void  irq6(void);
extern void  irq7(void);
extern void  irq8(void);
extern void  irq9(void);
extern void irq10(void);
extern void irq11(void);
extern void irq12(void);
extern void irq13(void);
extern void irq14(void);
extern void irq15(void);

#endif