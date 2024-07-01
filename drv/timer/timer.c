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
#include "irq_arch.h"
#include "printf.h"
#include "sched.h"
#include "task.h"

#define ARCH_TIMER_RATE 10000000

/*******************************************************************************
 * Definitions
 ******************************************************************************/
stack_t timer_driver_stack;
task_t* task_handler;

/******************************************************************************
 * @brief Initialization of the uart peripheral
 * @param None
 * @return None
 ******************************************************************************/
void timer_driver_handler() {
  while (1) {
    // get this task to sleep, it will be wake up by the interrupt
    ax_task_sleep();

    ax_task_wakeup(task_handler);
  }
}

/******************************************************************************
 * @brief set a timer
 * @param time duration before the timer will fire
 * @return None
 ******************************************************************************/
void timer_set(time_t time_in_us) {
  // register the task to wake up with the timer
  task_handler = sched_get_current_task();

  // set the timer
  uint64_t timer_period_in_s = 1;
  reg_write_double_word(TIMER_MTIMECMP_ADDR, time_in_us * ARCH_TIMER_RATE);

  // enable the interrupt in csr register
  ax_interrupt_request(TIMER_INTERRUPT);
}

/******************************************************************************
 * @brief read the monotonic clock from the processor
 * @param None
 * @return monotonic clock in us
 ******************************************************************************/
time_t clock_get() {
  uint64_t clock_in_s =
      reg_read_double_word(TIMER_MTIME_ADDR) / ARCH_TIMER_RATE;
  return clock_in_s * ONE_SECOND_IN_US;
}

REGISTER_APP("timer_driver_task", timer_driver_handler, timer_driver_stack,
             TIMER_TASK_PRIORITY);