#ifndef GDT_H
#define GDT_H

#include "common.h"

struct gdt_entry {
	uint16_t	ge_limit_lo;    /* The lower 16 bits of the limit. */
	uint16_t	ge_base_lo;     /* The lower 16 bits of the base. */
	uint8_t		ge_base_mi;     /* The next 8 bits of the base. */
	uint8_t		ge_access;      /* Access flags, determine what ring this segment can be used in. */
	uint8_t		ge_granularity;
	uint8_t		ge_base_hi;     /* The last 8 bits of the base. */
} __attribute__((packed));

struct gdt_ptr {
	uint16_t	gp_limit; /* The upper 16 bits of all selector limits. */
	uint32_t	gp_base;  /* The address of the first gdt_entry_t struct. */
} __attribute__((packed));


void init_gdt();


#endif