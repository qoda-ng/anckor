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

#include "interrupt.h"

#include "ax_syscall.h"
#include "printf.h"
#include "test.h"
#include "timer.h"

/*******************************************************************************
 * Definitions
 ******************************************************************************/
stack_t interrupt_thread_stack;

static uint8_t test_step = 0;

/******************************************************************************
 * @brief declare the interrupt handler
 * @param None
 * @return None
 ******************************************************************************/
void interrupt_handler() {
  // STEP 2
  test_step += 1;

  // disable timer interrupt
  ax_interrupt_release(TIMER_INTERRUPT);
}

/******************************************************************************
 * @brief initalize interrupt handler and timer
 * @param None
 * @return None
 ******************************************************************************/
void interrupt_thread(void) {
  // STEP 1
  test_step += 1;
  TEST_ASSERT(test_step >= 1)

  // enable timer interrupt
  ax_interrupt_request(TIMER_INTERRUPT, interrupt_handler);
  // set the timer to fire each second
  ax_timer_set(ONE_SECOND_IN_US);

  while (test_step < 2);

  // STEP 3
  test_step += 1;
  TEST_ASSERT(test_step >= 3)
}

REGISTER_TEST("interrupt_test", interrupt_thread, interrupt_thread_stack, 5)