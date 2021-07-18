#include "common.h"
#include "screen.h"
#include "gdt.h"
#include "idt.h"
#include "timer.h"
#include "paging.h"
#include "kheap.h"

int kernal_main()
{
    screen_clear();

    printf("kernel init...\n");

    init_gdt();
    init_idt();
    init_paging();

    uint32_t a = kmalloc(8);
    printf("%d\n", a);
    
    for (;;) {}

    return 0;
}