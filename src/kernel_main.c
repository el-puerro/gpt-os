/* kernel_main.c
 * created 2023-03-02 @ el-puerro
 * 
 * Updates: 
 *	2023-03-03 @ el-puerro: removed vga specific stuff to vga.h
 */

#include <stdint.h>
#include <stdarg.h>
#include "include/vga.h"
#include "include/gdt.h"


void kernel_main()
{
	/* GDT init */
	vga_printf("Initialising GDT\n");
	gdt_init();

	vga_printf("Hello World!\n");
	vga_printf("The answer is %d.\n", 42);
}

