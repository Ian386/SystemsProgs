#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <time.h>
#include <string.h>

// 2 processes
//  child process generate string and send it to parent process
// parent process receives the numbers and prints them

int main(int argc, char *argv[])
{
    int fd[2];
    if (pipe(fd) == -1)
    {
        printf("Pipe failed\n");
        return 1;
    }
    int pid = fork();
    if (pid == -1)
    {
        printf("Fork failed\n");
        return 2;
    }
    if (pid == 0)
    {
        // Child process
        close(fd[0]);
        char str[100];
        printf("Enter a string: ");
        fgets(str, 100, stdin);
        str[strlen(str) - 1] = '\0';
        int n = strlen(str) + 1;

        if(write(fd[1], &n, sizeof(int)) == -1){
            printf("Write failed\n");
            return 3;
        }

        if (write(fd[1], str, sizeof(char) * n) == -1)
        {
            printf("Write failed\n");
            return 4;
        }
        close(fd[1]);
    }else{
        //parent process
        close(fd[1]);
        char str[100];
        int n;
        if(read(fd[0], &n, sizeof(int)) == -1){
            printf("Read failed\n");
            return 5;
        }
        if(read(fd[0], str, sizeof(char)* n) == -1){
            printf("Read failed\n");
            return 4;
        }
        printf("Received string: %s\n", str);
        close(fd[0]);
        wait(NULL);
    }
    return 0;
 }