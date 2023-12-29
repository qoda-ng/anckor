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

#include "registers.h"

 /*
 * trap handler is called by an exception or an interrupt
 */
.section .text
# trap_handler will be stored in mtvec register and mtvec base address
# must be 4-byte aligned as defined in RISCV Privileged ISA, 3.1.7.
.align RISCV_PTR_LENGTH
.global _trap_handler
_trap_handler:
    # return address needs to be saved because handle_unknown_exception
    # will update ra register
    add	    sp,sp,-16
    sd	    ra,8(sp)
    csrr    t0, mepc
    sd      t0, 0(sp)
    # handle_interrupt and handle_unknown_exception
    # will exit to _ret_from_trap
    la	    ra, _ret_from_trap
    # get the interrupt cause 
    # save it in the first argument register
    csrr	t0, mcause
    bgez    t0, 1f
    # tail does not affect ra register
    tail    handle_interrupt
1:
    # compute the exception vector offset
    slli    t0, t0, COMPUTE_8_BYTES_ADDRESS
    la      t1, _exception_vector_table
    la      t2, _exception_vector_table_end
    # compute the exception handler address
    add     t0, t1, t0
    # check if the exception_vector_table can 
    # handle the exception
    bgeu    t0, t2, 2f
    # jump to the dedicated handler
    ld      t0, 0(t0)
    jr      t0
2:
    # handle unknown exception
    tail    handle_unknown_exception
    
 /*
 * _ret_from_trap is called when handle_interrupt or
 * the exception handler returns as its address is stored
 * in ra register
 */
.local _ret_from_trap
_ret_from_trap:
    # once the exception or interrupt has been processed, 
    # get the return address from the stack
    ld	    ra,8(sp)
    # get the instruction address which asserts the exception
    ld      t0, 0(sp)
    add	    sp,sp,16
    # return from trap by using the mepc register
    # ecall is a 4-byte length instruction so mepc
    # register is updated with the next instruction
    addi    t0, t0, 0x04
    csrw    mepc, t0
    # the kernels returns in machine mode after mret
    # execution
    li		t1, MACHINE_PREVIOUS_MODE | MACHINE_PREVIOUS_INTERRUPT_ENABLE | MACHINE_INTERRUPT_ENABLE
    csrw	mstatus, t1
    # mret sets PC to MEPC, sets the hart mode to MPP
    # and sets MPP to USER mode
    mret

.section .rodata
# this table contains all exception handlers
# 0 padding is adding to maintain alignment between
# mcause value and handler addresses
.align RISCV_PTR_LENGTH
_exception_vector_table:
    .dword handle_unknown_exception
    .dword handle_unknown_exception
    .dword handle_unknown_exception
    .dword handle_unknown_exception
    .dword handle_unknown_exception
    .dword handle_unknown_exception
    .dword handle_unknown_exception
    .dword handle_unknown_exception
    .dword _syscall_wrapper
    .dword _syscall_wrapper
    .dword handle_unknown_exception
    .dword _syscall_wrapper
    .dword handle_unknown_exception
    .dword handle_unknown_exception
    .dword handle_unknown_exception
    .dword handle_unknown_exception
_exception_vector_table_end: