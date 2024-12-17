#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <time.h>

// 2 processes
//  child process generate random numbers and send them to parent process
// parent process receives the numbers and sums them up

int main(int argc, char* argv[]){
    int fd[2];
    if(pipe(fd) == -1){
        printf("Pipe failed\n");
        return 1;
    }
    int pid = fork();
    if(pid == -1){
        printf("Fork failed\n");
        return 2;
    }
    if(pid == 0){
        // Child process
        close(fd[0]);
        int n,i;
        int arr[10];
        srand(time(NULL));
        n = rand() % 10 + 1;
        printf("Generating: ");
        for(i=0; i<n; i++){
            arr[i] = rand() % 11;
            printf("%d ", arr[i]);
        }
        printf("\n");
        if(write(fd[1], &n, sizeof(int)) == -1){
            printf("Write n failed\n");
            return 4;
        }
        if(write(fd[1], arr, sizeof(int) * n) == -1){
            printf("Write failed\n");
            return 3;
        }
        close(fd[1]);

    }else{
        //parent process
        close(fd[1]);
        int arr[10];
        int n, i, sum = 0;
        if(read(fd[0], &n, sizeof(int)) == -1){
            printf("Read n failed\n");
            return 5;
        }
        printf("Received n: %d\n", n);
        if(read(fd[0], arr, sizeof(int) * n) == -1){
            printf("Read failed\n");
            return 4;
        }
        printf("Received array\n");
        close(fd[0]);
        for(i=0; i<n; i++){
            sum += arr[i];
        }
        printf("Sum: %d\n", sum);
        wait(NULL);

    }
    return 0;
}