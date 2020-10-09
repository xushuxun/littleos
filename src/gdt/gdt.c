/*
 * Based on code from Bran's kernel development tutorials.
 * Rewritten for JamesM's kernel development tutorials.
 */
#include "gdt.h"

struct gdt_entry gdt_entries[5];
struct gdt_ptr   gdt_ptr;

extern void	gdt_flush(uint32_t gdt_p);

void gdt_set_gate(uint32_t n, uint32_t base, uint32_t limit, uint8_t access, uint8_t gran)
{
	gdt_entries[n].ge_base_lo = (base & 0xFFFF);
	gdt_entries[n].ge_base_mi = (base >> 16) & 0xFF;
	gdt_entries[n].ge_base_hi = (base >> 24) & 0xFF;

	gdt_entries[n].ge_limit_lo    = (limit & 0xFFFF);
	gdt_entries[n].ge_granularity = (limit >> 16) & 0x0F;

	gdt_entries[n].ge_granularity |= gran & 0xF0;
	gdt_entries[n].ge_access       = access;
}

void init_gdt()
{
	gdt_ptr.gp_limit = sizeof(struct gdt_entry) * 5 - 1;
	gdt_ptr.gp_base  = (uint32_t)&gdt_entries;

	gdt_set_gate(0, 0, 0, 0, 0);                /* Null segment */
	gdt_set_gate(1, 0, 0xFFFFFFFF, 0x9A, 0xCF); /* Code segment */
	gdt_set_gate(2, 0, 0xFFFFFFFF, 0x92, 0xCF); /* Data segment */
	gdt_set_gate(3, 0, 0xFFFFFFFF, 0xFA, 0xCF); /* User mode code segment */
	gdt_set_gate(4, 0, 0xFFFFFFFF, 0xF2, 0xCF); /* User mode data segment */

	gdt_flush((uint32_t)&gdt_ptr);
}


