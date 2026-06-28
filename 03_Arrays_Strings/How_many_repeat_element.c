#include<stdio.h>
int main(){

    int a[] = {10, 20, 10, 30, 20, 40, 10, 50};
    int size = sizeof(a)/sizeof(a[0]);
    int count = 0,i,j;

    for(i=0;i<size;i++){
        for(j=0;j<i;j++){
            if(a[i] == a[j]){
                break;
            }
        }
        if(i ==j){
            for(j=j+1,count =1;j<size;j++){
                if(a[i] == a[j]){
                    count++;
                }
            }
            if(count > 1){
                printf("%d occurs %d times\n", a[i], count);
            }
            else if(count == 1){
                printf("%d occurs %d time\n", a[i], count);
            }
        }
    }
}