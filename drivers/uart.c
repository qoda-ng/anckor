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

#include "uart.h"

void Uart_Init() {
  Register_WriteByte(UART_BASE_ADDR, UART_RCV_IT_OFFSET, (1 << 0));
  Register_WriteByte(UART_BASE_ADDR, UART_FIFO_OFFSET, (1 << 0));
  Register_WriteByte(UART_BASE_ADDR, UART_LCR_OFFSET, (1 << 0) | (1 << 1));
}

void Uart_Send(const uint8_t *data, const uint64_t size) {
  uint32_t byte_index = 0;

  while (byte_index < size) {
    Register_WriteByte(UART_BASE_ADDR, UART_RX_TX_OFFSET, data[byte_index]);

    byte_index += 1;
  }
}