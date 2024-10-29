//NAME : IAN NDOLO MWAU
//REG NO: SCT211-0034/2022

// The code below converts the text in a file to rainbow colors and prints it to the console since it is not possible with a notepad

//We will use ANSI color codes to change the text color in the console.


//header files
#include <stdio.h>
#include <stdlib.h>

// Following are ANSI color codes for ROYGBIV colors
//Define an array of strings each containing the ANSI color code for the rainbow colors sequence which will be used to repeat the colors in the file
const char *colors[] = {
    "\033[0;31m", // Red
    "\033[0;33m", // Orange 
    "\033[1;33m", // Yellow 
    "\033[0;32m", // Green
    "\033[0;34m", // Blue
    "\033[0;35m", // Indigo 
    "\033[1;35m"  // Violet 
};

//define a constant ANSI code string to reset the color to the default color black after each line to avoid overcoloring
const char *colorReset = "\033[0m"; 


//A function that takes a filename as a parameter and prints the contents of the file with rainbow colors
void printRainbowFile(const char *filename)
{
    // Open the file in read mode
    FILE *fp = fopen(filename, "r");

    // Check if the file was opened successfully
    if (!fp)
    {
        fprintf(stderr, "Error: Could not open the file.\n");
        return;
    }

    // a buffer to store each line of the file
    char buffer[300];

    //a counter to keep track of the current line number used to determine the color of the line based on its count
    int lineCounter = 0;

    // Read the file line-by-line
    while (fgets(buffer, sizeof(buffer), fp))
    {
        // Set color for the current line based on the line counter number
        printf("%s%s%s", colors[lineCounter % 7], buffer, colorReset);
        lineCounter++;
    }

    // Close the file
    fclose(fp);
}

int main()
{
    printRainbowFile("IanNdolo.txt");
    return 0;
}
