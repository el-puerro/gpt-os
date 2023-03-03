; kernel_entry.asm - entry point and bootloader information
; created 2023-03-02 @ el-puerro
;
; updates:
;	2023-03-03 @ el-puerro: make bootable by grub

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

section .text

kernel_entry:
	; set up stack pointer
	mov esp, stack_space + KERNEL_STACK_SIZE

	; call kernel_main
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

