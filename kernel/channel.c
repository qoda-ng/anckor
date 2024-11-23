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

#include "printk.h"
#include "sched.h"
#include "stddef.h"
#include "task.h"

#define MAX_NB_CHANNEL 10

typedef struct channel_t {
  bool_t  available;
  task_t *in;
  task_t *out;
} channel_t;

channel_t channel[MAX_NB_CHANNEL];

/******************************************************************************
 * channel snd / rcv procedures
 ******************************************************************************/
extern void _channel_snd(task_t *, task_t *, const uint64_t *);
extern void _channel_rcv(const uint64_t *);

/******************************************************************************
 * @brief get the channel struct from the channel handler
 * @param channel handler
 * @return none
 ******************************************************************************/
static inline channel_t channel_get_from_handler(
    const uint64_t channel_handler) {
  return channel[channel_handler];
}

/******************************************************************************
 * @brief create a communication channel between two tasks
 * @param channel handler
 * @return none
 ******************************************************************************/
void channel_create(uint64_t *channel_handler) {
  channel[0].in  = NULL;
  channel[0].out = NULL;

  *channel_handler = 0;
};

/******************************************************************************
 * @brief send a message through a communication channel
 * @param channel handler
 * @param msg pointer
 * @param length of message to send
 * @return none
 ******************************************************************************/
void channel_snd(const uint64_t channel_handler, const uint64_t *msg,
                 uint64_t msg_len) {
  // find channel from handler ID
  channel_t channel = channel_get_from_handler(channel_handler);

  // register the sender task
  channel.in = sched_get_current_task();

  // block until a rcv task is waiting
  // we may be awaken up by another task
  while (!channel.out) {
    // there is no waiting task, go to BLOCKED state and
    // release the cpu
    task_set_state(channel.in, BLOCKED);
    // remove it from the run queue
    sched_remove_task(channel.in);

    sched_run();
  }

  // if the sender was blocked, add in to the run queue
  if (task_get_state(channel.in) == BLOCKED) sched_add_task(channel.in);

  // snd task goes from RUNNING / BLOCKED state to READY state
  task_set_state(channel.in, READY);

  // there is a waiting task so switch to it
  sched_add_task(channel.out);
  task_set_state(channel.out, RUNNING);
  sched_set_current_task(channel.out);

  // eventualy do the switch
  // !!! CAUTION !!! this implementation is an early alpha version
  // channel messages can only contain 8-bytes (1 register) of data
  _channel_snd(channel.in, channel.out, msg);

  // release the channel endpoint
  channel.in = (task_t *)NULL;
};

/******************************************************************************
 * @brief receive a message through a communication channel
 * @param channel handler
 * @param msg pointer
 * @param length of message to send
 * @return none
 ******************************************************************************/
void channel_rcv(const uint64_t channel_handler, const uint64_t *msg,
                 uint64_t msg_len) {
  // find channel from handler ID
  channel_t channel = channel_get_from_handler(channel_handler);

  // register the rcv task
  channel.out = sched_get_current_task();

  // release the cpu
  task_set_state(channel.out, BLOCKED);

  // remove it from the run queue
  sched_remove_task(channel.out);

  _channel_rcv(msg);

  // once message has been consumed, release the channel. This prevents
  // to re-send a message if the rcv task is not waiting for it
  channel.out = (task_t *)NULL;
};