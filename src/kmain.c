#include "monitor.h"
#include "gdt.h"

int kern_entry()
{
    init_gdt();

    mon_clear();
    char s[] = "hello";
    mon_write(s);

    return 0;
}