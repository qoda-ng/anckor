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

#include "ax_syscall.h"
#include "common.h"
#include "init.h"
#include "sched.h"
#include "task.h"
#include "uart.h"

/******************************************************************************
 * @brief Idle routine runned when no other tasks are ready
 * @param None
 * @return None
 ******************************************************************************/
void idle_run(void) {
  while (1) {
    ax_task_yield();
  }
}

/******************************************************************************
 * @brief initialisation of kernel structures and launch the first task
 * @param None
 * @return None
 ******************************************************************************/
void kernel_init() {
  sched_init();

  init_create();

  idle_run();
}