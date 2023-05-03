# Scheduling

The scheduler is designed to run as few times as possible in order to let more CPU time to threads execution. The scheduler is heavily inspired by [Hubris](https://hubris.oxide.computer/reference/#_scheduling) and [Riot](https://doc.riot-os.org/group__core__sched.html#details).

Following this principle, Anckor scheduler uses a **cooperative** policy. Threads are never interrupted and they only release the CPU by an explicit call to **thread_yield()** or **thread_sleep()** (see [thread](./thread.md)).

A thread can also be awake after a **thread_sleep()** by a call to **thread_wakeup()**. This function is primarily designed to be called in an **interrupt routine**.

Interrupt handling is the only exception to the described scheme. When an interrupt occurs, it's handled by an ISR (interrupt service routine). This routine can then send a **notification** to a thread to effectively serve the interrupt. In case of a high priority interrupt, the ISR can **awake** a high priority thread which will be called immediatly.

Interrupt handling shares many behaviours with [QNX](https://www.qnx.com/developers/docs/6.5.0SP1.update/com.qnx.doc.neutrino_prog/inthandler.html)

## API reference

> **sched_run()**

Run the scheduler. If the current thread has not the highest priority, it leads to a **thread_switch()**.