#include <stdio.h>

// Exercise 1.5 Solution: Multiplication Table

int main() {
    int num;
    
    printf("Enter a number: ");
    scanf("%d", &num);
    
    printf("\nMultiplication table of %d:\n", num);
    printf("==========================\n");
    
    for (int i = 1; i <= 10; i++) {
        printf("%d * %d = %d\n", num, i, num * i);
    }
    
    return 0;
}
