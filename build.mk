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

include ../.config

CC := riscv64-unknown-elf-gcc
CFLAGS := -Wall -march=rv64gc -mabi=lp64 -fpie -ffreestanding

ifeq ($(CONFIG_BUILD_DEBUG),y)
	CFLAGS += -Og -ggdb
else 
	CFLAGS += -O1
endif

MODULE_CSRCS := $(wildcard *.c)
MODULE_ASMSRCS := $(wildcard *.S)

MODULE_COBJS := $(MODULE_CSRCS:.c=.o)
MODULE_ASMOBJS := $(MODULE_ASMSRCS:.S=.o)

MODULE_CTARGETS := $(addprefix $(BUILD_DIR), $(MODULE_COBJS))
MODULE_ASMTARGETS := $(addprefix $(BUILD_DIR), $(MODULE_ASMOBJS))

.PHONY: build

build: $(MODULE_CTARGETS) $(MODULE_ASMTARGETS)

$(BUILD_DIR)%.o: %.c
	$(info compiling $<)
	@$(CC) $(CFLAGS) $(MODULE_INCS) -c $< -o $@

$(BUILD_DIR)%.o: %.S
	$(info compiling $<)
	@$(CC) $(CFLAGS) $(MODULE_INCS) -c $< -o $@