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

#include "ax_syscall.h"
#include "interrupt.h"
#include "irq_arch.h"
#include "printk.h"
#include "test.h"

/*******************************************************************************
 * Definitions
 ******************************************************************************/
stack_t snd_messages_thread_stack;
stack_t rcv_messages_thread_stack;

uint64_t channel_handler = NULL;
uint64_t data_to_send    = NULL;
uint64_t data_to_receive = NULL;

static uint8_t test_step = 0;

/******************************************************************************
 * @brief initalize message and send it
 * @param None
 * @return None
 ******************************************************************************/
void snd_messages_thread(void) {
  // STEP 1
  test_step += 1;
  TEST_ASSERT(test_step >= 1)

  // create a communication channel
  ax_channel_create(&channel_handler);

  // STEP 2
  TEST_ASSERT(test_step >= 2)

  // send the message
  data_to_send = 0x5A5A;
  ax_channel_snd(&channel_handler, &data_to_send, sizeof(data_to_send));

  // STEP 5
  TEST_ASSERT(test_step >= 5)
}

REGISTER_TEST("snd_messages_test", snd_messages_thread,
              snd_messages_thread_stack, 5)

/******************************************************************************
 * @brief receive message
 * @param None
 * @return None
 ******************************************************************************/
void rcv_messages_thread(void) {
  // STEP 3
  TEST_ASSERT(test_step >= 3)

  // receive the message
  ax_channel_rcv(&channel_handler, &data_to_receive, sizeof(data_to_receive));

  // STEP 4
  TEST_ASSERT(test_step >= 4)
}

REGISTER_TEST("rcv_messages_test", rcv_messages_thread,
              rcv_messages_thread_stack, 4)