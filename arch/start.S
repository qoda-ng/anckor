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

.option norvc

# place this routine at the top of the binary file, this is the
# program entry point
.section .text.init
# use .global keyworkd makes the symbol visible to the linker
.global _start
_start:
	# check hart id and hang if it's not 0
	csrr	t0, mhartid
	bnez	t0, _secondary_hart_init

_primary_hart_init:
	# hart #0 goes here, continue init sequence
	# SATP should be zero, but let's make sure
	csrw	satp, zero
.option push
.option norelax
	la		gp, _global_pointer
.option pop

	# initialize bss section to zero
	la 		a0, _bss_start
	la		a1, _bss_end
	bgeu	a0, a1, 2f
1:
	sd		zero, (a0)
	addi	a0, a0, 8
	bltu	a0, a1, 1b
2:
	# from here the kernel runs in the idle task context
    la		sp, _idle_stack_end
	# set MPP = MACHINE_MODE, MPIE = ENABLE, MIE = ENABLE
	# enable machine level interrupts
    li		t0, MACHINE_PREVIOUS_MODE | MACHINE_PREVIOUS_INTERRUPT_ENABLE | MACHINE_INTERRUPT_ENABLE
    csrw	mstatus, t0
	# set the trap vector register with our trap handler
    la		t0, _trap_handler
    csrw	mtvec, t0
	# enable software level interrupt and external
	# interrupts for machine mode
    li		t0, MACHINE_EXTERNAL_INTERRUPT_ENABLE | MACHINE_SOFTWARE_INTERRUPT_ENABLE
    csrw	mie, t0
	# initialize hardware and platform related stuff
	call 	platform_init 
	# jump to the kernel init procedure, this should
	# never return
    call     kernel_init
3:
	# hang if we return from the kernel
	wfi
	j	3b

_secondary_hart_init:
	# hart !#0 hang here
	wfi
	j	_secondary_hart_init