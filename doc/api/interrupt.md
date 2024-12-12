# Interrupts

Interrupt handling shares many behaviours with [QNX](https://www.qnx.com/developers/docs/6.5.0SP1.update/com.qnx.doc.neutrino_prog/inthandler.html). We use only two interfaces to **request** and **release** interrupts.

## API reference

```C
void interrupt_request(interrupt_id_t interrupt_id)
```

Attach the interrupt passed as argument to the current task and enable the interrupt in the processor.

```C
void interrupt_release(interrupt_id_t interrupt_id)
```

Detach the interrupt passed as argument from the current task and disable the interrupt in the processor.
