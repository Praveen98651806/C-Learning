#include<stdio.h>
int main(){
    int i =0,n;
    printf("Enter the number of rows:");
    scanf("%d",&n);
    for(i =0;i<n;i++){
        for(int j = 0;j<=i;j++)
        printf("*");
        printf("\n");
    }
}