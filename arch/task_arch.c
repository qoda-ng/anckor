/*
 * Copyright (c) 2023 Qoda, engineering
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms and conditions of the GNU General Public License,
 * version 3 or later, as published by the Free Software Foundation.

 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * General Public License for more details.

 * You should have received copies of the GNU General Public License and
 * the GNU Lesser General Public License along with this program.  If
 * not, see https://www.gnu.org/licenses/
 */
#include "common.h"
#include "processor.h"
#include "task.h"

/******************************************************************************
 * @brief initialize task stack
 * @param stack start address pointer
 * @param size of the stack
 * @param function to run in the task context
 * @return top address of the initialized stack
 ******************************************************************************/
uint64_t task_stack_init(
    stack_t *stack, uint64_t stack_size,
    __attribute__((noreturn)) void (*task_rt)(void (*)(void))) {
  // save the return address at the first address of the stack
  uint64_t stack_return_addr       = (uint64_t)stack + stack_size - DWORD_SIZE;
  *(uint64_t *)(stack_return_addr) = (uint64_t)task_rt;

  return (uint64_t)stack + STACK_SIZE - LWORD_SIZE;
}