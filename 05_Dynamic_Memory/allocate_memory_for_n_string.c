#include<stdio.h>
#include<stdlib.h>
int main(){
    int i,j,n;

    char **p;
    printf("Enter the number of string that you want:\n");
    scanf("%d",&n);

    p = (char **)malloc(n*sizeof(char*));
    for(i=0;i<n;i++){
        p[i] = (char*)malloc(20*sizeof(char));
    }

    printf("Enter the %d strings:\n", n);
    for(i=0;i<n;i++){
        scanf("%s",p[i]);
    }

    printf("Display the strings\n");
    for(i=0;i<n;i++){
        printf("%s\n",p[i]);
    }

    for(i=0;i<n;i++){
        free(p[i]);
    }
    free(p);

    return 0;
}