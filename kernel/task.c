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
 * @brief task runtinme
 *
 * This function is used to run task_entry in a controlled environment. It cans
 * run an exit() procedure to properly clean the task if ever its main procedure
 * returns.
 *
 * @param function to run in the task
 * @return none
 ******************************************************************************/
static __attribute__((noreturn)) void task_rt(void (*task_entry)(void)) {
  // start the main task routine
  task_entry();

  // clean the task if ever it returns
  task_destroy();

  // tell the compiler we will never reach this point
  __builtin_unreachable();
}

/******************************************************************************
 * @brief initialize a task and schedule it
 * @param id of the task
 * @param function to run in the task
 * @param stack start address of the task
 * @param priority for the new task
 * @return ax_return -1 if task initialization failed
 ******************************************************************************/
ax_return_t task_create(uint32_t id, void (*task_entry)(void), stack_t *stack,
                        uint8_t prio) {
  // save task infos at the beginning of the task
  task_t *task = (task_t *)stack;

  // find a unique task ID
  task->task_id.vms_id    = 0;
  task->task_id.thread_id = id;

  // save task priority
  task->prio = prio;

  // all created tasks are placed in READY state
  task->state = READY;

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

  // save task entry in the a0 register which is the first function parameter in
  // the riscv ABI
  task->thread.a[0] = (uint64_t)task_entry;

  // move SP (128 bits aligned) to save return address
  task->thread.sp = task_stack_init(stack, STACK_SIZE, task_rt);

  // save the new task in the run queue
  sched_add_task(task);

  return AX_OK;
}

/******************************************************************************
 * @brief yield the cpu to an another task
 * @param none
 * @return ax_return -1 if error
 ******************************************************************************/
ax_return_t task_yield() {
  sched_run();

  return AX_OK;
}

/******************************************************************************
 * @brief task destroy
 *
 * This function cleans all memory used to save task informations, this
 * comprises all stacks and associated structures. It also delete the task from
 * the scheduler runqueue.
 *
 * @param none
 * @return none
 ******************************************************************************/
void task_destroy() {
}