/* Write another program using fork(). The child process need to print “Niko Juja” and the parent process to print “ ICS2305 ni softlife” . The child process should print first ---this can be done without calling wait() in the parent..
Hint : use of for loop and sleep */

// NAME: IAN NDOLO MWAU
// REG NO: SCT211-0034/2022

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>

int main(int args, char *argv[])
{
    pid_t pid = fork();//forking the process

    if (pid == 0)//child process
    {
        for (int i = 0; i < 3; i++)
        {
            sleep(1);//let the child process sleep for 1 second
        }
        printf("Niko Juja\n");
    }
    else if (pid > 0)
    {
        for (int i = 0; i < 3; i++)
        {
            // let the parent process sleep for 2 seconds
            sleep(2);
        }
        printf("ICS2305 ni softlife\n");
    }
    else
    {
        printf("Fork failed\n");
    }
    

    return 0;
}