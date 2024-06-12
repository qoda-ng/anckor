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
#include "offsets.h"
#include "processor.h"
#include "task.h"

extern void (*_task_start)(void);

/******************************************************************************
 * @brief initialize task stack
 *
 * WARNING : the stack design heavily relies on how _switch_to and sched_switch
 * behave. This should not be modified without careful attention.
 *
 * The stack follows the riscv ABI i.e task_runtime() argument is stored in a0
 * and sp is 128 bits aligned:
 *
 * ----------------------- stack_start
 * task_t start
 * ...
 * task_t end
 * -----------------------
 * ...
 * s11
 * s10
 * s9
 * s8
 * s7
 * s6
 * s5
 * s4
 * s3
 * s2
 * s1
 * s0
 * ----------- <--- SP
 * _task_start
 * task_entry
 * task_runtime
 * -----------
 * -----------
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

  // initialiaze SP at the end of the stack
  // and 16-bytes align it
  task->thread.sp = (uint64_t)stack + stack_size - LWORD_SIZE;

  // initialize kernel stack frame
  task->thread.sp -= KERNEL_STACK_FRAME_LENGTH;
  *(uint64_t *)(task->thread.sp + KERNEL_STACK_FRAME_MEPC) =
      (uint64_t)task_runtime;

  // initialize caller-saved stack frame
  task->thread.sp -= CALLER_STACK_FRAME_LENGTH;
  *(uint64_t *)(task->thread.sp + CALLER_STACK_FRAME_RA) = (uint64_t)task_entry;
  *(uint64_t *)(task->thread.sp + CALLER_STACK_FRAME_T0) = 0;
  *(uint64_t *)(task->thread.sp + CALLER_STACK_FRAME_T1) = 0;
  *(uint64_t *)(task->thread.sp + CALLER_STACK_FRAME_T2) = 0;
  *(uint64_t *)(task->thread.sp + CALLER_STACK_FRAME_T3) = 0;
  *(uint64_t *)(task->thread.sp + CALLER_STACK_FRAME_T4) = 0;
  *(uint64_t *)(task->thread.sp + CALLER_STACK_FRAME_T5) = 0;
  *(uint64_t *)(task->thread.sp + CALLER_STACK_FRAME_T6) = 0;
  *(uint64_t *)(task->thread.sp + CALLER_STACK_FRAME_A0) = 0;
  *(uint64_t *)(task->thread.sp + CALLER_STACK_FRAME_A1) = 0;
  *(uint64_t *)(task->thread.sp + CALLER_STACK_FRAME_A2) = 0;
  *(uint64_t *)(task->thread.sp + CALLER_STACK_FRAME_A3) = 0;
  *(uint64_t *)(task->thread.sp + CALLER_STACK_FRAME_A4) = 0;
  *(uint64_t *)(task->thread.sp + CALLER_STACK_FRAME_A5) = 0;
  *(uint64_t *)(task->thread.sp + CALLER_STACK_FRAME_A6) = 0;
  *(uint64_t *)(task->thread.sp + CALLER_STACK_FRAME_A7) = 0;

  // move up sp and save _task_start
  task->thread.sp -= LWORD_SIZE;
  *(uint64_t *)(task->thread.sp + DWORD_SIZE) = (uint64_t)&_task_start;

  // move up sp to initialize callee-saved registers
  task->thread.sp -= CALLEE_STACK_FRAME_LENGTH;
  *(uint64_t *)(task->thread.sp + CALLEE_STACK_FRAME_S0)  = 0;
  *(uint64_t *)(task->thread.sp + CALLEE_STACK_FRAME_S1)  = 0;
  *(uint64_t *)(task->thread.sp + CALLEE_STACK_FRAME_S2)  = 0;
  *(uint64_t *)(task->thread.sp + CALLEE_STACK_FRAME_S3)  = 0;
  *(uint64_t *)(task->thread.sp + CALLEE_STACK_FRAME_S4)  = 0;
  *(uint64_t *)(task->thread.sp + CALLEE_STACK_FRAME_S5)  = 0;
  *(uint64_t *)(task->thread.sp + CALLEE_STACK_FRAME_S6)  = 0;
  *(uint64_t *)(task->thread.sp + CALLEE_STACK_FRAME_S7)  = 0;
  *(uint64_t *)(task->thread.sp + CALLEE_STACK_FRAME_S8)  = 0;
  *(uint64_t *)(task->thread.sp + CALLEE_STACK_FRAME_S9)  = 0;
  *(uint64_t *)(task->thread.sp + CALLEE_STACK_FRAME_S10) = 0;
  *(uint64_t *)(task->thread.sp + CALLEE_STACK_FRAME_S11) = 0;
}