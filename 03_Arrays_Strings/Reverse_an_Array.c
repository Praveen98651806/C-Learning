#include<stdio.h>
int main(){
    int arr[] = {10,20,30,40,50,60,70,80,90,100,110};
    int size = sizeof(arr)/sizeof(arr[0]);
    int i,j,temp;

    for(i = 0,j = size-1;i<j;i++,j--){
        temp = arr[i];
        arr[i] = arr[j];
        arr[j] = temp;
    }
    for(i=0;i<size;i++)
    printf("%d ",arr[i]);
}