#include<stdio.h>
int main()
{
    int num,pos;
    printf("Enter the number and position to set the bit: ");
    scanf("%d%d",&num,&pos);


    if(num & (1 << pos)) {
        printf("The bit is already set");
    }
    else {
        num = num | (1 << pos);
        printf("The new number after setting the bit is: %d",num);
    }
}