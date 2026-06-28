#include<stdio.h>
int main(){
    char main_str[100], sub_str[100];
    int i,j,main_str_length,sub_str_length,found;
    printf("Enter the main string: ");  
    scanf("%[^\n]", main_str);
    printf("Enter the substring to search: ");
    scanf(" %[^\n]", sub_str);
    for(main_str_length=0;main_str[main_str_length]!='\0';main_str_length++);
    for(sub_str_length=0;sub_str[sub_str_length]!='\0';sub_str_length++);
    found = 0;
    for(i=0;i<main_str_length;i++){
        if(main_str[i] == sub_str[0]){
            for(j=0;sub_str[j] !='\0';j++){
                if(main_str[i+j]!=sub_str[j]){
                    break;
                }
            }
            if(sub_str[j]=='\0'){
                found = 1;
                break;
            }   
        }
    }
    if(found){
        printf("The substring '%s' is found in the main string '%s'.\n", sub_str, main_str);
    } else {
        printf("The substring '%s' is not found in the main string '%s'.\n", sub_str, main_str);
    }
}
