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

.PHONY: all clean build run

all: clean build

clean:
	rm -r build
	mkdir build

build:
# build all kernel components in objects files
	cd kernel && $(MAKE) $@
# link all components
	$(OBJCPY) -O binary build/kernel.elf build/kernel.img

run:
	qemu-system-riscv64 -machine virt -cpu rv64 -smp 4 -m 128M -nographic -serial mon:stdio -bios none -kernel build/kernel.img