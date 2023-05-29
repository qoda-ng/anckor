/* Copyright (c) 2023 Qoda, engineering

This program is free software; you can redistribute it and/or modify 
it under the terms and conditions of the GNU General Public License,
version 3 or later, as published by the Free Software Foundation.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
General Public License for more details.

You should have received copies of the GNU General Public License and
the GNU Lesser General Public License along with this program.  If
not, see https://www.gnu.org/licenses/ */

/*
riscv is the name of the architecture that the linker understands
for any RISC-V target (64-bit or 32-bit).
*/
OUTPUT_ARCH( "riscv" )

/*
we tell the link which procedure is the program entry point
*/
ENTRY( _start )

/*
we declare one memory region of 8MBytes to store our program.
This sections starts at address 0x8000_0000 as specified in 
Qemu for riscv virt machine.
*/
MEMORY
{
  ram (wxa) : ORIGIN = 0x80000000, LENGTH = 8M
}

/*
we declare 3 sections in the .ELF program headers and specify 
these sections as loadable
*/
PHDRS
{
  text PT_LOAD FLAGS(5);   /* PF_R|PF_X */
  rodata PT_LOAD FLAGS(4); /* PF_R */
  data PT_LOAD FLAGS(6);   /* PF_R|PF_W */
  bss PT_LOAD FLAGS(6);   /* PF_R|PF_W */
}

SECTIONS
{
  .text : {
    PROVIDE(_text_start = .);
    *(.text.boot) 
	  *(.text .text.*)
    *(.gnu.linkonce.t.*)
    PROVIDE(_text_end = .);
  } >ram AT>ram :text

  . = ALIGN(4K);

  /* 
  global read only data
  */
  .rodata : {
    PROVIDE(_rodata_start = .);
    *(.rodata .rodata.*)
    *(.gnu.linkonce.r.*)
    PROVIDE(_rodata_end = .);
  } >ram AT>ram :rodata

  . = ALIGN(4K);

  /* 
  global initialized data 
  */
  .data : {
    PROVIDE(_data_start = .);
	  *(.data .data.*)
    *(.gnu.linkonce.d.*)
    PROVIDE(_data_end = .);
  } >ram AT>ram :data

  PROVIDE(_global_pointer = .);

  .sdata : {
    __global_pointer$ = . + (4K / 2);
    *(.sdata .sdata.*)
    *(.gnu.linkonce.s.*)
  } >ram AT>ram :data

  .sbss : {
    *(.sbss .sbss.*) 
    *(.gnu.linkonce.sb.*)
  } >ram AT>ram :bss

  /* 
  global uninitialized data 
  */
  .bss : {
    PROVIDE(_bss_start = .);
	  *(.bss .bss.*)
    *(.gnu.linkonce.b.*)
    PROVIDE(_bss_end = .);
  } >ram AT>ram :bss

  PROVIDE(_memory_start = ORIGIN(ram));
  PROVIDE(_stack_start = _bss_end);
  PROVIDE(_stack_end = _stack_start + 0x80000);
  PROVIDE(_memory_end = ORIGIN(ram) + LENGTH(ram));
  PROVIDE(_heap_start = _stack_end);
  PROVIDE(_heap_size = _memory_end - _heap_start);
}