#include<stdio.h>
int main(){
    char s[50];
    printf("enter the string\n");
    scanf("%[^\n]",s);

    int length,i,j;
    for(length =0;s[length]!='\0';length++);

    for(i=0;i<length-1;i++){
        if(s[i] == ' '){
        for(j=i;j<length;j++)
        s[j] = s[j+1];
        length--;
        i--;
        }
    }
    s[j] = '\0';
    printf("%s\n",s);
}