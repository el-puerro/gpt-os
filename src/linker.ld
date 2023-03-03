OUTPUT_FORMAT(elf32-i386)
ENTRY(kernel_entry)

SECTIONS
{
	. = 1M;
	.text :
	{
		*(.multiboot)
		*(.text)
	}

	.rodata :
	{
		*(.rodata)
	}

	.data :
	{
		*(.data)
	}

	.bss :
	{
	    *(.bss)
	    *(COMMON)
	}

	/DISCARD/ :
	{
		*(.note.gnu.build-id)
	}
}
