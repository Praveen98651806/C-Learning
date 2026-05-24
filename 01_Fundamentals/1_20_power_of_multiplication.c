#include<stdio.h>
int main(){
    int num, power;
    printf("Enter the number and power: ");
    scanf("%d%d", &num, &power);
    int result = 1;
    result = num <<2;
    printf("%d to the power of %d is: %d\n", num, power, result);
}