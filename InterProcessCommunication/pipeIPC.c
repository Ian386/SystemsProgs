#include <stdio.h>
#include <unistd.h>


int main(){
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
        close(pipefds[0]);
        int n;
        printf("Enter a number to write into Pipe\n");
        scanf("%d", &n);
        if(write(pipefds[1], &n, sizeof(int)) == -1){
            printf("Unable to write to pipe\n");
            return 2;
        }
        close(pipefds[1]);
    }
    else{
        close(pipefds[1]);
        int n;
        if(read(pipefds[0], &n, sizeof(int)) == -1){
            printf("Unable to read from pipe\n");
            return 3;
        }
        n = n*2;
        close(pipefds[0]);
        printf("Parent Process: Reading from pipe – Number is %d\n", n);

    }

}