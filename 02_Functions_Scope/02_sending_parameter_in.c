#include<stdio.h>
void introduce(char *name, int age);
int main(){
    introduce("Praveen", 26);
    introduce("Akhil", 27);
    return 0;
}

void introduce(char *name, int age){
    printf("Hi, I am %s, my age is %d\n", name, age);
}