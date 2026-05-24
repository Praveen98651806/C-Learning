#include<stdio.h>

int main(void){
    int num;
    int ones_comp, twos_comp;
    printf("Enter the number: ");
    if (scanf("%d", &num) != 1) return 1;

    ones_comp = ~num;
    twos_comp = ones_comp + 1;

    printf("The ones complement (NOT) is: %d\n", ones_comp);
    printf("The twos complement is: %d\n", twos_comp);
    return 0;
}
