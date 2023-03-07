# Compiler and linker settings
CC = gcc
LD = ld
NASM = nasm
CFLAGS = -ffreestanding -m32 -Wall -Wextra -nostdlib -fno-builtin -fno-stack-protector -I./src/include
LDFLAGS = -melf_i386 -T src/linker.ld

# Source files
SRCS := $(wildcard src/*.c) $(wildcard src/*.asm)

# Object files
OBJS := $(patsubst %.c, %.o, $(SRCS))
OBJS := $(patsubst %.asm, %.o, $(OBJS))

# Targets
.PHONY: all clean run

all: kernel.iso

clean:
	rm -f $(OBJS) kernel.elf kernel.iso

kernel.elf: $(OBJS)
	$(LD) $(LDFLAGS) -o $@ $^

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

%.o: %.asm
	$(NASM) -f elf32 $< -o $@

kernel.iso: kernel.elf
	mkdir -p iso/boot/grub
	cp $< iso/boot/kernel.elf
	echo 'set timeout=0' 			> iso/boot/grub/grub.cfg
	echo 'set default=0'			>> iso/boot/grub/grub.cfg
	echo ''					>> iso/boot/grub/grub.cfg
	echo 'menuentry "gpt-os" {'		>> iso/boot/grub/grub.cfg
	echo '	multiboot /boot/kernel.elf' 	>> iso/boot/grub/grub.cfg
	echo '	boot'				>> iso/boot/grub/grub.cfg
	echo '}'				>> iso/boot/grub/grub.cfg
	grub-mkrescue -o $@ iso

run: kernel.iso
	qemu-system-i386 -m 1024M -cdrom $<

