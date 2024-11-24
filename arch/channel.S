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
#include "offsets.h"

 /*
 * channel_snd routine
 *
 * a0: channel input
 * a1: channel output
 * a2: msg address
 *
 */
.global _channel_snd
_channel_snd:
    # save ra on stack
    add	    sp, sp, -16
    sd      ra, 8(sp)

    # load the data in a2 register
    mv      t0, a2
    ld      a2, 0(t0)
    
    # switch from snd to rcv task
    call sched_switch

    # restore ra from stack
    ld	    ra, 8(sp)
    add	    sp, sp, 16
    ret

 /*
 * channel_rcv routine
 *
 * a0: msg address
 *
 */
.global _channel_rcv
_channel_rcv:
    # save ra as we call a subroutine
    add	    sp, sp, -16
    sd      ra, 8(sp)
    # save data address on stack
    sd      a0, 0(sp)

    # release the cpu
    call sched_run

    # load data address from stack
    ld      t0, 0(sp)
    # save transmitted data in receiver address space
    sd      a2, 0(t0)

    # restore ra
    ld	    ra, 8(sp)
    add	    sp, sp, 16
    ret