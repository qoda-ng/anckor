# Roadmap

For the initial release, focus is made on **core kernel services**. **kernel debugging** facilities and a minimal **shell** will also be part of this release.

## Initial release / r-1.0.0

### r-0.1.0 / Minimal runtime

- [x] thread creation
- [x] Qemu riscv 64 bits support
- [x] Modular build system
- [x] Anckor test engine
- [x] Configure CI to run tests for each pull request
- [x] exception management
- [x] syscalls
- [x] Interrupt management
- [x] synchronous message-based IPC
- [ ] heap allocator (binary buddy system)
- [ ] cooperative scheduling with min heap priority queue
- [ ] User / Kernel modes protection
- [ ] User / Kernel stacks

### r-0.2.0 / Threads synchronisation

- [ ] mutex support

### r-0.3.0 / Process management

- [ ] virtual memory management
- [ ] slab memory allocator

### r-0.4.0 / Inter-Process Communication

- [ ] asynchronous signal-based IPC

### r-0.5.0 / Drivers support

- [ ] independant module compilation
- [ ] IRQ redirection
- [ ] serial driver
- [ ] gpio driver

### r-0.6.0 / Shell

- [ ] minimal version for ash (anckor shell)

### r-0.7.0 / Kernel debug

- [ ] gdb server

### r-0.8.0 / Multi-Processor support

- [ ] SMP support

### r-0.9.0 / Aarch64 support

- [ ] Qemu aarch64 support

## Backlog / Post r-1.0.0

- [ ] Timer driver
- [ ] a convenient way to declare drivers for a platform (device tree ?)
- [ ] IDL support for inter-processes communication
- [ ] network stack
