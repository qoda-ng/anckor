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

#include "timer.h"

#include "app.h"
#include "ax_syscall.h"
#include "printf.h"

#define TIMER_BASE_ADDR 0x02004000

#define ARCH_TIMER_RATE 10000000

/*******************************************************************************
 * Definitions
 ******************************************************************************/
stack_t timer_driver_stack;

/******************************************************************************
 * @brief Initialization of the uart peripheral
 * @param None
 * @return None
 ******************************************************************************/
void timer_driver() {
  // set the timer
  uint64_t timer_period_in_s = 1;
  reg_write_double_word(TIMER_BASE_ADDR, timer_period_in_s * ARCH_TIMER_RATE);

  // enable the interrupt in csr register
  ax_interrupt_request(TIMER_INTERRUPT);

  // get this task to sleep, it will be wake up by the interrupt
  ax_task_sleep();

  // when woke up, print a message
  printf("Timer task - woke up by the timer interrupt");
}

REGISTER_APP("timer_driver_task", timer_driver, timer_driver_stack,
             TIMER_TASK_PRIORITY);