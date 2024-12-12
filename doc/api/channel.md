# Inter-Process communication

Anckor offers two ways to send information between processes: 
- One message-passing interface which is **synchronous**
- One notification interface which is **asynchronous** (**NOT IMPLEMENTED YET**)

The message passing interface is the main one to transfer data from process to process. It's heavily inspired by principles described in [QNX](https://www.qnx.com/developers/docs/6.5.0SP1.update/com.qnx.doc.neutrino_sys_arch/ipc.html) and [Hubris](https://hubris.oxide.computer/reference/#ipc) but its design mainly implements mechanisms described in [L4 paper](https://dl.acm.org/doi/pdf/10.1145/173668.168633).

The notification API is mainly designed to handle **interrupts** from threads. It implements behaviours described in [Hubris](https://hubris.oxide.computer/reference/#_sending_messages)  (**NOT IMPLEMENTED YET**).

## Message passing

The message passing first uses a **channel_create()** to create a communication channel between two processes. In case of success, this call returns a unique channel ID in **channel_handler**.

Once the channel is opened, a thread can use the handler to send and receive messages.

A send is handled in two ways under the hood:
- in **fast path mode** when the data size minimal, data are passed directly in CPU registers.
- in **shared memory mode** otherwise

## API reference

```C
k_return_t channel_create(uint64_t *channel_handler, const char *name)
```

Open a channel with one sender and one receiver.

```C
k_return_t channel_get(uint64_t *channel_handler, const char *name)
```

Find a channel created in the kernel. Return error if the channel does not exist.

```C
void channel_snd(const uint64_t channel_handler, const uint64_t *msg, uint64_t msg_len)
```

Send a message over a channel, blocks until the receiving task calls **channel_rcv()**. If the receiving task is already waiting for a message, the message will be send immediatly.

```C
void channel_rcv(const uint64_t channel_handler, const uint64_t *msg, uint64_t *msg_len)
```
 
Receive a message from a channel, this function blocks the current thread until the sending thread calls **channel_snd()**. If the sending thread is already waiting for sending a message, the message will be received immediatly.