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

extern void (*_task_start)(void);

/******************************************************************************
 * @brief initialize task stack
 *
 * The stack follows the riscv ABI i.e task_rt() argument is stored in a0 and sp
 * is 128 bits aligned:
 *
 * ra
 * sp -> stack_start + stack_size - 2*128
 * s0
 * s1
 * s2
 * s3
 * s4
 * s5
 * s6
 * s7
 * s8
 * s9
 * s10
 * s11
 * a0 -> task_entry
 * a1
 * a2
 * a3
 * a4
 * a5
 * a6
 * a7
 * ...
 * ----------------------- stack_start
 * ----------- <--- SP
 * _task_start
 * task_entry
 * task_rt
 * ----------------------- stack_end
 *
 * @param stack start address pointer
 * @param size of the stack
 * @param function to run in the task context
 * @return top address of the initialized stack
 ******************************************************************************/
void task_stack_init(stack_t *stack, uint64_t stack_size,
                     void (*task_entry)(void)) {
  // get task pointer from the stack
  task_t *task = (task_t *)stack;

  // zeroied callee-saved registers
  task->thread.s[0]  = 0;
  task->thread.s[1]  = 0;
  task->thread.s[2]  = 0;
  task->thread.s[3]  = 0;
  task->thread.s[4]  = 0;
  task->thread.s[5]  = 0;
  task->thread.s[6]  = 0;
  task->thread.s[7]  = 0;
  task->thread.s[8]  = 0;
  task->thread.s[9]  = 0;
  task->thread.s[10] = 0;
  task->thread.s[11] = 0;

  // initialiaze SP at the end of the stack
  // and 16-bytes align it
  task->thread.sp = (uint64_t)stack + stack_size - LWORD_SIZE;

  // move up sp and save task_rt / task_entry
  // these two pointers will be used by _task_start
  task->thread.sp -= LWORD_SIZE;
  *(uint64_t *)(task->thread.sp + DWORD_SIZE) = (uint64_t)task_rt;
  *(uint64_t *)(task->thread.sp)              = (uint64_t)task_entry;

  // move up sp and save _task_start
  task->thread.sp -= LWORD_SIZE;
  *(uint64_t *)(task->thread.sp + DWORD_SIZE) = (uint64_t)&_task_start;
}