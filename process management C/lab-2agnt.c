// NAME: IAN NDOLO MWAU
// REG NO: SCT211-0034/2022

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h> 



int main()
{
    // The fork() system call is used to create a new process by duplicating the existing process. The new process is called the child process, and the existing process is called the parent process.
    int c = 5;
    pid_t pid = fork(); //first fork

    if (pid == 0)
    {
        c += 5;//child process
    }
    else
    {
        pid = fork();//second fork
        c += 10;// parent process and child process
        if (pid)
        {
            c += 10;//parent process
        }
    }

    fork();//third fork -- 6processes formed
    printf("%d\n", c);//6 processes execute

    return 0;
}
