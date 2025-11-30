#!/usr/bin/env bash

CURR_DIR=$(pwd)
SOURCE=""
OUTPUT=""
PATH_TO_SOURCE=$CURR_DIR/
PATH_TO_OUTPUT=$CURR_DIR/
GCC_FLAGS="-Wall -Wextra -std=gnu99"

################################################################################
# Help                                                                         #
################################################################################
help() {
    echo 'GCC auto-compiler for C Programming Language.'
    echo 'cbench runs GCC for you with default flags in your current directory.'
    echo
    echo 'Syntax: cbench NAME_OF_SOURCE NAME_FOR_OUTPUT'
    echo 'Options:'
    echo '-s=      Name of the source.'
    echo '-o=      Name for the output.'
    echo '-std=    GCC Standards'
    echo '-v       Print version.'
    echo '-r       Run the output binary if GCC compiles successfully.'
    echo
}

compile_file() {
    local source=$1
    local output=$2

    gcc $GCC_FLAGS "$source" -o "$output"

    if [ $? -ne 0 ]; then
        echo "\e[1;31m[ERR]\[0m:  GCC FAILED TO COMPILE $source. SEE ABOVE!!!"
        return 1
    fi
    echo "\e[1;34m[INFO]\e[0m:  GCC SUCCESSFULLY COMPILED $source to $output."
    return 0
}

cleanup() {
    echo
    echo "\e[1;34m[INFO]\e[0m:  Cleaning up binaries..."
    rm -i "$OUTPUT"
    echo "\e[1;34m[INFO]\e[0m:  Cleanup complete."
}


