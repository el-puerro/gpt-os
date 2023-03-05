; kernel_entry.asm - entry point and bootloader information
; created 2023-03-02 @ el-puerro
;
; updates:
;	2023-03-03 @ el-puerro: make bootable by grub
; 	2023-03-05 @ chatGPT: GDT initialization
;	2023-03-06 @ chatGPT: Paging initialization

[bits 32]

; define multiboot header
align 4
multiboot_header:
	dd 0x1BADB002		; magic number
	dd 0			; flags
	dd - (0x1BADB002 + 0)	; checksum

; kernel entry point
global kernel_entry
extern kernel_main
extern enable_paging

; GDT initialization
gdt_start:
	dd 0x00000000		; null descriptor
	dd 0x00000000
gdt_code:
	dw 0xFFFF		; limit low
	dw 0x0000		; base low
	db 0x00			; base middle
	db 0x9A			; access
	db 0xCF			; granularity
	db 0x00			; base high
gdt_data:
	dw 0xFFFF		; limit low
	dw 0x0000		; base low
	db 0x00			; base middle
	db 0x92			; access
	db 0xCF			; granularity
	db 0x00			; base high
gdt_end:

gdt_descriptor:
	dw gdt_end - gdt_start - 1	; GDT limit
	dd gdt_start			; GDT base

section .text

kernel_entry:

	; set up stack pointer
	mov esp, stack_space + KERNEL_STACK_SIZE

	; initialize GDT
	lgdt [gdt_descriptor]

	; TODO: fix
	; enable paging
	; call enable_paging

	; call kernel_main()
	call kernel_main

	; if the kernel unexpectedly returns, halt the cpu
	cli
	hlt

; set up the stack
section .bss
align 4
stack_space:
	resb KERNEL_STACK_SIZE

KERNEL_STACK_SIZE equ 0x4000
