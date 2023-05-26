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
these sections as loadble
*/
PHDRS
{
  text PT_LOAD;
  data PT_LOAD;
  bss PT_LOAD;
}

SECTIONS
{
  .text : {
    PROVIDE(_text_start = .);
    *(.text.init) 
	*(.text .text.*)
    PROVIDE(_text_end = .);
  } >ram AT>ram :text

  PROVIDE(_global_pointer = .);

  /* 
  global read only data
  */
  .rodata : {
    PROVIDE(_rodata_start = .);
    *(.rodata .rodata.*)
    PROVIDE(_rodata_end = .);
  } >ram AT>ram :text

  /* 
  global initialized data 
  */
  .data : {
	/*
	   align this section to 4kBytes pages
	*/
    . = ALIGN(4096);
    PROVIDE(_data_start = .);
    *(.sdata .sdata.*) 
	*(.data .data.*)
    PROVIDE(_data_end = .);
  } >ram AT>ram :data

  /* 
  global uninitialized data 
  */
  .bss : {
    PROVIDE(_bss_start = .);
    *(.sbss .sbss.*) 
	*(.bss .bss.*)
    PROVIDE(_bss_end = .);
  } >ram AT>ram :bss

  PROVIDE(_memory_start = ORIGIN(ram));
  PROVIDE(_stack_start = _bss_end);
  PROVIDE(_stack_end = _stack_start + 0x80000);
  PROVIDE(_memory_end = ORIGIN(ram) + LENGTH(ram));
  PROVIDE(_heap_start = _stack_end);
  PROVIDE(_heap_size = _memory_end - _heap_start);
}