#include "monitor.h"
#include "gdt.h"
#include "idt.h"

int kern_entry()
{
    init_gdt();
    init_idt();

    mon_clear();
    char s[] = "hello\n";
    mon_write(s);

    asm volatile ("int $0x3");

    return 0;
}