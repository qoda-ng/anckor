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
#include "printf.h"
#include "sched.h"
#include "task.h"
#include "uart.h"

#define INIT_PRIO 1

stack_t init_stack;

/******************************************************************************
 * @brief Idle routine runned when no other tasks are ready
 * @param None
 * @return None
 ******************************************************************************/
void idle_run(void) {
  printf("start task %d / prio %d\r\n", 0, 0);

  task_yield();

  printf("return to task %d / prio %d\r\n", 0, 0);

  task_wakeup((task_t *)init_stack);

  printf("return to task %d / prio %d\r\n", 0, 0);

  while (1) {
  }
}

/******************************************************************************
 * @brief Init task will launch all registered tasks in the system
 * @param None
 * @return None
 ******************************************************************************/
void init_run(void) {
  uint64_t init_task_id   = task_get_tid((task_t *)init_stack);
  uint8_t  init_task_prio = task_get_priority((task_t *)init_stack);

  printf("start task %d / prio %d\r\n", init_task_id, init_task_prio);

  task_sleep();

  printf("wake up task %d / prio %d\r\n", init_task_id, init_task_prio);
}

/******************************************************************************
 * @brief initialisation of kernel structures and launch the first task
 * @param None
 * @return None
 ******************************************************************************/
void kernel_init() {
  printf("hello from the kernel\r\n");

  sched_init();

  task_create(init_run, &init_stack, INIT_PRIO);

  idle_run();
}