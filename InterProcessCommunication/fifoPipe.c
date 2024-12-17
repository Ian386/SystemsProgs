#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <errno.h>
#include <fcntl.h>

int main(int argc, char *argv[])
{
    // Create the FIFO named pipe
    if (mkfifo("myfifo1", 0777) == -1)
    {
        if (errno != EEXIST)
        {
            printf("Unable to create FIFO Pipe\n");
            return 1;
        }
    }

    printf("Opening FIFO...\n");
    // Open the FIFO for writing
    int fd = open("myfifo1", O_WRONLY);
    if (fd == -1)
    {
        printf("Failed to open FIFO\n");
        return 2;
    }

    printf("FIFO opened for writing...\n");
    int x = 79;
    // Write data to the FIFO
    if (write(fd, &x, sizeof(int)) == -1)
    {
        printf("Unable to write to FIFO Pipe\n");
        return 3;
    }
    printf("Written to FIFO Pipe: %d\n", x);

    // Close the FIFO
    close(fd);
    printf("Closed FIFO Pipe\n");

    return 0;
}
