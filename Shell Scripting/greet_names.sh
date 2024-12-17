#!/bin/bash

# Input and output file names
input_file="names.txt"
output_file="greetings.txt"

# Check if the input file exists
if [ ! -f "$input_file" ]; then
    echo "Error: File '$input_file' not found!"
    exit 1
fi

# Clear the output file (if it exists) to start fresh
> "$output_file"

# Read each line from the input file and process it
while read -r name; do
    echo "Hello, $name!" >> "$output_file"
done < "$input_file"

echo "Greetings have been written to '$output_file'."
