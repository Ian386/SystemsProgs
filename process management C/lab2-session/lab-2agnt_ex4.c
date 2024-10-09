// NAME: IAN NDOLO MWAU
// REG NO: SCT211-0034/2022

// Write a program that reads the /proc directory and prints the process ID (PID), Parent Process ID (PPID), and the nice value (priority) of each process currently in RAM

#include <stdio.h>
#include <stdlib.h>
//working with directories
#include <dirent.h>
#include <string.h>
#include <ctype.h>

#define MAX_PATH 256

// a function that reads process information from /proc/[pid]/status and prints the PID, PPID, and priority (Nice value) for each process.
void print_process_info(const char *pid)
{
    char path[MAX_PATH]; // Store full path to the status file for the process.
    FILE *file;//pointer to a file, used to open and read from the /proc/[pid]/status file.
    int ppid;  // store the parent process ID
    int priority;//store the nice value

    // Construct the path to the status file
    //snprintf() function is used to write formatted output to a string avoiding buffer overflows
    snprintf(path, sizeof(path), "/proc/%s/status", pid);

    // Open the status file for the process
    file = fopen(path, "r");
    if (file)
    {
        // buffer to store each line of the status file.
        char line[256];

        // Read the file line by line using fgets()
        while (fgets(line, sizeof(line), file))
        {
            // strcmp() checks id the current line starts with "PPid:" or "Nice:" and sscanf() extracts the value of the parent process ID and the nice value.
            // Read Parent PID (PPID)
            if (strncmp(line, "PPid:", 5) == 0)
            {
                sscanf(line + 5, "%d", &ppid);
            }
            // Read nice value (priority)
            if (strncmp(line, "Nice:", 5) == 0)
            {
                sscanf(line + 5, "%d", &priority);
            }
        }

        fclose(file);

        // Print the process information
        printf("PID: %s, PPID: %d, Nice: %d\n", pid, ppid, priority);
    }
}

int main()
{
    DIR *dir; // pointer to the /proc directory.
    struct dirent *entry;// pointer to the current entry in the /proc directory.

    // Open the /proc directory
    dir = opendir("/proc");
    if (dir == NULL)
    {
        perror("opendir");
        return 1;
    }

    // Loop through the entries in /proc
    while ((entry = readdir(dir)) != NULL)
    {
        // Check if the entry is a number (a process ID)
        if (isdigit(entry->d_name[0]))
        {
            print_process_info(entry->d_name);
        }
    }

    closedir(dir);
    return 0;
}
