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

#include "sched.h"

#include "processor.h"

#define MAX_PRIO 3

extern void __load_ctx(thread_t *next_thread);

static task_t *run_queue[MAX_PRIO];
static task_t *current_task;

/******************************************************************************
 * @brief main function to run the scheduler
 * @param none
 * @return none
 ******************************************************************************/
void sched_run() {
  task_t *new_task;
  task_t *prev_task;

  // save the current task
  prev_task = current_task;

  // get the new task to run
  // look over the run queue for a task to schedule
  uint8_t prio_idx = MAX_PRIO;
  while (prio_idx >= 0) {
    if (run_queue[prio_idx]) {
      // there is a task to run
      new_task = run_queue[prio_idx];
      // update the current task
      current_task = new_task;

      break;
    }

    prio_idx -= 1;
  }

  __load_ctx(&(new_task->thread));
}

/******************************************************************************
 * @brief add a new task to the run queue
 * @param task to add in run queue
 * @return none
 ******************************************************************************/
void sched_add_task(task_t *new_task) {
  run_queue[new_task->prio] = new_task;
}