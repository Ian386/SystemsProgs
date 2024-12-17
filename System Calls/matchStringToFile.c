#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

// Here is a C program that recursively searches the current directory and its subdirectories for files whose names begin with a specified string and prints their paths.


int find_files(const char* dir_path, const char* prefix){
    DIR* dir =opendir(dir_path);
    if(dir == NULL){
        perror("opendir");
        return -1;
    }
    struct dirent* entry;
    struct stat file_stat;
    char full_path[PATH_MAX];

    while((entry = readdir(dir)) != NULL){
        // Skip the current and parent directory entries
        if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0)
        {
            continue;
        }
        //construct the full path of the file
        snprintf(full_path, sizeof(full_path), "%s/%s", dir_path, entry->d_name);

        // Get the file's information
        if (stat(full_path, &file_stat) == -1)
        {
            perror("stat");
            continue;
        }

        //check if the file is a directory
        if(S_ISDIR(file_stat.st_mode)){
            // Recursively search the subdirectory
            find_files(full_path, prefix);

        }
        else if(S_ISREG(file_stat.st_mode)){
            // Check if the file name starts with the specified prefix
            if(strncmp(entry->d_name, prefix, strlen(prefix)) == 0){
                printf("%s\n", full_path);
            }
        }


    }

    closedir(dir);


}


int main(int argc, char* argv[]){
    if(argc != 2){
        fprintf(stderr, "Usage: %s <directory> <prefix>\n", argv[0]);
        return 1;
    }

    const char *prefix = argv[1];

    printf("Files beginning with '%s':\n", prefix);
    find_files(".", prefix);
    
    return 0;
}