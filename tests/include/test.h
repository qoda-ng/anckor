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

#ifndef TEST_H
#define TEST_H

#include "common.h"
#include "task.h"

#define _test_section __attribute__((section(".data.tests")))

#define TEST_END_WORD 0x55ABBA55

/*******************************************************************************
 * macros to register test applications and run them with the ATE
 ******************************************************************************/
#define REGISTER_TEST(_entry_name, _entry, _entry_stack, _prio) \
  test_info_t test_##_entry = {                                 \
      .name  = _entry_name,                                     \
      .stack = &_entry_stack,                                   \
      .prio  = _prio,                                           \
      .entry = _entry,                                          \
  };                                                            \
  _test_section test_info_t *test_##_entry##_pt = &test_##_entry;

/*******************************************************************************
 * @brief structure to save tests parameters
 * @param None
 * @return None
 ******************************************************************************/
typedef struct {
  const char *name;
  stack_t    *stack;
  uint8_t     prio;
  void (*entry)(void);
} test_info_t;

/*******************************************************************************
 * macros to use into test applications
 ******************************************************************************/
void test_set_error(bool_t);

#define TEST_ASSERT(_expr) \
  if (!(_expr)) {          \
    test_set_error(true);  \
  }

#define TEST_END()                                    \
  uint64_t test_data = TEST_END_WORD;                 \
  uint64_t test_chan_handler;                         \
  ax_channel_get(&test_chan_handler, "test_channel"); \
  ax_channel_snd(test_chan_handler, &test_data, sizeof(test_data));

#endif