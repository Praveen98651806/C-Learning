#include<stdio.h>
int main(){
    int i,j,k=0,length;
    char str[100],str1[100];
        printf("Enter the sentence:\n");
    scanf("%[^\n]",str);

    for(length=0;str[length]!='\0';length++); //outer loop iterate till end of string
    for(i=length;i>=0;i--){  // inner loop for each space break
        if(str[i] == ' '){
            for(j=i+1;str[j]!=' ' && str[j]!='\0';j++,k++)
                str1[k]=str[j];
                  str1[k]=' ';
                  k++;
        }
    }
    for(i=0;str[i]!= ' ' && str[i]!= '\0'; str1[k++]=str[i++]);
    str1[length] = '\0';
    printf("%s\n",str1);
}