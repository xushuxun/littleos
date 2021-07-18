#include "common.h"
#include "screen.h"
#include "gdt.h"
#include "idt.h"
#include "timer.h"
#include "paging.h"

int kernal_main()
{
    screen_clear();

    printf("kernel init...\n");

    init_gdt();
    init_idt();
    init_paging();

    uint32_t *ptr = (uint32_t*)0xA0000000;
    
    uint32_t do_page_fault = *ptr;
    for (;;) {}

    printf("%d", do_page_fault);
    return 0;
}