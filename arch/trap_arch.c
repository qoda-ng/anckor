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
#include "printk.h"

/******************************************************************************
 * @brief handle exceptions
 * @param exception cause
 * @param syscall number
 * @return none
 ******************************************************************************/
void handle_exception(uint64_t exception_cause, uint64_t syscall_number) {
  switch (exception_cause) {
    case 8:
    case 9:
    case 11:
      printk("syscall nb° %d\n", syscall_number);
      break;
    default:
      printk("exception not handled\n");
      break;
  }
}

/******************************************************************************
 * @brief handle interruptions
 * @param exception cause
 * @param syscall number
 * @return none
 ******************************************************************************/
void handle_interrupt() {
  printk("interrupt has been detected !\n");
}