#!/usr/bin/bash

STM32_Programmer_CLI --connect port=swd \
    --download ./build/debug/build/*.elf \
    -hardRst -g \
    || STM32_Programmer_CLI --connect port=swd debugauth=2 \
    ; STM32_Programmer_CLI --connect port=swd \
        --download ./build/debug/build/*.elf \
        -hardRst -g
