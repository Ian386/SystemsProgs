#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int main()
{
    int pipe1[2], pipe2[2]; // Two pipes for bidirectional communication
    pid_t child1, child2;
    char buffer[100];

    // Create the first pipe
    if (pipe(pipe1) == -1)
    {
        perror("pipe1 failed");
        exit(1);
    }

    // Fork the first child
    child1 = fork();
    if (child1 < 0)
    {
        perror("fork failed");
        exit(1);
    }

    if (child1 == 0)
    {                    // Child 1 process
        close(pipe1[0]); // Close the read end of the first pipe

        // Child 1 writes data into the pipe
        char message1[] = "Message from Child 1";
        write(pipe1[1], message1, sizeof(message1));

        close(pipe1[1]); // Close the write end of the first pipe
        exit(0);         // Exit child 1
    }

    // Create the second pipe
    if (pipe(pipe2) == -1)
    {
        perror("pipe2 failed");
        exit(1);
    }

    // Fork the second child
    child2 = fork();
    if (child2 < 0)
    {
        perror("fork failed");
        exit(1);
    }

    if (child2 == 0)
    {                    // Child 2 process
        close(pipe1[1]); // Close the write end of the first pipe
        close(pipe2[0]); // Close the read end of the second pipe

        // Child 2 reads data from the first pipe
        read(pipe1[0], buffer, sizeof(buffer));
        printf("Child 2 received: %s\n", buffer);

        // Child 2 writes a response into the second pipe
        char message2[] = "Message from Child 2";
        write(pipe2[1], message2, sizeof(message2));

        close(pipe1[0]); // Close the read end of the first pipe
        close(pipe2[1]); // Close the write end of the second pipe
        exit(0);         // Exit child 2
    }

    // Parent process
    close(pipe1[0]); // Close the read end of the first pipe
    close(pipe1[1]); // Close the write end of the first pipe
    close(pipe2[1]); // Close the write end of the second pipe

    // Parent reads the response from Child 2 through the second pipe
    read(pipe2[0], buffer, sizeof(buffer));
    printf("Parent received: %s\n", buffer);

    close(pipe2[0]); // Close the read end of the second pipe

    return 0;
}
