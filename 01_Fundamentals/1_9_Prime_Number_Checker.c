#include<stdio.h>
int main(){
    int a;
    printf("Enter the Number:");
    int rc = scanf("%d",&a);

    if(rc != 1){
        printf("Invalid input\n");
        return 1;   
    }
    if (a == 0){
        printf("0 is not a prime number\n");
        return 0;
    }

    if (a == 1){
        printf("1 is not a prime number\n");
        return 0;
    }
    if (a < 0){
        printf("Negative numbers are not prime\n");
        return 0;
    }
    int count = 0,i;
    for(i = 2;i <= a/2; i++){
        if(a % i ==0){
            count++;
            break;
        }
    }

    if(count == 0){
        printf("%d is a prime number\n",a);
    }
    else{
        printf("%d is not a prime number\n",a);
    }
}