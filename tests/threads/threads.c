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

stack_t main_thread_stack;
stack_t second_thread_stack;

void second_thread(void) {
  printf("second thread\r\n");

  task_yield();

  printf("immediatly resume second thread\r\n");
  printf("wakeup main thread\r\n");

  task_wakeup((task_t *)main_thread_stack);

  printf("second thread is resumed\r\n");

  printf("[test] end\r\n");

  while (1)
    ;
}

void threads_test_thread(void) {
  printf("[Test] threads\r\n");
  printf("[Test] start\r\n");

  // create the second thread
  task_create("second_thread", second_thread, &second_thread_stack, 2);

  // switch from the main thread to the second thread
  task_sleep();

  printf("resume main thread\r\n");
  printf("main thread finished, destroy it\r\n");
}

REGISTER_APP("threads_test", threads_test_thread, main_thread_stack, 3)