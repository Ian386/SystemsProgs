#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

// Working with multiple pipes in a single program to compute an addition.

int main(int argc, char * argv[]){
    int fd[3][2];
    for(int i = 0; i < 3; i++){
        if(pipe(fd[i]) == -1){
            printf("Pipe failed\n");
            return 1;
        }
    }
    int pid1 = fork();
    if(pid1 == -1){
        printf("Fork failed\n");
        return 2;
    }
    if(pid1 == 0){
        //child process 1
        close(fd[0][1]);
        close(fd[1][0]);
        close(fd[2][0]);
        close(fd[2][1]);
        int x;
        if(read(fd[0][0], &x, sizeof(int)) == -1){
            printf("Read failed\n");
            return 3;
        }

        x+=5;
        if(write(fd[1][1], &x, sizeof(int)) == -1){
            printf("Write failed\n");
            return 4;
        }

        close(fd[0][0]);
        close(fd[1][1]);

        return 0;

    }

    int pid2 = fork();
    if(pid2 == -1){
        printf("Fork failed\n");
        return 5;
    }
    if(pid2 == 0){
        //child process 2
        close(fd[0][0]);
        close(fd[0][1]);
        close(fd[1][1]);
        close(fd[2][0]);
        int y;
        if(read(fd[1][0], &y, sizeof(int)) == -1){
            printf("Read failed\n");
            return 6;
        }

        y+=5;
        if(write(fd[2][1], &y, sizeof(int)) == -1){
            printf("Write failed\n");
            return 7;
        }

        close(fd[1][0]);
        close(fd[2][1]);

        return 0;

    }

    //parent process

    close(fd[0][0]);
    close(fd[1][0]);
    close(fd[1][1]);
    close(fd[2][1]);

    int x;
    printf("Enter a number: ");
    scanf("%d", &x);
    
    if(write(fd[0][1], &x, sizeof(int)) == -1){
        printf("Write failed\n");
        return 8;
    }

    close(fd[0][1]);

    if(read(fd[2][0], &x, sizeof(int)) == -1){
        printf("Read failed\n");
        return 9;
    }

    close(fd[2][0]);

    printf("Result: %d\n", x);

    waitpid(pid1, NULL, 0); 
    waitpid(pid2, NULL, 0);

    return 0;
}