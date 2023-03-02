/* kernel_main.c
 * created 2023-03-02 @ el-puerro
 * 
 * Updates: 
 * 
 */

#include <stdint.h>
#include <stdarg.h>

#define VGA_BUFFER 	0xb8000
#define VGA_HEIGHT 	25
#define VGA_WIDTH 	80


static uint16_t *vga = (uint16_t *)VGA_BUFFER;
static int vga_x = 0;
static int vga_y = 0;

static void vga_putchar(char c) 
{
	if (c == '\n') {
		vga_x = 0;
		vga_y++;
	} else {
		vga[vga_y * VGA_WIDTH + vga_x] = (0x0f << 8) | c;
		vga_x++;
		if (vga_x >= VGA_WIDTH) {
			vga_x = 0;
			vga_y++;
		}
	}
	if (vga_y >= VGA_HEIGHT) {
		vga_y = 0;
	}
}

static void vga_putstr(const char *s)
{
	while (*s) {
		vga_putchar(*s++);
	}
}

static void vga_putint(int value, int base) {
	static const char digits[] = "0123456789abcdef";
	char buf[32];
	int i = 0;

	if (value < 0) {
		vga_putchar('-');
		value = -value;
	}

	do {
		buf[i++] = digits[value % base];
		value /= base;
	} while (value);

	while (i > 0) {
		vga_putchar(buf[--i]);
	}
}

static void vga_printf(const char *fmt, ...)
{
	va_list args; 
	va_start(args, fmt);

	while (*fmt) {
		if (*fmt == '%') {
			switch (*fmt) {
			case 'd':
				vga_putint(va_arg(args, int), 10);
				break;
			case 'x':
				vga_putint(va_arg(args, int), 16);
				break;
			case 's':
				vga_putstr(va_arg(args, const char *));
				break;
			default:
				vga_putchar(*fmt);
			}
		} else {
			vga_putchar(*fmt);
		}
		fmt++;
	}
	va_end(args);
}


void kernel_main()
{
	vga_printf("Hello World!\n");
	vga_printf("The answer is %d.\n", 42);
}

