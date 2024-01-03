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
    # save previous thread context
    sd sp, TASK_THREAD_SP(a0)
    sd s0, TASK_THREAD_S0(a0)
    sd s1, TASK_THREAD_S1(a0)
    sd s2, TASK_THREAD_S2(a0)
    sd s3, TASK_THREAD_S3(a0)
    sd s4, TASK_THREAD_S4(a0)
    sd s5, TASK_THREAD_S5(a0)
    sd s6, TASK_THREAD_S6(a0)
    sd s7, TASK_THREAD_S7(a0)
    sd s8, TASK_THREAD_S8(a0)
    sd s9, TASK_THREAD_S9(a0)
    sd s10, TASK_THREAD_S10(a0)
    sd s11, TASK_THREAD_S11(a0)

    # load next thread context
    ld sp, TASK_THREAD_SP(a1)
    ld s0, TASK_THREAD_S0(a1)
    ld s1, TASK_THREAD_S1(a1)
    ld s2, TASK_THREAD_S2(a1)
    ld s3, TASK_THREAD_S3(a1)
    ld s4, TASK_THREAD_S4(a1)
    ld s5, TASK_THREAD_S5(a1)
    ld s6, TASK_THREAD_S6(a1)
    ld s7, TASK_THREAD_S7(a1)
    ld s8, TASK_THREAD_S8(a1)
    ld s9, TASK_THREAD_S9(a1)
    ld s10, TASK_THREAD_S10(a1)
    ld s11, TASK_THREAD_S11(a1)
    
    ret