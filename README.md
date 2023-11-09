# Anckor

Anckor aims to be a real-time kernel with a focus on **determinism**, **robustness** and **simplicity**.

The main goal is to design a lightweight kernel with robust partionning between processes. Its architecture and API has to be as simple as possible to lower the cost of application design and maintenance. A particular attention is done on keeping as fewer system calls as possible.

All design choices are recorded following the [ADR](./doc/arch/README.md) framework.

## Features

* Preemptive, tickless scheduler with priorities
* Riscv64 architecture support

## Getting started

First install the **cross-toolchain** and **Qemu** for riscv. Then download the sources:

```shell
git clone https://github.com/qoda-dev/anckor.git
```
Then run the **setenv.sh** script: 

```shell
./setenv.sh
```

Now you can use the **anckor** meta tool to **configure**, **build** and **run** the project. Default target is **qemu-riscv64**.

```shell
anckor configure

anckor build

anckor run
```

## [Roadmap](/ROADMAP.md)