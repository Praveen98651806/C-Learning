#include<stdio.h>
int main(){
    char str1[100],str2[100];
    int i,j,str1_length,str2_length;
    printf("Enter the first string: ");
    scanf("%[^\n]", str1);
    getchar(); // To consume the newline character left by previous input
    printf("Enter the second string: ");
    scanf("%[^\n]", str2);
    // Concatenate str1 to str2
    for(str2_length=0;str2[str2_length]!='\0';str2_length++);
    for(i=str2_length,j=0;str1[j]!='\0' && (str2[i]=str1[j]);i++,j++);
    str2[i] = '\0'; // Null-terminate the concatenated string 

    printf("Concatenated string: %s\n", str2);
}