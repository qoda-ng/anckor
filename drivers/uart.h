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

#include "common.h"

#define UART_BASE_ADDR     0x10000000
#define UART_LCR_OFFSET    3
#define UART_FIFO_OFFSET   2
#define UART_RCV_IT_OFFSET 1
#define UART_RX_TX_OFFSET  0

void Uart_Init();
void Uart_Send(const uint8_t *data, const uint64_t size);