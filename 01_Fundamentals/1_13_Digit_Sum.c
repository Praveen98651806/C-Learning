#include<stdio.h>
int main(){
    int nadd=0, n, add=0;
    printf("Enter a number:");

    int rc = scanf("%d", &n);
    if(rc!=1){
        printf("Invalid input\n");
        return 1;
    }

    while(n!=0){
        
        int rem = n%10;
        add = add + rem;
        n = n/10;
    }
    printf("Sum of digits: %d\n", add);
}