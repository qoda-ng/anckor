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

#include "common.h"
#include "interrupt.h"

#define csr_write(val)                        \
  ({                                          \
    unsigned long __v = (unsigned long)(val); \
    __asm__ volatile(                         \
        "csrw mie"                            \
        ", %0"                                \
        :                                     \
        : "rK"(__v)                           \
        : "memory");                          \
  })

/******************************************************************************
 * @brief enable the interrupt in IE register
 * @param interrupt identifier
 * @return None
 ******************************************************************************/
void interrupt_request(interrupt_id_t interrupt_id) {
  csr_write(0x0000000000000080);
}
