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
#ifndef TASK_H
#define TASK_H

#include "common.h"
#include "processor.h"

typedef uint64_t stack_t[STACK_SIZE];

/******************************************************************************
 * @struct task_t
 * @brief structure to manage common thread and processes informations
 ******************************************************************************/
typedef struct task_t {
  uint32_t vm_id;
  uint32_t thread_id;
  uint8_t  prio;
  thread_t thread;
} task_t;

/*******************************************************************************
 * Function
 ******************************************************************************/
ax_return_t task_create(uint32_t, task_t *, void (*fn)(void), stack_t *,
                        uint8_t);
ax_return_t task_destroy(task_t *);
ax_return_t task_yield(void);
ax_return_t task_sleep(void);
ax_return_t task_wake_up(void);

#endif