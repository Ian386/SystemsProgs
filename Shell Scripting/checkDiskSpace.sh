#!/bin/bash


# drive to check
drive="/mnt/c"

# Get the available disk space in MB
availSpace=$(df -m "$drive" | awk 'NR==2 {print $4}')

echo "The space available on drive $drive is $availSpace MB."

