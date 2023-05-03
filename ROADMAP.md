# Roadmap

For the initial release, focus is made on **core kernel services**. **kernel debugging** facilities and a minimal **shell** will also be part of this release.

## Initial release / r-1.0.0

### r-0.1.0 / Minimal runtime

- [] thread creation
- [] cooperative scheduling
- [] mutex support
- [] SMP support
- [] Qemu aarch64 support
- [] Qemu riscv 64 bits support

### r-0.2.0 / Process management

- [] process creation
- [] memory management

### r-0.3.0 / Inter-Process Communication

- [] synchronous message-based IPC
- [] asynchronous signal-based IPC

### r-0.4.0 / Drivers support

- [] independant module compilation
- [] IRQ redirection
- [] serial driver
- [] gpio driver

### r-0.5.0 / Shell

- [] minimal version for ash (anckor shell)

### r-0.6.0 / Kernel debug

- [] gdb server

## Backlog / Post r-1.0.0

- [] dynamic memory allocation support
- [] a convenient way to declare drivers for a platform (device tree ?)
- [] IDL support for inter-processes communication
- [] network stack
