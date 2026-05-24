#include<stdio.h>
int main(){
    int a;
    printf("Enter the number:");
    int rc = scanf("%d",&a);

    if(rc != 1){
        printf("Scanf faild to get expected input\n");
        return 1;
    }

    printf("\nMultiplication table of %d:\n", a);
    printf("==========================\n");
    for(int i = 1;i <= 10;i++){
        printf("%d * %d  = %d\n", a,i,a*i);
    }
}