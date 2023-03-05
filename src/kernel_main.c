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


void kernel_main()
{
	interrupts_init();
	vga_printf("Hello World!\n");
	for (int i = 0; i < 256; i++) {
		vga_printf("The answer is %d.\n", i);
	}
}

