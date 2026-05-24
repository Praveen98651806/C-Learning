#include<stdio.h>
int main(){
    printf("Enter the value to convert from celsius to fahrenheit:");
    float celsius, fahr;

    scanf("%f",&celsius);

    fahr = (celsius * 9/5) + 32;

    printf("The value of %f in fahrenheit is %f",celsius,fahr);
}