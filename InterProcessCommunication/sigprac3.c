#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <time.h>
#include <signal.h>


int result=0;

void handle_sigusr1(int sig){
    if(result == 0){
        printf("\n(HINT): Remember to add slowly\n");
    }

    // fflush(stdout);
}



int main(int argc, char* argv[]){
    int pid = fork();
    if(pid == -1){
        printf("Fork failed\n");
        return 1;
    }
    if(pid == 0){
        sleep(5);
        //send signal to parent 
        kill(getppid(), SIGUSR1);
    }
    else{
        //Parent process
        struct sigaction sa = {0};    
        sa.sa_flags = SA_RESTART;
        sa.sa_handler = &handle_sigusr1;
        sigaction(SIGUSR1, &sa, NULL);

        printf("What is the result of 2+2?\n");
       
        scanf("%d", &result);
        if(result == 4){
            printf("Correct\n");
        }
        else{
            printf("Incorrect\n");
        }
        wait(NULL);
    }
    return 0;
}