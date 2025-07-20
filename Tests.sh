#!/bin/bash

# Initialize counters
total_tests=0
passed_tests=0

# Set inputs to all files in the folder (non-recursive)
inputs=(Tests/Code/*)
expected_folder="Tests/Bin"

gcc -Wall -Wextra -Werror -pedantic -g main.c assembler.c Instructions.c InstructionHandlers.c -o HASM

# Run tests
for input in "${inputs[@]}"; do
    total_tests=$((total_tests + 1))
    base_name=$(basename "$input") # Extract file name without folder path
    base_name="${base_name%.*}"
    expected="$expected_folder/$base_name"
    actual="OUTPUT"
    
    # Run the program and suppress its output
    ./HASM "$input" -o OUTPUT

    # Compare actual output with expected output
    if diff -q "$actual" "$expected" > /dev/null; then
        echo "Test $total_tests ($base_name): PASSED"
        passed_tests=$((passed_tests + 1))
    else
        echo "Test $total_tests ($base_name): FAILED"
        echo "Differences:"
        diff "$actual" "$expected"
    fi
done

# Display summary
echo
echo "Total tests: $total_tests"
echo "Passed tests: $passed_tests"