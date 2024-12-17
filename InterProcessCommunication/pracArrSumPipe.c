#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

int main(int argc, char *argv[]){
    int arr[]={1,2,3,4,5, 6, 7, 8, 9, 10};
    int arrSize = sizeof(arr)/sizeof(arr[0]);
    int start, end;
    int pipefds[2];
    if (pipe(pipefds) == -1){
        printf("Unable to create pipe\n");
        return 1;
    }
    int pid = fork();
    if(pid == -1){
        printf("Unable to fork\n");
        return 2;
    }
    else if (pid == 0){
        start = 0;
        end = start + arrSize/2;
    }
    else{
        start = arrSize/2;
        end = arrSize;
    }
    int sum = 0;
    for(int i=start; i<end; i++){
        sum += arr[i];
    }

    printf("Sum of the array elements from %d to %d is %d\n", start, end, sum);

    if(pid == 0){
        close(pipefds[0]);
        write(pipefds[1], &sum, sizeof(sum));
        close(pipefds[1]);

    }
    else{
        close(pipefds[1]);
        int sumFromChild;
        read(pipefds[0], &sumFromChild, sizeof(sumFromChild));
        close(pipefds[0]);
        int totalSum = sum + sumFromChild;
        printf("Total Sum of the array elements is %d\n", totalSum);
        wait(NULL);
    }
    return 0;
}