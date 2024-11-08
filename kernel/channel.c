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

typedef struct channel_t {
  task_t *in;
  task_t *out;
} channel_t;

channel_t channel;

/******************************************************************************
 * channel snd / rcv procedures
 ******************************************************************************/
extern void _channel_snd(task_t *, task_t *, const uint64_t *);
extern void _channel_rcv(const uint64_t *);

/******************************************************************************
 * @brief create a communication channel between two tasks
 * @param channel handler
 * @return none
 ******************************************************************************/
void channel_create(uint64_t *channel_handler) {
  channel.in  = NULL;
  channel.out = NULL;

  channel_handler = (uint64_t *)&channel;
};

/******************************************************************************
 * @brief send a message through a communication channel
 * @param channel handler
 * @param msg pointer
 * @param length of message to send
 * @return none
 ******************************************************************************/
void channel_snd(const uint64_t *channel_handler, const uint64_t *msg,
                 uint64_t msg_len) {
  task_t *next_task;

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

  // there is a waiting task so add it in the run queue
  task_set_state(channel.out, READY);
  sched_add_task(channel.out);

  // run the scheduler as the rcv task might not has the highest priority
  next_task = sched_get_next_task();

  // rcv task has the highest priority
  if (next_task == channel.out) {
    task_set_state(channel.out, RUNNING);
    sched_set_current_task(channel.out);

    // eventualy do the switch
    // !!! CAUTION !!! this implementation is an early alpha version
    // channel messages can only contain 8-bytes (1 register) of data
    _channel_snd(channel.in, channel.out, msg);
  } else {
    task_set_state(channel.out, RUNNING);
    sched_set_current_task(next_task);

    sched_switch(channel.in, next_task);
  }
};

/******************************************************************************
 * @brief receive a message through a communication channel
 * @param channel handler
 * @param msg pointer
 * @param length of message to send
 * @return none
 ******************************************************************************/
void channel_rcv(const uint64_t *channel_handler, const uint64_t *msg,
                 uint64_t msg_len) {
  // register the rcv task
  channel.out = sched_get_current_task();
  printk("channel->out : addr %x / data %x\r\n", &channel.out, channel.out);

  // release the cpu
  task_set_state(channel.out, BLOCKED);

  // remove it from the run queue
  sched_remove_task(channel.out);

  _channel_rcv(msg);

  // once message has been consumed, release the channel. This prevents
  // to re-send a message if the rcv task is not waiting for it
  channel.out = (task_t *)NULL;
};