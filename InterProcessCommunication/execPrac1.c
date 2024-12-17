#include <stdio.h>
#include <stdlib.h>
// #include <unistd.h>
#include <string.h>
#include <process.h>


int main(int argc, char * argv[]){
    execlp("ping", "ping", 
    "www.google.com", 
    NULL);
    printf("Ping executed successfully\n");
    return 0;
}


