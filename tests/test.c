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
#include "printf.h"

/*******************************************************************************
 * Definitions
 ******************************************************************************/
stack_t       test_engine_stack;
static bool_t test_error = false;

/******************************************************************************
 * @brief test scheduling routine
 * @param None
 * @return None
 ******************************************************************************/
void test_engine(void) {
  printf("ATE - Anckor tests engine\r\n");

  task_yield();

  if (test_error) {
    printf("ATE results - FAILED\r\n");
  } else {
    printf("ATE results - PASSED\r\n");
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

REGISTER_APP("test_engine", test_engine, test_engine_stack, 0);