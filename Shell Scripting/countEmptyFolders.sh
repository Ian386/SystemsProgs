#!/bin/bash

# Write a Shell Script that counts the number of empty folders in a directory
# (with size=0) and outputs the list of those folders and the time created.

#NAME: IAN NDOLO MWAU
#REG NO: SCT211-0034/2022

# enter directory path
echo "Enter the directory path: "
read dirPath

# check if directory exists
if [ ! -d $dirPath ]; then
    echo "Directory does not exist"
    exit 1
fi  


# use find command to get list of empty folders
emptyFolders=$(find $dirPath -type d -empty -printf "%p %TY-%Tm-%Td %TT\n") 

# check if there are empty folders
if [ -z "$emptyFolders" ]; then
    echo "No empty folders found"
else
    numEmptyFolders=$(echo "$emptyFolders" | wc -l)

    # display empty folders
    echo "Number of empty folders: $numEmptyFolders"
    echo "Empty folders:"
    echo "$emptyFolders"
fi