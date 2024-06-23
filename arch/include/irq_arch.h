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
#ifndef IRQ_ARCH_H
#define IRQ_ARCH_H

#define RISCV_INTERRUPT_SUPERVISOR_SOFTWARE 1
#define RISCV_INTERRUPT_MACHINE_SOFTWARE    MIE_SIE_OFFSET
#define RISCV_INTERRUPT_SUPERVISOR_TIMER    5
#define RISCV_INTERRUPT_MACHINE_TIMER       MIE_TIE_OFFSET
#define RISCV_INTERRUPT_SUPERVISOR_EXTERNAL 9
#define RISCV_INTERRUPT_MACHINE_EXTERNAL    MIE_EIE_OFFSET

#define TIMER_MTIMECMP_OFFSET 0x4000

#define TIMER_BASE_ADDR     0x02000000
#define TIMER_MTIMECMP_ADDR TIMER_BASE_ADDR + TIMER_MTIMECMP_OFFSET

#endif