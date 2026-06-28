#include<stdio.h>
int main(){
    char s[50];
    printf("Enter the number\n");
    scanf("%[^\n]",s);

    int i;
    for(i=0;s[i]!='\0';i++){
        if(s[i]==' ')
        i++;
        if(s[i]>=65 && s[i]<=90)
        s[i]=s[i]+32;
        else if(s[i]>=97 && s[i]<=122)
        s[i]=s[i]-32;
    }
    s[i]='\0';
    printf("%s\n",s);
}