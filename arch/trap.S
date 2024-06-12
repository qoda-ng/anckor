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
#include "offsets.h"

 /*
 * macro to save all callee-saved registers
 * we need this as the trap can be asynchronous
 */
.macro SAVE_CALLER_REGS
    sd	    ra, CALLER_STACK_FRAME_RA(sp)
    sd      t0, CALLER_STACK_FRAME_T0(sp)
    sd      t1, CALLER_STACK_FRAME_T1(sp)
    sd      t2, CALLER_STACK_FRAME_T2(sp)
    sd      t3, CALLER_STACK_FRAME_T3(sp)
    sd      t4, CALLER_STACK_FRAME_T4(sp)
    sd      t5, CALLER_STACK_FRAME_T5(sp)
    sd      t6, CALLER_STACK_FRAME_T6(sp)
    sd      a0, CALLER_STACK_FRAME_A0(sp)
    sd      a1, CALLER_STACK_FRAME_A1(sp)
    sd      a2, CALLER_STACK_FRAME_A2(sp)
    sd      a3, CALLER_STACK_FRAME_A3(sp)
    sd      a4, CALLER_STACK_FRAME_A4(sp)
    sd      a5, CALLER_STACK_FRAME_A5(sp)
    sd      a6, CALLER_STACK_FRAME_A6(sp)
    sd      a7, CALLER_STACK_FRAME_A7(sp)
.endm

 /*
 * macro to restore all callee-saved registers
 */
.macro RESTORE_CALLER_REGS
    ld	    ra, CALLER_STACK_FRAME_RA(sp)
    ld      t0, CALLER_STACK_FRAME_T0(sp)
    ld      t1, CALLER_STACK_FRAME_T1(sp)
    ld      t2, CALLER_STACK_FRAME_T2(sp)
    ld      t3, CALLER_STACK_FRAME_T3(sp)
    ld      t4, CALLER_STACK_FRAME_T4(sp)
    ld      t5, CALLER_STACK_FRAME_T5(sp)
    ld      t6, CALLER_STACK_FRAME_T6(sp)
    ld      a0, CALLER_STACK_FRAME_A0(sp)
    ld      a1, CALLER_STACK_FRAME_A1(sp)
    ld      a2, CALLER_STACK_FRAME_A2(sp)
    ld      a3, CALLER_STACK_FRAME_A3(sp)
    ld      a4, CALLER_STACK_FRAME_A4(sp)
    ld      a5, CALLER_STACK_FRAME_A5(sp)
    ld      a6, CALLER_STACK_FRAME_A6(sp)
    ld      a7, CALLER_STACK_FRAME_A7(sp)
.endm

 /*
 * trap handler is called by an exception or an interrupt
 */
.section .text
# trap_handler will be stored in mtvec register and mtvec base address
# must be 4-byte aligned as defined in RISCV Privileged ISA, 3.1.7.
.align RISCV_PTR_LENGTH
.global _trap_handler
_trap_handler:
    # store caller-saved registers as this trap can be triggered
    # by an interrupt, not an exception
    add	    sp, sp, -CALLER_STACK_FRAME_LENGTH
    SAVE_CALLER_REGS
    # save mepc as the kernel can switch context and return by an 
    # another function from which it enters in _trap_handler 
    add	    sp, sp, -KERNEL_STACK_FRAME_LENGTH
    csrr    t0, mepc
    sd      t0, KERNEL_STACK_FRAME_MEPC(sp)
    # handle_interrupt and exceptions handlers
    # will exit to _ret_from_trap
    la	    ra, _ret_from_trap
    # get the exception cause and dispatch
    # from interrupt or synchronous exception
    csrr	t0, mcause
    bgez    t0, 1f
    # tail does not affect ra register
    tail    handle_interrupt
1:
    # compute the exception vector offset
    slli    t0, t0, SHIFT_8_BYTES_ADDRESS
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
.global _ret_from_trap
_ret_from_trap:
    # get the instruction address which asserts the exception
    # to resume execution
    ld      t0, KERNEL_STACK_FRAME_MEPC(sp)
    csrw    mepc, t0
    add	    sp, sp, KERNEL_STACK_FRAME_LENGTH
    # restore caller-saved register
    RESTORE_CALLER_REGS
    add	    sp, sp, CALLER_STACK_FRAME_LENGTH
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