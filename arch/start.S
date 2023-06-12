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

.option norvc

.section .text.init
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
    la		sp, __idle_task_end
	# set MPP = 0b11, MPIE = 0b1, MIE = 0b1
	# hart will switch to MACHINE mode after the next 
	# exception handling
    li		t0, (0b11 << 11) | (1 << 7) | (1 << 3)
    csrw	mstatus, t0
	# set the trap vector register with our trap handler
    la		t1, asm_trap_vector
    csrw	mtvec, t1
	# enable software level interrupt and external
	# interrupts for machine mode
    li		t3, (1 << 3) | (1 << 11)
    csrw	mie, t3
	# initialize hardware and platform related stuff
	jal 	platform_init 
	# jump to the kernel init procedure, this should
	# never return
    jal     kernel_init
3:
	# hang if we return from the kernel
	wfi
	j	3b

_secondary_hart_init:
	# hart !#0 hang here
	wfi
	j	_secondary_hart_init