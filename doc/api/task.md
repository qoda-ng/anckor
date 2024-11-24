# Tasks

The anckor tasks interface is minimal, it allows to create tasks and manage their scheduling, that's all.

Anckor uses a **cooperative scheduling** policy, each task is responsible to release the cpu. This scheme allows to predict scheduler behaviour with ease compare to more general scheduling such as CFS used in Linux (or other comparable policy used in Fuschia for example).

Anckor aims to handle from one to a few tens of tasks. It's not fitted to handle thousands of tasks such as, once again, a more general OS.

## task states

Each task can be in the following states: 
- Running
- Ready
- Blocked

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