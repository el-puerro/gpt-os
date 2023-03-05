/* gdt.h
 *
 * created 2023-03-03 @ ChatGPT
 * Header file for Global Descriptor Table (GDT) initialization.
 */

#ifndef GDT_H
#define GDT_H

#include <stdint.h>

/* Segment Descriptor structure */
struct gdt_entry {
    uint16_t limit_low;
    uint16_t base_low;
    uint8_t base_middle;
    uint8_t access;
    uint8_t granularity;
    uint8_t base_high;
} __attribute__((packed));

/* GDTR structure */
struct gdt_ptr {
    uint16_t limit;
    uint32_t base;
} __attribute__((packed));

/* Define total number of GDT entries */
#define NUM_GDT_ENTRIES 3

/* Helper function to load the GDTR */
static inline void load_gdtr(uint32_t gdtr_base, uint16_t gdtr_limit)
{
    struct gdt_ptr gdtr;
    gdtr.base = gdtr_base;
    gdtr.limit = gdtr_limit;

    /* Load GDTR */
    asm volatile("lgdt %0" : : "m"(gdtr));
}

/* Helper function to load a segment register */
static inline void load_segment_register(uint16_t segment_selector)
{
    asm volatile("mov %0, %%ax; ltr %%ax;" : : "r"(segment_selector));
}

/* GDT entry initialization function */
static void gdt_entry_init(struct gdt_entry *entry, uint32_t base, uint32_t limit, uint8_t access, uint8_t granularity)
{
    entry->base_low = (base & 0xFFFF);
    entry->base_middle = (base >> 16) & 0xFF;
    entry->base_high = (base >> 24) & 0xFF;

    entry->limit_low = (limit & 0xFFFF);
    entry->granularity = ((limit >> 16) & 0x0F) | (granularity & 0xF0);

    entry->access = access;
}

/* Initialize the GDT */
static void gdt_init()
{
    struct gdt_entry gdt[NUM_GDT_ENTRIES];
    struct gdt_ptr gdtr;

    /* Null segment descriptor */
    gdt_entry_init(&gdt[0], 0, 0, 0, 0);

    /* Code segment descriptor */
    gdt_entry_init(&gdt[1], 0, 0xFFFFFFFF, 0x9A, 0xCF);

    /* Data segment descriptor */
    gdt_entry_init(&gdt[2], 0, 0xFFFFFFFF, 0x92, 0xCF);

    /* Load GDTR */
    gdtr.limit = sizeof(gdt) - 1;
    gdtr.base = (uint32_t)&gdt[0];
    load_gdtr(gdtr.base, gdtr.limit);

    /* Load segment registers */
    load_segment_register(0x08); /* Code segment selector */
    load_segment_register(0x10); /* Data segment selector */
}

#endif /* GDT_H */
