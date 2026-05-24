#include<stdio.h>
int main(){
    int num, power;
    printf("Enter a number: ");
    scanf("%d", &num);  
    printf("Enter the power of 2 to divide by: ");
    scanf("%d", &power);
    int result = num >> power;
    printf("Result of %d divided by 2^%d is: %d\n", num, power, result);
    return 0;   
}