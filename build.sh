#!/bin/bash
set -e

gcc dell_7820_fan_tools.c -o ./build/dell_7820_fan_tools

# Passing dummy arguments to verify they print.
# This also is done so we do not inadvertently change fan speeds
# during testing.
./build/dell_7820_fan_tools fan speed

