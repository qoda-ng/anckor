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

extern void __load_ctx(thread_t *next_thread);

/******************************************************************************
 * @brief main function to run the scheduler
 * @param none
 * @return ax_return -1 if the scheduler fails to run the next task
 ******************************************************************************/
void sched_run(task_t *next_task) {
  __load_ctx(&(next_task->thread));
}