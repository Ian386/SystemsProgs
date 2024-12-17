#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <time.h>
#include <signal.h>


void handle_sigstp(int sig){
    printf("Stop not allowed\n");
    fflush(stdout);

}

void handle_sigcont(int sig){
   printf("Input number: \n");
}

int main(int argc, char *argv[]){
    // struct sigaction sa;
    // sa.sa_handler = &handle_sigstp;
    // sa.sa_flags = SA_RESTART;
    // sigaction(SIGTSTP, &sa, NULL);

    struct sigaction sa2;
    sa2.sa_handler = &handle_sigcont;
    sa2.sa_flags = SA_RESTART;
    sigaction(SIGCONT, &sa2, NULL);

    // signal(SIGTSTP, &handle_sigstp);

    int x;
    printf("Enter a number: ");
    scanf("%d", &x);
    printf("Entered number: %d\n", x);

    
    return 0;
}