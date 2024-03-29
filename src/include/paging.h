#ifndef PAGING_H
#define PAGING_H

#include "common.h"
#include "isr.h"

struct page
{
   uint32_t present    : 1;   // Page present in memory
   uint32_t rw         : 1;   // Read-only if clear, readwrite if set
   uint32_t user       : 1;   // Supervisor level only if clear
   uint32_t accessed   : 1;   // Has the page been accessed since last refresh?
   uint32_t dirty      : 1;   // Has the page been written to since last refresh?
   uint32_t unused     : 7;   // Amalgamation of unused and reserved bits
   uint32_t frame      : 20;  // Frame address (shifted right 12 bits)
};

struct page_table
{
   struct page pages[1024];
};

struct page_directory
{
   /**
      Array of pointers to pagetables.
   **/
   struct page_table *tables[1024];
   /**
      Array of pointers to the pagetables above, but gives their *physical*
      location, for loading into the CR3 register.
   **/
   uint32_t tablesPhysical[1024];

   /**
      The physical address of tablesPhysical. This comes into play
      when we get our kernel heap allocated and the directory
      may be in a different location in virtual memory.
   **/
   uint32_t physicalAddr;
};

/**
   Sets up the environment, page directories etc and
   enables paging.
**/
void init_paging();

/**
   Causes the specified page directory to be loaded into the
   CR3 register.
**/
void switch_page_directory(struct page_directory *);

/**
   Retrieves a pointer to the page required.
   If make == 1, if the page-table in which this page should
   reside isn't created, create it!
**/
struct page *get_page(uint32_t address, int make, struct page_directory *dir);

/**
   Handler for page faults.
**/
void page_fault(struct cpu_regs*);

void free_frame(struct page *page);

void alloc_frame(struct page *page, int is_kernel, int is_writeable);

#endif