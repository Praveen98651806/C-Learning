#include<stdio.h>
int main(){

    char s[30];
    char c;
    int i,j,count=0;
    printf("Enter the string\n");
    scanf("%[^\n]",s);
    printf("Enter the Character\n");
    scanf(" %c",&c);

    printf("%s\n",s);
    for(i=0;s[i]!='\0';i++);
    for(j=0;j<i-1;j++){
        if(s[j] == c)
        count++;
    }

    printf("Count - %d",count);
}