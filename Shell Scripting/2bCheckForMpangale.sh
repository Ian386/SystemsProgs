#!/bin/bash



inputFile="Angukanayo.txt"
inputString="Mpangale"

if [ -f $inputFile ]; then
    if grep -q $inputString $inputFile; then
        echo "The string $inputString was found in $inputFile at line number: $(grep -n $inputString $inputFile | cut -d: -f1)"
    else
        echo "The string $inputString was not found in $inputFile"
    fi
else
    echo "File does not exist"
    exit 1
fi