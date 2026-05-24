#include<stdio.h>
int main(){
    int a = 0, b = 1, n;

    printf("Enter the number of Fibonacci terms to generate: ");
    int rc = scanf("%d", &n);
    if (rc != 1 || n < 0 || n == 0) {
        printf("Invalid input. Please enter a non-negative integer.\n");
        return 1;
    }

    printf("Fibonacci Series: ");
    printf("%d %d", a, b); // Print the first two terms
    for (int i = 2; i <n; i++){
        int next = a + b;
        a = b;
        b = next;
        printf(" %d", next);
    }
    printf("\n");
    return 0;
}
