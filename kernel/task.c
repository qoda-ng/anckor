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
#include "task.h"

#include "sched.h"

/******************************************************************************
 * @brief initialize a task and schedule it
 * @param task to initialize
 * @return ax_return -1 if task initialization failed
 ******************************************************************************/
ax_return_t task_create(uint32_t id, task_t *task, void (*fn)(void),
                        stack_t *stack, uint8_t prio) {
  // find a unique task ID
  task->vms_id    = 0;
  task->thread_id = id;

  // save thread function
  task->thread.ra = (uint64_t)fn;

  // save the last address of the allocated task stack
  task->thread.sp = (uint64_t)stack + STACK_SIZE - 1;

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

  // save the new task in the run queue
  sched_add_task(task);

  return AX_OK;
}

/******************************************************************************
 * @brief yield the cpu to an another task
 * @param
 * @return ax_return -1 if error
 ******************************************************************************/
ax_return_t task_yield() {
  sched_run();

  return AX_OK;
}