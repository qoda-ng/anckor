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
  const char thread_msg[] = "hello from the idle task\r\n";

  uart_send((const uint8_t *)&thread_msg[0], 27);

  task_yield();

  uart_send((const uint8_t *)"return in idle task\r\n", 22);

  while (1) {
  }
}

/******************************************************************************
 * @brief Init task will launch all registered tasks in the system
 * @param None
 * @return None
 ******************************************************************************/
void init_run(void) {
  const char thread_msg[] = "hello from the init task\r\n";

  uart_send((const uint8_t *)&thread_msg[0], 27);

  // while (1)
  //   ;
}

/******************************************************************************
 * @brief initialisation of kernel structures and launch the first task
 * @param None
 * @return None
 ******************************************************************************/
void kernel_init() {
  const char kernel_msg[] = "hello from the kernel\r\n";

  uart_send((const uint8_t *)&kernel_msg[0], 24);

  sched_init();

  task_create(init_run, &init_stack, INIT_PRIO);

  idle_run();
}