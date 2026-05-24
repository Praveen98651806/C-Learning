#include<stdio.h>
int main(){
    int a = 10,i;
    int result = ~a;

    printf (" The given value is a = %d\n", a);
    printf("The result of ~a is %d\n", result);

    printf("printing binaries of a =");
    for(i = 31; i>=0; i--){
        printf("%d ", (a>> i) & 1);
    }
    printf("\n");
    printf("printing binaries of result =");
    for(i = 31; i>=0; i--){
        printf("%d ", (result>> i) & 1);
    }
    printf("\n");
    return 0;
}