#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

int main(int argc, char *argv[])
{
    int arr[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    int arrSize = sizeof(arr) / sizeof(arr[0]);
    int pipefds[2][2]; // Two pipes to communicate with child processes
    int start, end;

    // Create pipes
    for (int i = 0; i < 2; i++)
    {
        if (pipe(pipefds[i]) == -1)
        {
            printf("Unable to create pipe %d\n", i);
            return 1;
        }
    }

    // Fork the first child process
    int pid1 = fork();
    if (pid1 == -1)
    {
        printf("Unable to fork process 1\n");
        return 2;
    }

    if (pid1 == 0)
    {
        // Child Process 1: Handles first third of the array
        close(pipefds[0][0]); // Close read end of first pipe
        start = 0;
        end = arrSize / 3;
        int sum = 0;
        for (int i = start; i < end; i++)
        {
            sum += arr[i];
        }
        write(pipefds[0][1], &sum, sizeof(sum));
        close(pipefds[0][1]); // Close write end of first pipe
        return 0;
    }

    // Fork the second child process
    int pid2 = fork();
    if (pid2 == -1)
    {
        printf("Unable to fork process 2\n");
        return 3;
    }

    if (pid2 == 0)
    {
        // Child Process 2: Handles second third of the array
        close(pipefds[1][0]); // Close read end of second pipe
        start = arrSize / 3;
        end = 2 * arrSize / 3;
        int sum = 0;
        for (int i = start; i < end; i++)
        {
            sum += arr[i];
        }
        write(pipefds[1][1], &sum, sizeof(sum));
        close(pipefds[1][1]); // Close write end of second pipe
        return 0;
    }

    // Parent process: Handles last third of the array and aggregates results
    start = 2 * arrSize / 3;
    end = arrSize;
    int sum = 0;
    for (int i = start; i < end; i++)
    {
        sum += arr[i];
    }

    // Read results from child processes
    close(pipefds[0][1]); // Close write end of first pipe
    close(pipefds[1][1]); // Close write end of second pipe
    int sumFromChild1, sumFromChild2;
    read(pipefds[0][0], &sumFromChild1, sizeof(sumFromChild1));
    read(pipefds[1][0], &sumFromChild2, sizeof(sumFromChild2));
    close(pipefds[0][0]); // Close read end of first pipe
    close(pipefds[1][0]); // Close read end of second pipe

    int totalSum = sum + sumFromChild1 + sumFromChild2;

    printf("Sum from Child 1: %d\n", sumFromChild1);
    printf("Sum from Child 2: %d\n", sumFromChild2);
    printf("Sum from Parent: %d\n", sum);
    printf("Total Sum of the array elements is %d\n", totalSum);

    // Wait for child processes to finish
    wait(NULL);
    wait(NULL);

    return 0;
}
