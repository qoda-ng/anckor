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

#define uint64_t    long unsigned int
#define uint32_t    unsigned int
#define uint16_t    unsigned short int
#define uint8_t     unsigned char

#define UART_BASE_ADDR          0x10000000
#define UART_LCR_OFFSET         3
#define UART_FIFO_OFFSET        2
#define UART_RCV_IT_OFFSET      1
#define UART_RX_TX_OFFSET       0

inline void write64(const uint64_t addr, const uint64_t data) {
    volatile uint64_t *reg_addr = (uint64_t *)addr;
    *reg_addr = data;
}

inline uint8_t read64(const uint64_t addr) {
    volatile uint64_t *reg_addr = (uint64_t *)addr;
    return (uint64_t)*reg_addr;
}

inline void write8(const uint64_t addr, const uint64_t offset, const uint64_t data) {
    uint64_t val = read64(UART_BASE_ADDR);
    val &= 0xFFFFFFFFFFFFFF00 << (8 * offset);
    val |= (uint64_t)data << (8 * offset);
    write64(UART_BASE_ADDR, val);
}

void uart_init() {
    write8(UART_BASE_ADDR, UART_RCV_IT_OFFSET, (1 << 0));
    write8(UART_BASE_ADDR, UART_FIFO_OFFSET, (1 << 0));
    write8(UART_BASE_ADDR, UART_LCR_OFFSET, (1 << 0) | (1 << 1));
}

void uart_send(const uint8_t *data, const uint64_t size) {
    uint32_t byte_index = 0;

    while(byte_index < size) {
        write8(UART_BASE_ADDR, UART_RX_TX_OFFSET, data[byte_index]);

        byte_index += 1;
    }
}

void platform_init() {
    uart_init();
}

void kernel_init() {

    unsigned char kernel_msg[] = "hello";

    uart_send(kernel_msg, 6);

    while(1);
}