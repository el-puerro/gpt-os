# Compiler and linker settings
CC = gcc
LD = ld
CFLAGS = -ffreestanding -m32 -Wall -Wextra -nostdlib -fno-builtin -fno-stack-protector -I./src/include
LDFLAGS = -melf_i386 -T src/linker.ld

# Source files
SRCS := $(wildcard src/*.c) $(wildcard src/*.asm)

# Object files
OBJS := $(patsubst %.c, %.o, $(SRCS))
OBJS := $(patsubst %.asm, %.o, $(OBJS))

# Targets
.PHONY: all clean

all: kernel.elf

clean:
	rm -f $(OBJS) kernel.elf

kernel.elf: $(OBJS)
	$(LD) $(LDFLAGS) -o $@ $^

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

%.o: %.asm
	nasm -f elf32 $< $@
