# Inter-Process communication

Anckor offers two ways to send information between processes: 
- One message-passing interface which is **synchronous**
- One notification interface which is **asynchronous**

The message passing interface is the main one to transfer data from process to process. It's heavily inspired by principles described in [QNX](https://www.qnx.com/developers/docs/6.5.0SP1.update/com.qnx.doc.neutrino_sys_arch/ipc.html) and [Hubris](https://hubris.oxide.computer/reference/#ipc).

The notification API is mainly designed to handle **interrupts** from threads. It implements behaviours described in [Hubris](https://hubris.oxide.computer/reference/#_sending_messages).

## Message passing

The message passing first uses a **channel_open()** to create a communication channel between two processes.

This functions takes an **AX_PORT_ID** in argument to identify the channel to create, it returns a **handle** to the **kernel object** used to access the channel in case of success.

Once the channel is opened, a thread can use the **channel_handle** to send and receive messages.

A send is handled in two ways under the hood:
- in **fast path mode** when the data size minimal, data are passed directly in CPU registers.
- in **shared memory mode** otherwise

## API reference

```C
ax_return channel_open(channel_handle *handle, channel_port port, channel_direction dir)
```

Open a channel with one sender and one receiver.

```C
ax_return channel_send(channel_handle *handle, channel_data *data, channel_data_size data_size)
```

Send a message over a channel, blocks until the receiving thread calls **channel_rcv()**. If the receiving thread is already waiting for a message, this function returns immediatly.

```C
ax_return channel_rcv(channel_handle *handle, channel_data *data, channel_data_size data_size)
```
 
Receive a message from a channel, this function blocks the current thread until the sending thread calls **channel_send()**. If the sending thread is already waiting for sending a message, this function returns immediatly.

```C
ax_return notification_rcv(thread_id id)
```

Check if a new notification has been received, doesn't block the current thread.

```C
ax_return notification_send(thread_id id)
```

Send a notification to the specified thread, doesn't block.