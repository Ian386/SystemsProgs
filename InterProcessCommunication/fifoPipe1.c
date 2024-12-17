#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <errno.h>
#include <fcntl.h>
#include <stdlib.h>
#include <time.h> 


int main(){
    int arr[5];
    srand(time(NULL));
    for(int i = 0; i < 5; i++){
        arr[i] = rand() % 100;
    }

    //sum fifo file is in the tmp directory
   int fd = open("/tmp/sum", O_WRONLY);
   if (fd == -1){
         printf("Failed to open FIFO\n");
         return 1;
   }

   for(int i=0; i<5; i++){
       if (write(fd, &arr[i], sizeof(int)) == -1){
           printf("Unable to write to FIFO Pipe\n");
           return 2;
       }
       printf("Written to FIFO Pipe: %d\n", arr[i]);
    }
    close(fd);
    return 0;
}