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
 * trap handler is called by an exception or an interrupt
 */
.section .text
# trap_handler will be stored in mtvec register and mtvec base address
# must be 4-byte aligned as defined in RISCV Privileged ISA, 3.1.7.
.align 4
.global _trap_handler
_trap_handler:
    # return address needs to be saved because handle_exception
    # will update ra register
    add	    sp,sp,-16
    sd	    ra,8(sp)
    # reset pending interrupt
    csrw    mip, 0x0
    # move syscall number to a1 register
    mv      a1, a0
    # handle_interrupt and handle_exception
    # will exit to _ret_from_trap
    la	    ra, _ret_from_trap
    # get the interrupt cause 
    # save it in the first argument register
    csrr	a0, mcause
    bgez    a0, 1f
    # tail does not affect ra register
    tail    handle_interrupt
1:
    tail    handle_exception
    
 /*
 * _ret_from_trap is called when handle_interrupt and
 * handle_exceptions returns as its address is stored
 * in ra register
 */
.local _ret_from_trap
_ret_from_trap:
    # once the exception or interrupt has been processed, 
    # get the return address from the stack
    ld	    ra,8(sp)
    add	    sp,sp,16
    # return from trap by using the mepc register
    # ecall is a 4-byte length instruction so mepc
    # register is updated with the next instruction
    csrr    t0, mepc
    addi    t0, t0, 0x04
    csrw    mepc, t0
    # copy mepc to pc register and jump
    mret