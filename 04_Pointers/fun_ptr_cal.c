#include<stdio.h>
int sum(int,int);
int sub(int,int);
int mul(int,int);
int div(int,int);
int mod(int,int);
int main(){


    int a,b,result;
    printf("Enter two numbers: ");
    scanf("%d %d",&a,&b);

    char op;
    printf("Enter operation (+, -, *, /, %): ");
    scanf(" %c", &op);

    int (*fp)(int,int);

    switch(op){
        case '+':
            fp = sum;
            break;
        case '-':
            fp = sub;
            break;
        case '*':
            fp = mul;
            break;
        case '/':
            fp = div;
            break;
        case '%':
            fp = mod;
            break;
        default:
            printf("Invalid operation\n");
            return 1;
    }
    
    result = fp(a,b);
    printf("Result: %d\n", result);
}
    int sum(int x, int y){
        return x + y;
    }
    int sub(int x, int y){
        return x - y;
    }
    int div(int x, int y){
        return x / y;
    }
    int mul(int x, int y){
        return x * y;
    }
    int mod(int x, int y){
        return x % y;
    }