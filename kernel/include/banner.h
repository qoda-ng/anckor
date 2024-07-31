/*
 * Copyright (c) 2023 Qoda, engineering
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms and conditions of the GNU General Public License,
 * version 3 or later, as published by the Free Software Foundation.

 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * General Public License for more details.

 * You should have received copies of the GNU General Public License and
 * the GNU Lesser General Public License along with this program.  If
 * not, see https://www.gnu.org/licenses/
 */

#ifndef BANNER_H
#define BANNER_H

#include "../../config.h"
#include "printk.h"

/**
 * @brief hello banner from the kernel with the build version
 * @param None
 * @return None
 */
void banner_display(void) {
  printk("Anckor OS build " BUILD_VERSION " - " BUILD_DATE " " BUILD_HOUR
         "\r\n");
}

#endif