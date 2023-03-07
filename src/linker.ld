ENTRY(kernel_entry)

SECTIONS
{
  . = 1M;

  .text ALIGN(4096) : { *(.multiboot_header) *(.text) }
  . = ALIGN(4096);
  .rodata ALIGN(4096) : { *(.rodata) }
  . = ALIGN(4096);
  .data ALIGN(4096) : { *(.data) }
  . = ALIGN(4096);
  .bss ALIGN(4096) : { *(.bss) }

  /DISCARD/ : { *(.comment) }
}
