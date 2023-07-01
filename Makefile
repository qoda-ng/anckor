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

# TOP LEVEL MAKEFILE

OBJCPY := riscv64-unknown-elf-objcopy
LD := riscv64-unknown-elf-ld

LDFLAGS += -nostdlib -Map build/output.map -T tools/virt.ld 

.PHONY: all clean build run

all: clean build

clean:
	rm -r build
	mkdir build

build:
# build all kernel components in objects files
	cd arch && $(MAKE) $@
	cd platform && $(MAKE) $@
	cd drivers && $(MAKE) $@
	cd kernel && $(MAKE) $@
	cd lib && $(MAKE) $@
# link all components
	$(LD) $(LDFLAGS) build/printf.o build/strlen.o build/context.o build/start.o build/trap.o build/task_arch.o build/uart.o build/kernel.o build/task.o build/sched.o build/platform.o -o build/kernel.elf
	$(OBJCPY) -O binary build/kernel.elf build/kernel.img

run:
	qemu-system-riscv64 -machine virt -cpu rv64 -smp 4 -m 512M -nographic -serial mon:stdio -bios none -kernel build/kernel.elf

debug:
	qemu-system-riscv64 -s -S -machine virt -cpu rv64 -m 512M -nographic -serial mon:stdio -bios none -kernel build/kernel.elf