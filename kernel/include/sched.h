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
#ifndef SCHED_H
#define SCHED_H

#include "common.h"
#include "task.h"

#define __no_inline __attribute__((noinline))

/******************************************************************************
 * context switch procedure
 ******************************************************************************/
extern void _switch_to(thread_t *prev_thread, thread_t *next_thread);

/******************************************************************************
 * @brief find the next task to run
 * @param none
 * @return task to run
 ******************************************************************************/
task_t *sched_get_next_task();

/******************************************************************************
 * @brief context switch from the scheduler
 *
 * This function is used to switch between two task contexts. It should not be
 * modified without careful attention: the task stack design heavily relies on
 * how this function saves parameters on the stack.
 *
 * The main use of sched_switch is saving RA before jumping to _switch_to and
 * restore the same register at the output
 *
 * @param previous_task address pointer
 * @param next_task address pointer
 * @return none
 ******************************************************************************/
__no_inline void sched_switch(task_t *prev_task, task_t *new_task);

/******************************************************************************
 * @brief initiliaze scheduler parameters
 * @param none
 * @return none
 ******************************************************************************/
void sched_init();

/******************************************************************************
 * @brief main function to run the scheduler
 * @param none
 * @return none
 ******************************************************************************/
void sched_run();

/******************************************************************************
 * @brief add a new task to the run queue
 * @param task to add in the run queue
 * @return none
 ******************************************************************************/
void sched_add_task(task_t *);

/******************************************************************************
 * @brief remove a task from the run queue
 * @param task to remove from the run queue
 * @return none
 ******************************************************************************/
void sched_remove_task(task_t *);

/******************************************************************************
 * @brief find the current running task
 * @param none
 * @return current_task address pointer
 ******************************************************************************/
task_t *sched_get_current_task();

/******************************************************************************
 * @brief set the current running task
 * @param current_task address pointer
 * @return none
 ******************************************************************************/
void sched_set_current_task(task_t *);

#endif