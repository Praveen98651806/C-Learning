#include<stdio.h>
int main(){
    int a[] = {10, 20, 10, 30, 20, 40, 10, 50};
    int n = sizeof(a)/sizeof(a[0]);
    int b[n],i;
    for(i=0;(i<n)&&(b[i]=a[i]);i++);
    for(i=0;i<n;i++){
        printf("%d ",b[i]);
    }
}