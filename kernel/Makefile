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

SRCS = $(wildcard *.c)
OBJS = $(SRCS:.c=.o)
CFLAGS = -Wall -O2 -ffreestanding -nostdinc -nostdlib -nostartfiles

CC = riscv64-unknown-elf-gcc
LD = riscv64-unknown-elf-ld
OBJCPY = riscv64-unknown-elf-objcopy

all: clean kernel.img

start.o: start.S
	$(CC) $(CFLAGS) -c start.S -o start.o

trap.o: trap.S
	$(CC) $(CFLAGS) -c trap.S -o trap.o

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

kernel.img: start.o trap.o $(OBJS)
	$(LD) -nostdlib start.o trap.o $(OBJS) -T virt.ld -o kernel.elf
	$(OBJCPY) -O binary kernel.elf kernel.img

clean:
	rm kernel.elf *.o >/dev/null 2>/dev/null || true

run:
	qemu-system-riscv64 -machine virt -cpu rv64 -smp 4 -m 128M -nographic -serial mon:stdio -bios none -kernel kernel.img