#include<stdio.h>
int main(){
    int a[] = {45,99,787,2432,98943,8978925,234,123,456,789,000001,8978924};
    int n = sizeof(a)/sizeof(a[0]);

    int biggest_ele = a[0],i;
    int second_biggest_ele = a[0];
    for(i=1;i<n;i++)
    if(a[i]>biggest_ele){
        biggest_ele = a[i];
    }
    for(i=1;i<n;i++){
    if((a[i]<biggest_ele) && (a[i]>second_biggest_ele)){
        second_biggest_ele = a[i];
    }}

    printf("The biggest element in the array is: %d\n", biggest_ele);
    printf("The second biggest element in the array is: %d\n", second_biggest_ele);
}