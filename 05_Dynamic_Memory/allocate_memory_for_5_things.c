#include<stdio.h>
#include<stdlib.h>
int main(){
    int i,j;
    char *p[5];
    for(i=0;i<5;i++)
    p[i] = (char*)malloc(20*sizeof(char));

    for(i=0;i<5;i++){
        printf("Enter the value for p[%d]\n",i);
        scanf("%s",p[i]);
    }
    for(i=0;i<5;i++){
        printf("%s\n",p[i]);
    }

    for(i=0;i<5;i++)
        free(p[i]);
}