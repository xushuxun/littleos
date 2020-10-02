#include <monitor.h>

int kern_entry()
{
    mon_clear();
    char s[] = "hello";
    mon_write(s);

    return 0;
}