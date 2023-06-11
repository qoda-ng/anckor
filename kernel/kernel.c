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
#include "task.h"
#include "uart.h"

void thread_func(void) {
  const char thread_msg[] = "hello from the thread\r\n";

  uart_send((const uint8_t *)&thread_msg[0], 24);

  while (1)
    ;
}

/******************************************************************************
 * @brief initialisation of kernel structures and launch the first task
 * @param None
 * @return None
 ******************************************************************************/
void kernel_init() {
  const char kernel_msg[] = "hello from the kernel\r\n";

  task_t  idle_task;
  stack_t idle_stack;

  uart_send((const uint8_t *)&kernel_msg[0], 24);

  task_create(&idle_task, thread_func, &idle_stack);

  sched_run(&idle_task);

  while (1)
    ;
}