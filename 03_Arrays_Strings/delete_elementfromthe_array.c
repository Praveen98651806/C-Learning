#include<stdio.h>
int main(){
    int a[] = {10,20,30,40,50,60,70,80,90,100};
    int n = sizeof(a)/sizeof(a[0]);
    int pos,j,i;

    printf("Enter the position of the element to delete: ");
    scanf("%d",&pos);

    if(pos<0 || pos>11){
        printf("Invalid position!\n");
    } else {
        for(i=0;i<n;i++){
            if(i+1 == pos){
                for(j=i;j<n-1;j++){
                    a[j] = a[j+1];
                }
            }
        }
        n--; // Decrease the size of the array after deletion
        printf("Array after deletion: ");
        for(i=0;i<n;i++){
            printf("%d ",a[i]);
        }
    }
}