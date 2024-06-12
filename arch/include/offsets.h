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
#ifndef OFFSETS_H
#define OFFSETS_H

#define TASK_INIT_STACK_RA 8

#define TASK_THREAD_SP 0

#define TASK_FRAME_LENGTH 96
#define TASK_FRAME_S0     0
#define TASK_FRAME_S1     8
#define TASK_FRAME_S2     16
#define TASK_FRAME_S3     24
#define TASK_FRAME_S4     32
#define TASK_FRAME_S5     40
#define TASK_FRAME_S6     48
#define TASK_FRAME_S7     56
#define TASK_FRAME_S8     64
#define TASK_FRAME_S9     72
#define TASK_FRAME_S10    80
#define TASK_FRAME_S11    88

#define EXCEPTION_FRAME_LENGTH 144
#define EXCEPTION_FRAME_MEPC   0
#define EXCEPTION_FRAME_RA     8
#define EXCEPTION_FRAME_T0     16
#define EXCEPTION_FRAME_T1     24
#define EXCEPTION_FRAME_T2     32
#define EXCEPTION_FRAME_T3     40
#define EXCEPTION_FRAME_T4     48
#define EXCEPTION_FRAME_T5     56
#define EXCEPTION_FRAME_T6     64
#define EXCEPTION_FRAME_A0     72
#define EXCEPTION_FRAME_A1     80
#define EXCEPTION_FRAME_A2     88
#define EXCEPTION_FRAME_A3     96
#define EXCEPTION_FRAME_A4     104
#define EXCEPTION_FRAME_A5     112
#define EXCEPTION_FRAME_A6     120
#define EXCEPTION_FRAME_A7     128

#endif