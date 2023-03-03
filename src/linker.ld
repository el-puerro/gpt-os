ENTRY(kernel_entry)
SECTIONS
{
	. = 1M;
	.text ALIGN(4096) : { *(.multiboot_header) *(.text) }
	.rodata ALIGN(4096) : { *(.rodata) }
	.data ALIGN(4096) : { *(.data) }
	.bss ALIGN(4096) : { *(.bss) }
}
