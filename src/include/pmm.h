/* pmm.h - physical memory management/page frame allocation
 * created 2023-03-7 @ chatGPT
 * 
 * Updates: 
 *
 */
#ifndef PMM_H
#define PMM_H

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include "paging.h"
#include "vga.h"

// Constants
#define PMM_FRAME_SIZE PAGE_SIZE
#define PMM_FRAME_ALIGN PMM_FRAME_SIZE

// External symbols from linker script
extern uint32_t __kernel_start;
extern uint32_t __kernel_end;

// Global variables
extern uint32_t placement_address;

// Function declarations
void pmm_init(void);
void* pmm_alloc_frame(void);
void pmm_free_frame(void* frame);

// Bitmap for physical memory
#define PMM_BITMAP_SIZE 131072 // 1 MiB of memory
static uint32_t pmm_bitmap[PMM_BITMAP_SIZE / sizeof(uint32_t)];

// Number of frames
static size_t pmm_nframes;

// Macros to get/set bits in the bitmap
#define PMM_FRAME_INDEX(addr) ((addr) / PMM_FRAME_SIZE)
#define PMM_BIT_INDEX(addr) ((addr) % PMM_FRAME_SIZE)
#define PMM_GET_BIT(n) (pmm_bitmap[(n) / 32] & (1 << ((n) % 32)))
#define PMM_SET_BIT(n) (pmm_bitmap[(n) / 32] |= (1 << ((n) % 32)))
#define PMM_CLEAR_BIT(n) (pmm_bitmap[(n) / 32] &= ~(1 << ((n) % 32)))

void pmm_init(void)
{
	// Get the kernel start and end address
	uint32_t kernel_end = (uint32_t)&__kernel_end;
	uint32_t kernel_start = (uint32_t)&__kernel_start;

	// Initialize the bitmap
	for (size_t i = 0; i < PMM_BITMAP_SIZE / sizeof(uint32_t); ++i) {
		pmm_bitmap[i] = 0;
	}

	// Mark all memory used by kernel as used in the bitmap
	for (uint32_t addr = (uint32_t)&kernel_start; addr < kernel_end; addr += PMM_FRAME_SIZE) {
		PMM_SET_BIT(PMM_FRAME_INDEX(addr));
	}

	// Initialize the placement address
	placement_address = kernel_end;
	vga_printf("Page Frame Allocator initialized!\n");
	vga_printf("Starting addr = 0x%x\n", placement_address);
}

void* pmm_alloc_frame(void)
{
	// Find first free frame
	for (size_t i = 0; i < PMM_BITMAP_SIZE; ++i) {
		if (!PMM_GET_BIT(i)) {
			PMM_SET_BIT(i);
			uint32_t addr = i * PMM_FRAME_SIZE;
			return (void*)addr;
		}
	}
	return NULL;
}

void pmm_free_frame(void* frame)
{
	uint32_t addr = (uint32_t)frame;
	size_t index = PMM_FRAME_INDEX(addr);
	PMM_CLEAR_BIT(index);
}

#endif // PMM_H
