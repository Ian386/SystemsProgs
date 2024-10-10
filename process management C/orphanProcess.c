#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>

int main()
{
    pid_t pid = fork();

    if (pid > 0)
    {
        // Parent process
        printf("Parent process (PID: %d) is exiting...\n", getpid());
        exit(0); // Parent exits
    }
    else if (pid == 0)
    {
        // Child process
        sleep(5); // Sleep for 5 seconds to ensure parent exits first
        printf("Orphan child process (PID: %d, Parent PID: %d)\n", getpid(), getppid());
        // At this point, the parent PID should be 1 (adopted by init)
    }
    else
    {
        perror("fork failed");
    }

    return 0;
}
