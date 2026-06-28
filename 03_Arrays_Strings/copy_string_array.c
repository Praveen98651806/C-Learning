#include<stdio.h>
int main(){
    char src[100],dest[100];
    int length,i;
    printf("Enter a string: ");
    scanf("%s", src);
    for(i=0;src[i]!='\0' && (dest[i]=src[i]);i++);
    dest[i] = '\0';
    printf("Copied string: %s\n", dest);
}