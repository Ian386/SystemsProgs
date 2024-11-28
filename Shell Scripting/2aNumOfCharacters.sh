#!/bin/bash

inputFile="Angukanayo.txt"

if [ -f $inputFile ]; then
    echo "Number of characters in $inputFile is: $(wc -c < $inputFile)"
else
    echo "File does not exist"
    exit 1
fi