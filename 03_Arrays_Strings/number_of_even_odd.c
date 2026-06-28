#include<stdio.h>
int main(){
    int a[] = {10, 20, 15, 30, 27, 40, 11, 50};
    int n = sizeof(a)/sizeof(a[0]);
    int even_num = 0, odd_num = 0,i;
    for(i=0;i<n;i++){
        if(a[i]%2 == 0){
            even_num ++;
        }
        else{
            odd_num ++;
        }
    }
    printf("Number of even numbers: %d\n",even_num);
    printf("Number of odd numbers: %d\n",odd_num);
}