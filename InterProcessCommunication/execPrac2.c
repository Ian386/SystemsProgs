#include <stdlib.h>
#include <stdio.h>
#include <unistd.h> 
// #include <process.h>
#include <time.h>
#include <sys/wait.h>
#include <fcntl.h>

int main(int argc, char* argv[]){
    int pid = fork();
    if(pid == -1){
        printf("Fork failed\n");
        return 1;
    }
    if(pid == 0){
        // Child process
        //open a file to write the output of the ping command
        int fd = open("pingOutput.txt", O_WRONLY | O_CREAT, 0777);
        if(fd == -1){
            printf("Error in opening file\n");
            return 2;
        }
        printf("File descriptor: %d\n", fd);
        int file2 = dup2(fd, STDOUT_FILENO);
        printf("File descriptor duplicator: %d\n", file2);
        close(fd);


        int err = execlp("ping", "ping","-c", "1", "www.google.com", NULL);
        if(err == -1){
            printf("Error in execlp\n");
            return 2;
        }
    }
    else{
        int waitStatus;
        wait(&waitStatus);
        if(WIFEXITED(waitStatus)){
        int exitStatus = WEXITSTATUS(waitStatus);
            printf("Child exited with status: %d\n", exitStatus);
            if(exitStatus == 0){
                printf("Ping executed successfully\n");
            }
            else{
                printf("Ping failed\n");
            }
        }
        printf("Some post processing goes here.\n");

    }
    
    return 0;
}