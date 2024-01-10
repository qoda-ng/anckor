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

#include "include/test.h"

#include "app.h"
#include "ax_syscall.h"
#include "printf.h"

/*******************************************************************************
 * Definitions
 ******************************************************************************/
stack_t       test_engine_stack;
static bool_t test_error   = false;
uint64_t      tests_passed = 0;
uint64_t      tests_failed = 0;

extern uint64_t _tests_start;
extern uint64_t _tests_end;

/******************************************************************************
 * @brief test scheduling routine
 * @param None
 * @return None
 ******************************************************************************/
void test_engine(void) {
  printf("ATE - Anckor test engine\r\n");

  // iterate over all tests descriptors saved in the section(.data.tests)
  for (uint64_t *test_pt = &_tests_start; test_pt < &_tests_end; test_pt += 1) {
    // get the test descriptor from the current pointer
    test_info_t *test = (test_info_t *)*test_pt;
    // create a task for the test
    ax_task_create(test->name, test->entry, test->stack, test->prio);

    // jump into the freshly created thread
    ax_task_yield();
    // when the test returns, display its result
    if (test_error) {
      tests_failed += 1;
      printf("ATE - %s - failed\r\n", test->name);
    } else {
      tests_passed += 1;
      printf("ATE - %s - passed\r\n", test->name);
    }
    // create a thread for the next test and go on
  }

  // all registered tests have been runned
  if (test_error) {
    printf("ATE - FAILED - %d passed - %d failed\r\n", tests_passed,
           tests_failed);
  } else {
    printf("ATE - PASSED - %d passed - %d failed\r\n", tests_passed,
           tests_failed);
  }
}

/******************************************************************************
 * @brief set test_error
 * @param bool_t test error state
 * @return None
 ******************************************************************************/
void test_set_error(bool_t error_state) {
  test_error = error_state;
}

// define max priority for the test engine thread
REGISTER_APP("test_engine", test_engine, test_engine_stack, 2);