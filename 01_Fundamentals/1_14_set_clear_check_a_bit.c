#include<stdio.h>
int main(){
    int n, pos;
   /* 
    printf("Enter the position of the bit to set: ");
    scanf("%d", &pos);
    // Set the bit at the specified position

    n = n|(1<<pos);*/
   // printf("Number after setting the bit: %d\n", n);
printf("Enter a number: ");
    scanf("%d", &n);
   /* printf("Enter the position of the bit to clear: ");
    scanf("%d", &pos);
    // Clear the bit at the specified position
    n = n & ~(1<<pos);
    printf("Number after clearing the bit: %d\n", n);*/
// check the bit at the specified position
    printf("Enter the position of the bit to check: ");
    scanf("%d", &pos);
    if (n & (1 << pos)) {
        printf("The bit at position %d is set.\n", pos);
    } else {
        printf("The bit at position %d is not set.\n", pos);
    }
}