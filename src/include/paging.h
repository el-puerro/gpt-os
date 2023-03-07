#ifndef PAGING_H
#define PAGING_H

#include <stdint.h>
#include <stdbool.h>
#include "vga.h"

// Page table size
#define PAGE_TABLE_SIZE 4096

// Page table entry flags
#define PAGE_PRESENT 0x1
#define PAGE_RW	  0x2
#define PAGE_USER	0x4

// Page directory entry flags
#define PAGE_DIR_PRESENT 0x1
#define PAGE_DIR_RW	  0x2
#define PAGE_DIR_USER	0x4
#define PAGE_DIR_4MB	 0x80

// Page directory size
#define PAGE_DIRECTORY_SIZE 4096

// Page size
#define PAGE_SIZE 4096

// Global page directory and page table
static uint32_t page_directory[PAGE_DIRECTORY_SIZE] __attribute__((aligned(PAGE_SIZE)));
static uint32_t page_table[PAGE_TABLE_SIZE] __attribute__((aligned(PAGE_SIZE)));

// Paging initialization function
void paging_init(void)
{
	// Map first 1MB with identity mapping
	uint32_t i;
	for (i = 0; i < 0x100000; i += PAGE_SIZE) {
		page_table[i / PAGE_SIZE] = i | PAGE_PRESENT | PAGE_RW;
	}

	// Map kernel code
	extern uint32_t __kernel_start;
	extern uint32_t __kernel_end;
	uint32_t kernel_start = (uint32_t)&__kernel_start;
	uint32_t kernel_end = (uint32_t)&__kernel_end;
	for (; kernel_start < kernel_end; kernel_start += PAGE_SIZE) {
		page_table[kernel_start / PAGE_SIZE] = kernel_start | PAGE_PRESENT | PAGE_RW;
	}

	// Create page directory entry for page table
	page_directory[768] = (uint32_t)page_table | PAGE_DIR_PRESENT | PAGE_DIR_RW;

	// Set up page directory
	uint32_t pd_addr = (uint32_t)page_directory;
	uint32_t cr3_val = pd_addr | PAGE_DIR_PRESENT | PAGE_DIR_RW;
	asm volatile("mov %0, %%cr3" :: "r" (cr3_val));

	// Enable paging
	uint32_t cr0_val;
	asm volatile("mov %%cr0, %0" : "=r" (cr0_val));
	cr0_val |= 0x80000000;
	asm volatile("mov %0, %%cr0" :: "r" (cr0_val));

	// Print debug information
	vga_printf("Paging initialized\n");
}


#endif // PAGING_H
