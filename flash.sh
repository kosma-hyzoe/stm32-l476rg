#!/usr/bin/bash

STM32_Programmer_CLI --connect port=swd \
    --download ./build/debug/build/*.elf \
    -hardRst -g
