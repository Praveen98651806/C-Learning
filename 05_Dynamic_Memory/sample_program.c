// Online C compiler to run C program online
#include <stdio.h>
#include <stdlib.h>
int main() {
    // Write C code here
    printf("Start small. Ship something.\n");
    int *p,i;
    p = (int*)malloc(5*sizeof(int));
    
    if(p == NULL){
        printf("DMAI is failed to allocte the memory\n");
    }
    
    printf("Enter the value\n");
    for(i=0;i<5;i++){
        scanf("%d",&p[i]);
    }
    
    printf("After memory and data allocated\n");
    for(i=0;i<5;i++)
    printf("%d ",p[i]);
}