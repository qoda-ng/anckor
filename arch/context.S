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
#include "offsets.h"

# use .global keyworkd makes the symbol visible to the linker
.global _switch_to
_switch_to:
    mv a3, a0
    mv a4, a1 

    # save previous thread context
    sd sp, TASK_THREAD_SP(a3)
    sd s0, TASK_THREAD_S0(a3)
    sd s1, TASK_THREAD_S1(a3)
    sd s2, TASK_THREAD_S2(a3)
    sd s3, TASK_THREAD_S3(a3)
    sd s4, TASK_THREAD_S4(a3)
    sd s5, TASK_THREAD_S5(a3)
    sd s6, TASK_THREAD_S6(a3)
    sd s7, TASK_THREAD_S7(a3)
    sd s8, TASK_THREAD_S8(a3)
    sd s9, TASK_THREAD_S9(a3)
    sd s10, TASK_THREAD_S10(a3)
    sd s11, TASK_THREAD_S11(a3)
    // save first argument register
    sd a0, TASK_THREAD_A0(a3)

    # load next thread context
    ld sp, TASK_THREAD_SP(a4)
    ld s0, TASK_THREAD_S0(a4)
    ld s1, TASK_THREAD_S1(a4)
    ld s2, TASK_THREAD_S2(a4)
    ld s3, TASK_THREAD_S3(a4)
    ld s4, TASK_THREAD_S4(a4)
    ld s5, TASK_THREAD_S5(a4)
    ld s6, TASK_THREAD_S6(a4)
    ld s7, TASK_THREAD_S7(a4)
    ld s8, TASK_THREAD_S8(a4)
    ld s9, TASK_THREAD_S9(a4)
    ld s10, TASK_THREAD_S10(a4)
    ld s11, TASK_THREAD_S11(a4)
    // we need this to load task_entry used by task_rt
    ld a0, TASK_THREAD_A0(a4)
    
    ret