#include<stdio.h>
int division(int a, int b, int * result);
int main(){
    int answer;
    if(division(10, 0, &answer) == 0){
        printf("Division is successful\n");
        printf("Result: %d\n", answer);
    }
    else{
        printf("Something went wrong\n");
    }
}
int division(int a, int b, int * result){
    if(b == 0){
        return -1; // Error code for division by zero
    }
    *result = a / b;
    return 0; // Success
}