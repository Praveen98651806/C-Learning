#include<stdio.h>
int main()
{
    int num,pos;
    printf("Enter the number and position:");
    scanf("%d%d",&num,&pos);
    num = num ^ (1 << pos);
    printf("The new number after toggling the bit is: %d",num);

}