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
OBJDIR := ../build/
OBJ_TARGETS := $(addprefix $(OBJDIR), $(OBJS))
CFLAGS := -Wall -march=rv64gc -mabi=lp64 -fpie -Og -ggdb -ffreestanding
INC := -I../tools -I../drivers -I../arch -I../lib

CC := riscv64-unknown-elf-gcc

.PHONY: all build

build: $(OBJ_TARGETS)

$(OBJDIR)%.o: %.c
	$(CC) $(CFLAGS) $(INC) -c $< -o $@