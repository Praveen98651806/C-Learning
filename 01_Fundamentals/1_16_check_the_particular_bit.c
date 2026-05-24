#include<stdio.h>
int main()
{
    int pos,num;
    printf("Enter the number and position to check the bit: ");
    scanf("%d%d",&num,&pos);
    if(num&(1<<pos))
        printf("The bit is set");
    else
        printf("The bit is not set");
}