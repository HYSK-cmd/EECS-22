/* Name: Hoon Yang        */
/* Date: Jan 8th, 2025    */
/* Program Title: Matrix  */
#include <stdio.h>
int main(void){
    int a[2][2];
    int b[2][2];
    int mult[2][2];
    //Take an input of each element of matrix A
    printf("Enter the first matrix(a) that will be multiplied:\n");
    for(int i = 0; i < 2; i++){
        for(int j = 0; j < 2; j++){
            while(1){
                printf("a%d%d = ", i+1, j+1);
                //Verify an input
                //If it's a number, break and go take a next input
                if(scanf("%d", &a[i][j]) == 1){
                    break;
                } else {
                    //If it's not a number, prompt an error message and clear the input before new input gets entered
                    printf("ERROR: Invalid input. Please enter numbers only!");
                    while (getchar() != '\n');
                    printf("\n");
                }
            }
        }
    }
    //Take an input of each element of matrix B
    printf("Enter the first matrix(b) that will be multiplied:\n");
    for(int i = 0; i < 2; i++){
        for(int j = 0; j < 2; j++){
            while(1){
                //Verify an input
                //If it's a number, break and go take a next input
                printf("b%d%d = ", i+1, j+1);
                if(scanf("%d", &b[i][j]) == 1){
                    break;
                } else {
                    //If it's not a number, prompt an error message and clear the input before new input gets entered
                    printf("ERROR: Invalid input. Please enter numbers only!");
                    while (getchar() != '\n');
                    printf("\n");
                }
            }
        }
    }
    //Multiply each corresponding element in matrix A and B together
    for(int i = 0; i < 2; i++){
        for(int j = 0; j < 2; j++){
            //I found the redundant indices after writing out i&j index of each element
            //Created a for loop instead of manually putting each multiplied element in the mult matrix
            mult[i][j] = a[i][0]*b[0][j] + a[i][1]*b[1][j]; 
        }
    }
    //Print out the result of 2x2 matrix
    printf("Result:\n");
    for(int i = 0; i < 2; i++){
        for(int j = 0; j < 2; j++){
            printf("%d", mult[i][j]);
            if(j == 0){
                printf(" ");
            }
        }
        printf("\n");
    }
    return 0;
}
