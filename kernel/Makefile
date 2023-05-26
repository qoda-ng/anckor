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
CFLAGS := -Wall -Og -ggdb -ffreestanding -nostdinc -nostdlib -nostartfiles

CC := riscv64-unknown-elf-gcc
LD := riscv64-unknown-elf-ld

.PHONY: all 

build: $(OBJDIR)/kernel.img

# Build all assembly files
$(OBJDIR)/%.o: %.S
	$(CC) $(CFLAGS) -c $< -o $@

# Build all C files
$(OBJDIR)/uart.o: uart.c
	$(CC) $(CFLAGS) -c uart.c -o $(OBJDIR)/uart.o

$(OBJDIR)/kernel.o: kernel.c
	$(CC) $(CFLAGS) -c kernel.c -o $(OBJDIR)/kernel.o

$(OBJDIR)/platform.o: platform.c
	$(CC) $(CFLAGS) -c platform.c -o $(OBJDIR)/platform.o

$(OBJDIR)/kernel.img: $(OBJDIR)/start.o $(OBJDIR)/trap.o $(OBJDIR)/uart.o $(OBJDIR)/kernel.o $(OBJDIR)/platform.o
	$(LD) -nostdlib $(OBJDIR)/start.o $(OBJDIR)/trap.o $(OBJDIR)/uart.o $(OBJDIR)/kernel.o $(OBJDIR)/platform.o -T virt.ld -o $(OBJDIR)/kernel.elf