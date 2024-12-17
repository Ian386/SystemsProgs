#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

//grep -c 5 google.com | grep rtt

int main(int argc, char * argv[]){
    int fd[2];
    if(pipe(fd) == -1){
        printf("Pipe failed\n");
        return 1;
    }
    int pid1 = fork();
    if(pid1 == -1){
        printf("Fork failed\n");
        return 2;
    }
    if(pid1 == 0){
        //child process 1 (ping)
        dup2(fd[1], STDOUT_FILENO);
        close(fd[0]);
        close(fd[1]);
        execlp("ping", "ping", "-c", "5", "google.com", NULL);

    }


    int pid2 = fork();
    if(pid2 == -1){
        printf("Fork failed\n");
        return 3;
    }
    if(pid2 == 0){
        //child process 2 (grep)
        dup2(fd[0], STDIN_FILENO);
        close(fd[0]);
        close(fd[1]);
        execlp("grep", "grep","rtt", NULL);
    }

    close(fd[0]);
    close(fd[1]);

    waitpid(pid1, NULL, 0);
    waitpid(pid2, NULL, 0);

    return 0;
}