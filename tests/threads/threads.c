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
#include "test.h"

/*******************************************************************************
 * Definitions
 ******************************************************************************/
stack_t main_thread_stack;
stack_t second_thread_stack;

uint8_t test_step = 0;

/******************************************************************************
 * @brief second thread
 * @param None
 * @return None
 ******************************************************************************/
void second_thread(void) {
  // STEP 2
  test_step += 1;
  TEST_ASSERT(test_step >= 2)

  // yield the second thread and resume immediatly
  task_yield();

  // STEP 3
  test_step += 1;
  TEST_ASSERT(test_step >= 3)

  // return from the second thread
  task_wakeup((task_t *)main_thread_stack);

  // STEP 5
  test_step += 1;
  TEST_ASSERT(test_step >= 5)
}

/******************************************************************************
 * @brief main thread
 * @param None
 * @return None
 ******************************************************************************/
void threads_test_thread(void) {
  // STEP 1
  test_step += 1;
  TEST_ASSERT(test_step >= 1)

  // create the second thread
  task_create("second_thread", second_thread, &second_thread_stack, 2);

  // switch from the main thread to the second thread
  task_sleep();

  // STEP 4
  test_step += 1;
  TEST_ASSERT(test_step >= 4)
}

REGISTER_TEST("threads_test", threads_test_thread, main_thread_stack, 3)