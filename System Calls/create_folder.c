#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <errno.h>

#define MAX_PATH 4096

// Here’s a C program that categorizes files in the current directory based on their file extensions and moves them into folders named after the extensions(e.g., .txt files into a txt folder).The program takes one argument : the name of the target directory where categorized folders will be created.


// Create a folder if it doesn't exist
void create_folder(const char* folder_path){
    if(mkdir(folder_path, S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH) == -1){
       if(errno != EEXIST){
           perror("mkdir");
           exit(EXIT_FAILURE);
       }
    }
}

//function to move a file to a folder
void move_file(const char* file_name, const char* target_folder){
    char target_path[MAX_PATH];
    snprintf(target_path, sizeof(target_path), "%s/%s", target_folder, file_name);
    if(rename(file_name, target_path) == -1){
        perror("rename");
        exit(EXIT_FAILURE);
    }
}

//Function to get the file extension
const char* get_extension(const char* file_name){
    const char* dot = strrchr(file_name, '.');
    if(!dot || dot == file_name){
        return "";
    }
    return dot + 1;
}


int main(int argc, char* argv[]){
    if(argc != 2){
        fprintf(stderr, "Usage: %s <target_directory>\n", argv[0]);
        exit(EXIT_FAILURE);
    }


    const char* target_folder = argv[1];
    DIR* dir = opendir(".");
    if(dir == NULL){
        perror("opendir");
        exit(EXIT_FAILURE);
    }
    struct dirent* entry;
    struct stat file_stat;

    //create the target folder
    create_folder(target_folder);


    //iterate over the files in the current directory
    while((entry = readdir(dir)) != NULL){
        // Skip the current and parent directory entries
        if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0)
        {
            continue;
        }

        //check if the entry is a file
        if(stat(entry->d_name, &file_stat) == 0 && S_ISREG(file_stat.st_mode)){
            //get the file extension
            const char* extension = get_extension(entry->d_name);

            //skip files without an extension
            if(strlen(extension) == 0){
                continue;
            }

            //create a folder for the extension if it doesn't exist inside the target folder

            char ext_folder[MAX_PATH];
            snprintf(ext_folder, sizeof(ext_folder), "%s/%s", target_folder, extension);
            create_folder(ext_folder);

            //move the file to the extension folder
            move_file(entry->d_name, ext_folder);

        }
    }

    closedir(dir);
    printf("Files have been categorized successfully in the target directory: %s\n", target_folder);
    return 0;
}

