#include<stdio.h>
int main(){
    int a[] = {45,99,787,2432,98943,8978925,234,123,456,789,000001};
    int n = sizeof(a)/sizeof(a[0]);

    int biggest_ele = a[0],i;
    for(i=1;i<n;i++)
    if(a[i]>biggest_ele){
        biggest_ele = a[i];
    }

    printf("The biggest element in the array is: %d\n", biggest_ele);
}