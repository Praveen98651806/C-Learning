#include<stdio.h>
int main(){

    int arr[] = {10,20,55,89,0,12,44,23232,98,-7};
    int size = sizeof(arr)/sizeof(arr[0]);
    int max,min,i;
    min=arr[0]; max=arr[0];

    for(i=0;i<size;i++){
        if(min>arr[i])
        min = arr[i];
        if(max<arr[i])
        max = arr[i];
    }
    printf("minimum number is %d\n",min);
    printf("maximum number is %d",max);
}