#!/bin/bash

# Input file
input_file="students.csv"

# Check if the file exists
if [ ! -f "$input_file" ]; then
    echo "Error: File '$input_file' not found!"
    exit 1
fi

# Use awk to process the file
echo "Students with marks > 80:"
awk -F',' 'NR > 1 { if ($3 > 80) print $1 }' "$input_file"
