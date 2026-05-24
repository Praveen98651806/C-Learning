#include<stdio.h>
int main(){
    int a, fact = 1;
    printf("Enter the Number:");
    int rc = scanf("%d",&a);
    if(rc != 1){
        printf("Scanf failed to get expected input\n");
        return 1;
    }

    if(a == 0){
        printf("Zero is not supported\n");
        return 1;
    }
    if (a < 0)
    {
        printf("Negative numbers are not supported\n");
        return 1;
    }
    while(a != 0){
            //fact = fact * a;
            fact *= a;
            a--;
    }
    printf("The factorial is %d\n", fact);
}