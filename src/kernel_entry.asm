; kernel_entry.asm - entry point and bootloader information
; created 2023-03-02 @ el-perro
;
; updates:
; 

global kernel_entry
extern kernel_main

section .text
KERNEL_STACK_SIZE	equ 0x4000
MULTIBOOT_MAGIC		equ 0x1BADB002
MULTIBOOT_HEADER	equ kernel_entry - 0x1000

kernel_entry:
	; set up the stack pointer 
	mov esp, stack_space + KERNEL_STACK_SIZE

	; load multiboot magic number into eax
	mov eax, MULTIBOOT_MAGIC

	; Load multiboot header into ebx
	mov ebx, MULTIBOOT_HEADER

	; main kernel entry point from kernel_main.c
	call kernel_main

	; if the kernel unexpectedly returns, halt the CPU
	cli

.endloop:
	halt
	jmp .endloop

; Setup the stack
section .bss
align 4
stack_space resb KERNEL_STACK_SIZE