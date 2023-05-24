# Threads

The anckor thread interface is minimal, it allows to create threads and maneg their scheduling, that's all.

Anckor uses a **cooperative scheduling** policy, each thread is responsible to release the cpu. This scheme allows to predict scheduler behaviour with ease compare to more general scheduling such as CFS used in Linux (or other comparable policy used in Fuschia for example).

Anckor aims to handle from one to a few tens of threads. It's not fitted to handle thousands of threads such as, once again, a more general OS.

## Thread states

Each thread can be in the following states: 
- Running
- Ready
- Blocked

At any moment, **only one thread is in Running state** and **one or more threads can be in Ready and Blocked states**.

## API reference

> **thread_create()**

Create a thread and place it on the run queue.

> **thread_destroy()**

Kill a thread, release its associated memory and kernel objects.

> **thread_yield()**

Stop the execution of the current thread, place it on the run queue and call **sched_run()**. If the current thread has the highest priority in the run queue, its execution resumes immediatly.

> **thread_sleep()**

Stop the execution of the current thread, remove it from the run queue and call **sched_run()**. The calling thread execution will not resume until a call to **thread_wakeup** is done.

> **thread_wakeup()**

Place a sleeped thread in the run queue and call **sched_run()**.