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
#include "channel.h"

void channel_create(uint64_t *channel_handler);
void channel_snd(const uint64_t *channel_handler, const uint64_t *msg,
                 uint64_t msg_len);
void channel_rcv(const uint64_t *channel_handler, const uint64_t *msg,
                 uint64_t msg_len);