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

.section .text
# mtvec base address must be 4-byte aligned as defined in RISCV Privileged ISA, 3.1.7.
.align 4
.global _trap_handler
_trap_handler:
    # get the interrupt cause 
    # save it in the first argument register
    csrr	a0, mcause
    # reset pending interrupt
    csrw    mip, 0x0
    # handle the interrupt
    call    _handle_exception
    # increment mepc
    # csrr a0, mepc
    # addi a0, a0, 0x04
    # csrw mepc, a0