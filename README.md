# Anckor

A lightweight kernel with a focus on **determinism**, **robustness** and **simplicity**.

## Getting started

## Design goals

The main goal is to design a small determinist kernel with robust partionning between processes.

This kernel aims to be as simple as possible to lower the cost of application design and maintenance.

To achieve this, a particular attention is done on keeping as fewer system calls as possible. Kernel services limits at the following primitives:
- process management
- thread management
- scheduling
- thread synchronization
- inter-process communication

All design choices will be done with performance in mind but when a tradeoff is needed, determinism, robustness and simplicity will always have priority.

For more information about ankor kernel design, please read the [docs](/docs/ARCHITECTURE.md).

## Tests

## [Roadmap](/ROADMAP.md)

## Supported platform

This kernel aims to run on **Aarch64** and **risv64** architectures.

See [platform](/PLATFORM.md) for a comprehensive list of supported platforms.