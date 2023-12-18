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

 /*
 * trap handler is call by an exception or an interrupt
 */
.section .text
# trap_handler will be stored in mtvec register and mtvec base address
# must be 4-byte aligned as defined in RISCV Privileged ISA, 3.1.7.
.align 4
.global _trap_handler
_trap_handler:
    # return address needs to be saved because exception_handler
    # will update ra register
    add	sp,sp,-16
    sd	ra,8(sp)
    # get the interrupt cause 
    # save it in the first argument register
    csrr	a0, mcause
    # reset pending interrupt
    csrw    mip, 0x0
    # handle the interrupt
    call    handle_exception
    # once the exception has been managed, get the return 
    # address from the stack
    ld	ra,8(sp)
    add	sp,sp,16
    # return from trap by using the mepc register
    # ecall is a 4-byte length instruction so mepc
    # register is updated with the next instruction
    csrr    t0, mepc
    addi    t0, t0, 0x04
    csrw    mepc, t0
    # copy mepc to pc register and jump
    mret