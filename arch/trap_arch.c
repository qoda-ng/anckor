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
void handle_exception() {
  printk("exception not handled\n");
}

/******************************************************************************
 * @brief handle exceptions
 * @param exception cause
 * @param syscall number
 * @return none
 ******************************************************************************/
void handle_syscall(uint64_t syscall_number) {
  printk("syscall nb° %d\n", syscall_number);
}

/******************************************************************************
 * @brief handle interruptions
 * @return none
 ******************************************************************************/
void handle_interrupt() {
  printk("interrupt has been detected !\n");
}