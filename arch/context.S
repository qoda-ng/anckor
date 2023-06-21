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
 * Switch from a previous thread context to the next thread context
 * Only callee saved registers are stored and loaded.
 *
 * a0: thread_t to store
 * a1: thread_t to load
 *
 */
.global _switch_to
_switch_to:
    mv a3, a0
    mv a4, a1 

    # save previous thread context
    sd sp, 8(a3)
    sd s0, 16(a3)
    sd s1, 24(a3)
    sd s2, 32(a3)
    sd s3, 40(a3)
    sd s4, 48(a3)
    sd s5, 56(a3)
    sd s6, 64(a3)
    sd s7, 72(a3)
    sd s8, 80(a3)
    sd s9, 88(a3)
    sd s10, 96(a3)
    sd s11, 104(a3)
    // save first argument register
    sd a0, 112(a3)

    # load next thread context
    ld sp, 8(a4)
    ld s0, 16(a4)
    ld s1, 24(a4)
    ld s2, 32(a4)
    ld s3, 40(a4)
    ld s4, 48(a4)
    ld s5, 56(a4)
    ld s6, 64(a4)
    ld s7, 72(a4)
    ld s8, 80(a4)
    ld s9, 88(a4)
    ld s10, 96(a4)
    ld s11, 104(a4)
    // we need this to load task_entry used by task_rt
    ld a0, 112(a4)
    
    ret