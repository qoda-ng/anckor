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
 * @ingroup     platform_setup
 * @{
 *
 * @file
 * @brief       platform init
 *
 * @author      nicolas cros
 *
 * @}
 */

#include "stdint.h"

/*******************************************************************************
 * Definitions
 ******************************************************************************/

/*******************************************************************************
 * Variables
 ******************************************************************************/

/*******************************************************************************
 * Functions
 ******************************************************************************/

/******************************************************************************
 * @brief platform init
 * @param None
 * @return None
 ******************************************************************************/
void platform_init(void)
{
    cpu_init();

    board_init();
}
