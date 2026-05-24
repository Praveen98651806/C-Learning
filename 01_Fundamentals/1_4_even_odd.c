#include<stdio.h>
int main(){
    int a;
    printf("Enter the number:");
    int rc = scanf("%d",&a);


    if(rc != 1){
        printf("Scanf faild to get expected input\n");
        return 1;
    }

    if(a%2 == 0){
        printf("Given number %d is Even Number", a);
    }
    else if(a%2 != 0){
        printf("Given number %d is Odd Number", a);
    }
    else if( a==0 ){
        printf("Given number %d is Zero", a);
    }
    else{
        printf("Invalid input");
    }
}