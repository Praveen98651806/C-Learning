#include<stdio.h>
int main(){
    char src[100],dest[100];
    int length,i;
    printf("Enter a string: ");
    scanf("%s", src);
    printf("Enter the number of characters to copy: ");
    scanf("%d", &length);
    for(i=0;i<length && (dest[i] = src[i]) ;i++);
    dest[i] = '\0';
    printf("Copied string: %s\n", dest);
}