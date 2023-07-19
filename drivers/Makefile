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

MODULE_ID := $(GET_LOCAL_DIR)

MODULE_DEPS := tools

# GENERIC BUILD SCRIPT
BUILD_DIR := build

CC := riscv64-unknown-elf-gcc
CFLAGS := -Wall -march=rv64gc -mabi=lp64 -fpie -ffreestanding

ifeq ($(CONFIG_BUILD_DEBUG),y)
	CFLAGS += -Og -ggdb
else 
	CFLAGS += -O1
endif

# manage dependancies
MODULE_DEPS_INCS := $(addsuffix /include,$(addprefix -I, $(MODULE_DEPS)))
MODULE_INCS += $(MODULE_DEPS_INCS)
MODULE_INCS += -I$(MODULE_ID)/include

# add sources for the current module
MODULE_CSRCS := $(wildcard $(MODULE_ID)/*.c)
MODULE_CINCS := $(MODULE_INCS)

MODULE_ASMSRCS := $(wildcard $(MODULE_ID)/*.S)
MODULE_ASMINCS := $(MODULE_INCS)

MODULE_COBJS := $(MODULE_CSRCS:.c=.o)
MODULE_ASMOBJS := $(MODULE_ASMSRCS:.S=.o)

MODULE_CTARGETS := $(addprefix $(BUILD_DIR)/, $(MODULE_COBJS))
MODULE_ASMTARGETS := $(addprefix $(BUILD_DIR)/, $(MODULE_ASMOBJS))

# update global module list
MODULE_LIST += $(MODULE_ID)

# declare C and ASM targets
.PHONY: build

create/$(MODULE_ID)/directory:
	mkdir $(BUILD_DIR)/drivers

$(BUILD_DIR)/$(MODULE_ID)/%.o: $(MODULE_ID)/%.c
	$(info compiling $<)
	@$(CC) $(CFLAGS) $(MODULE_CINCS) -c $< -o $@

$(BUILD_DIR)/$(MODULE_ID)/%.o: $(MODULE_ID)/%.S
	$(info compiling $<)
	@$(CC) $(CFLAGS) $(MODULE_ASMINCS) -c $< -o $@

$(MODULE_ID)/target: create/$(MODULE_ID)/directory $(MODULE_CTARGETS) $(MODULE_ASMTARGETS)

# reset variables set here
MODULE_DEPS :=
MODULE_INCS :=