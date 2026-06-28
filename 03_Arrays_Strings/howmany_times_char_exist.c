#include<stdio.h>
int main(){
    char str[100];
    int i,count=0,str_length,j;
    printf("Enter a string: "); 
    scanf("%[^\n]", str);
    for(str_length=0;str[str_length]!='\0';str_length++);
    for(i=0;i<str_length;i++){
        for(j=0;(j<i)&& (str[i]!=str[j]);j++);
        if(i==j){
        for(j=i+1,count=1;j<str_length;j++){
            if(str[i]==str[j])
            count++;
        }
        printf("The character '%c' occurs %d times in the string.\n", str[i], count);
    }
    }


}