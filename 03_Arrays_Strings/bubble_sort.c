#include<stdio.h>
int main(){
    int a[] = {45,99,787,2432,98943,8978925,234,123,456,789,000001,8978924,000};
    int n = sizeof(a)/sizeof(a[0]);
    int i,j,temp;
    int size = n;
    for(i=0;i<size-1;i++){
        for(j=0;j<size-1;j++){
            if(a[j]>a[j+1]){
                temp=a[j];
                a[j]=a[j+1];
                a[j+1]=temp;
            }
            
        }
    }
    for(i=0;i<n;i++){
        printf("%d ",a[i]);
    }
}