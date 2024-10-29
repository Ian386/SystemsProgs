//NAME: IAN NDOLO MWAU
//REG NO: SCT211-0034/2022


//header files needed for the program
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>// for directory operations
#include <sys/stat.h>// for file information operations



// This is the main function that searches for .mp3 files in the C:/ drive and all its subdirectories with the string of the directory and a pointer to the output file as parameters

void searchMp3Files(const char *directory, FILE *fpOutput)
{

    // Declare a pointer to dirent which represents a file or directory within a directory
    struct dirent *dentry;

    //open directory stream 
    DIR *dp = opendir(directory);

    //if successful then the dp ahould point to the directory
    if (dp == NULL)
    {
        fprintf(stderr, "Error: Could not open directory %s\n", directory);
        return;
    }


    //Next step is to loop through the directory entries using the readdir function which returns a pointer to the next directory entry
    while ((dentry = readdir(dp)) != NULL)
    {
        // Declare a buffer to store the path of the file
        char path[1024];

        // Declare a struct to store information about the file or directory
        struct stat fileStat;

        // Ignore "." and ".." entries which represent the current and parent directories
        // check if entry->name is equal to "." or ".."

        if (strcmp(dentry->d_name, ".") == 0 || strcmp(dentry->d_name, "..") == 0)
            continue;

        // Construct the full path of the file by concatenating the directory path and the file name

        snprintf(path, sizeof(path), "%s/%s", directory, dentry->d_name);

        // Get information about the file using the stat function and store it in the fileStat struct
        //chec if stat returns -1 to show error

        if (stat(path, &fileStat) == -1)
        {
            perror("stat");
            continue;
        }

        // Check if the entry is a directory or a regular file
        //if it is a directory then call the searchMp3Files function recursively

        if (S_ISDIR(fileStat.st_mode))
        {
            // Recursive call for directories
            searchMp3Files(path, fpOutput);
        }

        // Check if the entry is a regular file
        //if it is a regular file then check if it has an .mp3 extension and print the file name and size to the output file

        else if (S_ISREG(fileStat.st_mode))
        {
            // Check if the file has an .mp3 extension
            if (strstr(dentry->d_name, ".mp3") != NULL)
            {
                // Print the file name and size to the output file using the fileStat.st_size field
                fprintf(fpOutput, "File: %s, Size: %lld bytes\n", dentry->d_name, (long long)fileStat.st_size);
            }
        }
    }

    // Close the directory stream
    closedir(dp);
}

int main()
{
    // Open the output file in write mode
    FILE *fpOutput = fopen("IanNdolo.txt", "w");

    // Check if file was opened successfully
    if (!fpOutput)
    {
        //use the standard error stream to print the error message
        fprintf(stderr, "Error: Could not create output file.\n");
        return 1;
    }


    printf("Searching for .mp3 files in C:/ Takes some time...\n");

    // Call the searchMp3Files function with the C:/ directory and the output file pointer
    searchMp3Files("C:/", fpOutput);

    // Close the output file
    fclose(fpOutput);

    
    printf("Search completed. File Names saved to IanNdolo.txt\n");

    return 0;
}
