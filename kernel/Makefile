# Copyright (c) 2023 Qoda, engineering

# This program is free software; you can redistribute it and/or modify 
# it under the terms and conditions of the GNU General Public License,
# version 3 or later, as published by the Free Software Foundation.

# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
# General Public License for more details.

# You should have received copies of the GNU General Public License and
# the GNU Lesser General Public License along with this program.  If
# not, see https://www.gnu.org/licenses/

SRCS := $(wildcard *.c)
OBJS := $(SRCS:.c=.o)
OBJDIR := ../build
CFLAGS := -Wall -O2 -ffreestanding -nostdinc -nostdlib -nostartfiles

CC := riscv64-unknown-elf-gcc
LD := riscv64-unknown-elf-ld
OBJCPY := riscv64-unknown-elf-objcopy

.PHONY: all clean build run

all: clean $(OBJDIR)/kernel.img

# Build all assembly files
$(OBJDIR)/%.o: %.S
	$(CC) $(CFLAGS) -c $< -o $@

# Build all C files
$(OBJDIR)/%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJDIR)/kernel.img: $(OBJDIR)/start.o $(OBJDIR)/trap.o $(OBJDIR)/$(OBJS)
	$(LD) -nostdlib $(OBJDIR)/start.o $(OBJDIR)/trap.o $(OBJDIR)/$(OBJS) -T virt.ld -o $(OBJDIR)/kernel.elf
	$(OBJCPY) -O binary $(OBJDIR)/kernel.elf $(OBJDIR)/kernel.img

clean:
	rm -r ../build
	mkdir ../build

run:
	qemu-system-riscv64 -machine virt -cpu rv64 -smp 4 -m 128M -nographic -serial mon:stdio -bios none -kernel kernel.img