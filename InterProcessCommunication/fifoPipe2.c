#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <errno.h>
#include <fcntl.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    int arr[5];
    int fd = open("/tmp/sum", O_RDONLY);
    if (fd == -1)
    {
        printf("Failed to open FIFO\n");
        return 1;
    }   
    int i;
    for (i = 0; i < 5; i++)
    {
        if (read(fd, &arr[i], sizeof(int)) == -1)
        {
            printf("Unable to read from FIFO Pipe\n");
            return 2;
        }
        printf("Read from FIFO Pipe: %d\n", arr[i]);
    }
    close(fd);
    int sum = 0;
    for (i = 0; i < 5; i++)
    {
        sum += arr[i];
    }
    printf("Sum of the numbers: %d\n", sum);
    

    return 0;
}