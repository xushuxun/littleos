#include "common.h"
#include "screen.h"
#include "gdt.h"
#include "idt.h"
#include "timer.h"

int kernal_main()
{
    screen_clear();

    printf("kernel init...\n");

    init_gdt();
    init_idt();
    init_timer(200);

    asm volatile("sti");

    return 0;
}