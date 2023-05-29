# Anckor

A lightweight kernel with a focus on **determinism**, **robustness** and **simplicity**.

## Getting started

## Design goals

The main goal is to design a small kernel with an easy to understand and determinist behaviour.

This kernel aims to be as simple as possible to lower the cost of application design and maintenance.

To achieve this, system calls number is kept at minimal. The kernel is only responsible to create **tasks**, run them and manage communication between these objects.

All design choices are with performance in mind but when a tradeoff is needed, determinism, robustness and simplicity will always have priority.

For more information about anckor kernel design, please read the [docs](/docs/arch.md).

## Tests

## [Roadmap](/ROADMAP.md)

## Supported platform

This kernel aims to run on **Aarch64** and **risv64** architectures.