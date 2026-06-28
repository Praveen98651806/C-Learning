#include<stdio.h>
int main(){
   int a[] = {12,34,56,77,19,17,11,13,15,16,10,1,2,3,87};
   int n = sizeof(a)/sizeof(a[0]);
   int i,j,count=0;
   for(i=0;i<n;i++){
         for(j=1;j<=a[i]/2;j++){
            if(a[i]%j == 0){
               count++;
            }
         }
         if(count == 1){
            printf("%d is a prime number\n", a[i]);
         }
         count = 0;
   }
}