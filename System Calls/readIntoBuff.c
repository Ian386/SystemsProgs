#include <unistd.h>
#include <stdio.h>
#include <errno.h>
#include <fcntl.h>

// Write a function foo(int fd, char *buf, int b_size, int n, int skip) that reads to buf
//     from file with file descriptor fd,
//     n blocks of size b_size each.The last argument
//         specifies how many bytes to skip after reading each block.Return
//         - 1 if the
//           operation is unsuccessful.Else return total number of bytes read.

int foo(int fd, char *buf, int b_size, int n, int skip)
{
    if (fd < 0 || buf == NULL || b_size <= 0 || n <= 0 || skip < 0)
    {
        return -1; // Invalid arguments
    }

    int total_bytes_read = 0; // Total number of bytes read
    int bytes_read = 0;       // Number of bytes read in each iteration

    for(int i=0; i<n; i++)
    {
      if((bytes_read = read(fd, buf, b_size)) == -1)
      {
        return -1; // Error reading from file
      }
        total_bytes_read += bytes_read;

        // If the bytes read is less than b_size, the file might be too small
        if (bytes_read < b_size)
        {
            break; // No more data to read
        }

        // Skip the specified number of bytes
        if (lseek(fd, skip, SEEK_CUR) == -1)
        {
            return -1; // Error skipping bytes
        }

    }

    return total_bytes_read;


}

int main()
{
    char buf[100] = {0};
    int fd = open("./Angukanayo.txt", O_RDONLY | O_CREAT, 0777);
    int bytes_read = foo(fd, buf, 10, 3, 5);
    if (bytes_read == -1)
    {
        perror("Error reading file");
    }
    else
    {
        printf("Total bytes read: %d\n", bytes_read);
    }
    return 0;
}