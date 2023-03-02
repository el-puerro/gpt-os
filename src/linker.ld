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
	}

	/DISCARD/ :
	{
		*(.note.gnu.build-id)
	}
}
