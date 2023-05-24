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
#define uint8_t     unsigned char

#define UART_BASE_ADDR          0x10000000
#define UART_LCR_OFFSET         0x00000003
#define UART_FIFO_OFFSET        0x00000002
#define UART_RCV_IT_OFFSET      0x00000001
#define UART_RX_TX_OFFSET       0x00000000

void mmio_write_64(uint64_t addr, uint64_t data) {
    // we tell the compiler to not discard this write operation
    // by optimization
    volatile uint64_t *reg_addr = (uint64_t *)addr;
    *reg_addr = data;
}

uint8_t mmio_read_64(uint64_t addr) {
    // we tell the compiler to not discard this read operation
    // by optimization
    volatile uint64_t *reg_addr = (uint64_t *)addr;
    return (uint64_t)*reg_addr;
}

void uart_init() {
    mmio_write_64(UART_BASE_ADDR, (1 << 24) | (1 << 25) | (1 << 16) | (1 << 8));
}

void uart_send_byte(uint8_t data) {
    uint64_t val = mmio_read_64(UART_BASE_ADDR);
    val &= 0xFFFFFFFFFFFFFF00;
    val |= (uint64_t)data;
    mmio_write_64(UART_BASE_ADDR, val);
}

void uart_send(uint8_t *data) {

}

void kmain()
{
    uart_init();

    uart_send_byte('h');
    uart_send_byte('e');
    uart_send_byte('l');
    uart_send_byte('l');
    uart_send_byte('o');

    while(1);
}