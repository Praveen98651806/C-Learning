#include<stdio.h>
int main(){

    char s[20];
    int i,j,length;
    scanf("%s",s);
    printf("%s\n",s);
    for(length=0;s[length]!=0;length++);
    for(i=0,j=length-1;i<j;i++,j--){
        if(s[i] != s[j])
        break;
    }

    if(i<j)
    printf("%s is not a palindrom",s);
    else
    printf("%s is a palindrom",s);

}