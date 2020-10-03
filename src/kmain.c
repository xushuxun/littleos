#include "monitor.h"
#include "gdt.h"
#include "idt.h"
#include "timer.h"

int kern_entry()
{
    init_gdt();
    init_idt();

    mon_clear();
    char s[] = "hello\n";
    mon_write(s);

    init_timer(50); 

    asm volatile("sti");

    return 0;
}