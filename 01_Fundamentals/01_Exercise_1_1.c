#include<stdio.h>
int main(){
    float a, b, result;
    char operator;

    retry:
    printf("Enter the two digit values a and b:");
    scanf("%f %f", &a, &b);
    printf("Enter the operator:");
    scanf(" %c", &operator); // Read operator with leading space to skip whitespace

    switch(operator){
        case '+':
            result = a + b;
            printf("The Sum of the a and b is + %.3f",result);
            break;
        case '-':
            result = a - b;
            printf("The Difference of the a and b is - %.3f",result);
            break;

        case '*':
            result = a * b;
            printf("The Product of the a and b is * %.3f",result);
            break;

        case '/':
            if (b == 0) {
                printf("Division by zero is not allowed\n");
                goto retry;
            }
            result = a / b;
            printf("The Division of the a and b is / %.3f",result);
            break;
        default:
        printf("Invalid operator\n");
        goto retry;
    }
    return 0;
}