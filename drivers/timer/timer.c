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
  // register this task to be wake up by timer interrupt
  ax_interrupt_request(TIMER_INTERRUPT);

  // set the timer

  // get this task to sleep, it will be wake up by the interrupt
  ax_task_sleep();

  // when woke up, print a message
  printf("Timer task - woke up by the timer interrupt");
}

REGISTER_APP("timer_driver_task", timer_driver, timer_driver_stack,
             TIMER_TASK_PRIORITY);