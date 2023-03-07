ENTRY(kernel_entry)

SECTIONS
{
	. = 1M;
	.text ALIGN(4096) : { *(.multiboot_header) *(.text) }
	__kernel_start = .;
	. = ALIGN(4096);
	.rodata ALIGN(4096) : { *(.rodata) }
	. = ALIGN(4096);
	.data ALIGN(4096) : { *(.data) }
	. = ALIGN(4096);
	.bss ALIGN(4096) : { *(.bss) }
	__kernel_end = .;

	/DISCARD/ : { *(.comment) }
}
