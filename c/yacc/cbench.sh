#!/usr/bin/env bash

EMPTY_LINE=''

echo $EMPTY_LINE
echo 'Compiling...'
echo $EMPTY_LINE

# Define file paths for clarity and reuse
INPUT=~/projects/c/yacc/yacc.c
OUTPUT=~/projects/c/yacc/yacc

# 1. Attempt to compile the C++ file
# gcc outputs compilation errors to stderr, which the user will see in the terminal
gcc -Wall -Wextra -g -std=gnu99 "$INPUT" -o "$OUTPUT"

# Store the exit status of the last command (gcc)
COMPILATION_STATUS=$?

# 2. Check the exit status
if [ $COMPILATION_STATUS -eq 0 ]; then
    # SUCCESS: Exit status is 0
    echo '[CBENCH | INFO] Compiled without errors.'
    # echo $EMPTY_LINE
    # echo 'Running...'
    # echo $EMPTY_LINE
    
    # Execute the compiled program
    # "$OUTPUT"
    
    # Delete the executable after execution
    # rm -f "$OUTPUT"
else
    # ERROR: Exit status is non-zero (gcc failed)
    
    # The requirement was to delete testBench.exe if an error occurred.
    # gcc usually doesn't create the file on error, but we delete it just in case.
    # rm -f "$OUTPUT"
    
    # Echo the required error message
    echo $EMPTY_LINE
    echo '[CBENCH | ERR] Cannot compile, see above for the raised error.'
fi
