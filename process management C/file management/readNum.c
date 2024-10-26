// NAME: IAN NDOLO MWAU
// REG NO: SCT211-0034/2022



//The code below reads an integer from a file named Kenya.txt
//The integer is then printed to the console
//The file is then closed
# include <stdio.h>
# include <stdlib.h>


int main(){
    // Open the file in read mode
    FILE *fp;
    int readNum;
    fp = fopen("Kenya.txt", "r");
    if(fp == NULL){
        printf("Error opening file\n");
        exit(1);
    }
  
    //fscanf function returns the number of input items it successfully reads and assigns
    if (fscanf(fp, "%d", &readNum) == 1)
    {
        // Print the first integer found in the file
        printf("The first integer in Kenya.txt is: %d\n", readNum);
    }
    else
    {
        printf("No integer found in the file\n");
    }
    fclose(fp);
    return 0;
}