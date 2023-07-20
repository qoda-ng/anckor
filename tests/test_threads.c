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

#include "app.h"
#include "printf.h"
#include "task.h"

void main_thread(void) {
  printf("[Test] threads\r\n");
  printf("[Test] start\r\n");

  task_sleep();

  printf("resume main thread\r\n");
  printf("main thread finished, destroy it\r\n");
}

REGISTER_APP(main_thread, 3)

void second_thread(void) {
  printf("second thread\r\n");

  task_yield();

  printf("immediatly resume second thread\r\n");
  printf("wakeup main thread\r\n");

  task_wakeup((task_t *)stack_main_thread);

  printf("second thread is resumed\r\n");

  printf("[test] end\r\n");

  while (1)
    ;
}

REGISTER_APP(second_thread, 2)