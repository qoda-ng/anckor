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

include tools/make/macros.mk

include tools/generated/config.mk

OBJCPY := riscv64-unknown-elf-objcopy
LD := riscv64-unknown-elf-ld
GLOBAL_LDFLAGS += -nostdlib -Map build/output.map -T tools/linker/virt.ld 

ifeq ($(config_build_debug),y)
	GLOBAL_LDFLAGS += -g
endif

.PHONY: all build run

all: clean build

clean: 
# delete build directory if it already exists
	@if [ -d "build" ]; then \
		rm -r build; \
	fi

setup_build_dir: clean
	@mkdir build

MODULE_TARGET_LIST :=

MODULE_DEPS :=
MODULE_INCS :=

MODULE_CSRCS :=
MODULE_CINCS :=

MODULE_ASMSRCS :=
MODULE_ASMINCS :=

MODULE_COBJS :=
MODULE_ASMOBJS := 

MODULE_CTARGETS := 
MODULE_ASMTARGETS := 

MODULE_CFLAGS := 

GLOBAL_OBJECTS_LIST :=



include tools/make/collect.mk

# MODULE_TARGET_LIST contains all modules to build before linking
build: setup_build_dir $(MODULE_TARGET_LIST)
# link all components
	$(info link all objects files)
	@$(LD) $(GLOBAL_LDFLAGS) $(GLOBAL_OBJECTS_LIST) -o build/kernel.elf
	$(info generate kernel image)
	@$(OBJCPY) -O binary build/kernel.elf build/kernel.img

run:
	$(info run [release] build)
	qemu-system-riscv64 -machine virt -cpu rv64 -smp 4 -m 512M -nographic -serial mon:stdio -bios none -kernel build/kernel.elf

debug:
	$(info run [debug] build)
	qemu-system-riscv64 -s -S -machine virt -cpu rv64 -smp 4 -m 512M -nographic -serial mon:stdio -bios none -kernel build/kernel.elf