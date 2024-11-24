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
#include "printf.h"
#include "test.h"

#define MAGIC_WORD 0x5DA9CAB3

/*******************************************************************************
 * Definitions
 ******************************************************************************/
stack_t snd_messages_thread_stack;
stack_t rcv_messages_thread_stack;
stack_t messages_thread_stack;

/******************************************************************************
 * @brief initalize message and send it
 * @param None
 * @return None
 ******************************************************************************/
void snd_messages_thread(void) {
  uint64_t data_to_send = 0;
  uint64_t snd_chan_handler;
  // send the message
  data_to_send = MAGIC_WORD;

  // looking for the channel
  if (ax_channel_get(&snd_chan_handler, "data_channel") < 0) {
    // we didn't find the channel
    TEST_ASSERT(false);
  } else {
    // send data through the channel
    ax_channel_snd(snd_chan_handler, &data_to_send, sizeof(data_to_send));
  }
}

/******************************************************************************
 * @brief receive message
 * @param None
 * @return None
 ******************************************************************************/
void rcv_messages_thread(void) {
  uint64_t data_to_receive = 0;
  uint64_t rcv_chan_handler;

  // create a communication channel
  ax_channel_create(&rcv_chan_handler, "data_channel");

  // receive the message
  ax_channel_rcv(rcv_chan_handler, &data_to_receive, sizeof(data_to_receive));

  if (data_to_receive != MAGIC_WORD)
    printf("TEST KO : %x\r\n", data_to_receive);
  else
    printf("TEST OK\r\n");
}

/******************************************************************************
 * @brief create the channel and the send / rcv threads
 * @param None
 * @return None
 ******************************************************************************/
void messages_thread(void) {
  // create the send thread
  ax_task_create("snd_messages_test", snd_messages_thread,
                 &snd_messages_thread_stack, 4);

  // create the rcv thread
  ax_task_create("rcv_messages_test", rcv_messages_thread,
                 &rcv_messages_thread_stack, 5);

  ax_task_yield();

  // end of test, return to ATE engine
}

REGISTER_TEST("messages_thread", messages_thread, messages_thread_stack, 3)