#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <sys/wait.h>

int main(){
    // 5 => 5 * 4 = 20 => 20
    int p1[2]; //Child to Parent
    int p2[2]; //Parent to Child
    if (pipe(p1) == -1){
        printf("Unable to create pipe\n");
        return 1;
    }
    if (pipe(p2) == -1){
        printf("Unable to create pipe\n");
        return 1;
    }
    int pid = fork();
    if (pid == -1){
        printf("Unable to fork\n");
        return 2;
    }

    if (pid == 0){
        // Child Process
        close(p1[0]);
        close(p2[1]);
        int x;
        if(read(p2[0], &x, sizeof(int)) == -1){
            printf("Unable to read from pipe\n");
            return 3;
        }
        printf("Child Process Read: %d\n", x);
        x = x * 4 ;
        if(write(p1[1], &x, sizeof(int)) == -1){
            printf("Unable to write to pipe\n");
            return 4;
        }
        printf("Child Process Wrote: %d\n", x);
        close(p1[1]);
        close(p2[0]);
    }
    else{
        //Parent
        close(p1[1]);
        close(p2[0]);
        srand(time(NULL));
        int y= rand() % 10;
        if(write(p2[1], &y, sizeof(int)) == -1){
            printf("Unable to write to pipe\n");
            return 5;
        }
        printf("Parent Process Wrote: %d\n", y);

        if(read(p1[0], &y, sizeof(int)) == -1){
            printf("Unable to read from pipe\n");
            return 6;
        }
        printf("Parent Process Read Result: %d\n", y);
        close(p1[0]);
        close(p2[1]);
        wait(NULL);
    }

    return 0;

}

