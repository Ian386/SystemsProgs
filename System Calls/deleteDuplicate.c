#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <time.h>

// Here’s a C program that performs the following tasks:

// Searches for all files with the same name in the given directory and its subdirectories.
// Displays their name, the folder they are in, and their creation/modification date.
// Asks the user if each duplicate file should be kept or deleted.
// Deletes files based on user input.

#define MAX_PATH 4096
#define HASH_TABLE_SIZE 10007

typedef struct file_node{
    char file_path[MAX_PATH];
    time_t mod_time;
    struct file_node* next;
}file_node;


// Hash table to store file names
typedef struct{
    file_node* files;
}hash_table;



// Hash function to categorize files based on their names
unsigned int hash_function(const char* str){
    unsigned int hash =0;
    while(*str){
        hash = (hash * 31 + *str++) % HASH_TABLE_SIZE;
    }
    return hash;
}

// Insert a file into the hash table
void insert_file(hash_table* table, const char* file_path, time_t mod_time){
    char* file_name = strrchr(file_path, '/');
    if(!file_name)
        file_name = (char *)file_path; // If no '/', use the full path
    else file_name++; //skip the '/'

    unsigned int index = hash_function(file_name);

    file_node* new_node = (file_node*)malloc(sizeof(file_node));
    if(!new_node){
        perror("malloc");
        exit(EXIT_FAILURE);
    }

    strcpy(new_node->file_path, file_path);
    new_node->mod_time = mod_time;
    new_node->next = table[index].files;
    table[index].files = new_node;

}

// Recursively traverse the directory and collect files
void collect_files(const char* dir_path, hash_table* table){
    DIR* dir = opendir(dir_path);
    if(dir == NULL){
        perror("opendir");
        exit(EXIT_FAILURE);
    }

    struct dirent* entry;
    struct stat file_stat;
    while((entry = readdir(dir)) != NULL){
        if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0)
        {
            continue;
        }
        char file_path[MAX_PATH];
        snprintf(file_path, sizeof(file_path), "%s/%s", dir_path, entry->d_name);

        if(stat(file_path, &file_stat) == -1){
            perror("stat");
            continue;
        }

        if(S_ISDIR(file_stat.st_mode)){
            if(strcmp(entry->d_name, ".") != 0 && strcmp(entry->d_name, "..") != 0){
                collect_files(file_path, table);
            }
        }
        else if(S_ISREG(file_stat.st_mode)){
            // Insert the file into the hash table
            insert_file(table, file_path, file_stat.st_mtime);
        }
    }
    closedir(dir);
}


// Function to display and delete duplicate files

void handle_duplicates(hash_table* table){
    for(unsigned int i=0; i< HASH_TABLE_SIZE; i++){
        file_node* file_list= table[i].files;
        if(!file_list || !file_list->next){
            //skip if there are no duplicates
            continue;
        }

        printf("Duplicate files found:\n");
        file_node* current = file_list;
        while(current){
            char choice;
            printf("Keep file '%s'? (y/n):", current->file_path);
            scanf(" %c", &choice);

            if (choice == 'n' || choice == 'N')
            {
                if (unlink(current->file_path) < 0)
                {
                    perror("unlink");
                }
                else
                {
                    printf("Deleted: %s\n", current->file_path);
                }
    
            }
            current = current->next;
        }
    }
}

//free the memory allocated for the hash table
void free_hash_table(hash_table *table)
{
    for (unsigned int i = 0; i < HASH_TABLE_SIZE; i++)
    {
        file_node *current = table[i].files;
        while (current)
        {
            file_node *temp = current;
            current = current->next;
            free(temp);
        }
    }
}

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        fprintf(stderr, "Usage: %s <directory>\n", argv[0]);
        return EXIT_FAILURE;
    }

    const char *dir_path = argv[1];
    hash_table table[HASH_TABLE_SIZE] = {0};

    // Collect all files
    collect_files(dir_path, table);

    // Handle duplicates
    handle_duplicates(table);

    // Free memory
    free_hash_table(table);

    return EXIT_SUCCESS;
}
