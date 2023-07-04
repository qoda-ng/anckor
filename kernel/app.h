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

#ifndef APP_H
#define APP_H

#include "task.h"

#define _app_section __attribute__((section(".data.apps")))

#define REGISTER_APP(_name, _prio, _entry) \
  app_info_t app_##_name = {               \
      .name  = #_name,                     \
      .prio  = _prio,                      \
      .entry = _entry,                     \
  };                                       \
  _app_section app_info_t *app_##_name##_pt = &app_##_name;

/**
 * @brief structure to save apps parameters
 * @param None
 * @return None
 */
typedef struct {
  const char *name;
  uint8_t     prio;
  void (*entry)(void);
} app_info_t;

#endif