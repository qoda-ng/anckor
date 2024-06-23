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
#include "irq_arch.h"

#include "common.h"
#include "interrupt.h"
#include "printk.h"
#include "registers.h"
#include "trap_arch.h"

/******************************************************************************
 * @brief enable the interrupt in IE register
 * @param interrupt identifier
 * @return None
 ******************************************************************************/
void interrupt_request(interrupt_id_t interrupt_id) {
  uint64_t reg_value;

  // translate kernel interrupt number to riscv arch interrupt register offset
  switch (interrupt_id) {
    case TIMER_INTERRUPT:
      reg_value = 1 << MIE_TIE_OFFSET;
      break;
    default:
      break;
  }

  // configure interrupt enable register
  csr_write(CSR_MIE, reg_value);
}

/******************************************************************************
 * @brief handle interruptions
 * @return none
 ******************************************************************************/
void handle_interrupt(uint64_t cause) {
  printk("interrupt n° %d has been detected !\n", cause);

  switch (cause) {
    case RISCV_INTERRUPT_MACHINE_SOFTWARE:
      hang_processor();
      break;
    case RISCV_INTERRUPT_MACHINE_TIMER:
      break;
    case RISCV_INTERRUPT_MACHINE_EXTERNAL:
      hang_processor();
      break;
    default:
      hang_processor();
      break;
  }
}