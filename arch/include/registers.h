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
#ifndef REGISTERS_H
#define REGISTERS_H

#define MACHINE_PREVIOUS_MODE    (0x3 << 11)
#define HYPERVISOR_PREVIOUS_MODE (0x2 << 11)
#define SUPERVISOR_PREVIOUS_MODE (0x1 << 11)
#define USER_PREVIOUS_MODE       (0x0 << 11)

#define MACHINE_PREVIOUS_INTERRUPT_ENABLE  (0x1 << 7)
#define MACHINE_PREVIOUS_INTERRUPT_DISABLE (0x0 << 7)

#define MACHINE_INTERRUPT_ENABLE  (0x1 << 3)
#define MACHINE_INTERRUPT_DISABLE (0x0 << 3)

#define MACHINE_SOFTWARE_INTERRUPT_ENABLE  (0x1 << 3)
#define MACHINE_SOFTWARE_INTERRUPT_DISABLE (0x0 << 3)

#define MACHINE_TIMER_INTERRUPT_ENABLE  (0x1 << 7)
#define MACHINE_TIMER_INTERRUPT_DISABLE (0x0 << 7)

#define MACHINE_EXTERNAL_INTERRUPT_ENABLE  (0x1 << 11)
#define MACHINE_EXTERNAL_INTERRUPT_DISABLE (0x0 << 11)

#define RISCV_PTR_LENGTH        4
#define COMPUTE_8_BYTES_ADDRESS 3

#endif