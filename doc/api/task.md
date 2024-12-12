# Tasks

Task is the fundamental unit of work which is scheduled and runned by the kernel. Anckor uses a **cooperative scheduling** policy, so each task is responsible to release the cpu. This scheme allows to predict scheduler behaviour with ease compare to more general scheduling such as CFS used in Linux (or other comparable policy used in Fuschia for example).

Anckor aims to handle from one to a few tens of tasks. It's not fitted to handle thousands of tasks such as, once again, a more general OS.

The scheduler is designed to run as few times as possible in order to let more CPU time to threads execution. It is heavily inspired by [Hubris](https://hubris.oxide.computer/reference/#_scheduling) and [Riot](https://doc.riot-os.org/group__core__sched.html#details). 

Interrupt handling is the only exception to the cooperative scheme. When an interrupt occurs, it's handled by an ISR (interrupt service routine which have to wake up a dedicated task to effectively serve the interrupt. In case of a high priority interrupt, the registered task will run immediatly.


The kernel heavily relies on the notion of **tasks**. In anckor, **threads** and **processes** shares the same control structure **task_struct**.

The only difference is that threads share the same **virtual address space** (which is saved in **vas_id**) when processes have independent address spaces. This is convenient as anckor can manage threads and processes in the same manner.

When a **task_switch** occurs, anckor always saves the current **task_state** and load the next one. But the kernel configures **mmu** only if **vas_ids** are differents.

## task states

Each task can be in one of the following states: 
- **Running**
- **Ready**
- **Blocked**

At any moment, **only one task is in Running state** and **one or more tasks can be in Ready and Blocked states**.

## API reference

```C
void task_create(const char *name, void (*task_entry)(void), stack_t *stack, uint8_t prio)
```

Create a task and place it on the run queue.

```C
void task_exit()
```

Kill the current task, release its associated memory. This will call the scheduler.

```C
void task_destroy(task_t *task)
```

Kill the task passed in argument, release its associated memory.

```C
void task_yield()
```

Stop the execution of the current task, place it on the run queue and call the scheduler. If the current task has the highest priority in the run queue, its execution resumes immediatly.

```C
void task_sleep()
```

Stop the execution of the current task, remove it from the run queue and call the scheduler. The calling task execution will not resume until a call to **task_wakeup** is done.

```C
void task_wakeup(task_t *task)
```

Place a sleeped task in the run queue.