//NAME: IAN NDOLO MWAU
//REG NO: SCT211-0034/2022

//The code below writes an integer to a file named Kenya.txt
//The integer is input by the user
//The file is created if it does not exist
//If the file exists, the integer is written to the file
//The file is then closed
#include <stdio.h>
#include <stdlib.h>


int main(){
    FILE *fp;
    int integer;
    printf("Enter an integer to put into a notepad file: ");
    scanf("%d", &integer);
    fp = fopen("Kenya.txt", "w");
    if(fp == NULL){
        printf("Error opening file\n");
        exit(1);
    }
    fprintf(fp, "%d", integer);
    fclose(fp);
    //fputw adds more complexity to the program without any added benefit
    //fprintf is suitable due to its formated output capabilities
}