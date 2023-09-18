#!/usr/bin/bash

build () {
    STM32_Programmer_CLI --connect port=swd \
        --download ./build/debug/build/*.elf \
        -hardRst -g
}

fix_connection() {
    STM32_Programmer_CLI --connect port=swd debugauth=2
}

build || fix_connection 2> /dev/null || build

