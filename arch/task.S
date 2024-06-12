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
 * _task_start is the first routine which is runned when a task is created.
 * It's saved on the top of the task stack
 */
.global _task_start
_task_start:
    # get task_runtime 
    ld t0, EXCEPTION_FRAME_RA(sp)
    # get task_entry address
    ld a0, EXCEPTION_FRAME_MEPC(sp)
    # move up stack pointer
    add sp, sp, EXCEPTION_FRAME_LENGTH
    # load task_runtime in mepc
    csrw mepc, t0
    # load mstatus value
    li		t1, MACHINE_PREVIOUS_MODE | MACHINE_PREVIOUS_INTERRUPT_ENABLE | MACHINE_INTERRUPT_ENABLE
    csrw	mstatus, t1
    # mret sets PC to MEPC, sets the hart mode to MPP
    # and sets MPP to USER mode
    mret