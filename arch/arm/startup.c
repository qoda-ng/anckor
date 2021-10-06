/*
 * Copyright (c) 2021 nicolas cros.
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, version 3.
 *
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
 * General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program. If not, see <http://www.gnu.org/licenses/>.
 */

/**
 * @ingroup     cpu_startup
 * @{
 *
 * @file
 * @brief       cpu vector handlers declaration
 *
 * @author      nicolas cros
 *
 * @}
 */

#include "stdint.h"

/*******************************************************************************
 * Definitions
 ******************************************************************************/

/**
 * @brief   Memory markers, defined in the linker script
 * @{
 */

// .text: code section
extern uint32_t _etext;
// .data: static initialized data
extern uint32_t _sdata;
extern uint32_t _edata;
// .bss: static non initialized data
extern uint32_t _sbss;
extern uint32_t _ebss;

/*******************************************************************************
 * Variables
 ******************************************************************************/

/*******************************************************************************
 * Functions
 ******************************************************************************/

/******************************************************************************
 * @brief cpu reset handler
 * @param None
 * @return None
 ******************************************************************************/
void reset_handler(void)
{
    uint32_t *dst;
    const uint32_t *src = &_etext;

    /* load data section from flash to ram */
    for (dst = &_sdata; dst < &_edata;)
    {
        *(dst++) = *(src++);
    }

    /* initialiaze bss section to zero */
    for (dst = &_sbss; dst < &_ebss;)
    {
        *(dst++) = 0;
    }

    /* initialize the platform ( cpu + board ) */
    platform_init();

    /* launch the kernel */
    kernel_init();
}