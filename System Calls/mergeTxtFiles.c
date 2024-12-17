#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>

#define BUFFER_SIZE 4096

// Here is a C program that reads all .txt files in the current directory, merges their contents into a new file, and returns a file descriptor for the merged file.

int merge_txt_file(const char *output_filename){
    DIR *dir;
    struct dirent *entry;
    int output_fd, input_fd;
    char buffer[BUFFER_SIZE];
    ssize_t bytes_read, bytes_written;

    // Open the current directory
    dir = opendir(".");
    if (dir == NULL)
    {
        perror("opendir");
        return -1;
    }

    // Open the output file for writing
    output_fd = open(output_filename, O_WRONLY | O_CREAT | O_TRUNC, 0777);
    if (output_fd < 0)
    {
        perror("open output file");
        closedir(dir);
        return -1;
    }


    // Loop through all entries in the directory
    while((entry = readdir(dir)) != NULL){
        // check if file has a .txt extension
        if (strstr(entry->d_name, ".txt") != NULL && strcmp(entry->d_name, output_filename) != 0 && strcmp(entry->d_name + strlen(entry->d_name) - 4, ".txt") == 0)
        {
            // Open the input file for reading
            input_fd = open(entry->d_name, O_RDONLY);
            if (input_fd < 0)
            {
                perror("open input file");
                continue;
            }

            // Read from the input file and write to the output file

            while((bytes_read = read(input_fd, buffer, BUFFER_SIZE)) > 0){
                bytes_written = write(output_fd, buffer, bytes_read);
                if(bytes_written< 0 || bytes_written != bytes_read){
                    perror("write");
                    close(input_fd);
                    close(output_fd);
                    closedir(dir);
                    return -1;
                }
            }

            if (bytes_read < 0)
            {
                perror("read from input file");
            }

            close(input_fd);
        }

        entry = readdir(dir);

            
    }
    // Close the output file and directory
    close(output_fd);
    closedir(dir);

    // Reopen the output file in read - write mode and return its file descriptor
    return open(output_filename, O_RDWR);
    }

int main(){

    const char *output_filename = "merged.txt";
    int fd = merge_txt_file(output_filename);
    
    if(fd < 0){
        perror("merge_txt_file");
        return 1;
    }

    printf("Merged file created: %s\n", output_filename);
    printf("File descriptor: %d\n", fd);
    close(fd);



    return 0;
}