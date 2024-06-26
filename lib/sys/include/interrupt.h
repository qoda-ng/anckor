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
#ifndef INTERRUPT_H
#define INTERRUPT_H

/******************************************************************************
 * @brief enumerator with all interrupt IDs
 * @param None
 * @return None
 ******************************************************************************/
typedef enum interrupt_id {
  SOFTWARE_INTERRUPT = 0,
  TIMER_INTERRUPT    = 1,
  EXTERNAL_INTERRUPT = 2,
} interrupt_id_t;

#endif