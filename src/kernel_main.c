/* kernel_main.c
 * created 2023-03-02 @ el-puerro
 * 
 * Updates: 
 * 
 */

#include <stdint.h>

#define VGA_BUFFER 	0xb8000
#define VGA_HEIGHT 	25
#define VGA_WIDTH 	80

void kernel_main()
{
	uint16_t *vga = (uint16_t *)VGA_BUFFER;

	for (int i = 0; i < VGA_HEIGHT * VGA_WIDTH; i++) {
		vga[i] = (0x0f << 8) | ' ';
	}

	const char *msg = "Hello World!";
	int x = (VGA_WIDTH - 12) / 2;
	int y = VGA_HEIGHT / 2;
	uint16_t *pos = vga + y * VGA_WIDTH + x;

	while (*msg) {
		*pos++ = ()(0x0f << 8) | *msg++;
	}
}

