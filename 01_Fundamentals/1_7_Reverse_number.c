#include<stdio.h>
int main(){
    int a;
    printf("Enter the number:");
    int rc = scanf("%d",&a);

    if(rc != 1){
        printf("Scanf failed to get expected input\n");
        return 1;
    }
    if (a == 0) {
        printf("Zero is not supported\n");
        return 1;
    }
    if (a < 0) {
        printf("Negative numbers are not supported\n");
        return 1;
    }
    int rev = 0;
    while(a != 0){
    int rem = a % 10;
    rev = (rev * 10) + rem;
    a = a / 10;
    }

    printf("The reverse of the number is %d\n", rev);


}