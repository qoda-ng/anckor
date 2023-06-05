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

#define uint64_t long unsigned int
#define uint32_t unsigned int
#define uint16_t unsigned short int
#define uint8_t  unsigned char

inline void reg_write_double_word(const uint64_t addr, const uint64_t data) {
  volatile uint64_t *reg_addr = (uint64_t *)addr;
  *reg_addr                   = data;
}

inline uint8_t reg_read_double_word(const uint64_t addr) {
  volatile uint64_t *reg_addr = (uint64_t *)addr;
  return (uint64_t)*reg_addr;
}

inline void reg_write_byte(const uint64_t addr, const uint64_t offset,
                           const uint64_t data) {
  uint64_t val = reg_read_double_word(addr);
  val &= 0xFFFFFFFFFFFFFF00 << (8 * offset);
  val |= (uint64_t)data << (8 * offset);
  reg_write_double_word(addr, val);
}