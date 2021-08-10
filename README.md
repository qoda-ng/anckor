# stocky

![logo](doc/assets/logo.png)

## Resume

**Stocky** aims to be a lightweight and reactive microkernel targeting MCUs. The design is focused on the efficiency of three points: **scheduling**, **threading** and **IPC**.

All other services are build on top of these fundations.

## Scheduling

Try to design a tickless scheduler inspired by Riot with a priority inheritance system used for handling high priority interrupt handler.

## threading

Implement a threading service inspired Riot, FreeRTOS or Threadx.

## IPC

Try to design an efficient IPC system based on kernel object handling and as few data copies as possible.