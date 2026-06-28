#include<stdio.h>
int main(){

    int i,j,k=0,length;
    char str[100],str1[100];
    printf("Enter the sentence:\n");
    scanf("%[^\n]",str);

    for(length=0;str[length]!='\0';length++);
    printf("%d length\n", length);
    for(i=length;i>=0;i--){
        if(str[i] == ' '){
            for(j=i+1;str[j] != '\0' && str[j] != ' ';j++,k++){
                str1[k] = str[j];
            }
        // Append a space after the word in our new string
            str1[k] = ' ';
            k++;  
        }
    }
    for(j=0;str[j]!='\0' && str[j]!=' ';j++){
        str1[k] = str[j];
        k++;
    }
    str1[length]='\0';
    printf("%s\n", str1);
    return 0;
}