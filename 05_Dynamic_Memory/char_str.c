// Online C compiler to run C program online
#include <stdio.h>
#include <stdlib.h>
int main() {
    // Write C code here
    printf("Start small. Ship something.\n");
    char *p;
    int i;
    p = (char*)malloc(5*sizeof(char));
    
    if(p == NULL){
        printf("DMAI is failed to allocte the memory\n");
    }
    
    printf("Enter the value\n");
        scanf("%4s",p);

    printf("After memory and data allocated\n");
    printf("%s\n",p);
}