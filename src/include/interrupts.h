/* interrupts.h
 * created 2023-03-05 @ chatGPT
 *
 * Updates:
 *
 */

#ifndef INTERRUPTS_H
#define INTERRUPTS_H

#include <stdint.h>

/* IDT entry structure */
struct idt_entry {
	uint16_t offset_1;  // offset bits 0..15
	uint16_t selector;  // a code segment selector in GDT or LDT
	uint8_t zero;       // unused, set to 0
	uint8_t type_attr;  // type and attributes
	uint16_t offset_2;  // offset bits 16..31
} __attribute__((packed));

/* IDT descriptor structure */
struct idt_descriptor {
	uint16_t limit;           // size of IDT in bytes -1
	uint32_t base;            // address of first IDT entry
} __attribute__((packed));

/* Define the maximum number of interrupts */
#define NUM_INTERRUPTS 256

/* Define the interrupt handler function type */
typedef void (*interrupt_handler_t)(void);

/* Define the IDT and interrupt handler arrays */
static struct idt_entry idt[NUM_INTERRUPTS];
static interrupt_handler_t interrupt_handlers[NUM_INTERRUPTS];

/* IDT initialization function */
static inline void interrupts_init(void) {
	// Set up the IDT entries with the interrupt handlers
	for (int i = 0; i < NUM_INTERRUPTS; i++) {
		// Set the interrupt handler
		interrupt_handler_t handler = interrupt_handlers[i];
		uint32_t handler_addr = (uint32_t)handler;
		idt[i].offset_1 = handler_addr & 0xffff;
		idt[i].selector = 0x08;  // code segment in GDT
		idt[i].zero = 0;
		idt[i].type_attr = 0x8e;  // present, kernel-mode, 32-bit interrupt gate
		idt[i].offset_2 = (handler_addr >> 16) & 0xffff;
	}

	// Load the IDT descriptor
	struct idt_descriptor idt_desc = {
		.limit = sizeof(idt) - 1,
		.base = (uint32_t)&idt[0]
	};
	asm volatile("lidt %0" : : "m"(idt_desc));
}

/* Interrupt handler function definitions */
static inline void divide_error_handler(void) {
	asm volatile("cli");
	while (1) {}
}

static inline void debug_handler(void) {
	asm volatile("cli");
	while (1) {}
}

static inline void nmi_handler(void) {
	asm volatile("cli");
	while (1) {}
}

static inline void breakpoint_handler(void) {
	asm volatile("cli");
	while (1) {}
}

static inline void overflow_handler(void) {
	asm volatile("cli");
	while (1) {}
}

static inline void bounds_check_handler(void) {
	asm volatile("cli");
	while (1) {}
}

static inline void invalid_opcode_handler(void) {
	asm volatile("cli");
	while (1) {}
}

static inline void device_not_available_handler(void) {
	asm volatile("cli");
	while (1) {}
}

static inline void double_fault_handler(void) {
	asm volatile("cli");
	while (1) {}
}

static inline void coprocessor_segment_overrun_handler(void) {
	asm volatile("cli");
	while (1) {}
}

static inline void invalid_tss_handler(void) {
	asm volatile("cli");
	while (1) {}
}

static inline void segment_not_present_handler(void) {
	asm volatile("cli");
	while (1) {}
}

static inline void stack_segment_fault_handler(void) {
	asm volatile("cli");
	while (1) {}
}

static inline void general_protection_fault_handler(void) {
	asm volatile("cli");
	while (1) {}
}

static inline void page_fault_handler(void) {
	asm volatile("cli");
	while (1) {}
}

static inline void x87_floating_point_handler(void) {
	asm volatile("cli");
	while (1) {}
}

static inline void alignment_check_handler(void) {
	asm volatile("cli");
	while (1) {}
}

static inline void machine_check_handler(void) {
	asm volatile("cli");
	while (1) {}
}

static inline void simd_floating_point_handler(void) {
	asm volatile("cli");
	while (1) {}
}

static inline void virtualization_handler(void) {
	asm volatile("cli");
	while (1) {}
}

static inline void security_exception_handler(void) {
	asm volatile("cli");
	while (1) {}
}


