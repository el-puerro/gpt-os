/* kernel_main.c
 * created 2023-03-02 @ el-puerro
 * 
 * Updates: 
 *	2023-03-03 @ el-puerro: removed vga specific stuff to vga.h
 */

#include <stdint.h>
#include <stdarg.h>

#include "include/vga.h"
#include "include/interrupts.h"
#include "include/paging.h"
#include "include/pmm.h"


uint32_t placement_address;

void kernel_main()
{
	paging_init();
	interrupts_init();
	pmm_init();
	vga_printf("This OS is written almost completely by ChatGPT!\n");
}
