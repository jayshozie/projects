#!/usr/bin/env bash

EMPTY_LINE=''

echo $EMPTY_LINE
echo 'Compiling...'
echo $EMPTY_LINE

# Define file paths for clarity and reuse
SOURCE_FILE=~/projects/networking/socket-programming/showip.c
OUTPUT_FILE=~/projects/networking/socket-programming/showip

# 1. Attempt to compile the C++ file
# gcc outputs compilation errors to stderr, which the user will see in the terminal
gcc -Wall -std=gnu99 "$SOURCE_FILE" -o "$OUTPUT_FILE"

# Store the exit status of the last command (g++)
COMPILATION_STATUS=$?

# 2. Check the exit status
if [ $COMPILATION_STATUS -eq 0 ]; then
    # SUCCESS: Exit status is 0
    echo "[INFO] $SOURCE_FILE Compiled without errors."
    echo $EMPTY_LINE
    echo 'Running...'
    echo $EMPTY_LINE
    
    # Execute the compiled program
    "$OUTPUT_FILE"
    
    # Delete the executable after execution
    rm -f "$OUTPUT_FILE"
else
    # ERROR: Exit status is non-zero (g++ failed)
    
    # The requirement was to delete testBench.exe if an error occurred.
    # gcc usually doesn't create the file on error, but we delete it just in case.
    rm -f "$OUTPUT_FILE"
    
    # Echo the required error message
    echo $EMPTY_LINE
    echo '[ERROR] Cannot compile, see above for the raised error.'
fi
