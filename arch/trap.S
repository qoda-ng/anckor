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
 * trap handler is called by an exception or an interrupt
 */
.section .text
# trap_handler will be stored in mtvec register and mtvec base address
# must be 4-byte aligned as defined in RISCV Privileged ISA, 3.1.7.
.align RISCV_PTR_LENGTH
.global _trap_handler
_trap_handler:
    # move up stack pointer to save caller-saved stack frame
    add	    sp, sp, -CALLER_STACK_FRAME_LENGTH

    # save mepc as the kernel can switch context and return by an 
    # another function from which it enters in _trap_handler 
    csrr    t0, mepc
    sd      t0, KERNEL_STACK_FRAME_MEPC(sp)

    # return address needs to be saved because ra register will 
    # be overwritten with _ret_from_trap address
    sd	    ra, CALLER_STACK_FRAME_RA(sp)

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
.local _ret_from_trap
_ret_from_trap:
    # once the exception or interrupt has been processed, 
    # get the return address from the stack
    ld	    ra, CALLER_STACK_FRAME_RA(sp)
    # get the instruction address which asserts the exception
    # to resume execution
    ld      t0, KERNEL_STACK_FRAME_MEPC(sp)
    csrw    mepc, t0
    # move up stack pointer
    add	    sp, sp, CALLER_STACK_FRAME_LENGTH
    # the kernels returns in machine mode after mret
    # execution
    li		t1, MACHINE_PREVIOUS_MODE | MACHINE_PREVIOUS_INTERRUPT_ENABLE | MACHINE_INTERRUPT_ENABLE
    csrw	mstatus, t1
    # mret sets PC to MEPC, sets the hart mode to MPP
    # and sets MPP to USER mode
    mret

 /*
 * _task_start is the first routine which is runned when a task is created.
 * It's saved on the top of the task stack
 */
.global _task_start
_task_start:
    # get task_entry address
    # and load it in the first argument register
    ld a0, CALLER_STACK_FRAME_RA(sp)
    # load 0x0 to the stack CALLER_STACK_FRAME_RA
    # as _ret_from_trap will copy it and we do not
    # want user mode to be able to read it.
    li t0, 0x0
    sd t0, CALLER_STACK_FRAME_RA(sp)
    # exit kernel mode 
    j _ret_from_trap

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



# #define DO_CALLER_SAVED(op) 
#     # save mepc as the kernel can switch context and return by an 
#     # another function from which it enters in _trap_handler 
#     op t0, KERNEL_STACK_FRAME_MEPC(sp)
#         # return address needs to be saved because ra register will 
#     # be overwritten with _ret_from_trap address