# Architecure

## Tasks

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