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

# iterate until GLOBAL_MODULE_LIST is empty
ifneq ($(GLOBAL_MODULE_LIST),)

# get the last element of the list
MODULE := $(word $(words $(GLOBAL_MODULE_LIST)),$(GLOBAL_MODULE_LIST))
# delete the module we just included from the global list
GLOBAL_MODULE_LIST := $(filter-out $(MODULE),$(GLOBAL_MODULE_LIST))
# include the module specific makefile
include $(addsuffix /module.mk,$(MODULE))

include tools/make/collect.mk

endif