#include<stdio.h>
int main(){

    char s[] = "praveen", temp;
    int i,j,k,length;
    printf("%s\n",s);
    for(length=0;s[length]!='\0';length++);

    for(i = 0,j=length-1; i<j;i++,j--){
            temp = s[i];
            s[i] = s[j];
            s[j] = temp;
    }
    printf("%s\n",s);
}