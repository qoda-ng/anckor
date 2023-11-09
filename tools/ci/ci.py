# Copyright (c) 2023 Qoda, engineering

# This program is free software; you can redistribute it and/or modify
# it under the terms and conditions of the GNU General Public License,
# version 3 or later, as published by the Free Software Foundation.

# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
# General Public License for more details.

# You should have received copies of the GNU General Public License and
# the GNU Lesser General Public License along with this program.  If
# not, see https://www.gnu.org/licenses/

# This script is used to automate the run of anckor tests on a cloud 
# server provider

from pexpect import *
import sys

# create a process with the QEMU guest
child = spawn('anckor run')

# look for the output of the QEMU guest
while True:
    child_response = child.readline().decode('utf-8')
    print(child_response)
    if "ATE - PASSED" in child_response:
        test_passed = True
        break
    elif "ATE - FAILED" in child_response:
        test_passed = False
        break

if test_passed:
    print("TEST PASSED")
    sys.exit(0)
else:
    print("TEST FAILED")
    sys.exit(1)

# kill the Qemu guest
child.terminate(force=True)
