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
 * Syscall wrapper is used to call the syscall saved in the syscall table.
 * This routine is written in assembly left a[0-7] registers unchanged. This
 * avoid to pass arguments on the stack as all syscalls don't have the same 
 * prototype. 
 *
 * a0 contains the syscall number
 *
 */
 .global _syscall_wrapper
_syscall_wrapper:
    # compute the offset address in the syscall table
    mv      t0, a0
    slli    t0, t0, COMPUTE_8_BYTES_ADDRESS
    la      t1, _syscall_table
    la      t2, _syscall_table_end
    add     t0, t1, t0
    bgeu    t0, t2, 1f
    # load the syscall handler adress from the syscall table
    ld      t0, 0(t0)
    # jump to the syscall
    jr      t0
1:
    tail sys_default

 /*
 * Syscall is a routine which calls supervisor environment and passes
 * gives it the syscall number to serve
 *
 * a0: syscall number
 *
 */

# use .global keyworkd makes the symbol visible to the linker
.global _syscall
_syscall:
    # rise exception, this will update mepc register but left
    # the ra register unchanged
    ecall
    ret

.section .rodata
.align RISCV_PTR_LENGTH
_syscall_table:
    .dword sys_default
    .dword sys_default
    .dword sys_default
    .dword sys_default
    .dword sys_default
    .dword sys_default
    .dword sys_default
    .dword sys_default
    .dword sys_default
    .dword sys_default
    .dword sys_default
    .dword sys_default
    .dword sys_default
    .dword sys_default
    .dword sys_default
    .dword sys_default
    .dword sys_default
    .dword sys_default
    .dword sys_default
    .dword sys_default
    .dword sys_default
    .dword sys_default
    .dword sys_default
    .dword sys_default
    .dword sys_default
    .dword sys_default
    .dword sys_default
    .dword sys_default
    .dword sys_default
    .dword sys_default
    .dword sys_default
    .dword sys_default
_syscall_table_end: