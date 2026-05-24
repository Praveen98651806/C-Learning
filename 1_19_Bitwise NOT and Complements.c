#include<stdio.h>
int main(){
    int num,tow_comp;
    printf("Enter the numbet:");
    scanf("%d",&num);

    num = ~num;
    tow_comp = num +1;

    printf("The ones complement is(means NOT): %d\n",num);
    printf("The twos complement is: %d",tow_comp);
}