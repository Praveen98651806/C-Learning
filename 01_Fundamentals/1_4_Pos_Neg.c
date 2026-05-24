#include<stdio.h>
int main(){
    int a;
    printf("Enter the number:");
    int rc = scanf("%d",&a);
    
    if (rc != 1) {
        // scanf failed to read an int
        printf("Invalid input\n");
        return 1;
    }


    if(a > 0){
        printf("Given number %d is Positive Number", a);
    }
    else if(a < 0){
        printf("Given number %d is Negative Number", a);
    }
    else if( a==0 ){
        printf("Given number %d is Zero", a);
    }
    else{
        printf("Invalid input");
    }
}