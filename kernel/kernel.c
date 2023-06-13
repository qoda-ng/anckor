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

#define IDLE_PRIO 0
#define INIT_PRIO 1

void idle_run(void) {
  const char thread_msg[] = "hello from the idle task\r\n";

  uart_send((const uint8_t *)&thread_msg[0], 27);

  while (1)
    ;
}

extern stack_t idle_stack;
task_t         idle_task = {
            .vms_id       = 0,
            .thread_id    = 0,
            .thread.ra    = (uint64_t)idle_run,
            .thread.sp    = (uint64_t)idle_stack + STACK_SIZE - 1,
            .thread.s[0]  = 0,
            .thread.s[1]  = 0,
            .thread.s[2]  = 0,
            .thread.s[3]  = 0,
            .thread.s[4]  = 0,
            .thread.s[5]  = 0,
            .thread.s[6]  = 0,
            .thread.s[7]  = 0,
            .thread.s[8]  = 0,
            .thread.s[9]  = 0,
            .thread.s[10] = 0,
            .thread.s[11] = 0,
};

void init_run(void) {
  const char thread_msg[] = "hello from the init task\r\n";

  uart_send((const uint8_t *)&thread_msg[0], 27);

  while (1)
    ;
}

stack_t init_stack;
task_t  init_task;

/******************************************************************************
 * @brief initialisation of kernel structures and launch the first task
 * @param None
 * @return None
 ******************************************************************************/
void kernel_init() {
  const char kernel_msg[] = "hello from the kernel\r\n";

  uart_send((const uint8_t *)&kernel_msg[0], 24);

  sched_add_task(&idle_task);

  task_create(0, &init_task, init_run, &init_stack, INIT_PRIO);

  sched_run();

  while (1)
    ;
}