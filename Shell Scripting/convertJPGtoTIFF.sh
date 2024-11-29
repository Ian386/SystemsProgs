#!/bin/bash

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

# success counter
numConverted=0

#check if imagemagick is installed
if ! command -v convert &> /dev/null; then
    echo "ImageMagick is not installed. Please install it to convert images."
    exit 1
fi

# convert jpg files to tiff
for jpgFile in $dirPath/*.{jpg,JPG}; do
    if [ -f $jpgFile ]; then
        convert $jpgFile ${jpgFile%.*}.tiff
        numConverted=$((numConverted+1))
    fi

done

echo "Number of images converted: $numConverted"


