# Tasks

The anckor tasks interface is minimal, it allows to create tasks and manage their scheduling, that's all.

Anckor uses a **cooperative scheduling** policy, each task is responsible to release the cpu. This scheme allows to predict scheduler behaviour with ease compare to more general scheduling such as CFS used in Linux (or other comparable policy used in Fuschia for example).

Anckor aims to handle from one to a few tens of tasks. It's not fitted to handle thousands of tasks such as, once again, a more general OS.

The scheduler is designed to run as few times as possible in order to let more CPU time to threads execution. The scheduler is heavily inspired by [Hubris](https://hubris.oxide.computer/reference/#_scheduling) and [Riot](https://doc.riot-os.org/group__core__sched.html#details).

Following this principle, Anckor scheduler uses a **cooperative** policy. Threads are never interrupted and they only release the CPU by an explicit call to **thread_yield()** or **thread_sleep()** (see [thread](./thread.md)).

A thread can also be awake after a **thread_sleep()** by a call to **thread_wakeup()**. This function is primarily designed to be called in an **interrupt routine**.

Interrupt handling is the only exception to the described scheme. When an interrupt occurs, it's handled by an ISR (interrupt service routine). This routine can then send a **notification** to a thread to effectively serve the interrupt. In case of a high priority interrupt, the ISR can **awake** a high priority thread which will be called immediatly.

Interrupt handling shares many behaviours with [QNX](https://www.qnx.com/developers/docs/6.5.0SP1.update/com.qnx.doc.neutrino_prog/inthandler.html)

The kernel heavily relies on the notion of **tasks**. In anckor, **threads** and **processes** shares the same control structure **task_struct** of which you can see some fields below:  

```C
task_struct {
    vas_id 
    task_id

    ...

    task_state

    ...

    vmo *
    channels *
}
```

The only difference is that threads share the same **virtual address space** (which is saved in **vas_id**) when processes have independent address spaces. This is convenient as anckor can manage threads and processes in the same manner.

When a **task_switch** occurs, anckor always saves the current **task_state** and load the next one. But the kernel configures **mmu** only if **vas_ids** are differents.


## task states

Each task can be in the following states: 
- **Running**
- **Ready**
- **Blocked**

At any moment, **only one task is in Running state** and **one or more tasks can be in Ready and Blocked states**.

## API reference

```C
ax_return task_create(task_id *task_id, task_attr VM_SHARE)
```

Create a task and place it on the run queue. If the task attribute is equal to VM_SHARE, the created task shares the existing memory space (such as **tasks**). If not, the task is running in its own memory space (similar to a **process**).

```C
ax_return task_exit(task_id *task_id)
```

Kill a task, release its associated memory and kernel objects.

```C
ax_return task_yield(task_id *task_id)
```

Stop the execution of the current task, place it on the run queue and call **sched_run()**. If the current task has the highest priority in the run queue, its execution resumes immediatly.

```C
ax_return task_sleep(task_id *task_id)
```

Stop the execution of the current task, remove it from the run queue and call **sched_run()**. The calling task execution will not resume until a call to **task_wakeup** is done.

```C
ax_return task_awake(task_id *task_id)
```

Place a sleeped task in the run queue and call **sched_run()**.