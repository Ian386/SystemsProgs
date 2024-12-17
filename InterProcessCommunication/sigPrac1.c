#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <time.h>
#include <signal.h>

int main(int argc, char* argv[]){
    int pid = fork();
    if(pid == -1){
        printf("Fork failed\n");
        return 1;
    }
    if(pid == 0){
        // Child process
        while(1){
            printf("Child process running\n");
            usleep(50000);
        }

    }
    else{
        // Parent process
        kill(pid, SIGSTOP);
        int timeToRun;
        do{
            printf("Enter the time to run the child process: ");
            scanf("%d", &timeToRun);
            if(timeToRun > 0){
                kill(pid, SIGCONT);
                sleep(timeToRun);
                kill(pid, SIGSTOP); 
            }


        }while(timeToRun > 0);
        kill(pid, SIGKILL);
        wait(NULL);
    }
    return 0;
}   