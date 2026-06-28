#include<stdio.h>
int main(){
    char str[100];
    int i,length,j;
    printf("Enter a string: ");
    scanf("%s", str);

    for(length=0;str[length]!='\0';length++);
    for(i=0,j=length-1;i<j;i++,j--){
        if(str[i] != str[j]){
            printf("The string is not a palindrome.\n");
            break;
        }
    }
    if(i<j){
        printf("The string is not a palindrome.\n");
    } else {
        printf("The string is a palindrome.\n");
    }
}