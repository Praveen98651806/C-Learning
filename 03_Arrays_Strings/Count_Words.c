#include<stdio.h>
int main(){

    int length,i,count=1;
    char str[100];
    printf("Enter the sentence:\n");
    scanf("%[^\n]",str);
    for(length=0;str[length]!='\0';length++);

    for(i=0;i<length;i++){
        if(str[i]==' ')
        count++;
        if(str[i]=='\0')
        break;
    }
    printf("No of words %d\n",count);
}